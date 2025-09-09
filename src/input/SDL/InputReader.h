#pragma once

#include "game/InputReader.h"

namespace input {
namespace sdl {
class InputReader : public game::InputReader {
public:
    ~InputReader() override = default;

private:
    game::Messages::List read_input_() override;
};
} // namespace sdl
} // namespace input
