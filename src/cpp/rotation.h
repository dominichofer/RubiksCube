#pragma once
#include <string>

enum class Rotation
{
    L, L2, Li,
    R, R2, Ri,
    U, U2, Ui,
    D, D2, Di,
    F, F2, Fi,
    B, B2, Bi
};

std::string to_string(Rotation);
