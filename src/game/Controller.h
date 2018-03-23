#pragma once

#include "game/Message.h"
#include "graphics/Window.h"

namespace game {

class Controller {
public:
    Controller(graphics::SharedWindow window, SharedMessage messages);
    void run();
};
}
