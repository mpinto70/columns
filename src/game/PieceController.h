#pragma once

#include "game/Messages.h"
#include "piece/Board.h"
#include "piece/Position.h"
#include <atomic>
#include <utility>

namespace game {
class PieceController {
public:
    explicit PieceController(piece::SharedConstBoard board);
    bool has_piece() const { return piece_[0] != gui::Color::NONE; }

    const piece::Position& position() const;
    const piece::Piece& piece() const;

    void add(const piece::Piece& piece, size_t column);
    std::pair<piece::Piece, piece::Position> remove();

    void process(EMessage message);

    bool step();

private:
    piece::SharedConstBoard board_;
    piece::Piece piece_;
    piece::Position position_;
    size_t steps_per_step_; ///< normal == 1, accelerated == 5

    bool can_move_left() const;
    bool can_move_right() const;
    bool can_step_down() const;
    size_t lower_row_to_check() const;
};
}
