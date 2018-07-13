#include "Canvas.h"

namespace graphics {
namespace sdl {
namespace {

constexpr ColorTripletT COLORS[] = {
    { 0x98, 0x1b, 0x1e }, // RED
    { 0x2e, 0x85, 0x40 }, // GREEN
    { 0x02, 0xbf, 0xe7 }, // BLUE
    { 0xfd, 0xb8, 0x1e }, // YELLOW
    { 0x4c, 0x2c, 0x92 }, // LAVENDER
    { 0xf1, 0xf1, 0xf1 }, // NONE
};

constexpr ColorTripletT BLUE_LIGHT = { 0x00, 0x71, 0xbc };
constexpr ColorTripletT BLUE_MEDIUM = { 0x20, 0x54, 0x93 };
constexpr ColorTripletT BLUE_DARK = { 0x11, 0x2e, 0x51 };

constexpr ColorTripletT BLUE_COOL_DARK = { 0x20, 0x54, 0x93 };
constexpr ColorTripletT BLUE_COOL_MEDIUM = { 0x47, 0x73, 0xaa };
constexpr ColorTripletT BLUE_COOL_LIGHT = { 0x8b, 0xa6, 0xca };
constexpr ColorTripletT BLUE_COOL_LIGHTEST = { 0xdc, 0xe4, 0xef };

constexpr ColorTripletT NAVY = { 0x11, 0x2e, 0x51 };
constexpr ColorTripletT NAVY_LIGHT = { 0xdc, 0xe4, 0xef };

constexpr ColorTripletT GRAY_BLACK = { 0x21, 0x21, 0x21 };
constexpr ColorTripletT WHITE = { 0xff, 0xff, 0xff };

constexpr ColorTripletT GRAY_DARKEST = { 0x32, 0x3a, 0x45 };
constexpr ColorTripletT GRAY_DARK = { 0x5b, 0x61, 0x6b };
constexpr ColorTripletT GRAY_MEDIUM = { 0xae, 0xb0, 0xb5 };
constexpr ColorTripletT GRAY_LIGHT = { 0xd6, 0xd7, 0xd9 };
constexpr ColorTripletT GRAY_LIGHTEST = { 0xf1, 0xf1, 0xf1 };
constexpr ColorTripletT GRAY_WARM_DARK = { 0x49, 0x44, 0x40 };
constexpr ColorTripletT GRAY_WARM_LIGHT = { 0xe4, 0xe2, 0xe0 };

constexpr ColorTripletT CYAN_DARKEST = { 0x04, 0x6b, 0x99 };
constexpr ColorTripletT CYAN_DARK = { 0x00, 0xa6, 0xd2 };
constexpr ColorTripletT CYAN_MEDIUM = { 0x02, 0xbf, 0xe7 };
constexpr ColorTripletT CYAN_LIGHT = { 0x9b, 0xda, 0xf1 };
constexpr ColorTripletT CYAN_LIGHTEST = { 0xe1, 0xf3, 0xf8 };

constexpr ColorTripletT RED_DARKEST = { 0x98, 0x1b, 0x1e };
constexpr ColorTripletT RED_DARK = { 0xcd, 0x20, 0x26 };
constexpr ColorTripletT RED_MEDIUM = { 0xe3, 0x1c, 0x3d };
constexpr ColorTripletT RED_LIGHT = { 0xe5, 0x93, 0x93 };
constexpr ColorTripletT RED_LIGHTEST = { 0xf9, 0xde, 0xde };

constexpr ColorTripletT GOLD_DARK = { 0xfd, 0xb8, 0x1e };
constexpr ColorTripletT GOLD_MEDIUM = { 0xf9, 0xc6, 0x42 };
constexpr ColorTripletT GOLD_LIGHT = { 0xfa, 0xd9, 0x80 };
constexpr ColorTripletT GOLD_LIGHTEST = { 0xff, 0xf1, 0xd2 };

constexpr ColorTripletT GREEN_DARK = { 0x2e, 0x85, 0x40 };
constexpr ColorTripletT GREEN_MEDIUM = { 0x4a, 0xa5, 0x64 };
constexpr ColorTripletT GREEN_LIGHT = { 0x94, 0xbf, 0xa2 };
constexpr ColorTripletT GREEN_LIGHTEST = { 0xe7, 0xf4, 0xe4 };

static_assert(sizeof(COLORS) / sizeof(COLORS[0]) == static_cast<size_t>(gui::Color::NONE) + 1, "wrong array size");

void darken(ColorTripletT& out, const ColorTripletT& color, int percent) {
    out[0] = (int(color[0]) * percent) / 100;
    out[1] = (int(color[1]) * percent) / 100;
    out[2] = (int(color[2]) * percent) / 100;
}

constexpr int STEP_SIZE = 8;
constexpr int TILE_SIZE = STEP_SIZE * (piece::Position::SUBDIVISIONS + 1);
constexpr int BORDER_WIDTH = 5;
constexpr int INNER_SPACE = 10;
constexpr int TOP_MARGIN = 50;
constexpr int LEFT_MARGIN = 15;
constexpr int RIGHT_MARGIN = 10;
constexpr int BOTTOM_MARGIN = 75;
constexpr int BOARD_TOP = TOP_MARGIN + BORDER_WIDTH;
constexpr int BOARD_LEFT = LEFT_MARGIN + BORDER_WIDTH;
constexpr int SCORE_TOP = TOP_MARGIN + BORDER_WIDTH + 50;
constexpr int SCORE_WIDTH = 150;
constexpr int SCORE_HEIGHT = 80;
constexpr int NEXT_PIECE_TOP = SCORE_TOP + SCORE_HEIGHT + 20;
constexpr int NEXT_PIECE_WIDTH = SCORE_WIDTH;

int score_left(const piece::Board& board) {
    return LEFT_MARGIN
           + BORDER_WIDTH
           + board.width() * TILE_SIZE
           + BORDER_WIDTH
           + INNER_SPACE
           + BORDER_WIDTH;
}

int screen_width(const piece::Board& board) {
    return score_left(board)
           + SCORE_WIDTH
           + BORDER_WIDTH
           + RIGHT_MARGIN;
}

int screen_height(const piece::Board& board) {
    return TOP_MARGIN
           + BORDER_WIDTH
           + board.height() * TILE_SIZE
           + BORDER_WIDTH
           + BOTTOM_MARGIN;
}

constexpr int calculate_x(size_t column) {
    return column * TILE_SIZE + BOARD_LEFT;
}

constexpr int calculate_y(size_t row, size_t sub_row = 0) {
    return row * TILE_SIZE + BOARD_TOP + sub_row * STEP_SIZE;
}

void draw_tile(WindowSDL& window,
      const ColorTripletT& color,
      const int x1,
      const int y1) {
    const SDL_Rect rect = { x1, y1, TILE_SIZE, TILE_SIZE };
    ColorTripletT darker;
    darken(darker, color, 40);
    window.fill(rect, color);
    window.rectangle(rect, darker);
}

void draw_tile(WindowSDL& window,
      gui::Color color,
      const int x1,
      const int y1) {
    const ColorTripletT& sdl_color = COLORS[static_cast<unsigned int>(color)];
    draw_tile(window, sdl_color, x1, y1);
}

void draw_piece(WindowSDL& window,
      const piece::Piece& piece,
      const int x1,
      int y1) {
    for (size_t t = 0; t < piece::PIECE_SIZE; ++t) {
        draw_tile(window, piece[t], x1, y1);
        y1 += TILE_SIZE;
    }
}

void draw_frame(WindowSDL& window,
      int outer_left,
      int outer_top,
      int outer_right,
      int outer_bottom,
      int width,
      const ColorTripletT& light_triplet,
      const ColorTripletT& dark_triplet) {
    for (int l = outer_left,
             t = outer_top,
             r = outer_right;
          l < outer_left + width;
          ++l, ++t, --r) {
        window.line(l, t, r, t, dark_triplet);
    }
    for (int t = outer_top,
             b = outer_bottom,
             r = outer_right;
          t < outer_top + width;
          ++t, --b, --r) {
        window.line(r, t, r, b, dark_triplet);
    }

    for (int l = outer_left,
             b = outer_bottom,
             r = outer_right;
          l < outer_left + width;
          ++l, --b, --r) {
        window.line(l, b, r, b, light_triplet);
    }
    for (int t = outer_top,
             b = outer_bottom,
             l = outer_left;
          t < outer_top + width;
          ++t, --b, ++l) {
        window.line(l, t, l, b, light_triplet);
    }
}
}

Canvas::Canvas(const piece::Board& board,
      const std::string& name,
      int left,
      int top,
      const gui::Font& font_name,
      const gui::Font& font_score)
      : window_(name, left, top, screen_width(board), screen_height(board), GRAY_LIGHT),
        name_(name),
        font_name_(font_name),
        font_score_(font_score),
        board_width_(board.width() * TILE_SIZE),
        board_height_(board.height() * TILE_SIZE),
        score_left_(score_left(board)),
        next_piece_heigt_(20 + piece::PIECE_SIZE * TILE_SIZE) {
}

Canvas::~Canvas() = default;

void Canvas::start() {
    window_.clear();

    window_.fill(SDL_Rect{ BOARD_LEFT, BOARD_TOP, board_width_, board_height_ }, WHITE);
    const int outer_left = BOARD_LEFT - BORDER_WIDTH;
    const int outer_right = BOARD_LEFT + board_width_ + BORDER_WIDTH - 1;
    const int outer_top = BOARD_TOP - BORDER_WIDTH;
    const int outer_bottom = BOARD_TOP + board_height_ + BORDER_WIDTH - 1;

    draw_frame(window_,
          outer_left,
          outer_top,
          outer_right,
          outer_bottom,
          BORDER_WIDTH,
          GRAY_WARM_DARK,
          GRAY_BLACK);

    window_.write(name_,
          BOARD_LEFT + 10,
          5,
          font_name_.name(),
          font_name_.size() + 5,
          BLUE_DARK);

    window_.write("by mpinto70",
          BOARD_LEFT + 10,
          BOARD_TOP + board_height_ + 5,
          font_name_.name(),
          font_name_.size() + 5,
          BLUE_DARK);
}

void Canvas::draw_(const piece::Board& board) {
    for (size_t r = 0; r < board.height(); ++r) {
        for (size_t c = 0; c < board.width(); ++c) {
            if (board.used(c, r)) {
                const int x1 = calculate_x(c);
                const int y1 = calculate_y(r);
                draw_tile(window_, board.at(c, r), x1, y1);
            }
        }
    }
}

void Canvas::draw_(const piece::Piece& piece, const piece::Position& piece_position) {
    const int x1 = calculate_x(piece_position.column());
    int y1 = calculate_y(piece_position.row(), piece_position.sub_row());
    draw_piece(window_, piece, x1, y1);
}

void Canvas::draw_next_(const piece::Piece& next_piece) {
    const SDL_Rect rect = { score_left_, NEXT_PIECE_TOP, NEXT_PIECE_WIDTH, next_piece_heigt_ };
    window_.fill(rect, WHITE);

    draw_frame(window_,
          score_left_,
          NEXT_PIECE_TOP,
          score_left_ + NEXT_PIECE_WIDTH,
          NEXT_PIECE_TOP + next_piece_heigt_,
          BORDER_WIDTH - 1,
          GRAY_MEDIUM,
          GRAY_BLACK);

    const int x1 = score_left_ + (NEXT_PIECE_WIDTH - TILE_SIZE) / 2;
    int y1 = NEXT_PIECE_TOP + 10;
    draw_piece(window_, next_piece, x1, y1);
}

void Canvas::draw_(const state::ScoreBoard& score_board) {
    const SDL_Rect rect = { score_left_, BOARD_TOP, SCORE_WIDTH, SCORE_HEIGHT };
    window_.fill(rect, WHITE);

    draw_frame(window_,
          score_left_,
          BOARD_TOP,
          score_left_ + SCORE_WIDTH,
          BOARD_TOP + SCORE_HEIGHT,
          BORDER_WIDTH - 1,
          GRAY_MEDIUM,
          GRAY_BLACK);

    auto text_rect = window_.write("Score",
          score_left_ + 10,
          BOARD_TOP + BORDER_WIDTH + 2,
          font_name_.name(),
          font_name_.size(),
          BLUE_DARK);
    window_.write(std::to_string(score_board.score().total()),
          text_rect.x + text_rect.w + 20,
          text_rect.y,
          font_score_.name(),
          font_score_.size(),
          BLUE_DARK);

    text_rect = window_.write("Record",
          score_left_ + 10,
          text_rect.y + text_rect.h + 10,
          font_name_.name(),
          font_name_.size(),
          RED_DARKEST);
    window_.write(std::to_string(score_board.record().total()),
          text_rect.x + text_rect.w + 20,
          text_rect.y,
          font_score_.name(),
          font_score_.size(),
          RED_DARKEST);
}

void Canvas::draw_(const piece::Board::EliminationList& elimination_list) {
    for (const auto& eliminated : elimination_list) {
        const int x1 = calculate_x(eliminated.column);
        const int y1 = calculate_y(eliminated.row);
        draw_tile(window_, GRAY_MEDIUM, x1, y1);
    }
}

void Canvas::finish() {
    window_.update();
}
}
}
