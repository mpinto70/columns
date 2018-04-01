#pragma once

#include "game/Canvas.h"

#include <gmock/gmock.h>

namespace game {
namespace mck {
class CanvasMock : public Canvas {
public:
    MOCK_METHOD0(clear, void());

    MOCK_METHOD1(draw_, void(const piece::Board&));
    MOCK_METHOD2(draw_, void(const piece::Piece&, const piece::PiecePosition&));
    MOCK_METHOD1(draw_next_, void(const piece::Piece&));
    MOCK_METHOD1(draw_, void(const state::ScoreBoard&));
    MOCK_METHOD1(draw_, void(const state::EliminationList&));
};
}
}
