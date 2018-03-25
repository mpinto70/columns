#pragma once

#include "game/Message.h"
#include "graphics/ScoreBoardDrawer.h"
#include "graphics/Window.h"

namespace game {

class Controller {
public:
    Controller(graphics::SharedWindow window,
          const graphics::ScoreBoardDrawer& drawer,
          SharedMessage messages);
    void run();
};
}
