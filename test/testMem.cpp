#include "gtest/gtest.h"
#include "./mem.h"

TEST(MemcpySTest, BasicCopy) {
    char src[] = "Hello, world!";
    char dest[20];
    memcpy_s(dest, sizeof(dest), src, sizeof(src), strlen(src) + 1);
    EXPECT_STREQ(dest, src);
}

TEST(MemcpySTest, NullDestination) {
    char src[] = "Test";
    EXPECT_DEATH(memcpy_s(nullptr, 10, src, sizeof(src), 4), "");
}

TEST(MemcpySTest, NullSource) {
    char dest[10];
    EXPECT_DEATH(memcpy_s(dest, sizeof(dest), nullptr, 5, 3), "");
}

TEST(MemcpySTest, OverlappingMemory) {
    char data[] = "Overlap";
    EXPECT_DEATH(memcpy_s(data + 2, 5, data, 7, 4), "");
}

TEST(MemcpySTest, InsufficientDestinationSize) {
    char src[] = "Too long";
    char dest[5];
    EXPECT_DEATH(memcpy_s(dest, sizeof(dest), src, sizeof(src), 6), "");
}

TEST(MemcpySTest, InsufficientSourceSize) {
    char src[] = "Short";
    char dest[10];
    EXPECT_DEATH(memcpy_s(dest, sizeof(dest), src, 3, 4), "");
}

TEST(MemfillTest, BasicFill) {
    uint8_t buffer[10];
    memfill(buffer, 0x5A, sizeof(buffer));
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(buffer[i], 0x5A);
    }
}

TEST(MemfillTest, NullDestination) {
    EXPECT_DEATH(memfill(nullptr, 0xFF, 5), "");
}

TEST(MemfillTest, InvalidValue) {
    uint8_t buffer[5];
    EXPECT_DEATH(memfill(buffer, -1, sizeof(buffer)), "");
    EXPECT_DEATH(memfill(buffer, 256, sizeof(buffer)), "");
}

TEST(MemcmpSTest, EqualBuffers) {
    char buf1[] = "Equal";
    char buf2[] = "Equal";
    EXPECT_TRUE(memcmp_s(buf1, sizeof(buf1), buf2, sizeof(buf2), 5));
}

TEST(MemcmpSTest, UnequalBuffers) {
    char buf1[] = "Hello";
    char buf2[] = "World";
    EXPECT_FALSE(memcmp_s(buf1, sizeof(buf1), buf2, sizeof(buf2), 5));
}

TEST(MemcmpSTest, NullBuffer1) {
    char buf2[] = "Test";
    EXPECT_DEATH(memcmp_s(nullptr, 5, buf2, sizeof(buf2), 4), "");
}

TEST(MemcmpSTest, NullBuffer2) {
    char buf1[] = "Test";
    EXPECT_DEATH(memcmp_s(buf1, sizeof(buf1), nullptr, 5, 4), "");
}

TEST(MemcmpSTest, SameBuffer) {
    char data[] = "Same";
    EXPECT_DEATH(memcmp_s(data, sizeof(data), data, sizeof(data), 4), "");
}

TEST(MemcmpSTest, InsufficientSize1) {
    char buf1[] = "Short";
    char buf2[] = "Longer";
    EXPECT_DEATH(memcmp_s(buf1, 3, buf2, sizeof(buf2), 4), "");
}

TEST(MemcmpSTest, InsufficientSize2) {
    char buf1[] = "Longer";
    char buf2[] = "Short";
    EXPECT_DEATH(memcmp_s(buf1, sizeof(buf1), buf2, 3, 4), "");
}

TEST(StrncpySTest, BasicCopy) {
    char src[] = "Hello, world!";
    char dest[20] = { 0 };
    strncpy_s(dest, sizeof(dest), src, sizeof(src), strlen(src));
    EXPECT_STREQ(dest, "Hello, world!");
}

TEST(StrncpySTest, NullDestination) {
    char src[] = "Test";
    EXPECT_DEATH(strncpy_s(nullptr, 10, src, sizeof(src), 4), "");
}

TEST(StrncpySTest, NullSource) {
    char dest[10];
    EXPECT_DEATH(strncpy_s(dest, sizeof(dest), nullptr, 5, 3), "");
}

TEST(StrncpySTest, OverlappingMemory) {
    char data[] = "Overlap";
    EXPECT_DEATH(strncpy_s(data + 2, 5, data, 7, 4), "");
}

TEST(StrncpySTest, InsufficientDestinationSize) {
    char src[] = "Too long";
    char dest[5];
    EXPECT_DEATH(strncpy_s(dest, sizeof(dest), src, sizeof(src), 6), "");
}

TEST(StrncpySTest, InsufficientSourceSize) {
    char src[] = "Short";
    char dest[10];
    strncpy_s(dest, sizeof(dest), src, 3, 4);
    EXPECT_STREQ(dest, "Sho");
}

TEST(StrcpySTest, BasicCopy) {
    char src[] = "Hello";
    char dest[10];
    strcpy_s(dest, sizeof(dest), src, sizeof(src));
    EXPECT_STREQ(dest, "Hello");
}

TEST(StrcpySTest, NullDestination) {
    char src[] = "Test";
    EXPECT_DEATH(strcpy_s(nullptr, 10, src, sizeof(src)), "");
}

TEST(StrcpySTest, NullSource) {
    char dest[10];
    EXPECT_DEATH(strcpy_s(dest, sizeof(dest), nullptr, 5), "");
}

TEST(StrcpySTest, OverlappingMemory) {
    char data[] = "Overlap";
    EXPECT_DEATH(strcpy_s(data + 2, 5, data, 7), "");
}

TEST(StrcpySTest, InsufficientDestinationSize) {
    char src[] = "Too long";
    char dest[5];
    EXPECT_DEATH(strcpy_s(dest, sizeof(dest), src, sizeof(src)), "");
}

TEST(StrncatSTest, BasicConcatenation) {
    char dest[20] = "Hello, ";
    char src[] = "world!";
    strncat_s(dest, sizeof(dest), src, sizeof(src));
    EXPECT_STREQ(dest, "Hello, world!");
}

TEST(StrncatSTest, NullDestination) {
    char src[] = "Test";
    EXPECT_DEATH(strncat_s(nullptr, 10, src, sizeof(src)), "");
}

TEST(StrncatSTest, NullSource) {
    char dest[10] = "Hello";
    EXPECT_DEATH(strncat_s(dest, sizeof(dest), nullptr, 5), "");
}

TEST(StrncatSTest, OverlappingMemory) {
    char data[] = "Overlap";
    EXPECT_DEATH(strncat_s(data, 7, data + 2, 5), "");
}

TEST(StrncatSTest, InsufficientDestinationSize) {
    char dest[10] = "Too long ";
    char src[] = "already";
    EXPECT_DEATH(strncat_s(dest, sizeof(dest), src, sizeof(src)), "");
}

TEST(findFirstNotTest, BasicFind) {
    uint8_t data[] = {0, 0, 1, 0, 2};
    int len = 5;
    int targetValue = 0;
    int result = findFirstNot(data, len, targetValue);
    EXPECT_EQ(result, 2);
}

TEST(findFirstNotTest, NullData) {
    EXPECT_DEATH(findFirstNot(nullptr, 5, 0), "");
}

TEST(findFirstNotTest, NotFound) {
    uint8_t data[] = {0, 0, 0};
    int len = 3;
    int targetValue = 0;
    int result = findFirstNot(data, len, targetValue);
    EXPECT_EQ(result, -1);
}
