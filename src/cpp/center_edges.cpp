#include "center_edges.h"
#include <array>
#include <sstream>
#include <bitset>
#include <iostream>

CenterEdges::CenterEdges(__m128i state) noexcept : state(state) {}

CenterEdges::CenterEdges() noexcept : CenterEdges(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, 10, 0, 11, 0) {}

CenterEdges::CenterEdges(
    uint8_t edge_0, uint8_t orientation_0,
    uint8_t edge_1, uint8_t orientation_1,
    uint8_t edge_2, uint8_t orientation_2,
    uint8_t edge_3, uint8_t orientation_3,
    uint8_t edge_4, uint8_t orientation_4,
    uint8_t edge_5, uint8_t orientation_5,
    uint8_t edge_6, uint8_t orientation_6,
    uint8_t edge_7, uint8_t orientation_7,
    uint8_t edge_8, uint8_t orientation_8,
    uint8_t edge_9, uint8_t orientation_9,
    uint8_t edge_10, uint8_t orientation_10,
    uint8_t edge_11, uint8_t orientation_11) noexcept
{
    state = _mm_set_epi8(0, 0,
                         orientation_11 << 4 | edge_11,
                         orientation_10 << 4 | edge_10,
                         orientation_9 << 4 | edge_9,
                         orientation_8 << 4 | edge_8,
                         orientation_7 << 4 | edge_7,
                         orientation_6 << 4 | edge_6,
                         0, 0,
                         orientation_5 << 4 | edge_5,
                         orientation_4 << 4 | edge_4,
                         orientation_3 << 4 | edge_3,
                         orientation_2 << 4 | edge_2,
                         orientation_1 << 4 | edge_1,
                         orientation_0 << 4 | edge_0);
}

bool CenterEdges::operator==(const CenterEdges &o) const
{
    __m128i x = _mm_xor_si128(state, o.state);
    return _mm_testz_si128(x, x);
}
bool CenterEdges::operator!=(const CenterEdges &o) const { return !(*this == o); }

int CenterEdges::edge(int index) const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    if (index > 5)
        return hi >> ((index - 6) * 8) & 0x0F;
    else
        return lo >> (index * 8) & 0x0F;
}

int CenterEdges::orientation(int index) const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    if (index > 5)
        return hi >> ((index - 6) * 8 + 4) & 0x01;
    else
        return lo >> (index * 8 + 4) & 0x01;
}

bool CenterEdges::is_solved() const { return *this == CenterEdges(); }

__m128i byte_shuffle(__m128i state, int index_0, int index_1, int index_2, int index_3, int index_4, int index_5, int index_6, int index_7, int index_8, int index_9, int index_10, int index_11)
{
    return _mm_shuffle_epi8(
        state,
        _mm_set_epi8(15, 15, index_11, index_10, index_9, index_8, index_7, index_6, 15, 15, index_5, index_4, index_3, index_2, index_1, index_0));
}

// TODO: Remove!
// const __m128i L_mask = _mm_set_epi8(0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00);
// const __m128i R_mask = _mm_set_epi8(0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00);
// const __m128i U_mask = _mm_set_epi8(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10);
// const __m128i D_mask = _mm_set_epi8(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00);
const __m128i F_mask = _mm_set_epi8(0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10);
const __m128i B_mask = _mm_set_epi8(0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00);

CenterEdges CenterEdges::L() const
{
    return byte_shuffle(state, 0, 1, 2, 13, 4, 5, 8, 10, 3, 11, 12, 9);
}

CenterEdges CenterEdges::L2() const
{
    return byte_shuffle(state, 0, 1, 2, 9, 4, 5, 8, 3, 13, 11, 12, 10);
}

CenterEdges CenterEdges::Li() const
{
    return byte_shuffle(state, 0, 1, 2, 10, 4, 5, 8, 13, 9, 11, 12, 3);
}

CenterEdges CenterEdges::R() const
{
    return byte_shuffle(state, 0, 11, 2, 3, 4, 12, 8, 9, 10, 5, 1, 13);
}

CenterEdges CenterEdges::R2() const
{
    return byte_shuffle(state, 0, 5, 2, 3, 4, 1, 8, 9, 10, 12, 11, 13);
}

CenterEdges CenterEdges::Ri() const
{
    return byte_shuffle(state, 0, 12, 2, 3, 4, 11, 8, 9, 10, 1, 5, 13);
}

CenterEdges CenterEdges::U() const
{
    return byte_shuffle(state, 1, 2, 3, 0, 4, 5, 8, 9, 10, 11, 12, 13);
}

CenterEdges CenterEdges::U2() const
{
    return byte_shuffle(state, 2, 3, 0, 1, 4, 5, 8, 9, 10, 11, 12, 13);
}

