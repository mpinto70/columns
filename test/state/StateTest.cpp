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

TEST(StateTest, caracteristics) {
    EXPECT_FALSE(std::is_move_assignable<State>::value);
    EXPECT_FALSE(std::is_move_constructible<State>::value);
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

    const StatePtr state1 = mck::create_state(board1, score_board1);
    EXPECT_EQ(state1->board(), board1);
    EXPECT_EQ(state1->score_board(), score_board1);
    EXPECT_FALSE(state1->has_piece_falling());
    EXPECT_THROW(state1->piece(), std::logic_error);
    EXPECT_THROW(state1->piece_position(), std::logic_error);
    EXPECT_FALSE(state1->has_elimination_list());
    EXPECT_THROW(state1->elimination_list(), std::logic_error);
    EXPECT_FALSE(state1->has_next());
    EXPECT_THROW(state1->next(), std::logic_error);

    const StatePtr state2 = mck::create_state(board2, score_board2);
    EXPECT_EQ(state2->board(), board2);
    EXPECT_EQ(state2->score_board(), score_board2);
    EXPECT_FALSE(state2->has_piece_falling());
    EXPECT_THROW(state2->piece(), std::logic_error);
    EXPECT_THROW(state2->piece_position(), std::logic_error);
    EXPECT_FALSE(state2->has_elimination_list());
    EXPECT_THROW(state2->elimination_list(), std::logic_error);
    EXPECT_FALSE(state2->has_next());
    EXPECT_THROW(state2->next(), std::logic_error);

    const StatePtr state3 = mck::create_state(board3, score_board3, next3, piece3, position3);
    EXPECT_EQ(state3->board(), board3);
    EXPECT_EQ(state3->score_board(), score_board3);
    EXPECT_TRUE(state3->has_piece_falling());
    EXPECT_EQ(state3->piece(), piece3);
    EXPECT_EQ(state3->piece_position(), position3);
    EXPECT_FALSE(state3->has_elimination_list());
    EXPECT_THROW(state3->elimination_list(), std::logic_error);
    EXPECT_TRUE(state3->has_next());
    EXPECT_EQ(state3->next(), next3);

    const StatePtr state4 = mck::create_state(board4, score_board4, next4, piece4, position4);
    EXPECT_EQ(state4->board(), board4);
    EXPECT_EQ(state4->score_board(), score_board4);
    EXPECT_TRUE(state4->has_piece_falling());
    EXPECT_EQ(state4->piece(), piece4);
    EXPECT_EQ(state4->piece_position(), position4);
    EXPECT_FALSE(state4->has_elimination_list());
    EXPECT_THROW(state4->elimination_list(), std::logic_error);
    EXPECT_TRUE(state4->has_next());
    EXPECT_EQ(state4->next(), next4);

    const StatePtr state5 = mck::create_state(board5, score_board5, next5, elim5);
    EXPECT_EQ(state5->board(), board5);
    EXPECT_EQ(state5->score_board(), score_board5);
    EXPECT_FALSE(state5->has_piece_falling());
    EXPECT_THROW(state5->piece(), std::logic_error);
    EXPECT_THROW(state5->piece_position(), std::logic_error);
    EXPECT_TRUE(state5->has_elimination_list());
    EXPECT_EQ(state5->elimination_list(), elim5);
    EXPECT_TRUE(state5->has_next());
    EXPECT_EQ(state5->next(), next5);

    const StatePtr state6 = mck::create_state(board6, score_board6, next6, elim6);
    EXPECT_EQ(state6->board(), board6);
    EXPECT_EQ(state6->score_board(), score_board6);
    EXPECT_FALSE(state6->has_piece_falling());
    EXPECT_THROW(state6->piece(), std::logic_error);
    EXPECT_THROW(state6->piece_position(), std::logic_error);
    EXPECT_TRUE(state6->has_elimination_list());
    EXPECT_EQ(state6->elimination_list(), elim6);
    EXPECT_TRUE(state6->has_next());
    EXPECT_EQ(state6->next(), next6);

    auto p1 = mck::create_state(board1, score_board1);
    auto p2 = mck::create_state(board2, score_board2);
    EXPECT_EQ(*p1, *state1);
    EXPECT_EQ(*p2, *state2);
    EXPECT_NE(*p1, *state2);
    EXPECT_NE(*p2, *state1);
}
}
}
