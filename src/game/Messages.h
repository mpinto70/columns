#pragma once

#include <memory>
#include <mutex>
#include <vector>

namespace game {

/// Message identifiers
enum class EMessage {
    MoveLeft,
    MoveRight,
    MoveDown,
    RollUp,
    RollDown,
    Stop
};

/// Controls event messages
class Messages {
public:
    using List = std::vector<EMessage>;
    void add(EMessage msg);
    void add(const List& msgs);
    void clear();
    /** @return message list
     * @attention the list is cleared after returned
     */
    List get();

private:
    std::mutex message_mutex_;
    List messages_;
};

using SharedMessage = std::shared_ptr<Messages>;
}
