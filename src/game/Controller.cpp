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
constexpr auto CICLE_SIZE = std::chrono::milliseconds{ 20 };
constexpr auto ELIMINATION_SIZE = std::chrono::milliseconds{ 500 };

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
      size_t record,
      piece::CreatorPtr&& piece_creator)
      : canvas_(std::move(canvas)),
        input_reader_(std::move(input_reader)),
        match_controller_(board, record, std::move(piece_creator)),
        board_(board),
        score_board_(state::Score(record)) {
}

void Controller::run() {
    quit = false;
    canvas_->draw(match_controller_.state());
    std::thread input_thread(run_reader, input_reader_.get());
    std::this_thread::sleep_for(std::chrono::milliseconds{ 3 });

    util::Wait elimination_timer(ELIMINATION_SIZE);
    util::Wait cicle_timer(CICLE_SIZE);
    while (not quit) {
        cicle_timer.reset();
        match_controller_.tick();
        process_inputs();
        if (not quit) {
            const auto& state = match_controller_.state();
            canvas_->draw(state);
            if (state.has_elimination_list()) {
                elimination_timer.reset();
                elimination_timer.wait();
            }
        }
        cicle_timer.wait();
    }

    input_thread.join();
}

void Controller::process_inputs() {
    const auto inputs = input_reader_->get_input();
    for (const auto input : inputs) {
        if (input != EMessage::Stop) {
            match_controller_.process(input);
        } else {
            quit = true;
            return;
        }
    }
}
}
