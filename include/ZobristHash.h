#include <cstdint>
#include <array>
#include "figures.h"

namespace ZobristHashConsteval {
    namespace PRNG {
        static constexpr uint64_t Seed = 0x98f107;
        static constexpr uint64_t Multiplier = 0x71abc9;
        static constexpr uint64_t Summand = 0xff1b3f;
    }

// Хэшируем позиции фигур на шахматной доске а также условия рокировки

    static consteval uint64_t next_random(uint64_t previous) {
        return ZobristHashConsteval::PRNG::Multiplier * previous + ZobristHashConsteval::PRNG::Summand;
    }
    static consteval std::array<std::array<std::array<uint64_t, 6>, 2>, 64> calc_constants() {
        std::array<std::array<std::array<uint64_t, 6>, 2>, 64> constants{};

        uint64_t previous = ZobristHashConsteval::PRNG::Seed;

        for (uint8_t square = 0; square < 64; ++square) {
            for (uint8_t side = 0; side < 2; ++side) {
                for (uint8_t type = 0; type < 6; ++type) {
                    previous = ZobristHashConsteval::next_random(previous);
                    constants[square][side][type] = previous;
                }
            }
        }

        return constants;
    }

    static constexpr std::array<std::array<std::array<uint64_t, 6>, 2>, 64> Constants = calc_constants();
    static constexpr uint64_t BlackMove = ZobristHashConsteval::next_random(ZobristHashConsteval::Constants[63][1][5]);
    static constexpr uint64_t WhiteLongCastling = ZobristHashConsteval::next_random(ZobristHashConsteval::BlackMove);
    static constexpr uint64_t WhiteShortCastling = ZobristHashConsteval::next_random(ZobristHashConsteval::WhiteLongCastling);
    static constexpr uint64_t BlackLongCastling = ZobristHashConsteval::next_random(ZobristHashConsteval::WhiteShortCastling);
    static constexpr uint64_t BlackShortCastling = ZobristHashConsteval::next_random(ZobristHashConsteval::BlackLongCastling);
}

    class ZobristHash {

        uint64_t _hash;

        public:
            ZobristHash() = default;
            explicit ZobristHash(figure fig, bool black_move, bool w_l_castling, bool w_s_castling, bool b_l_castling, bool b_s_castling);
            ~ZobristHash() = default;

            bool operator ==(const ZobristHash &value) const;
            bool operator <(const ZobristHash& value) const;
            bool operator >(const ZobristHash& value) const;

            void invert_figure(uint8_t square, uint8_t type, uint8_t side);
            void invert_move();  
            void invert_w_l_castling();
            void invert_w_s_castling();       
            void invert_b_l_castling();       
            void invert_b_s_castling(); 
  
    };

