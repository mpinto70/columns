#include "MatchControllerTest.h"

#include "../../mck/piece/CreatorCycle.h"
#include "../mck/game/utilgame.h"
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

piece::CreatorPtr piece_creator(const std::vector<piece::Piece>& pieces = { DEFAULT_PIECE },
      const std::vector<size_t>& columns = { 1 }) {
    return piece::mck::create_cycle_creator(pieces, columns);
}
}

TEST_F(MatchControllerTest, initial_state) {
    const MatchController controller(board, 157, piece_creator());
    const state::ScoreBoard score_board(state::Score(157), state::Score(0));

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::CLEAN);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.score_board(), score_board);
}

TEST_F(MatchControllerTest, tick_add_a_piece) {
    MatchController controller(board, 178, piece_creator());
    controller.tick();
    const state::ScoreBoard score_board(state::Score(178), state::Score(0));

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::FALLING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.score_board(), score_board);
    EXPECT_EQ(state.piece(), DEFAULT_PIECE);
}

TEST_F(MatchControllerTest, tick_step_a_piece_falling) {
    MatchController controller(board, 178, piece_creator());
    controller.tick();
    auto position = controller.state().piece_position();
    EXPECT_EQ(position.row(), 0u);
    EXPECT_EQ(position.sub_row(), 0u);

    controller.tick();
    position.step_down();

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::FALLING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.piece_position(), position);
}

TEST_F(MatchControllerTest, tick_roll_a_piece_falling) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_ascending(0),
    };
    MatchController controller(board, 178, piece_creator(pieces));
    controller.tick();
    auto piece = controller.state().piece();
    EXPECT_EQ(piece, pieces[0]);

    controller.process(EMessage::RollDown);
    pieces[0].roll_down();

    piece = controller.state().piece();
    EXPECT_EQ(piece, pieces[0]);

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::FALLING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.piece(), pieces[0]);
}

namespace {
std::unique_ptr<piece::Board> drop_piece_to_bottom(MatchController& controller,
      const piece::Board& board,
      const piece::Piece& piece) {
    auto expected_board = piece::mck::dup(board);
    const size_t steps_to_bottom = (board.height() - piece::PIECE_SIZE) * 5;
    controller.tick();

    for (size_t i = 0; i < steps_to_bottom; ++i)
        controller.tick();

    piece::mck::fix(*expected_board, piece, controller.state().piece_position());

    controller.tick(); // fix the piece in the board and remove it

    return expected_board;
}
}

TEST_F(MatchControllerTest, tick_get_to_the_bottom_fixes_tiles_in_board) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_ascending(0),
    };

    MatchController controller(board, 178, piece_creator(pieces));
    auto expected_board = drop_piece_to_bottom(controller, *board, pieces[0]);

    EXPECT_EQ(*board, *expected_board);

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::ELIMINATED);
    EXPECT_EQ(state.board(), *board);
}

TEST_F(MatchControllerTest, tick_get_to_the_bottom_returns_list) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_step(1, 0),
        piece::mck::create_piece_ascending(2),
    };
    MatchController controller(board, 178, piece_creator(pieces));
    auto expected_board = drop_piece_to_bottom(controller, *board, pieces[0]);

    EXPECT_EQ(*board, *expected_board);
    const auto expected_elimination = board->elimination_list();

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::ELIMINATING);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.elimination_list(), expected_elimination);
    EXPECT_EQ(state.next(), pieces[1]);
}

TEST_F(MatchControllerTest, tick_after_elimination_list_eliminates) {
    std::vector<piece::Piece> pieces = {
        piece::mck::create_piece_step(1, 0),
        piece::mck::create_piece_ascending(2),
        piece::mck::create_piece_ascending(3),
    };

    auto expected_board = piece::mck::dup(*board);
    MatchController controller(board, 178, piece_creator(pieces));
    drop_piece_to_bottom(controller, *board, pieces[0]);

    controller.tick();

    EXPECT_EQ(*board, *expected_board);
    const auto elimination_list = board->elimination_list();
    EXPECT_TRUE(elimination_list.empty());

    const auto& state = controller.state();
    EXPECT_EQ(state.state(), state::EState::ELIMINATED);
    EXPECT_EQ(state.board(), *board);
    EXPECT_EQ(state.next(), pieces[1]);
}
}
}
