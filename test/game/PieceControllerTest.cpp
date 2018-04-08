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
      size_t height,
      size_t sub_row) {
    board = std::make_shared<piece::Board>(width, height, gui::Color::WHITE);
    return PieceController(board, sub_row);
}

PieceController PieceControllerTest::create_controller_with_piece(size_t column,
      size_t width,
      size_t height,
      size_t sub_row) {
    PieceController controller = create_controller(width, height, sub_row);
    piece::Piece piece = piece::Piece::create({ gui::Color::YELLOW, gui::Color::BLUE, gui::Color::RED });
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
    EXPECT_THROW(controller.position(), std::runtime_error);
    EXPECT_THROW(controller.piece(), std::runtime_error);
}

TEST_F(PieceControllerTest, add_piece) {
    PieceController controller = create_controller();
    piece::Piece piece = piece::Piece::create({ gui::Color::YELLOW, gui::Color::BLUE, gui::Color::RED });
    controller.add(piece, 2);
    EXPECT_TRUE(controller.has_piece());
    EXPECT_EQ(controller.position().row(), 0u);
    EXPECT_EQ(controller.position().sub_row(), 0u);
    EXPECT_EQ(controller.position().column(), 2u);
    EXPECT_EQ(controller.piece(), piece);
}

TEST_F(PieceControllerTest, add_piece_at_occupied_column_thows) {
    PieceController controller = create_controller();
    piece::Piece piece = piece::Piece::create({ gui::Color::YELLOW, gui::Color::BLUE, gui::Color::RED });
    fill_column(2, piece::PIECE_SIZE - 1, gui::Color::BLUE);
    EXPECT_THROW(controller.add(piece, 2), std::runtime_error);
    EXPECT_NO_THROW(controller.add(piece, 3));
}

TEST_F(PieceControllerTest, added_piece_move_left) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();
    const auto piece = controller.piece();

    position.move_left();
    position.move_left();
    controller.process({ EMessage::MoveLeft, EMessage::MoveLeft });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_left_when_at_left) {
    PieceController controller = create_controller_with_piece(0);
    const auto position = controller.position();
    const auto piece = controller.piece();

    controller.process({ EMessage::MoveLeft, EMessage::MoveLeft });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_left_when_tile_at_left_is_used) {
    PieceController controller = create_controller_with_piece(4);
    const auto position = controller.position();
    const auto piece = controller.piece();
    fill_column(3, piece::PIECE_SIZE - 1, gui::Color::BLUE);

    controller.process({ EMessage::MoveLeft, EMessage::MoveLeft });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_move_right) {
    PieceController controller = create_controller_with_piece();
    auto position = controller.position();
    const auto piece = controller.piece();

    position.move_right();
    position.move_right();
    controller.process({ EMessage::MoveRight, EMessage::MoveRight });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_right_when_at_right) {
    PieceController controller = create_controller_with_piece(7, 8);
    const auto position = controller.position();
    const auto piece = controller.piece();

    controller.process({ EMessage::MoveRight, EMessage::MoveRight });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_doesnt_move_right_when_tile_at_right_is_used) {
    PieceController controller = create_controller_with_piece(4);
    const auto position = controller.position();
    const auto piece = controller.piece();
    fill_column(5, piece::PIECE_SIZE - 1, gui::Color::BLUE);

    controller.process({ EMessage::MoveRight, EMessage::MoveRight });
    EXPECT_EQ(controller.piece(), piece);
    EXPECT_EQ(controller.position(), position);
}

TEST_F(PieceControllerTest, added_piece_step_move_down) {
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
    PieceController controller = create_controller_with_piece(4, 8, 10, 2);
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
    PieceController controller = create_controller_with_piece(4, 8, 10, 2);
    fill_column(4, piece::PIECE_SIZE);
    const auto position = controller.position();

    EXPECT_FALSE(controller.step());
    EXPECT_EQ(controller.position(), position);
}
}
}
