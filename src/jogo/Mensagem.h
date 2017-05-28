
#ifndef MENSAGEM_H_mhpa
#define MENSAGEM_H_mhpa

#include <memory>
#include <mutex>
#include <vector>

namespace jogo {

/** Identificadores de mensagem. */
enum class EMensagem {
    moveEsquerda,
    moveDireita,
    moveBaixo,
    rolaCima,
    rolaBaixo,
    parar
};

/** Responsável por controlar as mensagens de eventos. */
class Mensagem {
    public:
        /** lista de mensagens. */
        typedef std::vector<EMensagem> Lista;
        /** registra uma nova mensagem.
         * @param msg a mensagem a ser registrada
         */
        void registra(EMensagem msg);
        /** limpa a lista de mensagens. */
        void limpa();
        /** @return a lista de mensagens e limpa a atual. */
        Lista recupera();
    private:
        std::mutex mutexMensagem_;  ///< o mutex de mensagem
        Lista mensagens_;           ///< as mensagens
};

/** shared pointer para Mensagem. */
typedef std::shared_ptr<Mensagem> MensagemPtr;

}

#endif
