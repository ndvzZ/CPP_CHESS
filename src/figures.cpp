#include "../include/figures.h"

uint8_t figure::inverse(uint8_t side) {
    return !side;
}

bool operator ==(figure& left, figure& right) {
    for (uint8_t i = 0; i < 2; ++i) {
        for (uint8_t j = 0; j < 6; ++j) {
            if (left._type_bitboards[i][j] != right._type_bitboards[i][j]) return false;
        }
    }
    return true;
}

bool operator ==(const figure& left, const figure& right) {
    for (uint8_t i = 0; i < 2; ++i) {
        for (uint8_t j = 0; j < 6; ++j) {
            if (left._type_bitboards[i][j] != right._type_bitboards[i][j]) return false;
        }
    }
    return true;
}

void figure::update_bitboards() {
    this->_side_bitboards[figure::White] = this->_type_bitboards[figure::White][figure::Pawn] |
                                           this->_type_bitboards[figure::White][figure::Knight] |
                                           this->_type_bitboards[figure::White][figure::Bishop] |
                                           this->_type_bitboards[figure::White][figure::Rook] |
                                           this->_type_bitboards[figure::White][figure::Queen] |
                                           this->_type_bitboards[figure::White][figure::King];

    this->_side_bitboards[figure::Black] = this->_type_bitboards[figure::Black][figure::Pawn] |
                                           this->_type_bitboards[figure::Black][figure::Knight] |
                                           this->_type_bitboards[figure::Black][figure::Bishop] |
                                           this->_type_bitboards[figure::Black][figure::Rook] |
                                           this->_type_bitboards[figure::Black][figure::Queen] |
                                           this->_type_bitboards[figure::Black][figure::King];

    this->_inversion_side_bitboards[figure::White] = ~this->_side_bitboards[figure::White];
    this->_inversion_side_bitboards[figure::Black] = ~this->_side_bitboards[figure::Black];

    this->_all = this->_side_bitboards[figure::White] | this->_side_bitboards[figure::Black];
    this->_empty = ~this->_all;
}

figure::figure(const std::string& short_fen) {
    uint8_t x = 0;
    uint8_t y = 7;

    uint8_t side;

    for (auto buff : short_fen) {
        if (buff == '/') {
            x = 0;
            --y;
        }
        else if (std::isdigit(buff)) {
            x = x + buff - '0';
        }
        else {
            if (std::isupper(buff)) {
                buff = std::tolower(buff);
                side = figure::White;
            }
            else side = figure::Black;

            switch (buff) {
                case 'p': BitboardOperations::set_1(this->_type_bitboards[side][figure::Pawn], y * 8 + x); break;
                case 'n': BitboardOperations::set_1(this->_type_bitboards[side][figure::Knight], y * 8 + x); break;
                case 'b': BitboardOperations::set_1(this->_type_bitboards[side][figure::Bishop], y * 8 + x); break;
                case 'r': BitboardOperations::set_1(this->_type_bitboards[side][figure::Rook], y * 8 + x); break;
                case 'q': BitboardOperations::set_1(this->_type_bitboards[side][figure::Queen], y * 8 + x); break;
                case 'k': BitboardOperations::set_1(this->_type_bitboards[side][figure::King], y * 8 + x); break;
            }

            ++x;
        }
    }

    this->update_bitboards();
}

std::ostream &operator<<(std::ostream &ostream, figure figure) {
    for (int8_t y = 7; y >= 0; --y) {
        for (uint8_t x = 0; x < 8; x++) {
            ostream << "|  ";

            if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::Pawn], y * 8 + x)) ostream << "♙";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::Knight], y * 8 + x)) ostream << "♘";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::Bishop], y * 8 + x)) ostream << "♗";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::Rook], y * 8 + x)) ostream << "♖";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::Queen], y * 8 + x)) ostream << "♕";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::White][figure::King], y * 8 + x)) ostream << "♔";

            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::Pawn], y * 8 + x)) ostream << "♟";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::Knight], y * 8 + x)) ostream << "♞";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::Bishop], y * 8 + x)) ostream << "♝";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::Rook], y * 8 + x)) ostream << "♜";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::Queen], y * 8 + x)) ostream << "♛";
            else if (BitboardOperations::get_bit(figure._type_bitboards[figure::Black][figure::King], y * 8 + x)) ostream << "♚";

            else ostream << " ";

            ostream << "  ";
        }
        ostream << "|\n";
    }

    return ostream;
}