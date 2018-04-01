#include "BoardController.h"

#include "state/ScoreBoard.h"
#include "util/Random.h"

#include <map>
#include <stdexcept>
#include <utility>

namespace game {

BoardController::BoardController(const piece::Board& board, const uint16_t max_sub_row)
      : board_(board),
        max_sub_row_(max_sub_row),
        possibles_{ gui::Color::GREEN, gui::Color::RED, gui::Color::BLUE, gui::Color::YELLOW, gui::Color::LAVENDER } {
    if (max_sub_row_ == 0) {
        throw std::invalid_argument("BoardController - zero maximum subdivisions");
    }
}

bool BoardController::add_piece(const piece::Piece& piece) {
    if (has_piece()) {
        throw std::logic_error("BoardController::add_piece - there is a piece falling");
    }

    const uint16_t c = determine_column();
    if (c == board_.width()) {
        return false;
    }

    for (unsigned char i = 0; i < piece::PIECE_SIZE; ++i)
        if (piece[i] == board_.background_color()) {
            throw std::invalid_argument("BoardController::add_piece - piece with background color");
        }

    piece_position_.reset(new piece::PiecePosition(board_, c, max_sub_row_));
    piece_.reset(new piece::Piece(piece));
    return true;
}

const piece::PiecePosition& BoardController::piece_position() const {
    if (not has_piece()) {
        throw std::logic_error("BoardController::piece_position - there is no piece falling");
    }
    return *piece_position_;
}

const piece::Piece& BoardController::piece() const {
    if (not has_piece()) {
        throw std::logic_error("BoardController::piece - there is no piece falling");
    }
    return *piece_;
}

void BoardController::step() {
    if (not has_piece()) {
        return;
    }

    const uint16_t row_piece = piece_position_->row();
    const uint16_t column_piece = piece_position_->column();
    if (reached_end()) {
        const piece::Piece& piece = *piece_;
        for (unsigned char i = 0; i < piece::PIECE_SIZE; ++i) {
            board_.at(column_piece, row_piece + i) = piece[i];
        }
        piece_.reset();
        piece_position_.reset();
    } else { // there is still space to fall
        piece_position_->step_down();
    }
}

void BoardController::move_left() {
    if (not has_piece()) {
        return;
    }

    const uint16_t piece_column = piece_position_->column();
    if (can_move_to(piece_column - 1)) {
        piece_position_->move_left();
    }
}

void BoardController::move_right() {
    if (not has_piece()) {
        return;
    }

    const uint16_t piece_column = piece_position_->column();
    if (can_move_to(piece_column + 1)) {
        piece_position_->move_right();
    }
}

void BoardController::roll_up() {
    if (not has_piece()) {
        return;
    }

    piece_->roll_up();
}

void BoardController::roll_down() {
    if (not has_piece()) {
        return;
    }

    piece_->roll_down();
}

state::EliminationList BoardController::determine_elimination() const {
    state::EliminationList to_eliminate;
    for (uint16_t c = 0; c < board_.width(); ++c) {
        for (uint16_t l = 0; l < board_.height(); ++l) {
            if (should_eliminate(c, l)) {
                to_eliminate.push_back(std::make_pair(c, l));
            }
        }
    }
    return to_eliminate;
}

void BoardController::eliminate(const state::EliminationList& casas) {
    for (uint16_t i = 0; i < casas.size(); ++i) {
        const uint16_t col = casas[i].first;
        const uint16_t row = casas[i].second;
        board_.remove(col, row);
    }
}

state::State BoardController::state() const {
    if (has_piece()) {
        return state::State(board_,
              state::ScoreBoard(),
              *piece_,
              *piece_position_,
              piece::Piece({ gui::Color::BLUE, gui::Color::BLUE, gui::Color::BLUE }));
    } else {
        return state::State(board_,
              state::ScoreBoard(),
              determine_elimination(),
              piece::Piece({ gui::Color::BLUE, gui::Color::BLUE, gui::Color::BLUE }));
    }
}

bool BoardController::can_move_to(uint16_t column) const {
    if (not has_piece()) {
        return false;
    }

    if (column >= board_.width()) {
        return false;
    }

    const uint16_t piece_row = piece_position_->row();
    const uint16_t piece_sub_row = piece_position_->sub_row();

    for (uint16_t r = piece_row; r < piece_row + piece::PIECE_SIZE; ++r) {
        if (board_.at(column, r) != board_.background_color()) {
            return false;
        }
    }
    if (piece_sub_row > 0
          && board_.at(column, piece_row + piece::PIECE_SIZE) != board_.background_color()) {
        return false;
    }

    return true;
}

uint16_t BoardController::determine_column() const {
    std::vector<uint16_t> available;
    for (uint16_t i = 0; i < board_.width(); ++i) {
        if (can_add_piece(i)) {
            available.push_back(i);
        }
    }
    if (available.size() == 0) {
        return board_.width();
    } else {
        const uint16_t idx = util::Random::get(available.size() - 1);
        return available[idx];
    }
}

bool BoardController::can_add_piece(uint16_t column) const {
    for (unsigned char i = 0; i < piece::PIECE_SIZE; ++i)
        if (board_.at(column, i) != board_.background_color()) {
            return false;
        }
    return true;
}

bool BoardController::reached_end() const {
    using namespace std::rel_ops;
    if (not has_piece()) {
        return false;
    }

    if (piece_position_->reached_bottom()) {
        return true;
    }

    const uint16_t piece_sub_row = piece_position_->sub_row();

    // it is still in middle of a tile
    if (piece_sub_row != 0) {
        return false;
    }

    const uint16_t piece_row = piece_position_->row();
    const uint16_t piece_column = piece_position_->column();
    // is over a non background tile
    if (board_.at(piece_column, piece_row + piece::PIECE_SIZE) != board_.background_color()) {
        return true;
    }

    return false;
}

bool BoardController::should_eliminate(const uint16_t column, const uint16_t row) const {
    const gui::Color cor = board_.at(column, row);
    if (cor == board_.background_color()) {
        return false;
    }

    int c0 = column - 2;
    int c1 = column + 2;
    int l0 = row - 2;
    int l1 = row + 2;

    if (c0 < 0) {
        c0 = 0;
    }
    if (l0 < 0) {
        l0 = 0;
    }
    if (c1 >= int(board_.width())) {
        c1 = board_.width() - 1;
    }
    if (l1 >= int(board_.height())) {
        l1 = board_.height() - 1;
    }

    std::map<int, std::map<int, bool>> grid;
    for (int c = -2; c <= 2; ++c) {
        for (int r = -2; r <= 2; ++r) {
            grid[c][r] = false;
        }
    }

    for (int c = c0; c <= c1; ++c) {
        for (int r = l0; r <= l1; ++r) {
            if (board_.at(c, r) == cor) {
                int cc = c - column;
                int rr = r - row;
                grid[cc][rr] = true;
            }
        }
    }

    // diagonals
    if (grid[-2][-2] && grid[-1][-1]) {
        return true;
    }
    if (grid[-1][-1] && grid[+1][+1]) {
        return true;
    }
    if (grid[+1][+1] && grid[+2][+2]) {
        return true;
    }
    if (grid[-2][+2] && grid[-1][+1]) {
        return true;
    }
    if (grid[-1][+1] && grid[+1][-1]) {
        return true;
    }
    if (grid[+1][-1] && grid[+2][-2]) {
        return true;
    }

    // perpendiculars
    if (grid[0][-2] && grid[0][-1]) {
        return true;
    }
    if (grid[0][-1] && grid[0][+1]) {
        return true;
    }
    if (grid[0][+1] && grid[0][+2]) {
        return true;
    }
    if (grid[-2][0] && grid[-1][0]) {
        return true;
    }
    if (grid[-1][0] && grid[+1][0]) {
        return true;
    }
    if (grid[+1][0] && grid[+2][0]) {
        return true;
    }
    return false;
}
}
