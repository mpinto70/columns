
#include "utilgui.h"
#include <cstdio>
#include <string>

namespace gui {
namespace mck {

void print(const gui::Cor& cor) {
    printf(" %02x %02x %02x |", cor.R, cor.G, cor.B);
}

void print(const std::string& file,
      int line,
      const Cor& cor) {
    printf("Imprimindo cor de %s(%d)\n", file.c_str(), line);
    const std::string sep(11, '-');
    printf("%s\n", sep.c_str());
    print(cor);
    printf("\n");
    printf("%s\n\n", sep.c_str());
}
}
}
