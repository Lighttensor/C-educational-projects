//
// Created by ligtht on 5/12/22.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <bitset/bitset.h>
#include <iostream>


TEST_CASE("Bitset::Bitset(size)") {
Bitset b(16);   // Bitset<000000000000000>

for(int i=0; i<16; ++i)
CHECK_FALSE(b[i]);

Bitset b2(1);   // Bitset<0>
for(int i=0; i<1; ++i)
CHECK_FALSE(b2[i]);
}

TEST_CASE("Bitset::Bitset(size, filler)") {
Bitset b(16, false); // Bitset<000000000000000>

for(int i=0; i<16; ++i)
CHECK_FALSE(b[i]);

Bitset b2(16, true); // Bitset<1111111111111111>

for(int i=0; i<16; ++i)
CHECK(b2[i]);
}

TEST_CASE("Bitset::Bitset(copy)") {
Bitset b(16, true); // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

Bitset bc(b);                 // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(bc[i]);
}

TEST_CASE("Bitset::operator=(Bitset))") {
Bitset b(16, true); // Bitset<1111111111111111>

for(int i=0; i<16; ++i)
CHECK(b[i]);

Bitset bc(16);           // Bitset<000000000000000>

for(int i=0; i<16; ++i)
CHECK_FALSE(bc[i]);

bc = b;                      // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(bc[i]);
}

// and Bitset::operator<<(int64_t) because he worked through <<=
TEST_CASE("Bitset::operator<<=(int64_t)") {
Bitset b(16,true);  // Bitset<1111111111111111>

b <<= 2;                      // Bitset<1111111111111100>
for(int i=0; i<14; ++i)
CHECK(b[i]);
CHECK_FALSE(b[14]);
CHECK_FALSE(b[15]);

b <<= 2;                      // Bitset<1111111111110000>

for(int i=0; i<12; ++i)
CHECK(b[i]);

for(int i=12; i<16; ++i)
CHECK_FALSE(b[i]);

}

// and Bitset::operator>>(int64_t) because he worked through >>=
TEST_CASE("Bitset::operator>>=(int64_t)") {
Bitset b(16,true);  // Bitset<1111111111111111>

b >>= 2;                      // Bitset<0011111111111111>

CHECK_FALSE(b[0]);
CHECK_FALSE(b[1]);
for(int i=2; i<16; ++i)
CHECK(b[i]);

b >>= 2;                      // Bitset<0000111111111111>

for(int i=0; i<4; ++i)
CHECK_FALSE(b[i]);

for(int i=4; i<16; ++i)
CHECK(b[i]);

}

// and Bitset::operator&(int64_t) because he worked through &=
TEST_CASE("Bitset::operator&=(Bitset)") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);

b2 <<= 2;                         // Bitset<1111111111111100>
b2 >>= 2;                         // Bitset<0011111111111100>

b &= b2;                          // Bitset<0011111111111100>

for(int i=0; i<16; ++i)
CHECK(b[i] == b2[i]);
}

// and Bitset::operator|(int64_t) because he worked through |=
TEST_CASE("Bitset::operator|=(Bitset)") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);

b2 >>= 6;                         // Bitset<0000001111111111>
b2 <<= 2;                         // Bitset<0000111111111100>

b <<= 6;                          // Bitset<1111111111000000>
b >>= 3;                          // Bitset<0001111111111000>


b |= b2;                          // Bitset<0001111111111000>

for(int i=0; i<3; ++i)
CHECK_FALSE(b[i]);

for(int i=4; i<14; ++i)
CHECK(b[i]);

for(int i=14; i<16; ++i)
CHECK_FALSE(b[i]);
}

// and Bitset::operator^(int64_t) because he worked through ^=
TEST_CASE("Bitset::operator^=(Bitset)") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);

b2 >>= 6;                         // Bitset<0000001111111111>
b2 <<= 2;                         // Bitset<0000111111111100>

b <<= 6;                          // Bitset<1111111111000000>
b >>= 3;                          // Bitset<0001111111111000>


b ^= b2;                          // Bitset<0001000000000100>

for(int i=0; i<3; ++i)
CHECK_FALSE(b[i]);

CHECK(b[3]);

for(int i=4; i<13; ++i)
CHECK_FALSE(b[i]);

CHECK(b[13]);

for(int i=14; i<16; ++i)
CHECK_FALSE(b[i]);
}

TEST_CASE("Bitset::operator~()") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

b <<= 6;                          // Bitset<1111111111000000>

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);

b2 >>= 10;                        // Bitset<0000000000111111>
b = ~b;                           // Bitset<0000000000111111>

for(int i=0; i<16; ++i)
CHECK(b[i] == b2[i]);
}

// i do not want make doctest Bitset::operator[](int64_t)

TEST_CASE("Bitset::operator==()") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

b <<= 6;                          // Bitset<1111111111000000>

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);


b2 >>= 10;                        // Bitset<0000000000111111>
b = ~b;                           // Bitset<0000000000111111>

CHECK((b2 == b));
}

TEST_CASE("Bitset::operator!=()") {
Bitset b(16, true);     // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b[i]);

b <<= 6;                          // Bitset<1111111111000000>

Bitset b2(16, true);    // Bitset<1111111111111111>
for(int i=0; i<16; ++i)
CHECK(b2[i]);


b2 >>= 10;                        // Bitset<0000000000111111>
b = ~b;                           // Bitset<0000000000111111>

CHECK_FALSE((b2 != b));
}

TEST_CASE("Bitset::size()") {
Bitset b(16);               // Bitset<00000000000000000>

CHECK(b.size() == 16);

Bitset b2(12);              // Bitset<000000000000>

CHECK(b2.size() == 12);
}

TEST_CASE("Bitset::BitHolder::operator=(const bool& rhs)") {
Bitset b(16);               // Bitset<00000000000000000>

b[5] = 1;                       // Bitset<00000100000000000>

std::cout << b << std::endl;
}
