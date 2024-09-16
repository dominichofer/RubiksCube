#include "gtest/gtest.h"
#include "corners.h"
#include <random>
#include <vector>

TEST(Corners, default_is_solved)
{
    EXPECT_TRUE(Corners().is_solved());
}

TEST(Corners, twisted_is_not_solved)
{
    EXPECT_FALSE(Corners().L().is_solved());
}

TEST(Corners, cubies)
{
    Corners c;
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(c.cubie(i), i);
}

TEST(Corners, orientations)
{
    Corners c(0, 0, 1, 1, 2, 2, 3, 0, 4, 1, 5, 2, 6, 0, 7, 1);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(c.orientation(i), i % 3);
}

TEST(Corners, to_string)
{
    Corners c;
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  2 - 3    0 - 0\n"
              " /   /|   /   /|\n"
              "0 - 1 |  0 - 0 |\n"
              "| 6 | 7  | 0 | 0\n"
              "4 - 5/   0 - 0/\n");
}

TEST(Corners, L)
{
    auto c = Corners().L();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  6 - 3    2 - 0\n"
              " /   /|   /   /|\n"
              "2 - 1 |  2 - 0 |\n"
              "| 4 | 7  | 2 | 0\n"
              "0 - 5/   2 - 0/\n");
}

TEST(Corners, L1_twisted)
{
    auto c = Corners(0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1).L();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  6 - 3    1 - 1\n"
              " /   /|   /   /|\n"
              "2 - 1 |  1 - 1 |\n"
              "| 4 | 7  | 1 | 1\n"
              "0 - 5/   1 - 1/\n");
}

TEST(Corners, L2)
{
    EXPECT_EQ(Corners().L2(), Corners().L().L());
}

TEST(Corners, Li)
{
    EXPECT_EQ(Corners().Li(), Corners().L().L().L());
}

TEST(Corners, R)
{
    auto c = Corners().R();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  2 - 1    0 - 2\n"
              " /   /|   /   /|\n"
              "0 - 5 |  0 - 2 |\n"
              "| 6 | 3  | 0 | 2\n"
              "4 - 7/   0 - 2/\n");
}

TEST(Corners, R2)
{
    EXPECT_EQ(Corners().R2(), Corners().R().R());
}

TEST(Corners, Ri)
{
    EXPECT_EQ(Corners().Ri(), Corners().R().R().R());
}

TEST(Corners, U)
{
    auto c = Corners().U();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  0 - 2    0 - 0\n"
              " /   /|   /   /|\n"
              "1 - 3 |  0 - 0 |\n"
              "| 6 | 7  | 0 | 0\n"
              "4 - 5/   0 - 0/\n");
}

TEST(Corners, U2)
{
    EXPECT_EQ(Corners().U2(), Corners().U().U());
}

TEST(Corners, Ui)
{
    EXPECT_EQ(Corners().Ui(), Corners().U().U().U());
}

TEST(Corners, D)
{
    auto c = Corners().D();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  2 - 3    0 - 0\n"
              " /   /|   /   /|\n"
              "0 - 1 |  0 - 0 |\n"
              "| 7 | 5  | 0 | 0\n"
              "6 - 4/   0 - 0/\n");
}

TEST(Corners, D2)
{
    EXPECT_EQ(Corners().D2(), Corners().D().D());
}

TEST(Corners, Di)
{
    EXPECT_EQ(Corners().Di(), Corners().D().D().D());
}

TEST(Corners, F)
{
    auto c = Corners().F();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  2 - 3    0 - 0\n"
              " /   /|   /   /|\n"
              "4 - 0 |  1 - 1 |\n"
              "| 6 | 7  | 0 | 0\n"
              "5 - 1/   1 - 1/\n");
}

TEST(Corners, F2)
{
    EXPECT_EQ(Corners().F2(), Corners().F().F());
}

TEST(Corners, Fi)
{
    EXPECT_EQ(Corners().Fi(), Corners().F().F().F());
}

TEST(Corners, B)
{
    auto c = Corners().B();
    EXPECT_EQ(to_string(c),
              " Cubie  Orientation\n"
              "  3 - 7    1 - 1\n"
              " /   /|   /   /|\n"
              "0 - 1 |  0 - 0 |\n"
              "| 2 | 6  | 1 | 1\n"
              "4 - 5/   0 - 0/\n");
}

TEST(Corners, B2)
{
    EXPECT_EQ(Corners().B2(), Corners().B().B());
}

TEST(Corners, Bi)
{
    EXPECT_EQ(Corners().Bi(), Corners().B().B().B());
}

