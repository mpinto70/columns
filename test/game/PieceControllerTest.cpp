#include "PieceControllerTest.h"

#include "../mck/piece/utilpiece.h"

#include "game/Messages.h"
#include "game/PieceController.h"
#include "piece/Board.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <thread>

namespace game {
namespace tst {

PieceController PieceControllerTest::create_controller(size_t width,
      size_t height) {
    board = std::make_shared<piece::Board>(width, height);
    return PieceController(board);
}

PieceController PieceControllerTest::create_controller_with_piece(size_t column,
      size_t width,
      size_t height) {
    PieceController controller = create_controller(width, height);
    piece::Piece piece = piece::mck::create_piece_ascending(2);
    controller.add(piece, column);
    return controller;
}

void PieceControllerTest::fill_column(size_t column,
      size_t initial_row,
      gui::Color color) {
    for (size_t r = initial_row; r < board->height(); ++r) {
        board->at(column, r) = color;
    }
}

TEST_F(PieceControllerTest, create_there_is_no_piece) {
    PieceController controller = create_controller();
    EXPECT_FALSE(controller.has_piece());
    EXPECT_NO_THROW(controller.position());
    EXPECT_NO_THROW(controller.piece());
    EXPECT_NO_THROW(controller.remove());
    EXPECT_NO_THROW(controller.step());
    EXPECT_NO_THROW(controller.process(EMessage::RollDown));
}

TEST_F(PieceControllerTest, add_piece) {
    PieceController controller = create_controller();
    piece::Piece piece = piece::mck::create_piece_ascending(3);
    controller.add(piece, 2);
    EXPECT_TRUE(controller.has_piece());
    EXPECT_EQ(controller.position().row(), 0u);
    EXPECT_EQ(controller.position().sub_row(), 0u);
    EXPECT_EQ(controller.position().column(), 2u);
    EXPECT_EQ(controller.piece(), piece);
}

TEST_F(PieceControllerTest, added_piece_move_left) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();
    const auto piece = controller.piece();

    position.move_left();
    position.move_left();
    controller.process(EMessage::MoveLeft);
    controller.process(EMessage::MoveLeft);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_left_when_at_left) {
    PieceController controller = create_controller_with_piece(0);
    const auto position = controller.position();
    const auto piece = controller.piece();

    controller.process(EMessage::MoveLeft);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_left_when_tile_at_left_is_used) {
    PieceController controller = create_controller_with_piece(4);
    const auto position = controller.position();
    const auto piece = controller.piece();
    fill_column(3, piece::PIECE_SIZE - 1, gui::Color::BLUE);

    controller.process(EMessage::MoveLeft);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_left_when_tile_at_below_left_is_used_and_piece_is_sub_stepped) {
    PieceController controller = create_controller_with_piece(4, 8, 10);
    fill_column(3, piece::PIECE_SIZE, gui::Color::BLUE);

    EXPECT_TRUE(controller.step());
    const auto position = controller.position();
    const auto piece = controller.piece();
    controller.process(EMessage::MoveLeft);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_move_right) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();
    const auto piece = controller.piece();

    position.move_right();
    position.move_right();
    controller.process(EMessage::MoveRight);
    controller.process(EMessage::MoveRight);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_right_when_at_right) {
    PieceController controller = create_controller_with_piece(7, 8);
    const auto position = controller.position();
    const auto piece = controller.piece();

    controller.process(EMessage::MoveRight);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_right_when_tile_at_right_is_used) {
    PieceController controller = create_controller_with_piece(4);
    const auto position = controller.position();
    const auto piece = controller.piece();
    fill_column(5, piece::PIECE_SIZE - 1, gui::Color::BLUE);

    controller.process(EMessage::MoveRight);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_roll_up) {
    PieceController controller = create_controller_with_piece();
    const auto position = controller.position();
    auto piece = controller.piece();

    piece.roll_up();

    controller.process(EMessage::RollUp);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_roll_down) {
    PieceController controller = create_controller_with_piece();
    const auto position = controller.position();
    auto piece = controller.piece();

    piece.roll_down();

    controller.process(EMessage::RollDown);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_right_when_tile_at_right_is_used_and_piece_is_sub_stepped) {
    PieceController controller = create_controller_with_piece(4, 8, 10);
    fill_column(5, piece::PIECE_SIZE, gui::Color::BLUE);

    EXPECT_TRUE(controller.step());
    const auto position = controller.position();
    const auto piece = controller.piece();

    controller.process(EMessage::MoveRight);
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_step_moves_down) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();
    const auto piece = controller.piece();

    position.step_down();
    position.step_down();
    EXPECT_TRUE(controller.step());
    EXPECT_TRUE(controller.step());
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_step_doesnt_move_down_when_at_bottom) {
    PieceController controller = create_controller_with_piece(4, 8, 10);
    auto position = controller.position();

    size_t steps = 0;
    while (position.row() < 10 - piece::PIECE_SIZE) {
        position.step_down();
        ++steps;
    }
    for (size_t i = 0; i < steps; ++i) {
        EXPECT_TRUE(controller.step());
    }
    EXPECT_FALSE(controller.step());
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_step_doesnt_move_down_when_over_used_tile) {
    PieceController controller = create_controller_with_piece(4, 8, 10);
    fill_column(4, piece::PIECE_SIZE);
    const auto position = controller.position();

    EXPECT_FALSE(controller.step());
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, step_becomes_faster_after_drop_down) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();

    position.step_down();
    EXPECT_TRUE(controller.step());
    EXPECT_EQ(controller.position(), position);

    controller.process(EMessage::DropDown);

    position.step_down();
    position.step_down();
    position.step_down();
    position.step_down();
    position.step_down();
    EXPECT_TRUE(controller.step());
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, step_restore_to_original_for_new_piece) {
    PieceController controller = create_controller_with_piece(3);
    const auto piece = controller.piece();
    auto position = controller.position();

    controller.process(EMessage::DropDown);

    position.step_down();
    position.step_down();
    position.step_down();
    position.step_down();
    position.step_down();
    EXPECT_TRUE(controller.step());
    EXPECT_EQ(controller.position(), position);

    controller.remove();

    controller.add(piece, 3);

    position = controller.position();

    position.step_down();
    EXPECT_TRUE(controller.step());
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, accelerated_steps_does_not_overflow) {
    PieceController controller = create_controller_with_piece(3, 6, 11);
    auto position = controller.position();

    controller.process(EMessage::DropDown);

    while (controller.step()) {
        position.step_down();
        position.step_down();
        position.step_down();
        position.step_down();
        position.step_down();
        EXPECT_EQ(controller.position(), position);
    }
    position = controller.position();
    EXPECT_EQ(position.sub_row(), 0u);
    EXPECT_EQ(position.row(), 11u - piece::PIECE_SIZE);
}

TEST_F(PieceControllerTest, remove_with_added_piece_removes) {
    PieceController controller = create_controller(8, 16);
    piece::Piece added = piece::mck::create_piece_ascending(4);
    piece::Position position(3);
    controller.add(added, 3);
    EXPECT_TRUE(controller.has_piece());
    EXPECT_EQ(controller.piece(), added);
    EXPECT_EQ(controller.position(), position);

    for (size_t i = 0; i < 9; ++i) {
        controller.step();
        position.step_down();
    }

    controller.process(EMessage::RollDown);
    controller.process(EMessage::RollDown);
    added.roll_down();
    added.roll_down();

    const auto removed = controller.remove();

    EXPECT_EQ(removed.first, added);
    EXPECT_EQ(removed.second, position);
    EXPECT_FALSE(controller.has_piece());
}
}
}
