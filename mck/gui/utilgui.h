#pragma once

#include <gui/Color.h>
#include <iosfwd>

namespace gui {
namespace mck {

void print(const Color& color);
void print(const std::string& file,
      int line,
      const Color& color);
}
}
