#pragma once

#include "state/State.h"

namespace game {

class Canvas {
public:
    Canvas() = default;
    virtual ~Canvas() = default;

    Canvas(const Canvas&) = delete;
    Canvas& operator=(const Canvas&) = delete;
    Canvas(Canvas&&) = delete;
    Canvas& operator=(Canvas&&) = delete;

    virtual void clear() = 0;

    void draw(const state::State& state);

private:
    virtual void draw_(piece::SharedConstBoard board) = 0;
    virtual void draw_(const piece::Piece& piece, const piece::PiecePosition& piece_position) = 0;
    virtual void draw_next_(const piece::Piece& next_piece) = 0;
    virtual void draw_(const state::ScoreBoard& score_board) = 0;
    virtual void draw_(const piece::Board::EliminationList& elimination_list) = 0;
};

using CanvasPtr = std::unique_ptr<Canvas>;
}
