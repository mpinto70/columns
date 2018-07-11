#pragma once

#include "game/PieceController.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
class PieceControllerTest : public ::testing::Test {
protected:
    piece::SharedBoard board;

    PieceController create_controller(size_t width = 8,
          size_t height = 16);

    PieceController create_controller_with_piece(size_t column = 4,
          size_t width = 8,
          size_t height = 16);

    void fill_column(size_t column,
          size_t initial_row = piece::PIECE_SIZE - 1,
          gui::Color color = gui::Color::BLUE);
};
}
}
