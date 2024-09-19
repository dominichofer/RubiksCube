#include "gtest/gtest.h"
#include "center_edges.h"
#include <random>

TEST(CenterEdges, default_is_solved)
{
    EXPECT_TRUE(CenterEdges().is_solved());
}

TEST(CenterEdges, twisted_is_not_solved)
{
    EXPECT_FALSE(CenterEdges().L().is_solved());
}

TEST(CenterEdges, edge)
{
    CenterEdges c;
    for (int i = 0; i < 12; i++)
        EXPECT_EQ(c.edge(i), i);
}

TEST(CenterEdges, orientations)
{
    CenterEdges c(0, 0, 1, 1, 2, 0, 3, 1, 4, 0, 5, 1, 6, 0, 7, 1, 8, 0, 9, 1, 10, 0, 11, 1);
    for (int i = 0; i < 12; i++)
        EXPECT_EQ(c.orientation(i), i % 2);
}

TEST(CenterEdges, to_string)
{
    CenterEdges c;
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 2----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              "  3 11      1 10      0 0       0 0\n"
              " +--- 0----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 6-|--+      |  +----0-|--+\n"
              " 8  /      9 /       0 /       0 /\n"
              " | 7       | 5       |0        |0\n"
              " +--- 4----+         +----0----+\n");
}

TEST(CenterEdges, L)
{
    auto c = CenterEdges().L();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 2----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              " 11  7      1 10      0 0       0 0\n"
              " +--- 0----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 6-|--+      |  +----0-|--+\n"
              " 3  /      9 /       0 /       0 /\n"
              " | 8       | 5       |0        |0\n"
              " +--- 4----+         +----0----+\n");
}

TEST(CenterEdges, L2)
{
    EXPECT_EQ(CenterEdges().L2(), CenterEdges().L().L());
}

TEST(CenterEdges, Li)
{
    EXPECT_EQ(CenterEdges().Li(), CenterEdges().L().L().L());
}

TEST(CenterEdges, R)
{
    auto c = CenterEdges().R();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 2----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              "  3 11      9  1      0 0       0 0\n"
              " +--- 0----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 6-|--+      |  +----0-|--+\n"
              " 8  /      5 /       0 /       0 /\n"
              " | 7       |10       |0        |0\n"
              " +--- 4----+         +----0----+\n");
}

TEST(CenterEdges, R2)
{
    EXPECT_EQ(CenterEdges().R2(), CenterEdges().R().R());
}

TEST(CenterEdges, Ri)
{
    EXPECT_EQ(CenterEdges().Ri(), CenterEdges().R().R().R());
}

TEST(CenterEdges, U)
{
    auto c = CenterEdges().U();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 3----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              "  0 11      2 10      0 0       0 0\n"
              " +--- 1----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 6-|--+      |  +----0-|--+\n"
              " 8  /      9 /       0 /       0 /\n"
              " | 7       | 5       |0        |0\n"
              " +--- 4----+         +----0----+\n");
}

TEST(CenterEdges, U2)
{
    EXPECT_EQ(CenterEdges().U2(), CenterEdges().U().U());
}

TEST(CenterEdges, Ui)
{
    EXPECT_EQ(CenterEdges().Ui(), CenterEdges().U().U().U());
}

TEST(CenterEdges, D)
{
    auto c = CenterEdges().D();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 2----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              "  3 11      1 10      0 0       0 0\n"
              " +--- 0----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 5-|--+      |  +----0-|--+\n"
              " 8  /      9 /       0 /       0 /\n"
              " | 6       | 4       |0        |0\n"
              " +--- 7----+         +----0----+\n");
}

TEST(CenterEdges, D2)
{
    EXPECT_EQ(CenterEdges().D2(), CenterEdges().D().D());
}

TEST(CenterEdges, Di)
{
    EXPECT_EQ(CenterEdges().Di(), CenterEdges().D().D().D());
}

TEST(CenterEdges, F)
{
    auto c = CenterEdges().F();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +--- 2----+         +----0----+\n"
              "   /|        /|        /|        /|\n"
              "  3 11      1 10      0 0       0 0\n"
              " +--- 8----+  |      +----1----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +--- 6-|--+      |  +----0-|--+\n"
              " 4  /      0 /       1 /       1 /\n"
              " | 7       | 5       |0        |0\n"
              " +--- 9----+         +----1----+\n");
}

