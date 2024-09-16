#include "gtest/gtest.h"
#include "intrin.h"

TEST(popcount, empty)
{
    EXPECT_EQ(popcount(0), 0);
}

TEST(popcount, one)
{
    EXPECT_EQ(popcount(1), 1);
}

TEST(popcount, two)
{
    EXPECT_EQ(popcount(2), 1);
}

TEST(popcount, full)
{
    EXPECT_EQ(popcount(0xFF'FF'FF'FF'FF'FF'FF'FFULL), 64);
}
