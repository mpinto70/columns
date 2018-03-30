#pragma once

#include "game/InputReader.h"

#include <gmock/gmock.h>

namespace game {
namespace mck {

class InputReaderMock : public InputReader {
public:
    InputReaderMock(SharedMessage messages)
          : InputReader(messages) {
    }
    ~InputReaderMock() override = default;

    MOCK_METHOD0(should_process, bool());
    MOCK_METHOD0(get_input, Message::List());
};
}
}
