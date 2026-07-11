#include "common/aglResShaderArchive.h"
#include <prim/seadEndian.h>
#include "common/aglResBinaryShaderArchive.h"
#include "common/aglResShaderBinary.h"
#include "common/aglResShaderSymbol.h"
#include "common/aglResShaderVariation.h"
#include "common/aglShader.h"
#include "driver/aglNVNMgr.h"
#include <nvn/nvn_FuncPtrInline.h>

#ifdef cafe
#include <cafe/gx2.h>
#endif  // cafe

static inline void swap32(void* ptr, size_t size) {
    u32* ptr_u32 = (u32*)(ptr);
    u32 count = size / sizeof(u32);

    for (u32 i = 0; i < count; i++) {
        *ptr_u32 = sead::Endian::swapU32(*ptr_u32);
        ptr_u32++;
    }
}

namespace {

void modifyEndianResSymbolArray(bool is_le, agl::ResShaderSymbolArray symbol_array,
                                agl::ShaderSymbolType type) {
    symbol_array.modifyEndianArray(is_le);

    if (type != agl::cShaderSymbolType_UniformBlock)
        for (agl::ResShaderSymbolArray::iterator it = symbol_array.begin(),
                                                 it_end = symbol_array.end();
             it != it_end; ++it)
            agl::ModifyEndianU32(is_le, agl::ResShaderSymbol(&(*it)).getDefaultValue(),
                                 it->mDefaultValueSize);
}

#ifdef cafe

template <typename T>
T* modifyBinaryAndNamePtr(void* base_ptr, T* ptr, s32 num) {
    if (!ptr)
        return nullptr;

    ptr = (T*)(uintptr_t(base_ptr) + uintptr_t(ptr));

    for (s32 i = 0; i < num; i++)
        ptr[i].name += uintptr_t(base_ptr);

    return ptr;
}

void* modifyBinaryPtr(void* base_ptr, void* ptr) {
    return (void*)(uintptr_t(base_ptr) + uintptr_t(ptr));
}

#endif  // cafe

struct ResBinaryShaderSymbolData {
    s32 mSize;
    u32 mUnknown04;
    u32 mNameLen;
};

struct ResBinaryShaderDefaultValueData {
    s32 mSize;
    u32 mUnknown04;
    u32 mUnknown08;
};

using ResBinaryShaderSymbolArrayData = agl::ResArrayData<ResBinaryShaderSymbolData>;
using ResBinaryShaderDefaultValueArrayData =
    agl::ResArrayData<ResBinaryShaderDefaultValueData>;

void modifyEndianResBinarySymbolArray(ResBinaryShaderSymbolArrayData* symbol_array) {
    agl::ModifyEndianU32(false, symbol_array, sizeof(*symbol_array));

    ResBinaryShaderSymbolData* symbol = (ResBinaryShaderSymbolData*)(symbol_array + 1);
    for (u32 num = symbol_array->mNum; num != 0; --num) {
        agl::ModifyEndianU32(false, symbol, sizeof(*symbol));
        symbol = (ResBinaryShaderSymbolData*)(
            (u8*)(symbol) + symbol->mSize);
    }

    symbol = (ResBinaryShaderSymbolData*)(symbol_array + 1);
    const u32 symbol_num = symbol_array->mNum;
    for (u32 i = 0; i != symbol_num;
         ++i, symbol = (ResBinaryShaderSymbolData*)(
                  (u8*)(symbol) + symbol->mSize)) {
        ResBinaryShaderDefaultValueArrayData* default_array =
            (ResBinaryShaderDefaultValueArrayData*)(
                (u8*)(symbol + 1) + symbol->mNameLen);
        agl::ModifyEndianU32(false, default_array, sizeof(*default_array));

        ResBinaryShaderDefaultValueData* value =
            (ResBinaryShaderDefaultValueData*)(default_array + 1);
        for (u32 num = default_array->mNum; num != 0; --num) {
            agl::ModifyEndianU32(false, value, sizeof(*value));
            value = (ResBinaryShaderDefaultValueData*)(
                (u8*)(value) + value->mSize);
        }

    }
}

void modifyEndianResShaderArchiveSymbolArray(ResBinaryShaderSymbolArrayData* symbol_array) {
    agl::ModifyEndianU32(false, symbol_array, sizeof(*symbol_array));

    ResBinaryShaderSymbolData* symbol = (ResBinaryShaderSymbolData*)(symbol_array + 1);
    for (u32 num = symbol_array->mNum; num != 0; --num) {
        agl::ModifyEndianU32(false, symbol, sizeof(*symbol));
        symbol = (ResBinaryShaderSymbolData*)(
            (u8*)(symbol) + symbol->mSize);
    }

    symbol = (ResBinaryShaderSymbolData*)(symbol_array + 1);
    const u32 symbol_num = symbol_array->mNum;
    for (u32 i = 0; i != symbol_num;
         ++i, symbol = (ResBinaryShaderSymbolData*)(
                  (u8*)(symbol) + symbol->mSize)) {
        ResBinaryShaderDefaultValueArrayData* default_array =
            (ResBinaryShaderDefaultValueArrayData*)(
                (u8*)(symbol + 1) + symbol->mNameLen);
        agl::ModifyEndianU32(false, default_array, sizeof(*default_array));

        ResBinaryShaderDefaultValueData* value =
            (ResBinaryShaderDefaultValueData*)(default_array + 1);
        for (u32 num = default_array->mNum; num != 0; --num) {
            agl::ModifyEndianU32(false, value, sizeof(*value));
            value = (ResBinaryShaderDefaultValueData*)(
                (u8*)(value) + value->mSize);
        }

    }
}

template <typename Entry>
void resolveShaderBinaryArray(agl::ResShaderBinaryPtr<Entry>& relative, s32 count,
                              u8* binary_base, const void* pointer_base) {
    if (!relative.mPtr) {
        relative.mPtr = nullptr;
        return;
    }

    const u8* base = binary_base;
    if (pointer_base)
        base = (const u8*)(pointer_base);

    Entry* entries = (Entry*)(binary_base + relative.mOffset);
    for (s32 i = 0; i < count; ++i)
        entries[i].mValue.mPtr = base + entries[i].mValue.mOffset;

    relative.mPtr = entries;
}

}  // namespace

