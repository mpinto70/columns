#pragma once

#include "piece/Piece.h"

#include <memory>

namespace piece {
class Creator {
public:
    virtual ~Creator() = default;

    virtual Piece piece() const = 0;
    virtual size_t column() const = 0;
};

using CreatorPtr = std::unique_ptr<Creator>;
}
