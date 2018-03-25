#include "BoardDrawerTest.h"

#include "../mck/graphics/utilgraphics.h"
#include "../mck/state/utilstate.h"

#include "graphics/BoardDrawer.h"
#include "util/Random.h"

namespace graphics {
namespace tst {

void BoardDrawerTest::SetUp() {
    window_mock.reset(new StrictMock<mck::WindowMock>("name", 125, 500));
}

void BoardDrawerTest::TearDown() {
    window_mock.reset();
}

TEST_F(BoardDrawerTest, draw_empty_board) {
    const auto drawer = mck::create_board_drawer();
    const auto state = state::create_state(piece::Board{ 8, 24, gui::WHITE });
    ::graphics::mck::prepare_board_draw(drawer, *window_mock, state, gui::GRAY);
    drawer.draw(*window_mock, state, gui::GRAY);
}

TEST_F(BoardDrawerTest, draw_full_board) {
    const auto drawer = mck::create_board_drawer();
    const std::vector<gui::Color> POSSIBLES = { gui::RED, gui::BLUE, gui::GREEN };
    piece::Board board{ 8, 24, gui::GRAY };
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 23; ++j) {
            const size_t idx = util::Random::get(POSSIBLES.size() - 1);
            board.at(i, j) = POSSIBLES[idx];
        }
    }
    const auto state = state::create_state(board);
    ::graphics::mck::prepare_board_draw(drawer, *window_mock, state, gui::GRAY);
    drawer.draw(*window_mock, state, gui::GRAY);
}
}
}
