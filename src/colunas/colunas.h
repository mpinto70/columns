#pragma once
#include "grafico/Janela.h"
#include "jogo/Message.h"

namespace colunas {
void init_grafico();
void finaliza_grafico();
grafico::SharedJanela cria_janela(const std::string& versao,
      size_t largura_tela,
      size_t altura_tela);

enum class InputResult {
    QUIT,
    CONTINUE,
};
InputResult processa_input(jogo::MensagemPtr& mensagens);
}
