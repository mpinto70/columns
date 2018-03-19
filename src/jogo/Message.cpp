#include "Message.h"

namespace jogo {

void Message::add(EMessage msg) {
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.push_back(msg);
}

void Message::clear() {
    Lista empty;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    messages_.swap(empty);
    lock.unlock();
}

Message::Lista Message::get() {
    Lista res;
    auto lock = std::unique_lock<std::mutex>{ message_mutex_ };
    res.swap(messages_);
    lock.unlock();
    return res;
}
}
