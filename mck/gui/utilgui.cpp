#include "utilgui.h"

#include <cstdio>
#include <string>

namespace gui {
bool operator==(const Font& lhs, const Font& rhs) {
    return lhs.name() == rhs.name()
           && lhs.size() == rhs.size();
}

bool operator!=(const Font& lhs, const Font& rhs) {
    return not(lhs == rhs);
}

namespace mck {

void print(const gui::Color& color) {
    printf(" %02x %02x %02x |", color.R, color.G, color.B);
}

void print(const std::string& file,
      int line,
      const Color& color) {
    printf("Printing color from %s(%d)\n", file.c_str(), line);
    const std::string separator(11, '-');
    printf("%s\n", separator.c_str());
    print(color);
    printf("\n");
    printf("%s\n\n", separator.c_str());
}
}
}
