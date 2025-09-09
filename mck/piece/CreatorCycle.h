#pragma once

#include "piece/Creator.h"

#include <vector>

namespace piece {
namespace mck {
class CreatorCycle : public Creator {
public:
    CreatorCycle(const std::vector<Piece>& pieces, const std::vector<size_t>& columns);
    ~CreatorCycle() override = default;
    Piece piece() const override;
    size_t column() const override;

private:
    std::vector<Piece> pieces_;
    std::vector<size_t> columns_;
    mutable size_t current_piece_;
    mutable size_t current_column_;
};
} // namespace mck
} // namespace piece
