#include "../include/step.h"

Move::Move(){}

Move::Move(uint8_t from, uint8_t to, uint8_t attacker_type, uint8_t attacker_side, uint8_t defender_type, uint8_t defender_side, uint8_t flag = Move::Flag::Default) {
    _from = from;
    _to = to;
    _attacker_type = attacker_type;
    _attacker_side = attacker_side;
    _defender_side = defender_side;
    _defender_type = defender_type;
    _flag = flag;
}

bool operator ==(Move left, Move right) { 
    if (left._from == right._from &&
        left._to == right._to &&
        left._attacker_type == right._attacker_type &&
        left._attacker_side == right._attacker_side &&
        left._defender_type == right._defender_type &&
        left._defender_side == right._defender_side &&
        left._flag == right._flag)
        
        return true;
    return false;
}
