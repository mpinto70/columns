#pragma once

#include "game/State.h"

namespace game {
bool operator==(const State& lhs, const State& rhs);
bool operator!=(const State& lhs, const State& rhs);
}
