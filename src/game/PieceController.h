#pragma once

#include "game/Messages.h"
#include "piece/Board.h"
#include "piece/PiecePosition.h"

#include <atomic>
#include <utility>

namespace game {
class PieceController {
public:
    PieceController(piece::SharedConstBoard board,
          size_t max_sub_row);
    bool has_piece() const { return piece_[0] != gui::Color::NONE; }

    const piece::PiecePosition& position() const;
    const piece::Piece& piece() const;

    void add(const piece::Piece& piece, size_t column);
    std::pair<piece::Piece, piece::PiecePosition> remove();

    void process(EMessage message);

    bool step();

private:
    piece::SharedConstBoard board_;
    size_t max_sub_row_;
    piece::Piece piece_;
    piece::PiecePosition position_;
    size_t steps_per_step_; ///< normal == 1, accelerated == 5

    bool can_move_left() const;
    bool can_move_right() const;
    bool can_step_down() const;
    size_t lower_row_to_check() const;
};
}
