#include "Font.h"

#include <algorithm>

namespace gui {

Font::Font(const std::string& name,
      const unsigned char size)
      : name_(name),
        size_(size) {
}

bool operator==(const Font& lhs, const Font& rhs) {
    return lhs.name() == rhs.name()
           && lhs.size() == rhs.size();
}

bool operator!=(const Font& lhs, const Font& rhs) {
    return not(lhs == rhs);
}
}