TEST(Corners, inverse_rotations)
{
    Corners c;
    EXPECT_EQ(c.L().Li(), c);
    EXPECT_EQ(c.R().Ri(), c);
    EXPECT_EQ(c.U().Ui(), c);
    EXPECT_EQ(c.D().Di(), c);
    EXPECT_EQ(c.F().Fi(), c);
    EXPECT_EQ(c.B().Bi(), c);

    EXPECT_EQ(c.L2().L2(), c);
    EXPECT_EQ(c.R2().R2(), c);
    EXPECT_EQ(c.U2().U2(), c);
    EXPECT_EQ(c.D2().D2(), c);
    EXPECT_EQ(c.F2().F2(), c);
    EXPECT_EQ(c.B2().B2(), c);

    EXPECT_EQ(c.Li().L(), c);
    EXPECT_EQ(c.Ri().R(), c);
    EXPECT_EQ(c.Ui().U(), c);
    EXPECT_EQ(c.Di().D(), c);
    EXPECT_EQ(c.Fi().F(), c);
    EXPECT_EQ(c.Bi().B(), c);
}

TEST(Corners, full_rotations)
{
    Corners c;
    EXPECT_EQ(c.L().L().L().L(), c);
    EXPECT_EQ(c.R().R().R().R(), c);
    EXPECT_EQ(c.U().U().U().U(), c);
    EXPECT_EQ(c.D().D().D().D(), c);
    EXPECT_EQ(c.F().F().F().F(), c);
    EXPECT_EQ(c.B().B().B().B(), c);

    EXPECT_EQ(c.L2().L2(), c);
    EXPECT_EQ(c.R2().R2(), c);
    EXPECT_EQ(c.U2().U2(), c);
    EXPECT_EQ(c.D2().D2(), c);
    EXPECT_EQ(c.F2().F2(), c);
    EXPECT_EQ(c.B2().B2(), c);

    EXPECT_EQ(c.Li().Li().Li().Li(), c);
    EXPECT_EQ(c.Ri().Ri().Ri().Ri(), c);
    EXPECT_EQ(c.Ui().Ui().Ui().Ui(), c);
    EXPECT_EQ(c.Di().Di().Di().Di(), c);
    EXPECT_EQ(c.Fi().Fi().Fi().Fi(), c);
    EXPECT_EQ(c.Bi().Bi().Bi().Bi(), c);
}

TEST(Corners, rotation_fuzzing)
{
    auto rng = std::mt19937(13 /*arbitrary*/);
    Corners c;
    for (int i = 0; i < 1'000'000; i++)
    {
        int rnd = std::uniform_int_distribution<int>(0, 17)(rng);
        auto old_c = c;
        auto rot = static_cast<Rotation>(rnd);
        c = c.rotated(rot);

        bool is_legal = true;
        // Check that the cubies are in the range [0, 7].
        for (int i = 0; i < 8; i++)
            if (c.cubie(i) < 0 || c.cubie(i) > 7)
                is_legal = false;

        // Check that the orientation of each cubie is in the range [0, 2].
        for (int i = 0; i < 8; i++)
            if (c.orientation(i) < 0 || c.orientation(i) > 2)
                is_legal = false;

        // Check that each cubie is unique.
        for (int i = 0; i < 8; i++)
            for (int j = i + 1; j < 8; j++)
                if (c.cubie(i) == c.cubie(j))
                    is_legal = false;

        if (!is_legal)
        {
            std::cout << "Old state:\n" << to_string(old_c) << std::endl;
            std::cout << "Rotation: " << to_string(rot) << std::endl;
            std::cout << "New state:\n" << to_string(c) << std::endl;
            ASSERT_TRUE(false);
        }
    }
}

TEST(Corners, cubie_index)
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
    do
    {
        int index = Corners(v[0], 0, v[1], 0, v[2], 0, v[3], 0, v[4], 0, v[5], 0, v[6], 0, v[7], 0).cubie_index();
        int reference = 0;
        for (int i = 0; i < 7; i++)
            reference += v[i] * std::pow(8, i);
        ASSERT_EQ(index, reference);
    } while (std::next_permutation(v.begin(), v.end()));
}

TEST(Corners, orientation_index)
{
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
            for (int c = 0; c < 3; c++)
                for (int d = 0; d < 3; d++)
                    for (int e = 0; e < 3; e++)
                        for (int f = 0; f < 3; f++)
                            for (int g = 0; g < 3; g++)
                            {
                                int index = Corners(0, a, 1, b, 2, c, 3, d, 4, e, 5, f, 6, g, 7, 0).orientation_index();
                                int reference = g + f * 3 + e * 9 + d * 27 + c * 81 + b * 243 + a * 729;
                                ASSERT_EQ(index, reference);
                            }
}