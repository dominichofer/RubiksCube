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
            "{} - {}/   {} - {}/\n",
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

    void L() noexcept
    {
        state = _mm_shuffle_pi8()
    }
    void R() noexcept;
    void U() noexcept;
    void D() noexcept;
    void F() noexcept;
    void B() noexcept;

    void L2() noexcept;
    void R2() noexcept;
    void U2() noexcept;
    void D2() noexcept;
    void F2() noexcept;
    void B2() noexcept;

    void Li() noexcept;
    void Ri() noexcept;
    void Ui() noexcept;
    void Di() noexcept;
    void Fi() noexcept;
    void Bi() noexcept;
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
        .def("L", &Cube2x2::L);
        .def("R", &Cube2x2::R);
        .def("U", &Cube2x2::U);
        .def("D", &Cube2x2::D);
        .def("F", &Cube2x2::F);
        .def("B", &Cube2x2::B);
        .def("L2", &Cube2x2::L2);
        .def("R2", &Cube2x2::R2);
        .def("U2", &Cube2x2::U2);
        .def("D2", &Cube2x2::D2);
        .def("F2", &Cube2x2::F2);
        .def("B2", &Cube2x2::B2);
        .def("Li", &Cube2x2::Li);
        .def("Ri", &Cube2x2::Ri);
        .def("Ui", &Cube2x2::Ui);
        .def("Di", &Cube2x2::Di);
        .def("Fi", &Cube2x2::Fi);
        .def("Bi", &Cube2x2::Bi);
}
