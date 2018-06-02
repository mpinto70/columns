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

TEST(StateTest, create_puts_in_initial) {
    using namespace std::rel_ops;
    const piece::SharedConstBoard board1 = std::make_shared<piece::Board>(10, 20);
    const piece::SharedConstBoard board2 = std::make_shared<piece::Board>(11, 20);
    SharedScoreBoard score_board1 = std::make_shared<ScoreBoard>(Score(25));
    SharedScoreBoard score_board2 = std::make_shared<ScoreBoard>(Score(38), Score(34));

    const State state1(board1, score_board1);
    EXPECT_EQ(state1.state(), EState::CLEAN);
    EXPECT_EQ(state1.board(), *board1);
    EXPECT_EQ(state1.score_board(), *score_board1);
    EXPECT_FALSE(state1.has_piece_falling());
    EXPECT_THROW(state1.piece(), std::logic_error);
    EXPECT_THROW(state1.piece_position(), std::logic_error);
    EXPECT_FALSE(state1.has_elimination_list());
    EXPECT_THROW(state1.elimination_list(), std::logic_error);
    EXPECT_FALSE(state1.has_next());
    EXPECT_THROW(state1.next(), std::logic_error);

    const State state2(board2, score_board2);
    EXPECT_EQ(state2.state(), EState::CLEAN);
    EXPECT_EQ(state2.board(), *board2);
    EXPECT_EQ(state2.score_board(), *score_board2);
    EXPECT_FALSE(state2.has_piece_falling());
    EXPECT_THROW(state2.piece(), std::logic_error);
    EXPECT_THROW(state2.piece_position(), std::logic_error);
    EXPECT_FALSE(state2.has_elimination_list());
    EXPECT_THROW(state2.elimination_list(), std::logic_error);
    EXPECT_FALSE(state2.has_next());
    EXPECT_THROW(state2.next(), std::logic_error);
}

TEST(StateTest, transition_to_falling) {
    using namespace std::rel_ops;
    const piece::SharedConstBoard board = std::make_shared<piece::Board>(10, 20);
    SharedScoreBoard score_board = std::make_shared<ScoreBoard>(Score(25));
    const piece::Piece next = piece::mck::create_piece_ascending(17);
    const piece::Piece piece = piece::mck::create_piece_ascending(12);
    const piece::Position position(2);

    State state(board, score_board);

    state.to_falling(next, piece, position);
    EXPECT_EQ(state.state(), EState::FALLING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.score_board(), *score_board);
    EXPECT_TRUE(state.has_piece_falling());
    EXPECT_EQ(state.piece(), piece);
    EXPECT_EQ(state.piece_position(), position);
    EXPECT_FALSE(state.has_elimination_list());
    EXPECT_THROW(state.elimination_list(), std::logic_error);
    EXPECT_TRUE(state.has_next());
    EXPECT_EQ(state.next(), next);
}

TEST(StateTest, transition_still_falling) {
    using namespace std::rel_ops;
    const piece::SharedConstBoard board = std::make_shared<piece::Board>(10, 20);
    SharedScoreBoard score_board = std::make_shared<ScoreBoard>(Score(25));
    const piece::Piece next = piece::mck::create_piece_ascending(17);
    const piece::Piece piece1 = piece::mck::create_piece_ascending(12);
    const piece::Position position1(2);
    const piece::Piece piece2 = piece::mck::create_piece_ascending(13);
    const piece::Position position2(3);

    State state(board, score_board);

    state.to_falling(next, piece1, position1);

    state.still_falling(piece2, position2);
    EXPECT_EQ(state.state(), EState::FALLING);
    EXPECT_EQ(state.score_board(), *score_board);
    EXPECT_TRUE(state.has_piece_falling());
    EXPECT_EQ(state.piece(), piece2);
    EXPECT_EQ(state.piece_position(), position2);
    EXPECT_FALSE(state.has_elimination_list());
    EXPECT_THROW(state.elimination_list(), std::logic_error);
    EXPECT_TRUE(state.has_next());
    EXPECT_EQ(state.next(), next);
}

TEST(StateTest, transition_to_eliminating) {
    using namespace std::rel_ops;
    piece::SharedBoard board = std::make_shared<piece::Board>(10, 20);
    SharedScoreBoard score_board = std::make_shared<ScoreBoard>(Score(25));
    const piece::Piece next = piece::mck::create_piece_ascending(17);
    const piece::Piece piece = piece::mck::create_piece_ascending(12);
    const piece::Position position(2);

    State state(board, score_board);
    state.to_falling(next, piece, position);

    board->at(9, 0) = gui::Color::BLUE;
    board->at(9, 1) = gui::Color::BLUE;
    board->at(9, 2) = gui::Color::BLUE;

    EXPECT_FALSE(board->elimination_list().empty());

    state.to_elimination();

    EXPECT_EQ(state.state(), EState::ELIMINATING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.score_board(), *score_board);
    EXPECT_FALSE(state.has_piece_falling());
    EXPECT_THROW(state.piece(), std::logic_error);
    EXPECT_THROW(state.piece_position(), std::logic_error);
    EXPECT_TRUE(state.has_elimination_list());
    EXPECT_EQ(state.elimination_list(), board->elimination_list());
    EXPECT_TRUE(state.has_next());
    EXPECT_EQ(state.next(), next);
}

TEST(StateTest, transition_to_eliminated) {
    using namespace std::rel_ops;
    piece::SharedBoard board = std::make_shared<piece::Board>(10, 20);
    SharedScoreBoard score_board = std::make_shared<ScoreBoard>(Score(25));
    const piece::Piece next = piece::mck::create_piece_ascending(17);
    const piece::Piece piece = piece::mck::create_piece_ascending(12);
    const piece::Position position(2);

    State state(board, score_board);
    state.to_falling(next, piece, position);

    EXPECT_TRUE(board->elimination_list().empty());

    state.to_elimination();

    EXPECT_EQ(state.state(), EState::ELIMINATED);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.score_board(), *score_board);
    EXPECT_FALSE(state.has_piece_falling());
    EXPECT_THROW(state.piece(), std::logic_error);
    EXPECT_THROW(state.piece_position(), std::logic_error);
    EXPECT_FALSE(state.has_elimination_list());
    EXPECT_THROW(state.elimination_list(), std::logic_error);
    EXPECT_TRUE(state.has_next());
    EXPECT_EQ(state.next(), next);
}
}
}
