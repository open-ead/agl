#include "utility/aglResParameter.h"
#include <cstring>
#include <basis/seadNew.h>
#include <basis/seadRawPrint.h>
#include <heap/seadHeap.h>
#include <math/seadVector.h>
#include <prim/seadPtrUtil.h>
#include <prim/seadStringUtil.h>
#include "detail/aglPrivateResource.h"
#include "utility/aglParameter.h"

namespace agl::utl {

size_t ResParameter::getDataSize() const {
    switch (ParameterType(ptr()->getType())) {
    case ParameterType::Bool:
    case ParameterType::F32:
    case ParameterType::Int:
    case ParameterType::U32:
        return 4;
    case ParameterType::Vec2:
        return sizeof(sead::Vector2f);
    case ParameterType::Vec3:
        return sizeof(sead::Vector3f);
    case ParameterType::Vec4:
    case ParameterType::Color:
    case ParameterType::Quat:
        return sizeof(sead::Vector4f);
    case ParameterType::String32:
    case ParameterType::String64:
    case ParameterType::String256:
    case ParameterType::StringRef:
        return sead::SafeString(getData<char>()).calcLength() + 1;
    case ParameterType::Curve1:
        return 1 * 0x80;
    case ParameterType::Curve2:
        return 2 * 0x80;
    case ParameterType::Curve3:
        return 3 * 0x80;
    case ParameterType::Curve4:
        return 4 * 0x80;
    case ParameterType::BufferInt:
    case ParameterType::BufferF32:
    case ParameterType::BufferU32:
        return 4 * getBufferSize();
    case ParameterType::BufferBinary:
        return getBufferSize();
    default:
        SEAD_ASSERT_MSG(false, "illigal type:%d", ptr()->getType());
        return 0;
    }
}

s32 ResParameterObj::searchIndex(u32 param_hash) const {
    for (s32 i = 0; i < getNum(); ++i) {
        if (getResParameter(i).getParameterNameHash() == param_hash)
            return i;
    }
    return -1;
}

s32 ResParameterList::searchListIndex(u32 list_hash) const {
    for (s32 i = 0; i < getResParameterListNum(); ++i) {
        if (getResParameterList(i).getParameterListNameHash() == list_hash)
            return i;
    }
    return -1;
}

s32 ResParameterList::searchObjIndex(u32 obj_hash) const {
    for (s32 i = 0; i < getResParameterObjNum(); ++i) {
        if (getResParameterObj(i).getParameterObjNameHash() == obj_hash)
            return i;
    }
    return -1;
}

ResParameterArchive::ResParameterArchive(const void* p_data) {
    mpData = (ResParameterArchiveData*)p_data;
    if (!mpData)
        return;

    const u32 initial_flags = mpData->flags.getDirect();
    const bool little_endian = (initial_flags & u32(ResParameterArchiveFlag::LittleEndian)) != 0;
    bool utf8;
    if (little_endian) {
        if ((initial_flags & u32(ResParameterArchiveFlag::Utf8)) != 0)
            return;
        utf8 = false;
    } else {
        ModifyEndianU32(false, (ResParameterArchiveData*)mpData, sizeof(ResParameterArchiveData));
        utf8 = mpData->flags.isOn(ResParameterArchiveFlag::Utf8);
    }

    const size_t list_size = sizeof(ResParameterListData) * mpData->num_lists;
    u8* const parameter_io = ptrBytes() + sizeof(ResParameterArchiveData) + mpData->offset_to_pio;
    char* string = (char*)(parameter_io + list_size);
    const size_t object_size = sizeof(ResParameterObjData) * mpData->num_objects;
    string += object_size;
    const size_t parameter_size = sizeof(ResParameterData) * mpData->num_parameters;
    string += parameter_size;
    string += mpData->data_section_size;
    char* const string_end = string + mpData->string_section_size;

    if (!little_endian) {
        const size_t parameter_io_size =
            list_size + object_size + parameter_size + mpData->data_section_size;
        if (parameter_io_size != 0)
            ModifyEndianU32(false, parameter_io, parameter_io_size);

        const u32 unknown_size = mpData->unk_section_size;
        for (u32 offset = 0; offset < unknown_size; offset += *(u32*)(string_end + offset)) {
            ModifyEndianU32(false, string_end + offset, sizeof(u32));
        }

        ((ResParameterArchiveData*)mpData)->flags.set(ResParameterArchiveFlag::LittleEndian);
    }

    if (!utf8 && mpData->string_section_size != 0) {
        while (string < string_end) {
            const s32 source_length = sead::SafeString(string).calcLength();
            if (source_length > 0) {
                const s32 source_capacity = source_length + 1;
                sead::Heap* const heap = detail::PrivateResource::instance()->getWorkHeap();
                char16* const utf16 = new (heap, 8) char16[source_capacity];
                const s32 converted_capacity = 2 * source_capacity;
                char* const converted = new (heap, 8) char[converted_capacity];

                sead::StringUtil::convertSjisToUtf16(utf16, source_capacity, string, -1);
                sead::StringUtil::convertUtf16ToUtf8(converted, converted_capacity, utf16, -1);

                const s32 converted_length = sead::SafeString(converted).calcLength();
                const s32 copy_size = sead::Mathi::min(converted_length + 1, source_capacity);
                std::memcpy(string, converted, copy_size);
                heap->free(utf16);
                heap->free(converted);
            }

            string += (source_length + 4) & ~3;
        }

        ((ResParameterArchiveData*)mpData)->flags.set(ResParameterArchiveFlag::Utf8);
    }
}

}  // namespace agl::utl
