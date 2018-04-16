#include "State.h"

#include <utility>

namespace state {

State::State(piece::SharedConstBoard board, const state::ScoreBoard& score_board)
      : board_(board),
        score_board_(score_board) {
}

const piece::Piece& State::next() const {
    throw std::logic_error("State::next - there is no next piece");
}

const piece::PiecePosition& State::piece_position() const {
    throw std::logic_error("State::piece_position - there is no falling piece on the board");
}

const piece::Piece& State::piece() const {
    throw std::logic_error("State::piece - there is no falling piece on the board");
}

const piece::Board::EliminationList& State::elimination_list() const {
    throw std::logic_error("State::piece - there is no elimination list");
}

StateWithNext::StateWithNext(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next)
      : State(board, score_board),
        next_(next) {
}

StateElimination::StateElimination(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const piece::Board::EliminationList& list)
      : StateWithNext(board, score_board, next),
        elimination_list_(list) {
}

StateFalling::StateFalling(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const piece::Piece& falling,
      const piece::PiecePosition& position)
      : StateWithNext(board, score_board, next),
        piece_(falling),
        piece_position_(position) {
}
}
