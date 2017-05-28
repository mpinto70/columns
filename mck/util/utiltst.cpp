
#include "../mck/util/utiltst.h"

namespace mck {

std::string montaMensagem(const std::string & file,
                          const int line) {
    return file + "(" + std::to_string(line) + ")";
}

}
