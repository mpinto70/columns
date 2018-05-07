#include "PieceCreatorCycle.h"

namespace piece {
namespace mck {
PieceCreatorCycle::PieceCreatorCycle(const std::vector<Piece>& pieces)
      : pieces_(pieces),
        current_(0) {
}

Piece PieceCreatorCycle::get_next() const {
    Piece next = pieces_[current_];
    ++current_;
    if (current_ == pieces_.size())
        current_ = 0;
    return next;
}
}
}
