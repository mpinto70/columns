#pragma once

#include "piece/Board.h"
#include "piece/Creator.h"

namespace piece {
class CreatorRandom : public Creator {
public:
    explicit CreatorRandom(SharedConstBoard board, const std::vector<gui::Color>& possibles);
    ~CreatorRandom() override = default;

    Piece piece() const override;
    size_t column() const override;

private:
    SharedConstBoard board_;
    std::vector<gui::Color> possibles_;
    size_t max_column_;
};
}
