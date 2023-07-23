#include <iostream>
#include <stdint.h>
#include <array>
#include <bitset>
#include <bit>

typedef uint64_t Bitboard;

// установка в поле шахматной доски значения для позиционирования фигур

namespace BitboardOperations {

static constexpr void set_1(Bitboard &bb, uint8_t square) {
    bb = bb | (1ull << square);
}

static constexpr void set_0(Bitboard &bb, uint8_t square) {
    bb = bb & (~(1ull << square));
}

static constexpr bool get_bit(Bitboard &bb, uint8_t square) {
    return (bb & (1ull << square));
}

static constexpr uint8_t count_1(Bitboard bb) {
    return std::popcount(bb);
}

static constexpr std::array<uint8_t, 64> BitScanTable = {
            0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63
    };
}
