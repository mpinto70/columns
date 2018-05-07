#pragma once

#include "piece/PieceCreator.h"

namespace piece {
class PieceCreatorRandom : public PieceCreator {
public:
    explicit PieceCreatorRandom(const std::vector<gui::Color>& possibles);
    ~PieceCreatorRandom() override = default;

    Piece get_next() const override;

private:
    std::vector<gui::Color> possibles_;
};
}
