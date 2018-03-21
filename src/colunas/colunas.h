#pragma once

#include "game/Message.h"
#include "graphics/Window.h"

namespace colunas {
void init_grafico();
void finaliza_grafico();
graphics::SharedJanela cria_janela(const std::string& versao,
      size_t largura_tela,
      size_t altura_tela);

enum class InputResult {
    QUIT,
    CONTINUE,
};
InputResult processa_input(game::MensagemPtr& mensagens);
}
