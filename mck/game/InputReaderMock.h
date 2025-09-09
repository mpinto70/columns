#pragma once

#include "game/InputReader.h"

#include <gmock/gmock.h>

namespace game {
namespace mck {

class InputReaderMock : public InputReader {
public:
    InputReaderMock() : InputReader() {}
    ~InputReaderMock() override = default;

    MOCK_METHOD0(read_input_, Messages::List());
};
} // namespace mck
} // namespace game
