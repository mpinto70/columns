#include "MatchControllerTest.h"

#include "../mck/game/utilgame.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"

namespace game {
namespace tst {
using ::testing::Return;

void MatchControllerTest::SetUp() {
    input_reader_mock = new mck::InputReaderMock();
    InputReaderPtr input_reader(input_reader_mock);
    board = std::make_shared<piece::Board>(8, 16);
}

void MatchControllerTest::TearDown() {
}

TEST_F(MatchControllerTest, initial_state) {
    const MatchController controller(board, 157);
    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    EXPECT_NE(dynamic_cast<const state::StateInitial*>(state.get()), nullptr);
    EXPECT_EQ(*state->board(), *board);
    EXPECT_EQ(state->score_board(), state::ScoreBoard(state::Score(157), state::Score(0)));
}

TEST_F(MatchControllerTest, tick_add_a_piece) {
    MatchController controller(board, 178);
    controller.tick();

    auto state = controller.state();
    ASSERT_NE(state.get(), nullptr);
    EXPECT_NE(dynamic_cast<const state::StateFalling*>(state.get()), nullptr);
    EXPECT_EQ(*state->board(), *board);
    EXPECT_EQ(state->score_board(), state::ScoreBoard(state::Score(178), state::Score(0)));
    ASSERT_TRUE(state->has_piece_falling());
}

TEST_F(MatchControllerTest, tick_step_a_piece_falling) {
    MatchController controller(board, 178);
    controller.tick();
    auto position = controller.state()->piece_position();
    EXPECT_EQ(position.row(), 0u);
    EXPECT_EQ(position.sub_row(), 0u);

    controller.tick();
    position.step_down();
    EXPECT_EQ(controller.state()->piece_position(), position);
}

}
}
