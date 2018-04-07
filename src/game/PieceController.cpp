#include "PieceController.h"

namespace game {
PieceController::PieceController(piece::SharedConstBoard board)
      : board_(board) {
}

piece::PiecePosition PieceController::piece_position() const {
    throw std::runtime_error("PieceController - no piece falling");
}

bool PieceController::step() {
    return false;
}
}
