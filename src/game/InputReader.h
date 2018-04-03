#pragma once

#include "game/Message.h"

#include <memory>

namespace game {
class InputReader {
public:
    InputReader();
    virtual ~InputReader() = default;

    void run();

    Message::List get_input();

    void stop();

    bool is_running() const { return running_; }

private:
    Message messages_;
    bool running_;
    bool stop_;

    virtual bool should_process() = 0;
    virtual Message::List get_input_() = 0;
};

using InputReaderPtr = std::unique_ptr<InputReader>;
}
