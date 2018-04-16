#pragma once

#include "game/Messages.h"
#include "piece/Board.h"
#include "piece/PiecePosition.h"

#include <atomic>

namespace game {
class PieceController {
public:
    PieceController(piece::SharedConstBoard board,
          size_t max_sub_row);
    bool has_piece() const { return piece_.get() != nullptr; }

    piece::PiecePosition position() const;
    piece::Piece piece() const;

    void add(const piece::Piece& piece, size_t column);

    void process(const Messages::List& messages);

    bool step();

private:
    piece::SharedConstBoard board_;
    size_t max_sub_row_;
    piece::PiecePtr piece_;
    piece::PiecePositionPtr position_;
    size_t steps_per_step_; ///< normal == 1, accelerated == 5

    bool can_move_left() const;
    bool can_move_right() const;
    bool can_step_down() const;
    size_t lower_row_to_check() const;
};
}
