#include "utilgame.h"

#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"

namespace game {
namespace mck {

void prepare_state_draw(::testing::StrictMock<CanvasMock>& canvas_mock,
      const state::State& state) {
    EXPECT_CALL(canvas_mock, clear()).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state.board())).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state.score_board())).Times(1);
    if (state.has_piece_falling()) {
        EXPECT_CALL(canvas_mock, draw_(state.piece(), state.piece_position())).Times(1);
    }
    EXPECT_CALL(canvas_mock, draw_(state.elimination_list())).Times(1);
    if (state.has_next()) {
        EXPECT_CALL(canvas_mock, draw_next_(state.next())).Times(1);
    }
}
}
}
