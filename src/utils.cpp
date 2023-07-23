#include "../include/utils.h"

static constexpr uint8_t bsf(Bitboard bb) {                 // поиск первого единичного бита
    return BitboardOperations::BitScanTable[((bb ^ (bb - 1)) * 0x03f79d71b4cb0a89) >> 58];
}
static constexpr uint8_t bsr(Bitboard bb) {                 // поиск последнего единичного бита
    bb = bb | (bb >> 1);
    bb = bb | (bb >> 2);
    bb = bb | (bb >> 4);
    bb = bb | (bb >> 8);
    bb = bb | (bb >> 16);
    bb = bb | (bb >> 32);

    return BitboardOperations::BitScanTable[(bb * 0x03f79d71b4cb0a89) >> 58];
}

// оценка количества фигур в строке и в столбце
namespace BitboardRows {
    static consteval std::array<Bitboard, 8> calc_rows() {      ///
        std::array<Bitboard, 8> rows {};

        for (uint8_t y = 0; y < 8; ++y) {
            for (uint8_t x = 0; x < 8; ++x)  
                BitboardOperations::set_1(rows[y], y * 8 + x);
        }
        return rows;
    }

    static constexpr std::array<Bitboard, 8> Rows = BitboardRows::calc_rows();


    static consteval std::array<Bitboard, 8> calc_inversion_rows() {    ///
        std::array<Bitboard, 8> inversion_rows{};
        for(uint8_t i = 0; i < 8; ++i) 
            inversion_rows[i] = ~Rows[i];

        return inversion_rows;
    }

    static constexpr std::array<Bitboard, 8> InversionRows = BitboardRows::calc_inversion_rows();
}


namespace BitboardColumns {
    static consteval std::array<Bitboard, 8> calc_columns() {   ////
        std::array<Bitboard, 8> columns{};

        for (uint8_t x = 0; x < 8; ++x) {
            for (uint8_t y = 0; y < 8; ++y) BitboardOperations::set_1(columns[x], y * 8 + x);
        }

        return columns;
    }

    static constexpr std::array<Bitboard, 8> Columns = BitboardColumns::calc_columns();

    static consteval std::array<Bitboard, 8> calc_inversion_columns() { ///
        std::array<Bitboard, 8> inversion_columns{};

        for (uint8_t i = 0; i < 8; ++i) inversion_columns[i] = ~Columns[i];

        return inversion_columns;
    }

    static constexpr std::array<Bitboard, 8> InversionColumns = BitboardColumns::calc_inversion_columns();
}