#pragma once

#include "piece/PieceCreator.h"

#include <vector>

namespace piece {
namespace mck {
class PieceCreatorCycle : public PieceCreator {
public:
    PieceCreatorCycle(const std::vector<Piece>& pieces);
    ~PieceCreatorCycle() override = default;
    Piece get_next() const override;

private:
    std::vector<Piece> pieces_;
    mutable size_t current_;
};
}
}
