#pragma once

#include "gui/Cor.h"
#include <iosfwd>

namespace gui {
namespace mck {

void print(const Cor& cor);
void print(const std::string& file,
      int line,
      const Cor& cor);
}
}
