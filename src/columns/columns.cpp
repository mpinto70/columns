#include "columns.h"

#include "game/Controller.h"
#include "graphics/SDL/Canvas.h"
#include "input/SDL/InputReader.h"
#include "piece/CreatorRandom.h"

#include <iostream>
#include <string>
#include <array>

namespace {
constexpr const char VERSION[] = "0.8";

/// available colors
const std::array<gui::Color, 5> POSSIBLES = {
    gui::Color::GREEN,
    gui::Color::RED,
    gui::Color::BLUE,
    gui::Color::YELLOW,
    gui::Color::LAVENDER,
};

constexpr size_t BOARD_WIDTH = 8;   ///< board width in tiles
constexpr size_t BOARD_HEIGHT = 25; ///< board height in tiles

int run() {
    try {
        columns::init_graphics();

        const gui::Font font_name("/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf", 25);
        const gui::Font font_score("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 25);

        auto board = std::make_shared<piece::Board>(BOARD_WIDTH, BOARD_HEIGHT);
        auto canvas = std::make_unique<graphics::sdl::Canvas>(*board,
              "Columns " + std::string(VERSION),
              1000,
              100,
              font_name,
              font_score);
        auto input_reader = std::make_unique<input::sdl::InputReader>();
        auto piece_creator = std::make_unique<piece::CreatorRandom>(board, std::vector<gui::Color>(POSSIBLES.begin(), POSSIBLES.end()));

        game::Controller controller(std::move(canvas),
              std::move(input_reader),
              board,
              0,
              std::move(piece_creator));

        controller.run();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return -1;
    }
    columns::stop_graphics();

    std::cout << "BYE\n";
    return 0;
}
}

int main() {
    return run();
}
