
#include "Cor.h"
#include <stdexcept>

namespace gui {

bool operator==(const Cor& lhs, const Cor& rhs) {
    return lhs.R == rhs.R
           && lhs.G == rhs.G
           && lhs.B == rhs.B;
}

bool operator!=(const Cor& lhs, const Cor& rhs) {
    return not(lhs == rhs);
}

Cor escurece(Cor cor,
      const unsigned char percentual) {
    if (percentual > 100) {
        throw std::invalid_argument("escurece - percentual acima do limite");
    }
    const double fator = (100 - percentual) / 100.0;
    cor.R = fator * cor.R;
    cor.G = fator * cor.G;
    cor.B = fator * cor.B;
    return cor;
}
}
