#pragma once

#include "gui/Color.h"
#include "gui/Font.h"

namespace gui {
bool operator==(const Font& lhs, const Font& rhs);
bool operator!=(const Font& lhs, const Font& rhs);

namespace mck {

void print(const Color& color);
void print(const std::string& file,
      int line,
      const Color& color);
}
}
