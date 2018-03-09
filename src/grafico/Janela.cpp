
#include "Janela.h"
#include <stdexcept>

namespace grafico {
Janela::Janela(const std::string& nome,
      const uint16_t largura,
      const uint16_t altura)
      : nome_(nome),
        largura_(largura),
        altura_(altura) {
    if (nome == "") {
        throw std::invalid_argument("Janela - nome vazio");
    }
    if (largura_ == 0) {
        throw std::invalid_argument("Janela - largura nula");
    }
    if (altura_ == 0) {
        throw std::invalid_argument("Janela - altura nula");
    }
}

Janela::~Janela() {
}

void Janela::linha(const gui::Ponto& ini,
      const gui::Ponto& fim,
      const gui::Cor& cor) {
    linha_(ini.X, ini.Y, fim.X, fim.Y, cor);
}

void Janela::retangulo(const gui::Retangulo& ret,
      const gui::Cor& cor) {
    retangulo_(ret.X1(), ret.Y1(), ret.X2(), ret.Y2(), cor);
}

void Janela::retangulo(const gui::Ponto& te,
      const gui::Ponto& fd,
      const gui::Cor& cor) {
    retangulo_(te.X, te.Y, fd.X, fd.Y, cor);
}

void Janela::preenche(const gui::Retangulo& ret,
      const gui::Cor& cor) {
    preenche_(ret.X1(), ret.Y1(), ret.X2(), ret.Y2(), cor);
}

void Janela::preenche(const gui::Ponto& te,
      const gui::Ponto& fd,
      const gui::Cor& cor) {
    preenche_(te.X, te.Y, fd.X, fd.Y, cor);
}

gui::Retangulo Janela::escreve(const std::string& texto,
      const gui::Ponto& pt,
      const gui::Fonte& fonte,
      const gui::Cor& cor) {
    return escreve_(texto, pt.X, pt.Y, fonte, cor);
}
}
