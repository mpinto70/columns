#include "Font.h"

#include <algorithm>

namespace gui {

Font::Font(const std::string& name, const unsigned char size)
      : name_(name),
        size_(size) {
}
}
