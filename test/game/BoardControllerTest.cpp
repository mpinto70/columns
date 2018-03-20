#include "game/BoardController.h"

#include "../mck/piece/utilpeca.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

namespace game {
namespace tst {
namespace {

static void check_create_invalid_piece(BoardController& cont,
      const std::string& msg) {
    try {
        const auto piece = ::piece::mck::criaPecaSequencialCrescente(12);
        cont.add_piece(piece);
        FAIL() << "didn't throw " + msg;
    } catch (std::exception& e) {
        EXPECT_EQ(e.what(), msg);
    }
}

} // unnamed namespace

TEST(BoardControllerTest, create) {
    piece::Board board(10, 20, gui::WHITE);
    BoardController contr(board, 4);
    EXPECT_TRUE(contr.has_piece() == false);
}

TEST(BoardControllerTest, create_invalid) {
    piece::Board board(10, 20, gui::WHITE);
    EXPECT_NO_THROW(BoardController t(board, 4));

    // zero size piece
    EXPECT_THROW(BoardController c(board, 0), std::invalid_argument);
}

TEST(BoardControllerTest, add_piece) {
    piece::Board white(10, 20, gui::WHITE);
    BoardController contr(white, 4);

    const auto piece = ::piece::mck::criaPecaSequencialCrescente(12);

    EXPECT_TRUE(contr.has_piece() == false);
    EXPECT_THROW(contr.piece_position(), std::logic_error);
    EXPECT_THROW(contr.piece(), std::logic_error);

    EXPECT_TRUE(contr.add_piece(piece));

    EXPECT_TRUE(contr.has_piece() == true);
    EXPECT_EQ(contr.piece(), piece);
    EXPECT_EQ(contr.piece_position().row(), 0u);
    EXPECT_EQ(contr.piece_position().sub_row(), 0u);
    EXPECT_LT(contr.piece_position().column(), 10u);
}

TEST(BoardControllerTest, invalid_add_piece) {
    piece::Board white(10, 20, gui::WHITE);
    BoardController contr(white, 4);

    const auto piece = ::piece::mck::criaPecaSequencialCrescente(12);

    EXPECT_TRUE(contr.add_piece(piece));
    EXPECT_TRUE(contr.has_piece() == true);

    check_create_invalid_piece(contr, "BoardController::add_piece - there is a piece falling");
}

TEST(BoardControllerTest, step) {
    const piece::Board b0(10, 20, gui::WHITE);
    BoardController white(b0, 4);
    EXPECT_TRUE(white.board() == b0);
    const auto piece = ::piece::mck::criaPecaSequencialCrescente(12);

    EXPECT_TRUE(white.add_piece(piece));
    const uint16_t col = white.piece_position().column();
    EXPECT_TRUE(white.board() == b0);
    uint16_t row = 0;
    uint16_t sub_row = 0;
    while (white.has_piece()) {
        const piece::PiecePosition& position = white.piece_position();
        EXPECT_EQ(position.column(), col);
        EXPECT_EQ(position.row(), row);
        EXPECT_EQ(position.sub_row(), sub_row);
        EXPECT_EQ(position.max_sub_row(), 4u);
        EXPECT_TRUE(white.board() == b0);
        white.step();
        if (sub_row == 3) {
            ++row;
            sub_row = 0;
        } else {
            ++sub_row;
        }
    }

    EXPECT_TRUE(white.board() != b0);

    std::vector<gui::Color> colors;
    for (unsigned char i = 0; i < piece::PIECE_SIZE; ++i) {
        colors.push_back(white.board().at(col, white.board().height() - piece::PIECE_SIZE + i));
    }
    const piece::Piece fixed(colors);
    EXPECT_EQ(fixed, piece);
}

TEST(BoardControllerTest, move) {
    piece::Board white_board(10, 20, gui::WHITE);
    BoardController white(white_board, 4);

    const auto piece = ::piece::mck::criaPecaSequencialCrescente(12);
    EXPECT_TRUE(white.add_piece(piece));

    piece::PiecePosition position = white.piece_position();
    EXPECT_LT(position.column(), white_board.width());
    EXPECT_EQ(position.row(), 0u);
    EXPECT_EQ(position.sub_row(), 0u);
    EXPECT_EQ(position.max_sub_row(), 4u);

    white.move_left();

    position = white.piece_position();
    while (position.column() < 2u) {
        white.move_right();
        position = white.piece_position();
    }
    while (position.column() > 2u) {
        white.move_left();
        position = white.piece_position();
    }

    EXPECT_EQ(position.column(), 2u);
    EXPECT_EQ(position.row(), 0u);
    EXPECT_EQ(position.sub_row(), 0u);
    EXPECT_EQ(position.max_sub_row(), 4u);

    white.move_left();

    position = white.piece_position();
    EXPECT_EQ(position.column(), 1u);

    white.move_left();

    position = white.piece_position();
    EXPECT_EQ(position.column(), 0u);

    white.move_left();

    position = white.piece_position();
    EXPECT_EQ(position.column(), 0u);

    for (uint16_t i = 0; i < 10; ++i) {
        position = white.piece_position();
        EXPECT_EQ(position.column(), i);
        white.move_right();
    }
    position = white.piece_position();
    EXPECT_EQ(position.column(), 9u);
}

TEST(BoardControllerTest, determine_elimination) {
    piece::Board white_board(10, 20, gui::WHITE);
    EliminationList elimination;

    EXPECT_EQ(BoardController(white_board, 4).determine_elimination().size(), 0u);

    // initial state
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - .....
    // will fill the three tiles at the bottom left (horizontal)
    white_board.at(0, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - p....
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination().size(), 0u);
    white_board.at(1, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - pp...
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination().size(), 0u);
    white_board.at(2, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //         these will be eliminated --> 19 - PPP..
    elimination = BoardController(white_board, 4).determine_elimination();
    EXPECT_EQ(elimination.size(), 3u);
    EXPECT_EQ(elimination.at(0).first, 0u);
    EXPECT_EQ(elimination.at(0).second, 19u);
    EXPECT_EQ(elimination.at(1).first, 1u);
    EXPECT_EQ(elimination.at(1).second, 19u);
    EXPECT_EQ(elimination.at(2).first, 2u);
    EXPECT_EQ(elimination.at(2).second, 19u);

    // will fill the three tiles at the bottom left (vertical)
    white_board.at(0, 18) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - p....
    //                                      19 - PPP..
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination().size(), 3u);
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
    white_board.at(0, 17) = gui::BLACK;
    //                                           01234
    //  now the first line and first        15 - .....
    //  colmn will be eliminated, but the   16 - .....
    //  filling is done from left to right  17 - P....
    //  and from bottom to top              18 - P....
    //                                      19 - PPP..
    elimination.insert(elimination.begin() + 0, EliminationItem(0, 18));
    elimination.insert(elimination.begin() + 0, EliminationItem(0, 17));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);

