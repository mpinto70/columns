#pragma once

#include <cstdint>
#include <string>

namespace gui {

/// Represents a text font
class Font {
public:
    /**
     * @param name  font name (path to file, for example)
     * @param size  font size
     */
    Font(const std::string& name,
          unsigned char size);
    const std::string& name() const { return name_; }
    unsigned char size() const { return size_; }

private:
    std::string name_;   ///< font name (path to file, for example)
    unsigned char size_; ///< font size
};
}
