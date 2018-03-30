#include "Message.h"

namespace game {

void Message::add(EMessage msg) {
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.push_back(msg);
}

void Message::add(const List& msgs) {
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.insert(messages_.end(), msgs.begin(), msgs.end());
}

void Message::clear() {
    List empty;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.swap(empty);
    lock.unlock();
}

Message::List Message::get() {
    List res;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    res.swap(messages_);
    lock.unlock();
    return res;
}
}
