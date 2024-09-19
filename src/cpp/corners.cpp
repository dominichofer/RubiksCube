#include "corners.h"
#include "intrin.h"
#include <array>
#include <sstream>

Corners::Corners(uint64_t state) noexcept : state(state) {}

Corners::Corners() noexcept : Corners(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0) {}

Corners::Corners(
    uint8_t cubie_0, uint8_t orientation_0,
    uint8_t cubie_1, uint8_t orientation_1,
    uint8_t cubie_2, uint8_t orientation_2,
    uint8_t cubie_3, uint8_t orientation_3,
    uint8_t cubie_4, uint8_t orientation_4,
    uint8_t cubie_5, uint8_t orientation_5,
    uint8_t cubie_6, uint8_t orientation_6,
    uint8_t cubie_7, uint8_t orientation_7) noexcept
{
    state = 0;
    state += ((static_cast<uint64_t>(orientation_0) << 4) + cubie_0);
    state += ((static_cast<uint64_t>(orientation_1) << 4) + cubie_1) << 8;
    state += ((static_cast<uint64_t>(orientation_2) << 4) + cubie_2) << 16;
    state += ((static_cast<uint64_t>(orientation_3) << 4) + cubie_3) << 24;
    state += ((static_cast<uint64_t>(orientation_4) << 4) + cubie_4) << 32;
    state += ((static_cast<uint64_t>(orientation_5) << 4) + cubie_5) << 40;
    state += ((static_cast<uint64_t>(orientation_6) << 4) + cubie_6) << 48;
    state += ((static_cast<uint64_t>(orientation_7) << 4) + cubie_7) << 56;
}

bool Corners::operator==(const Corners &o) const { return state == o.state; }
bool Corners::operator!=(const Corners &o) const { return !(*this == o); }

int Corners::cubie(int index) const { return (state >> (index * 8)) & 0x07; }
int Corners::orientation(int index) const { return (state >> (index * 8 + 4)) & 0x03; }

bool Corners::is_solved() const { return *this == Corners(); }

uint64_t byte_shuffle(uint64_t state, int index_0, int index_1, int index_2, int index_3, int index_4, int index_5, int index_6, int index_7)
{
    return _mm_cvtsi128_si64(
        _mm_shuffle_epi8(
            _mm_cvtsi64_si128(state),
            _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, index_7, index_6, index_5, index_4, index_3, index_2, index_1, index_0)));
}

const uint64_t ori_mask = 0x30'30'30'30'30'30'30'30ULL;
const uint64_t upper_ori_bit = 0x20'20'20'20'20'20'20'20ULL;
const uint64_t lower_ori_bit = 0x10'10'10'10'10'10'10'10ULL;
const uint64_t L_mask = 0x00'FF'00'FF'00'FF'00'FFULL;
const uint64_t R_mask = 0xFF'00'FF'00'FF'00'FF'00ULL;
const uint64_t U_mask = 0x00'00'00'00'FF'FF'FF'FFULL;
const uint64_t D_mask = 0xFF'FF'FF'FF'00'00'00'00ULL;
const uint64_t F_mask = 0x00'00'FF'FF'00'00'FF'FFULL;
const uint64_t B_mask = 0xFF'FF'00'00'FF'FF'00'00ULL;

uint64_t ori_swap_0_and_1(uint64_t state, uint64_t mask)
{
    // 1 NOT, 1 AND, 1 XOR, 1 SHIFT
    mask &= upper_ori_bit;
    return ((~state & mask) >> 1) ^ state;
}

uint64_t ori_swap_0_and_2(uint64_t state, uint64_t mask)
{
    // 1 NOT, 1 AND, 1 OR, 1 SUB
    mask &= ori_mask;
    uint64_t x = (upper_ori_bit & mask) - (state & mask);
    return (state & ~mask) | x;
}

uint64_t ori_swap_1_and_2(uint64_t state, uint64_t mask)
{
    // 3 AND, 2 SHIFT, 2 OR
    uint64_t l = (upper_ori_bit & mask & state) >> 1;
    uint64_t r = (lower_ori_bit & mask & state) << 1;
    return (state & ~(mask & ori_mask)) | l | r;
}

Corners Corners::L() const
{
    auto s = byte_shuffle(state, 2, 1, 6, 3, 0, 5, 4, 7);
    return ori_swap_0_and_2(s, L_mask);
}

Corners Corners::L2() const
{
    return byte_shuffle(state, 6, 1, 4, 3, 2, 5, 0, 7);
}

Corners Corners::Li() const
{
    auto s = byte_shuffle(state, 4, 1, 0, 3, 6, 5, 2, 7);
    return ori_swap_0_and_2(s, L_mask);
}

