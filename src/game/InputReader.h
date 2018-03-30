#pragma once

#include "game/Message.h"

#include <memory>

namespace game {
class InputReader {
public:
    explicit InputReader(SharedMessage messages);
    virtual ~InputReader() = default;

    SharedMessage messages() const { return messages_; }

    void run();

private:
    SharedMessage messages_;

    virtual bool should_process() = 0;
    virtual Message::List get_input() = 0;
};

using InputReaderPtr = std::unique_ptr<InputReader>;
}
