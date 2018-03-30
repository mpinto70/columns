#pragma once

#include "graphics/Window.h"
#include "state/State.h"

#include <memory>
#include <vector>

namespace graphics {

class Drawer {
public:
    virtual ~Drawer() = default;

    virtual void draw(Window& window, const state::State& state) const = 0;
};

using DrawerPtr = std::unique_ptr<Drawer>;
using DrawerList = std::vector<DrawerPtr>;
}
