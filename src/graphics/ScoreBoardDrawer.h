#pragma once

#include "graphics/Window.h"
#include "score/ScoreBoard.h"

namespace graphics {
class ScoreBoardDrawer {
public:
    void draw(SharedWindow window, const score::ScoreBoard& score_board) const;
};
}
