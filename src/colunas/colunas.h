#pragma once
#include "grafico/Janela.h"
#include "jogo/Mensagem.h"

namespace colunas {
void init_grafico();
grafico::SharedJanela cria_janela();

enum class InputResult {
    QUIT,
    CONTINUE,
};
InputResult processa_input(jogo::MensagemPtr& mensagens);

}
