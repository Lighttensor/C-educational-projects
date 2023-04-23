#include<stdint.h>
#include<vector>
#include<istream>
#include<ostream>

#include "iostream"
#include"bitset.h"

Bitset::BitHolder::BitHolder(uint32_t& e, const int p)
    : eData_(e), position_(p){}

Bitset::BitHolder& Bitset::BitHolder::operator=(const bool rhs){
    uint32_t hyi = 1;
    hyi <<= position_;

    if (rhs == 1){
        eData_ |= hyi;
    }
    else{
        eData_ &= ~hyi;
    }
    return *(this);
}

Bitset& Bitset::operator=(const Bitset& rhs){
    data_ = rhs.data_;
    size_ = rhs.size_;
}

Bitset::BitHolder::operator bool() const{
    uint32_t hyi = 1;
    hyi <<= position_;
    return ((hyi & eData_) != 0);
}

Bitset::Bitset(const int64_t size, const bool filler){

    if (size < 0)
        throw std::invalid_argument("Bitset error: Bitset size can not be negative");

    int64_t v1 = 0;
    size_ = size;

    data_ = std::vector<uint32_t>(size_ / 32 + 1, (~v1) * filler);
}

Bitset& Bitset::operator&=(const Bitset& rhs){
    for (int64_t i = 0; i < (size_ / 32) + 1; ++i)
        data_[i] &= rhs.data_[i];
    return *(this);
}

Bitset& Bitset::operator|=(const Bitset& rhs){
    for (int64_t i = 0; i < (size_ / 32) + 1; ++i)
        data_[i] |= rhs.data_[i];
    return *(this);
}

Bitset& Bitset::operator^=(const Bitset& rhs){
    for (int64_t i = 0; i < (size_ / 32) + 1; ++i){
        data_[i] ^= rhs.data_[i];
    }
    return *(this);
}

bool Bitset::operator==(Bitset& rhs){
    for(int64_t i=0; i < size_; ++i){
        if ((*this)[i] != rhs[i]){
            return false;
        }
    }
    return true;
}

bool Bitset::operator!=(Bitset& rhs){
    for(int64_t i=0; i < size_; ++i){
        if ((*this)[i] != rhs[i]){
            return true;
        }
    }
    return false;
}


Bitset Bitset::operator~() const{
    Bitset kopia(*this);
    for (int64_t i=0; i < (size_ / 32) + 1; ++i){
        kopia.data_[i] = ~data_[i];
    }
    return kopia;
}

Bitset& Bitset::operator<<=(const int64_t rhs){
    if (rhs < 0){
        return (*this>>=-(rhs));
    }
    for (int64_t j = 0; j < rhs; ++j){
        for (int64_t i = 0; i < size_ - 1; ++i){
            (*this)[i] = (*this)[i + 1].operator bool();
        }
        (*this)[size_ - 1] = 0;
    }
    return *(this);
}

Bitset& Bitset::operator>>=(const int64_t rhs){
    if (rhs < 0)
        throw std::logic_error("Bitset error: b_sizes of operands do not match");

    else if (!rhs)
        return *this;

    else
        for (int64_t j = 0; j < rhs; ++j) {
            for (int64_t i = size_ - 1; i > 0; --i)
                (*this)[i] = (*this)[i - 1].operator bool();
            (*this)[0] = 0;
        }

    return *this;
}

Bitset Bitset::operator&(const Bitset& rhs) const{
    Bitset kopia(*this);
    return (kopia &= rhs);
}

Bitset Bitset::operator|(const Bitset& rhs) const{
    Bitset kopia(*this);
    return (kopia |= rhs);
}

Bitset Bitset::operator^(const Bitset& rhs) const{
    Bitset kopia(*this);
    return (kopia ^= rhs);
}

Bitset Bitset::operator<<(const int64_t rhs) const{
    Bitset kopia(*this);
    return (kopia <<= rhs);
}

Bitset Bitset::operator>>(const int64_t rhs) const{
    Bitset kopia(*this);
    return (kopia >>= rhs);
}

Bitset::BitHolder Bitset::operator[](const int64_t position) {
    if (position == 0)
        return BitHolder(data_[0], 0);

    return BitHolder(data_[(position + (32 - 1)) / 32 - 1], position % 32);
}

void Bitset::resize(const int64_t size, const bool filler) {
    if (size < 0)
        throw std::invalid_argument("Bitset error: Bitset size can not be negative");

    else
        if (size < size_) {
        *this <<= (size_ - size);
        size_ = size;
    }

    else
        if (size > size_) {
        for (int i = 0; i < (size+31) / 32 - (size_ + 31) / 32; ++i)
            data_.push_back(0);

        *this >>= (size - size_);

        for (int i = 0; i < size - size_; ++i)
            (*this)[i] = filler;

        size_ = size;
    }
}

std::istream& operator>>(std::istream& istream, Bitset& data){
    int64_t c = 1;
    int64_t i = 0;
    while(istream.good()){
        if (i % 32 == 0) {
            data.resize(32 * c);
            ++c;
        }
        char a = istream.peek();
        if (a == '1' || a == '0')
            data[i] = istream.get();
        else
            break;
        ++i;
    }
    return istream;
}

std::ostream& operator<<(std::ostream& ostream, Bitset& data){
    for (int64_t i=0; i < data.size(); ++i){
        ostream<<data[i];
    }
    return ostream;
}