Corners Corners::R() const
{
    auto s = byte_shuffle(state, 0, 5, 2, 1, 4, 7, 6, 3);
    return ori_swap_0_and_2(s, R_mask);
}

Corners Corners::R2() const
{
    return byte_shuffle(state, 0, 7, 2, 5, 4, 3, 6, 1);
}

Corners Corners::Ri() const
{
    auto s = byte_shuffle(state, 0, 3, 2, 7, 4, 1, 6, 5);
    return ori_swap_0_and_2(s, R_mask);
}

Corners Corners::U() const
{
    auto s = byte_shuffle(state, 1, 3, 0, 2, 4, 5, 6, 7);
    return ori_swap_1_and_2(s, U_mask);
}

Corners Corners::U2() const
{
    return byte_shuffle(state, 3, 2, 1, 0, 4, 5, 6, 7);
}

Corners Corners::Ui() const
{
    auto s = byte_shuffle(state, 2, 0, 3, 1, 4, 5, 6, 7);
    return ori_swap_1_and_2(s, U_mask);
}

Corners Corners::D() const
{
    auto s = byte_shuffle(state, 0, 1, 2, 3, 6, 4, 7, 5);
    return ori_swap_1_and_2(s, D_mask);
}

Corners Corners::D2() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 7, 6, 5, 4);
}

Corners Corners::Di() const
{
    auto s = byte_shuffle(state, 0, 1, 2, 3, 5, 7, 4, 6);
    return ori_swap_1_and_2(s, D_mask);
}

Corners Corners::F() const
{
    auto s = byte_shuffle(state, 4, 0, 2, 3, 5, 1, 6, 7);
    return ori_swap_0_and_1(s, F_mask);
}

Corners Corners::F2() const
{
    return byte_shuffle(state, 5, 4, 2, 3, 1, 0, 6, 7);
}

Corners Corners::Fi() const
{
    auto s = byte_shuffle(state, 1, 5, 2, 3, 0, 4, 6, 7);
    return ori_swap_0_and_1(s, F_mask);
}

Corners Corners::B() const
{
    auto s = byte_shuffle(state, 0, 1, 3, 7, 4, 5, 2, 6);
    return ori_swap_0_and_1(s, B_mask);
}

Corners Corners::B2() const
{
    return byte_shuffle(state, 0, 1, 7, 6, 4, 5, 3, 2);
}

Corners Corners::Bi() const
{
    auto s = byte_shuffle(state, 0, 1, 6, 2, 4, 5, 7, 3);
    return ori_swap_0_and_1(s, B_mask);
}

Corners Corners::rotated(Rotation r) const
{
    // Array of pointers to member functions
    static const auto rotations = std::array{
        &Corners::L, &Corners::L2, &Corners::Li,
        &Corners::R, &Corners::R2, &Corners::Ri,
        &Corners::U, &Corners::U2, &Corners::Ui,
        &Corners::D, &Corners::D2, &Corners::Di,
        &Corners::F, &Corners::F2, &Corners::Fi,
        &Corners::B, &Corners::B2, &Corners::Bi};
    return (this->*rotations[static_cast<int>(r)])();
}

int Corners::position_index() const
{
    return _pext_u64(state, 0x00'07'07'07'07'07'07'07ULL);
}

int Corners::orientation_index() const
{
    uint64_t ori_1 = state & 0x00'30'00'30'00'30'00'30ULL;
    uint64_t ori_2 = state & 0x00'00'30'00'30'00'30'00ULL;
    int index_1 = (ori_1 * 0x02'D9'00'51'00'09'00'01ULL) >> 52;
    int index_2 = (ori_2 * 0x00'00'F3'00'1B'00'03'00ULL) >> 52;
    return index_1 + index_2;
}

std::string to_string(Corners corners)
{
    auto c = [corners](uint8_t i)
    { return std::to_string(corners.cubie(i)); };
    auto o = [corners](uint8_t i)
    { return std::to_string(corners.orientation(i)); };

    //   2 - 3    2 - 3
    //  /   /|   /   /|
    // 0 - 1 |  0 - 1 |
    // | 6 | 7  | 6 | 7
    // 4 - 5/   4 - 5/
    std::ostringstream oss;
    oss << " Cubie  Orientation\n"
        << "  " << c(2) << " - " << c(3) << "    " << o(2) << " - " << o(3) << "\n"
        << " /   /|   /   /|\n"
        << c(0) << " - " << c(1) << " |  " << o(0) << " - " << o(1) << " |\n"
        << "| " << c(6) << " | " << c(7) << "  | " << o(6) << " | " << o(7) << "\n"
        << c(4) << " - " << c(5) << "/   " << o(4) << " - " << o(5) << "/\n";
    return oss.str();
}
