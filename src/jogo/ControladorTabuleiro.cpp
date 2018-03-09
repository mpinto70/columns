
#include "ControladorTabuleiro.h"
#include "pontuacao/Placar.h"
#include "util/Aleatorio.h"

#include <map>
#include <stdexcept>
#include <utility>

namespace jogo {

ControladorTabuleiro::ControladorTabuleiro(const peca::Tabuleiro& tabuleiro,
      const uint16_t maxSubLinha)
      : tabuleiro_(tabuleiro),
        maxSubLinha_(maxSubLinha),
        possiveis_{ gui::Verde, gui::Vermelho, gui::Azul, gui::Amarelo, gui::Lavanda } {
    if (maxSubLinha_ == 0) {
        throw std::invalid_argument("ControladorTabuleiro - m�ximo de subdivis�es do quadrado nulo");
    }
}

bool ControladorTabuleiro::adicionaPeca(const peca::Peca& peca) {
    if (temPeca()) {
        throw std::logic_error("ControladorTabuleiro::adicionaPeca - h� pe�a caindo no tabuleiro");
    }

    const uint16_t c = determinaColuna();
    if (c == tabuleiro_.largura()) {
        return false;
    }

    for (unsigned char i = 0; i < peca::TAMANHO_PECA; ++i)
        if (peca[i] == tabuleiro_.cor()) {
            throw std::invalid_argument("ControladorTabuleiro::adicionaPeca - pe�a com cor de fundo");
        }

    posicaoPeca_.reset(new peca::PosicaoPeca(tabuleiro_, c, maxSubLinha_));
    peca_.reset(new peca::Peca(peca));
    return true;
}

const peca::PosicaoPeca& ControladorTabuleiro::posicaoPeca() const {
    if (not temPeca()) {
        throw std::logic_error("ControladorTabuleiro::posicaoPeca - n�o h� pe�a caindo no tabuleiro");
    }
    return *posicaoPeca_;
}

const peca::Peca& ControladorTabuleiro::peca() const {
    if (not temPeca()) {
        throw std::logic_error("ControladorTabuleiro::peca - n�o h� pe�a caindo no tabuleiro");
    }
    return *peca_;
}

void ControladorTabuleiro::passo() {
    if (not temPeca()) {
        return;
    }

    const uint16_t linhaPeca = posicaoPeca_->linha();
    const uint16_t colunaPeca = posicaoPeca_->coluna();
    if (atingiuFim()) {
        const peca::Peca& peca = *peca_;
        for (unsigned char i = 0; i < peca::TAMANHO_PECA; ++i) {
            tabuleiro_.at(colunaPeca, linhaPeca + i) = peca[i];
        }
        peca_.reset();
        posicaoPeca_.reset();
    } else { // ainda h� espa�o para cair
        posicaoPeca_->caiUmPasso();
    }
}

void ControladorTabuleiro::moveEsquerda() {
    if (not temPeca()) {
        return;
    }

    const uint16_t colunaPeca = posicaoPeca_->coluna();
    if (podeMoverPara(colunaPeca - 1)) {
        posicaoPeca_->moveEsquerda();
    }
}

void ControladorTabuleiro::moveDireita() {
    if (not temPeca()) {
        return;
    }

    const uint16_t colunaPeca = posicaoPeca_->coluna();
    if (podeMoverPara(colunaPeca + 1)) {
        posicaoPeca_->moveDireita();
    }
}

void ControladorTabuleiro::rolaParaCima() {
    if (not temPeca()) {
        return;
    }

    peca_->rolaParaCima();
}

void ControladorTabuleiro::rolaParaBaixo() {
    if (not temPeca()) {
        return;
    }

    peca_->rolaParaBaixo();
}

ListaEliminacao ControladorTabuleiro::determinaEliminacao() const {
    ListaEliminacao eliminaveis;
    for (uint16_t c = 0; c < tabuleiro_.largura(); ++c) {
        for (uint16_t l = 0; l < tabuleiro_.altura(); ++l) {
            if (deveEliminar(c, l)) {
                eliminaveis.push_back(std::make_pair(c, l));
            }
        }
    }
    return eliminaveis;
}

void ControladorTabuleiro::elimina(const ListaEliminacao& casas) {
    for (uint16_t i = 0; i < casas.size(); ++i) {
        const uint16_t col = casas[i].first;
        const uint16_t lin = casas[i].second;
        tabuleiro_.elimina(col, lin);
    }
}

Situacao ControladorTabuleiro::situacao() const {
    if (temPeca()) {
        return Situacao(tabuleiro_, pontuacao::Placar(), *peca_, *posicaoPeca_, peca::Peca({ gui::Azul, gui::Azul, gui::Azul }));
    } else {
        return Situacao(tabuleiro_, pontuacao::Placar(), determinaEliminacao(), peca::Peca({ gui::Azul, gui::Azul, gui::Azul }));
    }
}

bool ControladorTabuleiro::podeMoverPara(uint16_t coluna) const {
    using namespace std::rel_ops;

    if (not temPeca()) {
        return false;
    }

    if (coluna >= tabuleiro_.largura()) {
        return false;
    }

    const uint16_t linhaPeca = posicaoPeca_->linha();
    const uint16_t sublinhaPeca = posicaoPeca_->subLinha();

    for (uint16_t l = linhaPeca; l < linhaPeca + peca::TAMANHO_PECA; ++l) {
        if (tabuleiro_.at(coluna, l) != tabuleiro_.cor()) {
            return false;
        }
    }
    if (sublinhaPeca > 0 && tabuleiro_.at(coluna, linhaPeca + peca::TAMANHO_PECA) != tabuleiro_.cor()) {
        return false;
    }

    return true;
}

uint16_t ControladorTabuleiro::determinaColuna() const {
    std::vector<uint16_t> livres;
    for (uint16_t i = 0; i < tabuleiro_.largura(); ++i) {
        if (podeColocarPeca(i)) {
            livres.push_back(i);
        }
    }
    if (livres.size() == 0) {
        return tabuleiro_.largura();
    } else {
        const uint16_t idx = util::Aleatorio::gera(livres.size() - 1);
        return livres[idx];
    }
}

bool ControladorTabuleiro::podeColocarPeca(uint16_t coluna) const {
    using namespace std::rel_ops;
    for (unsigned char i = 0; i < peca::TAMANHO_PECA; ++i)
        if (tabuleiro_.at(coluna, i) != tabuleiro_.cor()) {
            return false;
        }
    return true;
}

bool ControladorTabuleiro::atingiuFim() const {
    using namespace std::rel_ops;
    if (not temPeca()) {
        return false;
    }

    // chegou ao fundo
    if (posicaoPeca_->chegouAoFundo()) {
        return true;
    }

    const uint16_t sublinhaPeca = posicaoPeca_->subLinha();
    // est� numa situa��o no meio de uma pe�a
    if (sublinhaPeca != 0) {
        return false;
    }

    const uint16_t linhaPeca = posicaoPeca_->linha();
    const uint16_t colunaPeca = posicaoPeca_->coluna();
    // est� sobre uma pe�a n�o vazia
    if (tabuleiro_.at(colunaPeca, linhaPeca + peca::TAMANHO_PECA) != tabuleiro_.cor()) {
        return true;
    }

    return false;
}

bool ControladorTabuleiro::deveEliminar(const uint16_t coluna,
      const uint16_t linha) const {
    const gui::Cor cor = tabuleiro_.at(coluna, linha);
    if (cor == tabuleiro_.cor()) {
        return false;
    }

    int c0 = coluna - 2;
    int c1 = coluna + 2;
    int l0 = linha - 2;
    int l1 = linha + 2;

    if (c0 < 0) {
        c0 = 0;
    }
    if (l0 < 0) {
        l0 = 0;
    }
    if (c1 >= (int) tabuleiro_.largura()) {
        c1 = tabuleiro_.largura() - 1;
    }
    if (l1 >= (int) tabuleiro_.altura()) {
        l1 = tabuleiro_.altura() - 1;
    }

    std::map<int, std::map<int, bool>> grid;
    for (int c = -2; c <= 2; ++c) {
        for (int l = -2; l <= 2; ++l) {
            grid[c][l] = false;
        }
    }

    for (int c = c0; c <= c1; ++c) {
        for (int l = l0; l <= l1; ++l) {
            if (tabuleiro_.at(c, l) == cor) {
                int cc = c - coluna;
                int ll = l - linha;
                grid[cc][ll] = true;
            }
        }
    }

    // diagonais
    if (grid[-2][-2] && grid[-1][-1]) {
        return true;
    }
    if (grid[-1][-1] && grid[+1][+1]) {
        return true;
    }
    if (grid[+1][+1] && grid[+2][+2]) {
        return true;
    }
    if (grid[-2][+2] && grid[-1][+1]) {
        return true;
    }
    if (grid[-1][+1] && grid[+1][-1]) {
        return true;
    }
    if (grid[+1][-1] && grid[+2][-2]) {
        return true;
    }

    // perpendiculares
    if (grid[0][-2] && grid[0][-1]) {
        return true;
    }
    if (grid[0][-1] && grid[0][+1]) {
        return true;
    }
    if (grid[0][+1] && grid[0][+2]) {
        return true;
    }
    if (grid[-2][0] && grid[-1][0]) {
        return true;
    }
    if (grid[-1][0] && grid[+1][0]) {
        return true;
    }
    if (grid[+1][0] && grid[+2][0]) {
        return true;
    }
    return false;
}
}
