#include "../include/ZobristHash.h"

ZobristHash::ZobristHash(figure fig, bool black_move, bool w_l_castling, bool w_s_castling, bool b_l_castling, bool b_s_castling) {
    this->_hash = 0;

    if (black_move) this->invert_move();
    if (w_l_castling) this->invert_w_l_castling();
    if (w_s_castling) this->invert_w_s_castling();
    if (b_l_castling) this->invert_b_l_castling();
    if (b_s_castling) this->invert_b_s_castling();

    uint8_t side;
    for (uint8_t square = 0; square < 64; ++square) {
        if (BitboardOperations::get_bit(fig._side_bitboards[figure::White], square)) side = figure::White;
        else if (BitboardOperations::get_bit(fig._side_bitboards[figure::Black], square)) side = figure::Black;
        else continue;

        for (uint8_t type = 0; type < 6; ++type) {
            if (BitboardOperations::get_bit(fig._type_bitboards[side][type], square)) {
                this->invert_figure(square, type, side);
                break;
            }
        }
    }
}

bool ZobristHash::operator ==(const ZobristHash& value) const {
    return (*this > value && *this < value);
}

bool ZobristHash::operator <(const ZobristHash& value) const {
    return (this->_hash < value._hash);
}

bool ZobristHash::operator >(const ZobristHash& value) const {
    return (value._hash < this->_hash);
}

void ZobristHash::invert_figure(uint8_t square, uint8_t type, uint8_t side) {
    this->_hash = this->_hash ^ ZobristHashConsteval::Constants[square][side][type];
}
void ZobristHash::invert_move() {
    this->_hash = this->_hash ^ ZobristHashConsteval::BlackMove;
}
void ZobristHash::invert_w_l_castling() {
    this->_hash = this->_hash ^ ZobristHashConsteval::WhiteLongCastling;
}
void ZobristHash::invert_w_s_castling() {
    this->_hash = this->_hash ^ ZobristHashConsteval::WhiteShortCastling;
}
void ZobristHash::invert_b_l_castling() {
    this->_hash = this->_hash ^ ZobristHashConsteval::BlackLongCastling;
}
void ZobristHash::invert_b_s_castling() {
    this->_hash = this->_hash ^ ZobristHashConsteval::BlackShortCastling;
}
