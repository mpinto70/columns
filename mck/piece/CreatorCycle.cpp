#include "CreatorCycle.h"

namespace piece {
namespace mck {
CreatorCycle::CreatorCycle(const std::vector<Piece>& pieces, const std::vector<size_t>& columns)
      : pieces_(pieces),
        columns_(columns),
        current_piece_(0),
        current_column_(0) {
}

Piece CreatorCycle::piece() const {
    Piece next = pieces_[current_piece_];
    ++current_piece_;
    if (current_piece_ == pieces_.size())
        current_piece_ = 0;
    return next;
}

size_t CreatorCycle::column() const {
    size_t column = columns_[current_column_];
    ++current_column_;
    if (current_column_ == columns_.size())
        current_column_ = 0;
    return column;
}
}
}
