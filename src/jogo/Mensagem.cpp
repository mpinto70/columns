
#include "Mensagem.h"

namespace jogo {

void Mensagem::registra(EMensagem msg) {
    auto lock = std::unique_lock<std::mutex>{ mutexMensagem_ };
    mensagens_.push_back(msg);
}

void Mensagem::limpa() {
    Lista vazia;
    auto lock = std::unique_lock<std::mutex>{ mutexMensagem_ };
    mensagens_.swap(vazia);
    lock.unlock();
}

Mensagem::Lista Mensagem::recupera() {
    Lista res;
    auto lock = std::unique_lock<std::mutex>{ mutexMensagem_ };
    res.swap(mensagens_);
    lock.unlock();
    return res;
}
}
