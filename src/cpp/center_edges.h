#pragma once
#include "rotation.h"
#include "intrin.h"
#include <cstdint>
#include <string>

class CenterEdges
{
    //     +----2----+
    //    /|        /|
    //   3 11      1 10
    //  +----0----+  |
    //  |  |      |  |
    //  |  +----6-|--+
    //  8 /       9 /
    //  |7        |5
    //  +----4----+

    __m128i state;

    CenterEdges(__m128i state) noexcept;

public:
    CenterEdges() noexcept;
    CenterEdges(
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
        uint8_t edge_11, uint8_t orientation_11) noexcept;

    bool operator==(const CenterEdges &) const;
    bool operator!=(const CenterEdges &) const;

    int edge(int) const;
    int orientation(int) const;

    bool is_solved() const;

    CenterEdges L() const;
    CenterEdges L2() const;
    CenterEdges Li() const;

    CenterEdges R() const;
    CenterEdges R2() const;
    CenterEdges Ri() const;

    CenterEdges U() const;
    CenterEdges U2() const;
    CenterEdges Ui() const;

    CenterEdges D() const;
    CenterEdges D2() const;
    CenterEdges Di() const;

    CenterEdges F() const;
    CenterEdges F2() const;
    CenterEdges Fi() const;

    CenterEdges B() const;
    CenterEdges B2() const;
    CenterEdges Bi() const;

    CenterEdges rotated(Rotation) const;

    uint64_t position_index() const;
    int orientation_index() const;
};

std::string to_string(CenterEdges);
