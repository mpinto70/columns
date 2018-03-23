#pragma once

#include "game/Message.h"
#include "graphics/Window.h"

namespace columns {

void init_graphics();
void stop_graphics();

graphics::SharedWindow create_window(const std::string& version,
      size_t screen_width,
      size_t screen_height);

enum class InputResult {
    QUIT,
    CONTINUE,
};

InputResult process_input(game::SharedMessage& messages);
}
