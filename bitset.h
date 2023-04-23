#pragma once
#ifndef bitset
#define bitset

#include<iosfwd>
#include<stdint.h>
#include<vector>

class Bitset{
    public:
        class BitHolder{
            public:
                BitHolder(uint32_t& e, const int p);
                friend class Bitset;
                BitHolder& operator=(const bool rhs);
                ~BitHolder() = default;
                operator bool() const;

            private:
                uint32_t& eData_;
                int position_;
            };
    Bitset(const int64_t size = 0, const bool filler = false);
    Bitset(const Bitset& copy) = default;
    Bitset& operator=(const Bitset& rhs);
    Bitset& operator&=(const Bitset& rhs);              // логическое и
    Bitset& operator|=(const Bitset& rhs);              // логическое или
    Bitset& operator^=(const Bitset& rhs);          // ксор
    Bitset& operator<<=(const int64_t rhs);         // сдвиг влево на скока та
    Bitset& operator>>=(const int64_t rhs);         // сдвиг вправа на скока та (если отриц двигаем в другую сторону) для всех ретурн мохнатую точку и зыс
    ~Bitset() = default;
    bool operator==(Bitset& rhs);           //  оператор сравнения
    bool operator!=(Bitset& rhs);           // оператор неравно
    Bitset operator~() const;                           //  инверсия битов

    Bitset operator&(const Bitset& rhs) const;
    Bitset operator|(const Bitset& rhs) const;          
    Bitset operator^(const Bitset& rhs) const;
    Bitset operator<<(const int64_t rhs) const;
    Bitset operator>>(const int64_t rhs) const;
    BitHolder operator[](const int64_t position);       // обращение к итому элементу(возвращает битхолдер с нужным значением)

    int64_t size() const {return size_;};
    void resize(const int64_t size, const bool filler = false);     // ресайзим дата заново заполняем филер

    private:
    std::vector<uint32_t> data_ {0};
    int64_t size_ = 0;
};

std::istream& operator>>(std::istream& istream, Bitset& data);
std::ostream& operator<<(std::ostream& ostream, Bitset& data);

#endif

