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

void Janela::linha(const gui::Point& ini,
      const gui::Point& fim,
      const gui::Color& cor) {
    linha_(ini.X, ini.Y, fim.X, fim.Y, cor);
}

void Janela::retangulo(const gui::Rectangle& ret,
      const gui::Color& cor) {
    retangulo_(ret.P1().X, ret.P1().Y, ret.P2().X, ret.P2().Y, cor);
}

void Janela::retangulo(const gui::Point& te,
      const gui::Point& fd,
      const gui::Color& cor) {
    retangulo_(te.X, te.Y, fd.X, fd.Y, cor);
}

void Janela::preenche(const gui::Rectangle& ret,
      const gui::Color& cor) {
    preenche_(ret.P1().X, ret.P1().Y, ret.P2().X, ret.P2().Y, cor);
}

void Janela::preenche(const gui::Point& te,
      const gui::Point& fd,
      const gui::Color& cor) {
    preenche_(te.X, te.Y, fd.X, fd.Y, cor);
}

gui::Rectangle Janela::escreve(const std::string& texto,
      const gui::Point& pt,
      const gui::Fonte& fonte,
      const gui::Color& cor) {
    return escreve_(texto, pt.X, pt.Y, fonte, cor);
}
}