CenterEdges CenterEdges::Ui() const
{
    return byte_shuffle(state, 3, 0, 1, 2, 4, 5, 8, 9, 10, 11, 12, 13);
}

CenterEdges CenterEdges::D() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 9, 4, 5, 8, 10, 11, 12, 13);
}

CenterEdges CenterEdges::D2() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 8, 9, 4, 5, 10, 11, 12, 13);
}

CenterEdges CenterEdges::Di() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 5, 8, 9, 4, 10, 11, 12, 13);
}

CenterEdges CenterEdges::F() const
{
    auto s = byte_shuffle(state, 10, 1, 2, 3, 11, 5, 8, 9, 4, 0, 12, 13);
    return _mm_xor_si128(s, F_mask);
}

CenterEdges CenterEdges::F2() const
{
    return byte_shuffle(state, 4, 1, 2, 3, 0, 5, 8, 9, 11, 10, 12, 13);
}

CenterEdges CenterEdges::Fi() const
{
    auto s = byte_shuffle(state, 11, 1, 2, 3, 10, 5, 8, 9, 0, 4, 12, 13);
    return _mm_xor_si128(s, F_mask);
}

CenterEdges CenterEdges::B() const
{
    auto s = byte_shuffle(state, 0, 1, 12, 3, 4, 5, 13, 9, 10, 11, 8, 2);
    return _mm_xor_si128(s, B_mask);
}

CenterEdges CenterEdges::B2() const
{
    return byte_shuffle(state, 0, 1, 8, 3, 4, 5, 2, 9, 10, 11, 13, 12);
}

CenterEdges CenterEdges::Bi() const
{
    auto s = byte_shuffle(state, 0, 1, 13, 3, 4, 5, 12, 9, 10, 11, 2, 8);
    return _mm_xor_si128(s, B_mask);
}

CenterEdges CenterEdges::rotated(Rotation r) const
{
    // Array of pointers to member functions
    static const auto rotations = std::array{
        &CenterEdges::L, &CenterEdges::L2, &CenterEdges::Li,
        &CenterEdges::R, &CenterEdges::R2, &CenterEdges::Ri,
        &CenterEdges::U, &CenterEdges::U2, &CenterEdges::Ui,
        &CenterEdges::D, &CenterEdges::D2, &CenterEdges::Di,
        &CenterEdges::F, &CenterEdges::F2, &CenterEdges::Fi,
        &CenterEdges::B, &CenterEdges::B2, &CenterEdges::Bi};
    return (this->*rotations[static_cast<int>(r)])();
}

uint64_t CenterEdges::position_index() const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    uint64_t index_0 = _pext_u64(lo, 0x00'00'0F'0F'0F'0F'0F'0FULL);
    uint64_t index_1 = _pext_u64(hi, 0x00'00'00'0F'0F'0F'0F'0FULL);
    return index_0 | (index_1 << 24);
}

int CenterEdges::orientation_index() const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    int index_0 = _pext_u64(lo, 0x00'00'10'10'10'10'10'10ULL);
    int index_1 = _pext_u64(hi, 0x00'00'00'10'10'10'10'10ULL);
    return index_0 | (index_1 << 6);
}

std::string to_string(CenterEdges edges)
{
    auto e = [edges](uint8_t i)
    { 
        std::string s = std::to_string(edges.edge(i));
        return std::string(2 - s.length(), ' ') + s;
    };
    auto o = [edges](uint8_t i)
    { return std::to_string(edges.orientation(i)); };

    //     +----2----+         +----0----+
    //    /|        /|        /|        /|
    //   3 11      1 10      0 0       0 0
    //  +----0----+  |      +----0----+  |
    //  |  |      |  |      |  |      |  |
    //  |  +----6-|--+      |  +----0-|--+
    //  8 /       9 /       0 /       0 /
    //  |7        |5        |0        |0
    //  +----4----+         +----4----+
    std::ostringstream oss;
    oss << "       Edge             Orientation\n"
        << "    +---" << e(2) << "----+         +----" << o(2) << "----+\n"
        << "   /|        /|        /|        /|\n"
        << " " << e(3) << " " << e(11) << "     " << e(1) << " " << e(10) << "      " << o(3) << " " << o(11) << "       " << o(1) << " " << o(10) << "\n"
        << " +---" << e(0) << "----+  |      +----" << o(0) << "----+  |\n"
        << " |  |      |  |      |  |      |  |\n"
        << " |  +---" << e(6) << "-|--+      |  +----" << o(6) << "-|--+\n"
        << e(8) << "  /     " << e(9) << " /       " << o(8) << " /       " << o(9) << " /\n"
        << " |" << e(7) << "       |" << e(5) << "       |" << o(7) << "        |" << o(5) << "\n"
        << " +---" << e(4) << "----+         +----" << o(4) << "----+\n";
    return oss.str();
}
