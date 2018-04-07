#include "game/PieceController.h"
#include "piece/Board.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace game {
namespace tst {
TEST(PieceControllerTest, create_there_is_no_piece) {
    piece::SharedBoard board = std::make_shared<piece::Board>(16, 8, gui::Color::WHITE);
    PieceController controller(board);
    EXPECT_FALSE(controller.has_piece());
    EXPECT_THROW(controller.piece_position(), std::runtime_error);
    EXPECT_FALSE(controller.step());
}
}
}
