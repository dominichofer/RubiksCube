#include "corner_solution.h"
#include "intrin.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>

std::vector<Corners> neighbors(Corners c)
{
    return {c.L(), c.L2(), c.Li(),
            c.R(), c.R2(), c.Ri(),
            c.U(), c.U2(), c.Ui(),
            c.D(), c.D2(), c.Di(),
            c.F(), c.F2(), c.Fi(),
            c.B(), c.B2(), c.Bi()};
}

class DistanceTable
{
    std::vector<std::vector<uint8_t>> table;

public:
    DistanceTable() noexcept
    {
        std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
        do
        {
            int index = Corners(v[0], 0, v[1], 0, v[2], 0, v[3], 0, v[4], 0, v[5], 0, v[6], 0, v[7], 0).position_index();
            if (table.size() <= index)
                table.resize(index + 1);
            table[index].resize(std::pow(3, 7), 0xFF);
        } while (std::next_permutation(v.begin(), v.end()));

        std::string filename = "corners_table.bin";
        if (std::ifstream(filename).good())
        {
            std::fstream file(filename, std::ios::binary | std::ios::in);
            for (auto &v : table)
                if (!v.empty())
                    file.read(reinterpret_cast<char *>(v.data()), v.size());
        }
        else
        {
            (*this)[Corners()] = 0;
            std::vector<Corners> last_pos = {Corners()};
            std::vector<Corners> next_pos;
            for (int distance = 1; true; distance++)
            {
                #pragma omp parallel
                {
                    std::vector<Corners> next_pos_private;
                    #pragma omp for nowait
                    for (size_t i = 0; i < last_pos.size(); i++)
                        for (Corners n : neighbors(last_pos[i]))
                        {
                            uint8_t& item = (*this)[n];
                            if (item > distance)
                            {
                                item = distance;
                                next_pos_private.push_back(n);
                            }
                        }
                    #pragma omp critical
                    next_pos.insert(next_pos.end(), next_pos_private.begin(), next_pos_private.end());
                }
                if (next_pos.empty())
                    break;
                last_pos = next_pos;
                next_pos.clear();
            }
            std::fstream stream(filename, std::ios::binary | std::ios::out);
            for (const auto &v : table)
                if (!v.empty())
                    stream.write(reinterpret_cast<const char *>(v.data()), v.size());
        }

        int sum = 0;
        for (const auto &v : table)
            sum += v.size();
        if (sum != 8 * 7 * 6 * 5 * 4 * 3 * 2 * std::pow(3, 7))
            throw std::runtime_error("Invalid table size");
    }

    uint8_t operator[](Corners c) const { return table[c.position_index()][c.orientation_index()]; }

private:
    uint8_t &operator[](Corners c) { return table[c.position_index()][c.orientation_index()]; }
};

int solution_distance(Corners c)
{
    static const DistanceTable distance_table;
    return distance_table[c];
}

std::vector<Rotation> solution(Corners c)
{
    std::vector<Rotation> rotations = {Rotation::L, Rotation::L2, Rotation::Li,
                                       Rotation::R, Rotation::R2, Rotation::Ri,
                                       Rotation::U, Rotation::U2, Rotation::Ui,
                                       Rotation::D, Rotation::D2, Rotation::Di,
                                       Rotation::F, Rotation::F2, Rotation::Fi,
                                       Rotation::B, Rotation::B2, Rotation::Bi};
    int dst = solution_distance(c);
    std::vector<Rotation> solution;
    solution.reserve(dst);
    for (; dst > 0; dst--)
        for (Rotation r : rotations)
        {
            Corners c_rotated = c.rotated(r);
            if (solution_distance(c_rotated) < dst)
            {
                solution.push_back(r);
                c = c_rotated;
                break;
            }
        }
    return solution;
}
