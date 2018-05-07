#include "MatchControllerTest.h"

#include "../mck/game/utilgame.h"
#include "../mck/piece/PieceCreatorCycle.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"

namespace game {
namespace tst {
void MatchControllerTest::SetUp() {
    input_reader_mock = new mck::InputReaderMock();
    InputReaderPtr input_reader(input_reader_mock);
    board = std::make_shared<piece::Board>(8, 16);
}

void MatchControllerTest::TearDown() {
}

namespace {
const piece::Piece DEFAULT_PIECE = piece::mck::create_piece_ascending(0);

piece::PieceCreatorPtr piece_creator(const std::vector<piece::Piece>& pieces = { DEFAULT_PIECE }) {
    return std::make_unique<piece::mck::PieceCreatorCycle>(pieces);
}
}

TEST_F(MatchControllerTest, initial_state) {
    const MatchController controller(board, 157, piece_creator());
    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    EXPECT_NE(dynamic_cast<const state::StateInitial*>(state.get()), nullptr);
    EXPECT_EQ(*state->board(), *board);
    EXPECT_EQ(state->score_board(), state::ScoreBoard(state::Score(157), state::Score(0)));
}

TEST_F(MatchControllerTest, tick_add_a_piece) {
    MatchController controller(board, 178, piece_creator());
    controller.tick();

    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    EXPECT_NE(dynamic_cast<const state::StateFalling*>(state.get()), nullptr);
    EXPECT_EQ(*state->board(), *board);
    EXPECT_EQ(state->score_board(), state::ScoreBoard(state::Score(178), state::Score(0)));
    ASSERT_TRUE(state->has_piece_falling());
    EXPECT_EQ(state->piece(), DEFAULT_PIECE);
}

TEST_F(MatchControllerTest, tick_step_a_piece_falling) {
    MatchController controller(board, 178, piece_creator());
    controller.tick();
    auto position = controller.state()->piece_position();
    EXPECT_EQ(position.row(), 0u);
    EXPECT_EQ(position.sub_row(), 0u);

    controller.tick();
    position.step_down();
    EXPECT_EQ(controller.state()->piece_position(), position);
}

TEST_F(MatchControllerTest, tick_roll_a_piece_falling) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_ascending(0),
    };
    MatchController controller(board, 178, piece_creator(pieces));
    controller.tick();
    auto piece = controller.state()->piece();
    EXPECT_EQ(piece, pieces[0]);

    controller.process(EMessage::RollDown);
    pieces[0].roll_down();

    piece = controller.state()->piece();
    EXPECT_EQ(piece, pieces[0]);
}

namespace {
void drop_piece_to_bottom(MatchController& controller,
      piece::Board& expected_board,
      const piece::Board& board,
      const piece::Piece& piece) {
    const size_t steps_to_bottom = (board.height() - piece::PIECE_SIZE) * 4;
    controller.tick();

    for (size_t i = 0; i < steps_to_bottom; ++i)
        controller.tick();

    piece::mck::fix(expected_board, piece, controller.state()->piece_position());

    controller.tick(); // fix the piece in the board and remove it
}
}

TEST_F(MatchControllerTest, tick_get_to_the_bottom_fixes_tiles_in_board) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_ascending(0),
    };
    auto expected_board = piece::mck::dup(*board);

    MatchController controller(board, 178, piece_creator(pieces));
    drop_piece_to_bottom(controller, *expected_board, *board, pieces[0]);

    EXPECT_EQ(*board, *expected_board);
    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    EXPECT_NE(dynamic_cast<const state::StateInitial*>(state.get()), nullptr);
}

TEST_F(MatchControllerTest, tick_get_to_the_bottom_returns_list) {
    std::vector<piece::Piece> pieces = {
		piece::mck::create_piece_step(1, 0),
		piece::mck::create_piece_ascending(2),
    };
    auto expected_board = piece::mck::dup(*board);

    MatchController controller(board, 178, piece_creator(pieces));
    drop_piece_to_bottom(controller, *expected_board, *board, pieces[0]);

    EXPECT_EQ(*board, *expected_board);
    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    const auto elimination_state = dynamic_cast<const state::StateElimination*>(state.get());
    ASSERT_NE(elimination_state, nullptr);
    const auto expected_elimination = board->elimination_list();
    EXPECT_EQ(elimination_state->elimination_list(), expected_elimination);
    EXPECT_EQ(elimination_state->next(), pieces[0]);
}
}
}
