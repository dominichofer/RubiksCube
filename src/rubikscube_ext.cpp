#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <array>
#include <cctype>
#include <format>
#include <string>
#include "Intrin.h"

namespace nb = nanobind;
using namespace nb::literals;

class Cube2x2
{
    //   2 - 3
    //  /   /|
    // 0 - 1 7
    // |   |/
    // 4 - 5
    uint64_t state;

public:
    Cube2x2(
        uint8_t cub0, uint8_t ori0,
        uint8_t cub1, uint8_t ori1,
        uint8_t cub2, uint8_t ori2,
        uint8_t cub3, uint8_t ori3,
        uint8_t cub4, uint8_t ori4,
        uint8_t cub5, uint8_t ori5,
        uint8_t cub6, uint8_t ori6,
        uint8_t cub7, uint8_t ori7) noexcept
    {
        state = 0;
        state += (ori7 * 8ULL + cub7) << 56;
        state += (ori6 * 8ULL + cub6) << 48;
        state += (ori5 * 8ULL + cub5) << 40;
        state += (ori4 * 8ULL + cub4) << 32;
        state += (ori3 * 8ULL + cub3) << 24;
        state += (ori2 * 8ULL + cub2) << 16;
        state += (ori1 * 8ULL + cub1) << 8;
        state += (ori0 * 8ULL + cub0) << 0;
    }
    Cube2x2() noexcept : Cube2x2(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0) {}

    bool operator==(const Cube2x2& other) const noexcept { return state == other.state; }
    bool operator!=(const Cube2x2& other) const noexcept { return !(*this == other); }

    int cubie(uint8_t i) const noexcept { return (state >> (i * 8)) & 0x07; }
    int orientation(uint8_t i) const noexcept { return (state >> (i * 8 + 3)) & 0x18; }

    std::string to_string() const noexcept
    {
        auto c = [this](uint8_t i) { return std::to_string(this->cubie(i)); };
        auto o = [this](uint8_t i) { return std::to_string(this->orientation(i)); };
        //  2 - 3    2 - 3
        // /   /|   /   /|
        //0 - 1 |  0 - 1 |
        //| 6 | 7  | 6 | 7
        //4 - 5/   4 - 5/ 
        return std::format(
            "  {} - {}    {} - {}\n"
            " /   /|   /   /|\n"
            "{} - {} |  {} - {} |\n"
            "| {} | {}  | {} | {}\n"
            "{} - {}/   {} - {}/ \n",
            c(2), c(3), o(2), o(3),
            c(0), c(1), o(0), o(1),
            c(6), c(7), o(6), o(7),
            c(4), c(5), o(4), o(5));
        // "  " + c(2) + " - " + c(3) + "    " + o(2) + " - " + o(3) + "\n"
        // " /   /|   /   /|\n"
        // c(0) + " - " + c(1) + " |  " + o(0) + " - " + o(1) + " |\n"
        // "| " + c(6) + " | " + c(7) + "  | " + o(6) + " | " + o(7) + "\n"
        // c(4) + " - " + c(5) + "/   " + o(4) + " - " + o(5) + "/ \n";
    }

    bool is_solved() const noexcept { return *this == Cube2x2(); }

    void L1() noexcept
    {
        state = _mm_shuffle_pi8()
    }
    void R1() noexcept;
    void U1() noexcept;
    void D1() noexcept;
    void F1() noexcept;
    void B1() noexcept;

    void L2() noexcept;
    void R2() noexcept;
    void U2() noexcept;
    void D2() noexcept;
    void F2() noexcept;
    void B2() noexcept;

    void L3() noexcept;
    void R3() noexcept;
    void U3() noexcept;
    void D3() noexcept;
    void F3() noexcept;
    void B3() noexcept;
};

NB_MODULE(rubikscube_ext, m)
{
    nb::class_<Cube2x2>(m, "Cube2x2")
        .def(nb::init<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>())
        .def(nb::init<>())
        .def("__eq__", &Cube2x2::operator==)
        .def("__ne__", &Cube2x2::operator!=)
        .def("__str__", &Cube2x2::to_string)
        .def("is_solved", &Cube2x2::is_solved)
        .def("L1", &Cube2x2::L1);
        .def("R1", &Cube2x2::R1);
        .def("U1", &Cube2x2::U1);
        .def("D1", &Cube2x2::D1);
        .def("F1", &Cube2x2::F1);
        .def("B1", &Cube2x2::B1);
        .def("L2", &Cube2x2::L2);
        .def("R2", &Cube2x2::R2);
        .def("U2", &Cube2x2::U2);
        .def("D2", &Cube2x2::D2);
        .def("F2", &Cube2x2::F2);
        .def("B2", &Cube2x2::B2);
        .def("L3", &Cube2x2::L3);
        .def("R3", &Cube2x2::R3);
        .def("U3", &Cube2x2::U3);
        .def("D3", &Cube2x2::D3);
        .def("F3", &Cube2x2::F3);
        .def("B3", &Cube2x2::B3);
}
