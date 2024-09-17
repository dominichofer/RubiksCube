#include "gtest/gtest.h"
#include "rotation.h"
#include <string>

TEST(Rotation, to_string)
{
    EXPECT_EQ(to_string(Rotation::L), "L");
    EXPECT_EQ(to_string(Rotation::L2), "L2");
    EXPECT_EQ(to_string(Rotation::Li), "Li");
    EXPECT_EQ(to_string(Rotation::R), "R");
    EXPECT_EQ(to_string(Rotation::R2), "R2");
    EXPECT_EQ(to_string(Rotation::Ri), "Ri");
    EXPECT_EQ(to_string(Rotation::U), "U");
    EXPECT_EQ(to_string(Rotation::U2), "U2");
    EXPECT_EQ(to_string(Rotation::Ui), "Ui");
    EXPECT_EQ(to_string(Rotation::D), "D");
    EXPECT_EQ(to_string(Rotation::D2), "D2");
    EXPECT_EQ(to_string(Rotation::Di), "Di");
    EXPECT_EQ(to_string(Rotation::F), "F");
    EXPECT_EQ(to_string(Rotation::F2), "F2");
    EXPECT_EQ(to_string(Rotation::Fi), "Fi");
    EXPECT_EQ(to_string(Rotation::B), "B");
    EXPECT_EQ(to_string(Rotation::B2), "B2");
    EXPECT_EQ(to_string(Rotation::Bi), "Bi");
}
