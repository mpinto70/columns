#pragma once

#include "graphics/Window.h"

#include <gmock/gmock.h>

namespace graphics {
namespace mck {
class WindowMock : public Window {
public:
    WindowMock(const std::string& name,
          uint16_t width,
          uint16_t height)
          : Window(name, width, height) {
    }

    MOCK_METHOD0(clear, void());
    MOCK_METHOD0(update, void());
    MOCK_METHOD5(line_, void(uint16_t, uint16_t, uint16_t, uint16_t, gui::Color));
    MOCK_METHOD5(rectangle_, void(uint16_t, uint16_t, uint16_t, uint16_t, gui::Color));
    MOCK_METHOD5(fill_, void(uint16_t, uint16_t, uint16_t, uint16_t, gui::Color));
    MOCK_METHOD5(write_, gui::Rectangle(const std::string&, uint16_t, uint16_t, const gui::Font&, gui::Color));

    MOCK_METHOD1(draw_, void(const piece::Board&));
    MOCK_METHOD2(draw_, void(const piece::Piece&, const piece::PiecePosition&));
    MOCK_METHOD1(draw_next_, void(const piece::Piece&));
    MOCK_METHOD1(draw_, void(const state::ScoreBoard&));
    MOCK_METHOD1(draw_, void(const state::EliminationList&));
};
}
}
