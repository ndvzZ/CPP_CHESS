#include <vector>
#include "../include/ZobristHash.h"

class RepetitionHistory {
public:
    RepetitionHistory();

    void add_position(const ZobristHash& hash);

    void clear();

    uint8_t get_repetition_number(const ZobristHash& hash) const;
private:
    std::vector<ZobristHash> _hashes;
};
