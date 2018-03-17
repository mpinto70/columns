#include "gui/Color.h"

#include <stdexcept>

namespace gui {

Color darken(Color color, const unsigned char percent) {
    if (percent > 100) {
        throw std::invalid_argument("darken - percent above limit");
    }
    const double factor = (100 - percent) / 100.0;
    color.R = factor * color.R;
    color.G = factor * color.G;
    color.B = factor * color.B;
    return color;
}
}