TEST(CenterEdges, F2)
{
    EXPECT_EQ(CenterEdges().F2(), CenterEdges().F().F());
}

TEST(CenterEdges, Fi)
{
    EXPECT_EQ(CenterEdges().Fi(), CenterEdges().F().F().F());
}

TEST(CenterEdges, B)
{
    auto c = CenterEdges().B();
    EXPECT_EQ(to_string(c),
              "       Edge             Orientation\n"
              "    +---10----+         +----1----+\n"
              "   /|        /|        /|        /|\n"
              "  3  2      1  6      0 1       0 1\n"
              " +--- 0----+  |      +----0----+  |\n"
              " |  |      |  |      |  |      |  |\n"
              " |  +---11-|--+      |  +----1-|--+\n"
              " 8  /      9 /       0 /       0 /\n"
              " | 7       | 5       |0        |0\n"
              " +--- 4----+         +----0----+\n");
}

TEST(CenterEdges, B2)
{
    EXPECT_EQ(CenterEdges().B2(), CenterEdges().B().B());
}

TEST(CenterEdges, Bi)
{
    EXPECT_EQ(CenterEdges().Bi(), CenterEdges().B().B().B());
}

TEST(CenterEdges, inverse_rotations)
{
    CenterEdges c;
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

TEST(CenterEdges, full_rotations)
{
    CenterEdges c;
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

TEST(CenterEdges, rotation_fuzzing)
{
    auto rng = std::mt19937(13 /*arbitrary*/);
    CenterEdges c;
    for (int i = 0; i < 1'000'000; i++)
    {
        int rnd = std::uniform_int_distribution<int>(0, 17)(rng);
        auto old_c = c;
        auto rot = static_cast<Rotation>(rnd);
        c = c.rotated(rot);

        bool is_legal = true;
        // Check that the edges are in the range [0, 11].
        for (int i = 0; i < 12; i++)
            if (c.edge(i) < 0 || c.edge(i) > 11)
                is_legal = false;

        // Check that the orientation of each edge is in the range [0, 1].
        for (int i = 0; i < 12; i++)
            if (c.orientation(i) < 0 || c.orientation(i) > 1)
                is_legal = false;

        // Check that each edge is unique.
        for (int i = 0; i < 12; i++)
            for (int j = i + 1; j < 12; j++)
                if (c.edge(i) == c.edge(j))
                    is_legal = false;

        if (!is_legal)
        {
            std::cout << "Old state:\n"
                      << to_string(old_c) << std::endl;
            std::cout << "Rotation: " << to_string(rot) << std::endl;
            std::cout << "New state:\n"
                      << to_string(c) << std::endl;
            ASSERT_TRUE(false);
        }
    }
}

TEST(CenterEdges, position_index) // Fuzzing
{
    auto rng = std::mt19937(71 /*arbitrary*/);
    std::vector<uint64_t> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 1'000'000; i++)
    {
        std::shuffle(v.begin(), v.end(), rng);
        uint64_t index = CenterEdges(v[0], 0, v[1], 0, v[2], 0, v[3], 0, v[4], 0, v[5], 0, v[6], 0, v[7], 0, v[8], 0, v[9], 0, v[10], 0, v[11], 0).position_index();
        uint64_t reference = 0;
        for (int i = 0; i < 11; i++)
            reference += v[i] * std::pow(16, i);
        ASSERT_EQ(index, reference);
    }
}

TEST(CenterEdges, orientation_index)
{
    for (int a = 0; a < 2; a++)
        for (int b = 0; b < 2; b++)
            for (int c = 0; c < 2; c++)
                for (int d = 0; d < 2; d++)
                    for (int e = 0; e < 2; e++)
                        for (int f = 0; f < 2; f++)
                            for (int g = 0; g < 2; g++)
                                for (int h = 0; h < 2; h++)
                                    for (int i = 0; i < 2; i++)
                                        for (int j = 0; j < 2; j++)
                                            for (int k = 0; k < 2; k++)
                                            {
                                                int index = CenterEdges(0, a, 1, b, 2, c, 3, d, 4, e, 5, f, 6, g, 7, h, 8, i, 9, j, 10, k, 11, 0).orientation_index();
                                                int reference = a + b * 2 + c * 4 + d * 8 + e * 16 + f * 32 + g * 64 + h * 128 + i * 256 + j * 512 + k * 1024;
                                                ASSERT_EQ(index, reference);
                                            }
}
