#pragma once
#include <cstdint>
#include <string>
#include <vector>

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

class Corners
{
    //   2 - 3
    //  /   /|
    // 0 - 1 |
    // | 6 | 7
    // 4 - 5/

    uint64_t state;

public:
    Corners() noexcept;
    Corners(
        uint8_t cubie_0, uint8_t orientation_0,
        uint8_t cubie_1, uint8_t orientation_1,
        uint8_t cubie_2, uint8_t orientation_2,
        uint8_t cubie_3, uint8_t orientation_3,
        uint8_t cubie_4, uint8_t orientation_4,
        uint8_t cubie_5, uint8_t orientation_5,
        uint8_t cubie_6, uint8_t orientation_6,
        uint8_t cubie_7, uint8_t orientation_7) noexcept;
    explicit Corners(uint64_t state) noexcept;

    bool operator==(const Corners &) const;
    bool operator!=(const Corners &) const;

    uint64_t get_state() const;
    
    int cubie(int) const;
    int orientation(int) const;

    bool is_solved() const;

    Corners L() const;
    Corners L2() const;
    Corners Li() const;

    Corners R() const;
    Corners R2() const;
    Corners Ri() const;

    Corners U() const;
    Corners U2() const;
    Corners Ui() const;

    Corners D() const;
    Corners D2() const;
    Corners Di() const;

    Corners F() const;
    Corners F2() const;
    Corners Fi() const;

    Corners B() const;
    Corners B2() const;
    Corners Bi() const;

    Corners rotated(Rotation) const;

    int cubie_index() const;
    int orientation_index() const;
};

std::string to_string(Corners);

namespace std
{
    template <>
    struct hash<Corners>
    {
        size_t operator()(Corners) const;
    };
}
