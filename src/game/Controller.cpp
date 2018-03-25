#include "Controller.h"

namespace game {

Controller::Controller(graphics::SharedWindow window,
      const graphics::ScoreBoardDrawer& drawer,
      SharedMessage messages) {
    window->clear();
    drawer.draw(window, state::ScoreBoard());
}

void Controller::run() {
}
}
