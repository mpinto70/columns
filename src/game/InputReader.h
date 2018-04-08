#pragma once

#include "game/Messages.h"

#include <atomic>
#include <memory>

namespace game {
class InputReader {
public:
    InputReader();
    virtual ~InputReader() = default;

    void run();

    Messages::List get_input();

    void stop();

    bool is_running() const { return running_; }

private:
    Messages messages_;
    std::atomic<bool> running_;
    std::atomic<bool> stop_;

    virtual bool should_process() = 0;
    virtual Messages::List get_input_() = 0;
};

using InputReaderPtr = std::unique_ptr<InputReader>;
}
