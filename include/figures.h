#pragma once
#include "utils.h"
#include <iterator>
#include <string>

typedef struct figure {
    std::array<std::array<Bitboard, 6>, 2> _type_bitboards{}; // позиция конкретной фигуры
    std::array<Bitboard, 2> _side_bitboards{};                  // позиция белой или черной фигуры
    std::array<Bitboard, 2> _inversion_side_bitboards{};
    Bitboard _all;
    Bitboard _empty;

    //Коструктор доски
    figure(const std::string& short_fen);
    uint8_t inverse(uint8_t side);
    void update_bitboards();
    // Константы для индексов фигур
    static constexpr uint8_t Pawn = 0;
    static constexpr uint8_t Knight = 1;
    static constexpr uint8_t Bishop = 2;
    static constexpr uint8_t Rook = 3;
    static constexpr uint8_t Queen = 4;
    static constexpr uint8_t King = 5;

    static constexpr uint8_t White = 0;
    static constexpr uint8_t Black = 1;

} _figure;


bool operator==(figure& left, figure &right); 
bool operator==(const figure& left, const figure &right);
std::ostream &operator<<(std::ostream &ostream, figure pieces);