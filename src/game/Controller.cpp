#include "Controller.h"

#include "util/Wait.h"

#include <chrono>
#include <thread>
#include <utility>

namespace game {
namespace {
void run_reader(InputReader* reader) {
    reader->run();
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
        state_(std::make_unique<state::State>(board_, score_board_)),
        quit_(false) {
}

void Controller::run() {
    canvas_->draw(*state_);
    std::thread input_thread(run_reader, input_reader_.get());
    std::this_thread::sleep_for(std::chrono::milliseconds{ 3 });

    util::Wait cicle_size(std::chrono::milliseconds{ 10 });
    while (not quit_) {
        cicle_size.reset();
        process_inputs();
        cicle_size.wait();
    }

    input_thread.join();
}

void Controller::process_inputs() {
    const auto inputs = input_reader_->get_input();
    for (const auto input : inputs) {
        if (input == EMessage::Stop) {
            input_reader_->stop();
            quit_ = true;
            return;
        }
        process_input(input);
    }
}

void Controller::process_input(EMessage input) {
    if (not state_->has_piece_falling())
        return;

    switch (input) {
        case EMessage::DropDown:
        case EMessage::MoveRight:
        case EMessage::MoveLeft:
        case EMessage::RollUp:
        case EMessage::RollDown:
            break;
        case EMessage::Stop:
            break;
    }
}
}
