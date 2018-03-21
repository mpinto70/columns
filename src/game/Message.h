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
class Message {
public:
    using Lista = std::vector<EMessage>;
    void add(EMessage msg);
    void clear();
    /** @return message list
     * @attention the list is cleared after returned
     */
    Lista get();

private:
    std::mutex message_mutex_;
    Lista messages_;
};

using MensagemPtr = std::shared_ptr<Message>;
}
