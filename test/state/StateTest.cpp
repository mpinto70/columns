#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"
#include "../mck/util/utiltest.h"

#include "state/State.h"

#include "piece/Board.h"
#include "state/ScoreBoard.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace state {
namespace tst {

static State create_state(piece::SharedConstBoard board, const state::ScoreBoard& score_board) {
    return State(board, score_board);
}

static State create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& falling,
      const piece::PiecePosition& position,
      const piece::Piece& next) {
    return State(board, score_board, falling, position, next);
}

static State create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const EliminationList& elimination,
      const piece::Piece& next) {
    return State(board, score_board, elimination, next);
}

TEST(StateTest, caracteristics) {
    EXPECT_TRUE(std::is_move_assignable<State>::value);
    EXPECT_TRUE(std::is_move_constructible<State>::value);
    EXPECT_FALSE(std::is_copy_assignable<State>::value);
    EXPECT_FALSE(std::is_copy_constructible<State>::value);
}

TEST(StateTest, create) {
    using namespace std::rel_ops;
    const piece::SharedConstBoard board1 = std::make_shared<piece::Board>(10, 20, gui::Color::WHITE);
    const piece::SharedConstBoard board2 = std::make_shared<piece::Board>(11, 20, gui::Color::WHITE);
    const piece::SharedConstBoard board3 = std::make_shared<piece::Board>(10, 21, gui::Color::WHITE);
    const piece::SharedConstBoard board4 = std::make_shared<piece::Board>(10, 20, gui::Color::BLUE);
    const piece::SharedConstBoard board5 = std::make_shared<piece::Board>(12, 21, gui::Color::WHITE);
    const piece::SharedConstBoard board6 = std::make_shared<piece::Board>(13, 20, gui::Color::BLUE);
    const state::ScoreBoard score_board1(state::Score(25));
    const state::ScoreBoard score_board2(state::Score(38), state::Score(34));
    const state::ScoreBoard score_board3(state::Score(38), state::Score(35));
    const state::ScoreBoard score_board4(state::Score(39), state::Score(34));
    const state::ScoreBoard score_board5(state::Score(40), state::Score(35));
    const state::ScoreBoard score_board6(state::Score(41), state::Score(34));
    const piece::Piece piece3 = piece::mck::create_piece_ascending(12);
    const piece::Piece piece4 = piece::mck::create_piece_ascending(15);
    const piece::Piece next3 = piece::mck::create_piece_ascending(17);
    const piece::Piece next4 = piece::mck::create_piece_ascending(23);
    const piece::PiecePosition position3(board3, 2, 4);
    const piece::PiecePosition position4(board4, 3, 4);
    const EliminationList elim5 = { { 1, 2 }, { 3, 4 } };
    const EliminationList elim6 = { { 5, 6 }, { 3, 4 } };
    const piece::Piece next5 = piece::mck::create_piece_ascending(19);
    const piece::Piece next6 = piece::mck::create_piece_ascending(21);

    const State state1 = create_state(board1, score_board1);
    EXPECT_TRUE(state1.board() == board1);
    EXPECT_TRUE(state1.score_board() == score_board1);
    EXPECT_TRUE(state1.has_piece_falling() == false);
    EXPECT_THROW(state1.piece(), std::logic_error);
    EXPECT_THROW(state1.piece_position(), std::logic_error);
    EXPECT_TRUE(state1.elimination_list().empty());
    EXPECT_TRUE(state1.has_next() == false);
    EXPECT_THROW(state1.next(), std::logic_error);

    const State state2 = create_state(board2, score_board2);
    EXPECT_TRUE(state2.board() == board2);
    EXPECT_TRUE(state2.score_board() == score_board2);
    EXPECT_TRUE(state2.has_piece_falling() == false);
    EXPECT_THROW(state2.piece(), std::logic_error);
    EXPECT_THROW(state2.piece_position(), std::logic_error);
    EXPECT_TRUE(state2.elimination_list().empty());
    EXPECT_TRUE(state2.has_next() == false);
    EXPECT_THROW(state2.next(), std::logic_error);

    const State state3 = create_state(board3, score_board3, piece3, position3, next3);
    EXPECT_TRUE(state3.board() == board3);
    EXPECT_TRUE(state3.score_board() == score_board3);
    EXPECT_TRUE(state3.has_piece_falling() == true);
    EXPECT_TRUE(state3.piece() == piece3);
    EXPECT_TRUE(state3.piece_position() == position3);
    EXPECT_TRUE(state3.elimination_list().empty());
    EXPECT_TRUE(state3.has_next() == true);
    EXPECT_TRUE(state3.next() == next3);

    const State state4 = create_state(board4, score_board4, piece4, position4, next4);
    EXPECT_TRUE(state4.board() == board4);
    EXPECT_TRUE(state4.score_board() == score_board4);
    EXPECT_TRUE(state4.has_piece_falling() == true);
    EXPECT_TRUE(state4.piece() == piece4);
    EXPECT_TRUE(state4.piece_position() == position4);
    EXPECT_TRUE(state4.elimination_list().empty());
    EXPECT_TRUE(state4.has_next() == true);
    EXPECT_TRUE(state4.next() == next4);

    const State state5 = create_state(board5, score_board5, elim5, next5);
    EXPECT_TRUE(state5.board() == board5);
    EXPECT_TRUE(state5.score_board() == score_board5);
    EXPECT_TRUE(state5.has_piece_falling() == false);
    EXPECT_THROW(state5.piece(), std::logic_error);
    EXPECT_THROW(state5.piece_position(), std::logic_error);
    EXPECT_TRUE(state5.elimination_list() == elim5);
    EXPECT_TRUE(state5.has_next() == true);
    EXPECT_TRUE(state5.next() == next5);

    const State state6 = create_state(board6, score_board6, elim6, next6);
    EXPECT_TRUE(state6.board() == board6);
    EXPECT_TRUE(state6.score_board() == score_board6);
    EXPECT_TRUE(state6.has_piece_falling() == false);
    EXPECT_THROW(state6.piece(), std::logic_error);
    EXPECT_THROW(state6.piece_position(), std::logic_error);
    EXPECT_TRUE(state6.elimination_list() == elim6);
    EXPECT_TRUE(state6.has_next() == true);
    EXPECT_TRUE(state6.next() == next6);

    auto p1 = create_state(board1, score_board1);
    auto p2 = create_state(board2, score_board2);
    EXPECT_TRUE(p1 == state1);
    EXPECT_TRUE(p2 == state2);
    EXPECT_TRUE(p1 != state2);
    EXPECT_TRUE(p2 != state1);
}
}
}
