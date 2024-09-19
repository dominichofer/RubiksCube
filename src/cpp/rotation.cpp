#include "rotation.h"
#include <array>

std::string to_string(Rotation r)
{
    return std::array{
        "L", "L2", "Li",
        "R", "R2", "Ri",
        "U", "U2", "Ui",
        "D", "D2", "Di",
        "F", "F2", "Fi",
        "B", "B2", "Bi"}[static_cast<int>(r)];
}
