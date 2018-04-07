#pragma once

#include "game/Messages.h"
#include "graphics/Window.h"

namespace columns {

void init_graphics();
void stop_graphics();

graphics::WindowPtr create_window(const std::string& version,
      size_t screen_width,
      size_t screen_height);

enum class InputResult {
    QUIT,
    CONTINUE,
};

InputResult process_input(game::SharedMessage& messages);
}
