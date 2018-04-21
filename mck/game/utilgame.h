#pragma once

#include "../mck/game/CanvasMock.h"

#include "game/Messages.h"

namespace game {
namespace mck {

void prepare_state_draw(::testing::StrictMock<CanvasMock>& canvas_mock,
      const state::State& state);

std::string to_string(EMessage input);
}
}