    // goint to fill the diagonal that starts ad the bottom left corner
    white_board.at(1, 18) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P....
    //                                      18 - PP...
    //                                      19 - PPP..
    elimination.insert(elimination.begin() + 3, EliminationItem(1, 18));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
    white_board.at(2, 17) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    elimination.insert(elimination.begin() + 5, EliminationItem(2, 17));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);

    // going to put a fourth tile in the sequence
    white_board.at(0, 16) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    elimination.insert(elimination.begin() + 0, EliminationItem(0, 16));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
    white_board.at(3, 16) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    elimination.insert(elimination.begin() + 8, EliminationItem(3, 16));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
    white_board.at(3, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPPP.
    elimination.insert(elimination.begin() + 9, EliminationItem(3, 19));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);

    // going to add another color and will not change the result
    white_board.at(1, 16) = gui::BLUE;
    white_board.at(2, 16) = gui::BLUE;
    white_board.at(1, 17) = gui::BLUE;
    white_board.at(3, 17) = gui::BLUE;
    white_board.at(2, 18) = gui::BLUE;
    white_board.at(3, 18) = gui::BLUE;
    //                                           01234
    //                                      15 - .....
    //                                      16 - PzzP.
    //                                      17 - PzPz.
    //                                      18 - PPzz.
    //                                      19 - PPPP.
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
    // going to add another color and will include many
    white_board.at(4, 18) = gui::BLUE;
    //                                           01234
    //                                      15 - .....
    //                                      16 - PzZP.
    //                                      17 - PzPZ.
    //                                      18 - PPZZZ
    //                                      19 - PPPP.
    elimination.insert(elimination.begin() + 6, EliminationItem(2, 16));
    elimination.insert(elimination.begin() + 8, EliminationItem(2, 18));
    elimination.insert(elimination.begin() + 11, EliminationItem(3, 17));
    elimination.insert(elimination.begin() + 12, EliminationItem(3, 18));
    elimination.insert(elimination.begin() + 14, EliminationItem(4, 18));
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);

    // going to add other colors and not change the elimination list
    white_board.at(0, 15) = gui::GREEN;
    white_board.at(1, 15) = gui::GREEN;
    white_board.at(2, 15) = gui::RED;
    white_board.at(3, 15) = gui::GREEN;
    white_board.at(4, 15) = gui::RED;
    white_board.at(4, 16) = gui::GREEN;
    white_board.at(4, 17) = gui::GREEN;
    white_board.at(4, 19) = gui::GREEN;
    //                                           01234
    //                                      15 - vvmvm
    //                                      16 - PzZPv
    //                                      17 - PzPZv
    //                                      18 - PPZZZ
    //                                      19 - PPPPv
    EXPECT_EQ(BoardController(white_board, 4).determine_elimination(), elimination);
}
}
}
