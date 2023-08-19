#pragma once

#include <basis/seadRawPrint.h>
#include <prim/seadBitUtil.h>

namespace agl {

// maybe first parameter is is_le, maybe it is big_endian - different between decomps
void ModifyEndianU32(bool is_le, void* p_data, size_t size);

template <typename DataType_>
class ResCommon {
public:
    using DataType = DataType_;

    ResCommon() : mpData(nullptr) {}

    ResCommon(const void* data) : mpData(static_cast<const DataType*>(data)) {}

    bool isValid() const { return mpData != nullptr; }

    void verify() const {
        if (isValidMagic()) {
            const char* b = reinterpret_cast<const char*>(mpData);
            SEAD_ASSERT_MSG(false, "Wrong binary. [%c%c%c%c].", b[0], b[1], b[2], b[3]);
        }

        if (isValidVersion()) {
            SEAD_ASSERT_MSG(false, "Version error.current:%d binary:%d", DataType::getVersion(),
                            sead::BitUtil::bitCastPtr<u32>(ptr(), 4));
        }
    }

    DataType* ptr() {
        assertValid();
        return const_cast<DataType*>(mpData);
    }

    const DataType* ptr() const {
        assertValid();
        return mpData;
    }

    u8* ptrBytes() const { return const_cast<u8*>(reinterpret_cast<const u8*>(mpData)); }

    DataType& ref() {
        assertValid();
        return *ptr();
    }

    const DataType& ref() const {
        assertValid();
        return *ptr();
    }

    bool isValidMagic() const {
        return sead::BitUtil::bitCastPtr<u32>(ptr(), 0) == DataType::getSignature();
    }

    bool isValidVersion() const {
        return sead::BitUtil::bitCastPtr<u32>(ptr(), 4) == DataType::getVersion();
    }

    void assertValid() const { SEAD_ASSERT(isValid()); }

protected:
    const DataType* mpData;
};

#define AGL_RES_FILE_HEADER()                                                                      \
public:                                                                                            \
    bool modifyEndian() const { return ref().mEndian & DataType::cEndianCheckBit; }                \
                                                                                                   \
    bool isEndianResolved() const { return !modifyEndian(); }                                      \
                                                                                                   \
    void setEndianResolved() { ref().mEndian = 1 - ref().mEndian; }

template <typename DataType>
struct ResArrayData {
    s32 mSize;
    u32 mNum;
    // DataType mData[];

    using ElemType = DataType;
};

template <typename Type>
class ResArray : public ResCommon<ResArrayData<typename Type::DataType>> {
public:
    using ElemType = Type;
    using ElemDataType = typename Type::DataType;
    using DataType = typename ResArray<Type>::DataType;
    using Base = ResCommon<DataType>;

    using ResCommon<DataType>::ResCommon;

public:
    class iterator {
    public:
        iterator(s32 index, ElemDataType* elem) : mIndex(index), mElem(elem) {}

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.mIndex == rhs.mIndex;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.mIndex != rhs.mIndex;
        }

        iterator& operator++() {
            ++mIndex;
            mElem = (ElemDataType*)((uintptr_t)mElem + Type(mElem).ref().mSize);
            return *this;
        }

        ElemDataType& operator*() const { return *mElem; }
        ElemDataType* operator->() const { return mElem; }
        s32 getIndex() const { return mIndex; }

    private:
        s32 mIndex;
        ElemDataType* mElem;
    };

    class constIterator {
    public:
        constIterator(s32 index, const ElemDataType* elem) : mIndex(index), mElem(elem) {}

        friend bool operator==(const constIterator& lhs, const constIterator& rhs) {
            return lhs.mIndex == rhs.mIndex;
        }

        friend bool operator!=(const constIterator& lhs, const constIterator& rhs) {
            return lhs.mIndex != rhs.mIndex;
        }

        constIterator& operator++() {
            ++mIndex;
            mElem = (const ElemDataType*)((uintptr_t)mElem + Type(mElem).ref().mSize);
            return *this;
        }

        const ElemDataType& operator*() const { return *mElem; }
        const ElemDataType* operator->() const { return mElem; }
        s32 getIndex() const { return mIndex; }

    private:
        s32 mIndex;
        const ElemDataType* mElem;
    };

public:
    iterator begin() { return iterator(0, (ElemDataType*)(Base::ptr() + 1)); }
    constIterator begin() const { return constIterator(0, (const ElemDataType*)(Base::ptr() + 1)); }
    constIterator constBegin() const {
        return constIterator(0, (const ElemDataType*)(Base::ptr() + 1));
    }

    iterator end() { return iterator(getNum(), nullptr); }
    constIterator end() const { return constIterator(getNum(), nullptr); }
    constIterator constEnd() const { return constIterator(getNum(), nullptr); }

public:
    u32 getNum() const { return Base::ref().mNum; }

    ElemType get(s32 n) const {
        // clang-format off
        SEAD_ASSERT(0 <= n && n <= static_cast< int >( this->getNum() ));
        // clang-format on

        constIterator itr = constBegin();
        constIterator itr_end = constIterator(n, nullptr);

        while (itr != itr_end)
            ++itr;

        return &(*itr);
    }

    void modifyEndianArray(bool is_le) {
        ModifyEndianU32(is_le, Base::ptr(), sizeof(DataType));

        for (iterator it = begin(), it_end = end(); it != it_end; ++it)
            ModifyEndianU32(is_le, &(*it), sizeof(ElemDataType));
    }
};
}  // namespace agl
