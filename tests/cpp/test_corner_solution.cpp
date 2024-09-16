#include "gtest/gtest.h"
#include "corner_solution.h"
#include <cstdint>
#include <vector>

TEST(Corner_solution, solution_distance_0)
{
    Corners c;
    EXPECT_EQ(solution_distance(c), 0);
}

TEST(Corner_solution, solution_distance_1)
{
    Corners c;
    EXPECT_EQ(solution_distance(c.L()), 1);
    EXPECT_EQ(solution_distance(c.L2()), 1);
    EXPECT_EQ(solution_distance(c.Li()), 1);
    EXPECT_EQ(solution_distance(c.R()), 1);
    EXPECT_EQ(solution_distance(c.R2()), 1);
    EXPECT_EQ(solution_distance(c.Ri()), 1);
    EXPECT_EQ(solution_distance(c.U()), 1);
    EXPECT_EQ(solution_distance(c.U2()), 1);
    EXPECT_EQ(solution_distance(c.Ui()), 1);
    EXPECT_EQ(solution_distance(c.D()), 1);
    EXPECT_EQ(solution_distance(c.D2()), 1);
    EXPECT_EQ(solution_distance(c.Di()), 1);
    EXPECT_EQ(solution_distance(c.F()), 1);
    EXPECT_EQ(solution_distance(c.F2()), 1);
    EXPECT_EQ(solution_distance(c.Fi()), 1);
    EXPECT_EQ(solution_distance(c.B()), 1);
    EXPECT_EQ(solution_distance(c.B2()), 1);
    EXPECT_EQ(solution_distance(c.Bi()), 1);
}

TEST(Corner_solution, solution_distance)
{
    Corners c;
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 3);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 6);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 9);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 10);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 10);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 8);
    c = c.R().Fi().Ui();
    EXPECT_EQ(solution_distance(c), 9);
}

TEST(Corner_solution, solution)
{
    Corners c;
    c = c.R().Fi().Ui();
    c = c.R().Fi().Ui();
    c = c.R().Fi().Ui();

    auto s = solution(c);
    
    for (auto rot : s)
        c = c.rotated(rot);
    EXPECT_EQ(c, Corners());
}
