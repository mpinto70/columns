#pragma once

#include "piece/Piece.h"

#include <memory>

namespace piece {
class PieceCreator {
public:
    virtual ~PieceCreator() = default;

    virtual Piece get_next() const = 0;
};

using PieceCreatorPtr = std::unique_ptr<PieceCreator>;
}