namespace agl {

void ResShaderBinary::resolvePtr(const void* pointer_base) {
    ResShaderBinaryData* data = ptr();
    u8* binary_base = (u8*)(data + 1);
    ResShaderBinaryNvnData* nvn_data = (ResShaderBinaryNvnData*)(binary_base);

    nvn_data->mData.mPtr = binary_base + nvn_data->mData.mOffset;
    resolveShaderBinaryArray(nvn_data->mEntry16A, nvn_data->mEntry16ANum, binary_base,
                             pointer_base);
    resolveShaderBinaryArray(nvn_data->mEntry16B, nvn_data->mEntry16BNum, binary_base,
                             pointer_base);
    resolveShaderBinaryArray(nvn_data->mEntry12A, nvn_data->mEntry12ANum, binary_base,
                             pointer_base);
    resolveShaderBinaryArray(nvn_data->mEntry12B, nvn_data->mEntry12BNum, binary_base,
                             pointer_base);
    resolveShaderBinaryArray(nvn_data->mEntry12C, nvn_data->mEntry12CNum, binary_base,
                             pointer_base);

    ResShaderBinaryPtr<ResShaderBinaryPtrEntry12>& relative = nvn_data->mEntry12D;
    if (!relative.mPtr) {
        relative.mPtr = nullptr;
        return;
    }

    const s32 count = (s32)(nvn_data->mEntry12DNum);
    const u8* base = binary_base;
    if (pointer_base)
        base = (const u8*)(pointer_base);

    ResShaderBinaryPtrEntry12* entries =
        (ResShaderBinaryPtrEntry12*)(binary_base + relative.mOffset);
    for (s32 i = 0; i < count; ++i)
        entries[i].mValue.mPtr = base + entries[i].mValue.mOffset;

    relative.mPtr = entries;
}

void ResShaderBinary::modifyBinaryEndian() {
    size_t size = 0;
    void* data = nullptr;

#ifdef cafe
    switch (getShaderType()) {
    case cShaderType_Vertex: {
        GX2VertexShader* vertex_shader = (GX2VertexShader*)(getData());
        swap32(vertex_shader, sizeof(GX2VertexShader));

        size += vertex_shader->numUniformBlocks * sizeof(GX2UniformBlock) +
                vertex_shader->numUniforms * sizeof(GX2UniformVar) +
                vertex_shader->numInitialValues * sizeof(GX2UniformInitialValue) +
                vertex_shader->numSamplers * sizeof(GX2SamplerVar) +
                vertex_shader->numAttribs * sizeof(GX2AttribVar);

        data = vertex_shader + 1;
    } break;
    case cShaderType_Fragment: {
        GX2PixelShader* pixel_shader = (GX2PixelShader*)(getData());
        swap32(pixel_shader, sizeof(GX2PixelShader));

        size += pixel_shader->numUniformBlocks * sizeof(GX2UniformBlock) +
                pixel_shader->numUniforms * sizeof(GX2UniformVar) +
                pixel_shader->numInitialValues * sizeof(GX2UniformInitialValue) +
                pixel_shader->numSamplers * sizeof(GX2SamplerVar);

        data = pixel_shader + 1;
    } break;
    case cShaderType_Geometry: {
        GX2GeometryShader* geometry_shader = (GX2GeometryShader*)(getData());
        swap32(geometry_shader, sizeof(GX2GeometryShader));

        size += geometry_shader->numUniformBlocks * sizeof(GX2UniformBlock) +
                geometry_shader->numUniforms * sizeof(GX2UniformVar) +
                geometry_shader->numInitialValues * sizeof(GX2UniformInitialValue) +
                geometry_shader->numSamplers * sizeof(GX2SamplerVar);

        data = geometry_shader + 1;
    } break;
    }
#endif  // cafe

    swap32(data, size);
}

// unknown state, does not exist in SMO
void ResShaderBinary::setUp() {
#ifdef cafe
    switch (getShaderType()) {
    case cShaderType_Vertex: {
        GX2VertexShader* vertex_shader = (GX2VertexShader*)(getData());

        vertex_shader->uniformBlocks = modifyBinaryAndNamePtr<GX2UniformBlock>(
            vertex_shader, vertex_shader->uniformBlocks, vertex_shader->numUniformBlocks);
        vertex_shader->uniformVars = modifyBinaryAndNamePtr<GX2UniformVar>(
            vertex_shader, vertex_shader->uniformVars, vertex_shader->numUniforms);
        vertex_shader->samplerVars = modifyBinaryAndNamePtr<GX2SamplerVar>(
            vertex_shader, vertex_shader->samplerVars, vertex_shader->numSamplers);
        vertex_shader->attribVars = modifyBinaryAndNamePtr<GX2AttribVar>(
            vertex_shader, vertex_shader->attribVars, vertex_shader->numAttribs);

        vertex_shader->_loopVars = modifyBinaryPtr(vertex_shader, vertex_shader->_loopVars);
        vertex_shader->shaderPtr = modifyBinaryPtr(vertex_shader, vertex_shader->shaderPtr);
    } break;
    case cShaderType_Fragment: {
        GX2PixelShader* pixel_shader = (GX2PixelShader*)(getData());

        pixel_shader->uniformBlocks = modifyBinaryAndNamePtr<GX2UniformBlock>(
            pixel_shader, pixel_shader->uniformBlocks, pixel_shader->numUniformBlocks);
        pixel_shader->uniformVars = modifyBinaryAndNamePtr<GX2UniformVar>(
            pixel_shader, pixel_shader->uniformVars, pixel_shader->numUniforms);
        pixel_shader->samplerVars = modifyBinaryAndNamePtr<GX2SamplerVar>(
            pixel_shader, pixel_shader->samplerVars, pixel_shader->numSamplers);

        pixel_shader->_loopVars = modifyBinaryPtr(pixel_shader, pixel_shader->_loopVars);
        pixel_shader->shaderPtr = modifyBinaryPtr(pixel_shader, pixel_shader->shaderPtr);
    } break;
    case cShaderType_Geometry: {
        GX2GeometryShader* geometry_shader = (GX2GeometryShader*)(getData());

        geometry_shader->uniformBlocks = modifyBinaryAndNamePtr<GX2UniformBlock>(
            geometry_shader, geometry_shader->uniformBlocks, geometry_shader->numUniformBlocks);
        geometry_shader->uniformVars = modifyBinaryAndNamePtr<GX2UniformVar>(
            geometry_shader, geometry_shader->uniformVars, geometry_shader->numUniforms);
        geometry_shader->samplerVars = modifyBinaryAndNamePtr<GX2SamplerVar>(
            geometry_shader, geometry_shader->samplerVars, geometry_shader->numSamplers);

        geometry_shader->_loopVars = modifyBinaryPtr(geometry_shader, geometry_shader->_loopVars);
        geometry_shader->shaderPtr = modifyBinaryPtr(geometry_shader, geometry_shader->shaderPtr);
        geometry_shader->copyShaderPtr =
            modifyBinaryPtr(geometry_shader, geometry_shader->copyShaderPtr);
    } break;
    }
#endif  // cafe
}

const char* ResShaderVariation::getID() const {
    const char* value = getName() + ref().mNameLen;

    for (s32 i = 0, index = (s32)(ref().mValueNum);; i++) {
        while (*value == '\0')
            value++;

        if (i == index)
            break;

        while (*value != '\0')
            value++;
    }

    return value;
}

const char* ResShaderVariation::getValue(s32 index) const {
    // clang-format off
    SEAD_ASSERT(0 <= index && index < (int)( ref().mValueNum ));
    // clang-format on

    const char* value = getName() + ref().mNameLen;

    for (s32 i = 0;; i++) {
        while (*value == '\0')
            value++;

        if (i == index)
            break;

        while (*value != '\0')
            value++;
    }

    return value;
}

// unknown state, does not exist in SMO
ResShaderSymbol ResShaderSymbolArray::searchResShaderSymbolByID(const sead::SafeString& id) const {
    for (constIterator it = begin(), it_end = end(); it != it_end; ++it) {
        if (id.isEqual(ResShaderSymbol(&(*it)).getID()))
            return &(*it);
    }

    return nullptr;
}

ResShaderMacroArray ResShaderProgram::getResShaderMacroArray(ShaderType type) const {
    const DataType* const data = ptr();
    const char* address = (const char*)(data + 1) + data->mNameLen;
    for (s32 i = 0; i < type; ++i)
        address += *(const s32*)(address);
    return (const ResShaderMacroArrayData*)(address);
}

ResShaderVariationArray ResShaderProgram::getResShaderVariationArray() const {
    const DataType* const data = ptr();
    uintptr_t address = (uintptr_t)(data + 1) + data->mNameLen;
    address += *(const s32*)(address);
    address += *(const s32*)(address);
    address += *(const s32*)(address);
    address += *(const s32*)(address);
    return (const ResShaderVariationArrayData*)(address);
}

// unknown state, does not exist in SMO
ResShaderSymbolArray ResShaderProgram::getResShaderSymbolArray(ShaderSymbolType type) const {
    const ResShaderSymbolArrayData* symbol_array;
    {
        const ResShaderVariationArrayData* const data = getResShaderVariationDefaultArray().ptr();
        symbol_array = (const ResShaderSymbolArrayData*)((uintptr_t)data + data->mSize);
    }

    for (s32 i = 0; i < type; i++)
        symbol_array =
            (const ResShaderSymbolArrayData*)((uintptr_t)symbol_array + symbol_array->mSize);

    return symbol_array;
}

// unknown state, does not exist in SMO
ResShaderSymbolArray ResBinaryShaderProgram::getResShaderSymbolArray(ShaderSymbolType type) const {
    const ResShaderSymbolArrayData* symbol_array;
    {
        const ResShaderVariationArrayData* const data = getResShaderVariationDefaultArray().ptr();
        symbol_array = (const ResShaderSymbolArrayData*)((uintptr_t)data + data->mSize);
    }

    for (s32 i = 0; i < type; i++)
        symbol_array =
            (const ResShaderSymbolArrayData*)((uintptr_t)symbol_array + symbol_array->mSize);

    return symbol_array;
}

bool ResShaderArchive::setUp() {
#ifdef cafe
    SEAD_ASSERT(isValid());
#endif

    if ((ref().mEndian & 1) != 0)
        return true;

    ModifyEndianU32(false, ptr(), sizeof(DataType));

    ResShaderProgramArray program_array = getResShaderProgramArray();
    program_array.modifyEndianArray(false);

    getResShaderSourceArray().modifyEndianArray(false);

    for (ResShaderProgramArray::iterator it = program_array.begin(), it_end = program_array.end();
         it != it_end; ++it) {
        ResShaderProgram program(&(*it));

        program.getResShaderMacroArray(cShaderType_Vertex).modifyEndianArray(false);
        program.getResShaderMacroArray(cShaderType_Fragment).modifyEndianArray(false);
        {
            const ResShaderProgramData* data = program.ptr();
            const u8* address = (const u8*)(data + 1) + data->mNameLen;
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            ResShaderMacroArray(address).modifyEndianArray(false);
        }
        {
            const ResShaderProgramData* data = program.ptr();
            const u8* address = (const u8*)(data + 1) + data->mNameLen;
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            ResShaderMacroArray(address).modifyEndianArray(false);
        }
        {
            const ResShaderProgramData* data = program.ptr();
            const u8* address = (const u8*)(data + 1);
            address += data->mNameLen;
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            ResShaderVariationArray(address).modifyEndianArray(false);
        }
        {
            const ResShaderProgramData* data = program.ptr();
            const u8* address = (const u8*)(data + 1);
            address += data->mNameLen;
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            ResShaderVariationArray(address).modifyEndianArray(false);
        }
        {
            const ResShaderProgramData* data = program.ptr();
            const u8* address = (const u8*)(data + 1);
            address += data->mNameLen;
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            address += *(const s32*)(address);
            modifyEndianResShaderArchiveSymbolArray(
                (ResBinaryShaderSymbolArrayData*)address);
        }
    }

    ResShaderSourceArray source_array = getResShaderSourceArray();
    ResShaderSourceArray final_source_array((u8*)(source_array.ptr()) +
                                            source_array.ref().mSize);
    final_source_array.modifyEndianArray(false);

    ref().mEndian |= 1;
    return true;
}

void ResBinaryShaderArchive::createMemoryPoolBuffer_() {
    u8* storage = (u8*)((uintptr_t)ref().mMemoryPoolOffset + (uintptr_t)ptrBytes());
    driver::NVNMgr* nvn_mgr = driver::NVNMgr::instance();
    NVNmemoryPool* pool = &ref().mMemoryPool;
    NVNdevice* device = nvn_mgr->getDevice();

    NVNmemoryPoolBuilder pool_builder;
    nvnMemoryPoolBuilderSetDefaults(&pool_builder);
    nvnMemoryPoolBuilderSetDevice(&pool_builder, device);
    nvnMemoryPoolBuilderSetFlags(&pool_builder, 0x62);
    nvnMemoryPoolBuilderSetStorage(
        &pool_builder, storage,
        ((size_t)ref().mMemoryPoolSize + 0xFFF) & ~(size_t)0xFFF);
    nvnMemoryPoolInitialize(pool, &pool_builder);

    NVNbufferBuilder buffer_builder;
    nvnBufferBuilderSetDevice(&buffer_builder, device);
    nvnBufferBuilderSetDefaults(&buffer_builder);
    nvnBufferBuilderSetStorage(
        &buffer_builder, pool, 0,
        ((size_t)ref().mMemoryPoolSize + 0xFFF) & ~(size_t)0xFFF);
    nvnBufferInitialize(&ref().mBuffer, &buffer_builder);
}

// NON_MATCHING: Retail extracts the pointer-base flag with UBFX; LLVM emits an equivalent AND.
// Next hypothesis: recover the original flag accessor that returns a normalized bit.
bool ResBinaryShaderArchive::setUp(bool le_resolve_pointers) {
    SEAD_ASSERT(isValid());

    const u32 endian_resolved = ref().mEndian & sead::Endian::getHostEndian();
    if (!endian_resolved)
        ModifyEndianU32(false, ptr(), sizeof(DataType));

    createMemoryPoolBuffer_();

    const u32 flags = ref().mEndian;
    ResShaderBinaryArray binary_arr = getResShaderBinaryArray();
    if (endian_resolved) {
        if ((flags & 2) != 0)
            return true;

        const u32 binary_num = binary_arr.ref().mNum;
        if (binary_num != 0) {
            if ((flags & 4) != 0) {
                for (ResShaderBinaryArray::iterator it = binary_arr.begin(), it_end = binary_arr.end();
                     it != it_end; ++it) {
                    ResShaderBinary binary(&(*it));
                    binary.resolvePtr(ptrBytes() + sizeof(DataType));
                }
            } else {
                for (ResShaderBinaryArray::iterator it = binary_arr.begin(), it_end = binary_arr.end();
                     it != it_end; ++it) {
                    ResShaderBinary binary(&(*it));
                    binary.resolvePtr(nullptr);
                }
            }
        }

        ref().mEndian |= 2;
        return true;
    }

    binary_arr.modifyEndianArray(false);

    ResBinaryShaderProgramArray binary_prog_arr = getResBinaryShaderProgramArray();
    binary_prog_arr.modifyEndianArray(false);

    ResBinaryShaderProgramData* binary_prog_data =
        (ResBinaryShaderProgramData*)(binary_prog_arr.ptr() + 1);
    const u32 binary_prog_num = binary_prog_arr.ref().mNum;
    for (u32 i = 0; i != binary_prog_num;
         ++i, binary_prog_data =
                  (ResBinaryShaderProgramData*)((u8*)binary_prog_data + binary_prog_data->mSize)) {
        ResBinaryShaderProgram binary_prog(binary_prog_data);

        binary_prog.getResShaderVariationArray().modifyEndianArray(false);
        ResShaderVariationArray variation_default_arr =
            binary_prog.getResShaderVariationDefaultArray();
        variation_default_arr.modifyEndianArray(false);

        const u8* variation_data = (const u8*)variation_default_arr.ptr();
        const u8* symbol_address = &variation_data[variation_default_arr.ref().mSize];
        ResBinaryShaderSymbolArrayData* symbol_array =
            (ResBinaryShaderSymbolArrayData*)symbol_address;
        modifyEndianResBinarySymbolArray(symbol_array);
    }

    ResShaderBinaryArray::iterator it = binary_arr.begin();
    ResShaderBinaryArray::iterator it_end = binary_arr.end();
    const u32 pointer_base = (flags >> 2) & 1;
    const bool pointers_resolved = ((flags >> 1) & 1) != 0;
    for (; it != it_end; ++it) {
        ResShaderBinary binary(&(*it));
        binary.modifyBinaryEndian();

        if (le_resolve_pointers) {
            if (!pointers_resolved) {
                if (pointer_base)
                    binary.resolvePtr(ptrBytes() + sizeof(DataType));
                else
                    binary.resolvePtr(nullptr);
            }
        }
    }

    if (le_resolve_pointers) {
        if (!pointers_resolved)
            ref().mEndian |= 2;
    }

    ref().mEndian |= 1;
    return true;
}

const char* ResShaderArchiveData::getExtension() {
    return "sharc";
}

const char* ResBinaryShaderArchiveData::getExtension() {
    return "sharcfb";
}

}  // namespace agl
