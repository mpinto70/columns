#include "Controller.h"

#include <chrono>
#include <thread>
#include <utility>

namespace game {
namespace {
bool quit = false;

void run_reader(InputReader* reader) {
    reader->run();
}
}

Controller::Controller(CanvasPtr&& canvas,
      InputReaderPtr&& input_reader,
      size_t board_width,
      size_t board_height,
      gui::Color board_background,
      size_t record)
      : canvas_(std::move(canvas)),
        input_reader_(std::move(input_reader)),
        board_(std::make_shared<piece::Board>(board_width, board_height, board_background)),
        score_board_(state::Score(record)),
        state_(std::make_unique<state::State>(board_, score_board_)) {
}

void Controller::run() {
    canvas_->draw(*state_);
    std::thread input_thread(run_reader, input_reader_.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(3));

    while (not quit) {
        const auto inputs = input_reader_->get_input();
        for (const auto input : inputs) {
            switch (input) {
                case EMessage::MoveDown:
                case EMessage::MoveRight:
                case EMessage::MoveLeft:
                case EMessage::RollUp:
                case EMessage::RollDown:
                    break;
                case EMessage::Stop:
                    input_reader_->stop();
                    quit = true;
                    break;
            }
            if (quit) {
                break;
            }
        }
    }

    input_thread.join();
}
}
