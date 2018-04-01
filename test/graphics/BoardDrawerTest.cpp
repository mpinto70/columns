#include "../mck/graphics/WindowMock.h"
#include "../mck/graphics/utilgraphics.h"
#include "../mck/state/utilstate.h"

#include "graphics/BoardDrawer.h"
#include "util/Random.h"

#include <gtest/gtest.h>

namespace graphics {
namespace tst {
using ::testing::StrictMock;

TEST(BoardDrawerTest, draw_empty_board) {
    StrictMock<mck::WindowMock> window_mock("name", 125, 500);
    const auto drawer = mck::create_board_drawer();
    const auto state = state::create_state(piece::Board{ 8, 24, gui::Color::WHITE });
    ::graphics::mck::prepare_board_draw(drawer, window_mock, state, gui::Color::GRAY);
    drawer.draw(window_mock, state);
}

TEST(BoardDrawerTest, draw_full_board) {
    const auto drawer = mck::create_board_drawer();
    const std::vector<gui::Color> POSSIBLES = { gui::Color::RED, gui::Color::BLUE, gui::Color::GREEN };
    piece::Board board{ 8, 24, gui::Color::GRAY };
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 23; ++j) {
            const size_t idx = util::Random::get(POSSIBLES.size() - 1);
            board.at(i, j) = POSSIBLES[idx];
        }
    }
    const auto state = state::create_state(board);
    StrictMock<mck::WindowMock> window_mock("name", 125, 500);
    ::graphics::mck::prepare_board_draw(drawer, window_mock, state, gui::Color::GRAY);
    drawer.draw(window_mock, state);
}
}
}
