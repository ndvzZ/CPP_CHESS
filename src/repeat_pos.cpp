#include "../include/RepetitionHistory.h"

#pragma once

RepetitionHistory::RepetitionHistory() = default;
void RepetitionHistory::add_position(const ZobristHash& hash) {
    this->_hashes.push_back(hash);
}
void RepetitionHistory::clear() {
    this->_hashes.clear();
}
uint8_t RepetitionHistory::get_repetition_number(const ZobristHash& hash) const {
    uint8_t ctr = 0;

    for (auto hash1 : this->_hashes) 
        if (hash == hash1) 
            ++ctr;

    return ctr;
}
