#include "columns.h"

#include "game/BoardController.h"
#include "game/GameController.h"
#include "game/StateObserver.h"
#include "graphics/BoardDrawer.h"
#include "piece/Board.h"
#include "util/Wait.h"

#include <atomic>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

namespace {
const std::string VERSION = "0.6";

/// available colors
const std::vector<gui::Color> POSSIBLE = {
    gui::GREEN,
    gui::RED,
    gui::BLUE,
    gui::YELLOW,
    gui::LAVENDER,
};

constexpr size_t TILE_SIZE = 30;                                ///< tile size in pixels
constexpr size_t TILE_STEP = 2;                                 ///< # of steps in each tile
constexpr size_t BOARD_WIDTH = 8;                               ///< board width in tiles
constexpr size_t BOARD_HEIGHT = 25;                             ///< board height in tiles
constexpr size_t SCREEN_WIDTH = BOARD_WIDTH * TILE_SIZE + 200;  ///< screen width in pixels
constexpr size_t SCREEN_HEIGHT = BOARD_HEIGHT * TILE_SIZE + 75; ///< screen height in pixels

bool initialized = false;
bool quit = false;

static void wait_for_initialization() {
    while (not initialized) {
        usleep(200);
    }
}

class ColumnsObserver : public game::StateObserver {
public:
    ColumnsObserver(const graphics::SharedWindow& window,
          const gui::Font& font_name,
          const gui::Font& font_score,
          const graphics::BoardDrawer& drawer)
          : window_(window),
            font_name_(font_name),
            font_score_(font_score),
            drawer_(drawer) {
        if (not window_) {
            throw std::invalid_argument("ColumnsObserver - null window");
        }
    }
    ~ColumnsObserver() override = default;

    void update(const game::State& state) const override {
        window_->clear();
        window_->line(gui::Point{ 0, BOARD_HEIGHT * TILE_SIZE + 40 },
              gui::Point{ SCREEN_WIDTH, BOARD_HEIGHT * TILE_SIZE + 40 },
              gui::WHITE);
        window_->write("Columns - by mpinto70",
              gui::Point{ 10, BOARD_HEIGHT * TILE_SIZE + 45 },
              font_name_,
              gui::WHITE);
        window_->write("Score",
              gui::Point{ 10 + BOARD_WIDTH * TILE_SIZE + 10, 50 },
              font_name_,
              gui::YELLOW);
        window_->write(std::to_string(state.score_board().score().total()),
              gui::Point{ 10 + BOARD_WIDTH * TILE_SIZE + 10, 90 },
              font_score_,
              gui::YELLOW);
        drawer_.draw(*window_, state, gui::WHITE);
        window_->update();
    }

private:
    graphics::SharedWindow window_;
    gui::Font font_name_;
    gui::Font font_score_;
    graphics::BoardDrawer drawer_;
};

void game_loop(game::SharedMessage mensagens) {
    try {
        auto window = columns::create_window(VERSION, SCREEN_WIDTH, SCREEN_HEIGHT);
        const graphics::BoardDrawer drawer(10, 15, TILE_SIZE, TILE_STEP);
        const gui::Font font_name("/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf", 25);
        const gui::Font font_score("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 25);

        game::GameController controller(piece::Board(BOARD_WIDTH, BOARD_HEIGHT, gui::WHITE),
              TILE_SIZE / 2,
              score::Score(0),
              POSSIBLE,
              game::StateObserverPtr(new ColumnsObserver(window, font_name, font_score, drawer)),
              mensagens);

        initialized = true;

        controller.execute();
        quit = true;
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        quit = true;
        initialized = true;
    }
}

void input_loop(game::SharedMessage& messages) {
    util::Wait input_interval(3);
    while (!quit) {
        input_interval.reset();
        if (columns::process_input(messages) == columns::InputResult::QUIT) {
            quit = true;
            break;
        }
        input_interval.wait();
    }
}

int run() {
    try {
        columns::init_graphics();

        auto messages = std::make_shared<game::Message>();
        std::thread game_thread(game_loop, messages);

        wait_for_initialization();

        // when the input loop finishes, the player has quit
        input_loop(messages);

        messages->add(game::EMessage::Stop);
        game_thread.join();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
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
