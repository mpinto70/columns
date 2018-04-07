#pragma once

#include "game/Messages.h"

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
    bool running_;
    bool stop_;

    virtual bool should_process() = 0;
    virtual Messages::List get_input_() = 0;
};

using InputReaderPtr = std::unique_ptr<InputReader>;
}
