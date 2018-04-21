#include "Controller.h"

#include "util/Wait.h"

#include <atomic>
#include <chrono>
#include <thread>
#include <utility>

namespace game {
namespace {
std::atomic<bool> quit(false);
constexpr auto INPUT_SLEEP = std::chrono::milliseconds{ 1 };
constexpr auto CICLE_SIZE = std::chrono::milliseconds{ 10 };

void run_reader(InputReader* reader) {
    while (not quit) {
        reader->read_input();
        std::this_thread::sleep_for(INPUT_SLEEP);
    }
}
}

Controller::Controller(CanvasPtr&& canvas,
      InputReaderPtr&& input_reader,
      piece::SharedBoard& board,
      size_t record)
      : canvas_(std::move(canvas)),
        input_reader_(std::move(input_reader)),
        board_(board),
        score_board_(state::Score(record)),
        state_(std::make_unique<state::StateInitial>(board_, score_board_)) {
}

void Controller::run() {
    quit = false;
    canvas_->draw(*state_);
    std::thread input_thread(run_reader, input_reader_.get());
    std::this_thread::sleep_for(std::chrono::milliseconds{ 3 });

    util::Wait cicle_timer(CICLE_SIZE);
    while (not quit) {
        cicle_timer.reset();
        process_inputs();
        cicle_timer.wait();
    }

    input_thread.join();
}

void Controller::process_inputs() {
    const auto inputs = input_reader_->get_input();
    for (const auto input : inputs) {
        switch (input) {
            case EMessage::Stop:
                quit = true;
                return;
            case EMessage::DropDown:
            case EMessage::MoveRight:
            case EMessage::MoveLeft:
            case EMessage::RollUp:
            case EMessage::RollDown:
                break;
        }
    }
}
}
