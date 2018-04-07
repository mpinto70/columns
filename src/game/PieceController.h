#pragma once

#include "piece/Board.h"
#include "piece/PiecePosition.h"

namespace game {
class PieceController {
public:
    explicit PieceController(piece::SharedConstBoard board);
    bool has_piece() const { return false; }
    piece::PiecePosition piece_position() const;
    bool step();

private:
    piece::SharedConstBoard board_;
};
}
