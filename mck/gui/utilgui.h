
#ifndef util_gui_h
#define util_gui_h

#include "gui/Cor.h"
#include <iosfwd>

namespace gui {
namespace mck {

void print(const Cor & cor);
void print(const std::string & file,
           int line,
           const Cor & cor);
}
}
#endif
