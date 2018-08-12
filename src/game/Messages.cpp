#include "game/Messages.h"

namespace game {

void Messages::add(EMessage msg) {
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.push_back(msg);
}

void Messages::add(const List& msgs) {
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.insert(messages_.end(), msgs.begin(), msgs.end());
}

void Messages::clear() {
    List empty;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.swap(empty);
}

Messages::List Messages::get() {
    List res;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    res.swap(messages_);
    lock.unlock();
    return res;
}
}
