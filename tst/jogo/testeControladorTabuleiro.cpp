
#include "testeControladorTabuleiro.h"
#include "jogo/ControladorTabuleiro.h"

#include <stdexcept>
#include <utility>

namespace jogo {
namespace tst {
namespace {

static void confereCriaPecaInvalida(ControladorTabuleiro & cont,
                                    const std::string & msg) {
    try {
        const auto peca = cont.criaPeca();
        cont.adicionaPeca(peca);
        TS_FAIL("não ocorreu " + msg);
    } catch (std::exception & e) {
        TS_ASSERT_EQUALS(e.what(), msg);
    }
}

} // unnamed namespace

void TesteControladorTabuleiro::testeCriacao() {
    peca::Tabuleiro tabuleiro(10, 20, gui::Branco);
    ControladorTabuleiro contr(tabuleiro, 4);
    TS_ASSERT(contr.temPeca() == false);
}

void TesteControladorTabuleiro::testeCriacaoInvalida() {
    peca::Tabuleiro tabuleiro(10, 20, gui::Branco);
    TS_ASSERT_THROWS_NOTHING(ControladorTabuleiro t(tabuleiro, 4));

    // tamanho da peça nula
    TS_ASSERT_THROWS(ControladorTabuleiro c(tabuleiro, 0), std::invalid_argument);
}

void TesteControladorTabuleiro::testeCriaPeca() {
    peca::Tabuleiro branco(10, 20, gui::Branco);
    ControladorTabuleiro contr(branco, 4);
    constexpr uint16_t QTD = 5;

    std::vector<peca::Peca> pecas;
    for (uint16_t i = 0; i < QTD; ++i) {
        pecas.push_back(contr.criaPeca());
    }
    uint16_t iguais = 0;
    for (uint16_t i = 0; i < QTD - 1; ++i) {
        if (pecas[i] == pecas[i + 1])
            ++iguais;
    }

    TS_ASSERT_LESS_THAN(iguais, QTD - 1);
}

void TesteControladorTabuleiro::testeAdicionaPeca() {
    peca::Tabuleiro branco(10, 20, gui::Branco);
    ControladorTabuleiro contr(branco, 4);

    const auto peca = contr.criaPeca();

    TS_ASSERT(contr.temPeca() == false);
    TS_ASSERT_THROWS(contr.posicaoPeca(), std::logic_error);
    TS_ASSERT_THROWS(contr.peca(), std::logic_error);

    TS_ASSERT(contr.adicionaPeca(peca));

    TS_ASSERT(contr.temPeca() == true);
    TS_ASSERT_EQUALS(contr.peca(), peca);
    TS_ASSERT_EQUALS(contr.posicaoPeca().linha(), 0u);
    TS_ASSERT_EQUALS(contr.posicaoPeca().subLinha(), 0u);
    TS_ASSERT_LESS_THAN(contr.posicaoPeca().coluna(), 10u);
}

void TesteControladorTabuleiro::testeAdicionaPecaInvalida() {
    peca::Tabuleiro branco(10, 20, gui::Branco);
    ControladorTabuleiro contr(branco, 4);

    const auto peca = contr.criaPeca();

    TS_ASSERT(contr.adicionaPeca(peca));
    TS_ASSERT(contr.temPeca() == true);

    confereCriaPecaInvalida(contr, "ControladorTabuleiro::criaPeca - há peça caindo no tabuleiro");
}

void TesteControladorTabuleiro::testePasso() {
    using namespace std::rel_ops;

    const peca::Tabuleiro b0(10, 20, gui::Branco);
    ControladorTabuleiro branco(b0, 4);
    TS_ASSERT(branco.tabuleiro() == b0);
    const auto peca = branco.criaPeca();

    TS_ASSERT(branco.adicionaPeca(peca));
    const uint16_t col = branco.posicaoPeca().coluna();
    TS_ASSERT(branco.tabuleiro() == b0);
    uint16_t linha = 0;
    uint16_t sublinha = 0;
    while (branco.temPeca()) {
        const peca::PosicaoPeca & posic = branco.posicaoPeca();
        TS_ASSERT_EQUALS(posic.coluna(), col);
        TS_ASSERT_EQUALS(posic.linha(), linha);
        TS_ASSERT_EQUALS(posic.subLinha(), sublinha);
        TS_ASSERT_EQUALS(posic.maxSubLinha(), 4u);
        TS_ASSERT(branco.tabuleiro() == b0);
        branco.passo();
        if (sublinha == 3) {
            ++linha;
            sublinha = 0;
        } else {
            ++sublinha;
        }
    }

    TS_ASSERT(branco.tabuleiro() != b0);

    std::vector<gui::Cor> cores;
    for (unsigned char i = 0; i < peca::TAMANHO_PECA; ++i) {
        cores.push_back(branco.tabuleiro().at(col, branco.tabuleiro().altura() - peca::TAMANHO_PECA + i));
    }
    const peca::Peca fixada(cores);
    TS_ASSERT_EQUALS(fixada, peca);
}

void TesteControladorTabuleiro::testeMove() {
    peca::Tabuleiro tbbranco(10, 20, gui::Branco);
    ControladorTabuleiro branco(tbbranco, 4);

    const auto peca = branco.criaPeca();
    TS_ASSERT(branco.adicionaPeca(peca));

    peca::PosicaoPeca posic = branco.posicaoPeca();
    TS_ASSERT_LESS_THAN(posic.coluna(), tbbranco.largura());
    TS_ASSERT_EQUALS(posic.linha(), 0u);
    TS_ASSERT_EQUALS(posic.subLinha(), 0u);
    TS_ASSERT_EQUALS(posic.maxSubLinha(), 4u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    while (posic.coluna() < 2u) {
        branco.moveDireita();
        posic = branco.posicaoPeca();
    }
    while (posic.coluna() > 2u) {
        branco.moveEsquerda();
        posic = branco.posicaoPeca();
    }

    TS_ASSERT_EQUALS(posic.coluna(), 2u);
    TS_ASSERT_EQUALS(posic.linha(), 0u);
    TS_ASSERT_EQUALS(posic.subLinha(), 0u);
    TS_ASSERT_EQUALS(posic.maxSubLinha(), 4u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    TS_ASSERT_EQUALS(posic.coluna(), 1u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    TS_ASSERT_EQUALS(posic.coluna(), 0u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    TS_ASSERT_EQUALS(posic.coluna(), 0u);

    for (uint16_t i = 0; i < 10; ++i) {
        posic = branco.posicaoPeca();
        TS_ASSERT_EQUALS(posic.coluna(), i);
        branco.moveDireita();
    }
    posic = branco.posicaoPeca();
    TS_ASSERT_EQUALS(posic.coluna(), 9u);
}

void TesteControladorTabuleiro::testeDeterminaEliminacao() {
    peca::Tabuleiro tbbranco(10, 20, gui::Branco);
    ListaEliminacao eliminacao;

    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);

    // situação inicial
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - .....
    // vai preencher as três peças no fundo à esquerda (horizontal)
    tbbranco.at(0, 19) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - p....
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);
    tbbranco.at(1, 19) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - pp...
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);
    tbbranco.at(2, 19) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //           essas serão eliminadas --> 19 - PPP..
    eliminacao = ControladorTabuleiro(tbbranco, 4).determinaEliminacao();
    TS_ASSERT_EQUALS(eliminacao.size(), 3u);
    TS_ASSERT_EQUALS(eliminacao.at(0).first, 0u);
    TS_ASSERT_EQUALS(eliminacao.at(0).second, 19u);
    TS_ASSERT_EQUALS(eliminacao.at(1).first, 1u);
    TS_ASSERT_EQUALS(eliminacao.at(1).second, 19u);
    TS_ASSERT_EQUALS(eliminacao.at(2).first, 2u);
    TS_ASSERT_EQUALS(eliminacao.at(2).second, 19u);

    // vai preencher as três peças no fundo à esquerda (vertical)
    tbbranco.at(0, 18) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - p....
    //                                      19 - PPP..
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 3u);
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(0, 17) = gui::Preto;
    //                                           01234
    //  agora serão eliminadas a primeira   15 - .....
    //  linha e a primeira coluna, mas o    16 - .....
    //  preenchiemnto é feito da esquerda   17 - P....
    //  para a direita e de cima para       18 - P....
    //  baixo                               19 - PPP..
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 18));
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 17));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai preencher a diagonal que começa no canto inferior esquerdo
    tbbranco.at(1, 18) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P....
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 3, ItemEliminacao(1, 18));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(2, 17) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 5, ItemEliminacao(2, 17));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai colocar uma quarta peça na sequência

    tbbranco.at(0, 16) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 16));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(3, 16) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 8, ItemEliminacao(3, 16));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(3, 19) = gui::Preto;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPPP.
    eliminacao.insert(eliminacao.begin() + 9, ItemEliminacao(3, 19));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);


    // vai adicionar de outra cor e não vai alterar
    tbbranco.at(1, 16) = gui::Azul;
    tbbranco.at(2, 16) = gui::Azul;
    tbbranco.at(1, 17) = gui::Azul;
    tbbranco.at(3, 17) = gui::Azul;
    tbbranco.at(2, 18) = gui::Azul;
    tbbranco.at(3, 18) = gui::Azul;
    //                                           01234
    //                                      15 - .....
    //                                      16 - PzzP.
    //                                      17 - PzPz.
    //                                      18 - PPzz.
    //                                      19 - PPPP.
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    // vai adicionar de outra cor que vai acrescentar vários
    tbbranco.at(4, 18) = gui::Azul;
    //                                           01234
    //                                      15 - .....
    //                                      16 - PzZP.
    //                                      17 - PzPZ.
    //                                      18 - PPZZZ
    //                                      19 - PPPP.
    eliminacao.insert(eliminacao.begin() + 6, ItemEliminacao(2, 16));
    eliminacao.insert(eliminacao.begin() + 8, ItemEliminacao(2, 18));
    eliminacao.insert(eliminacao.begin() + 11, ItemEliminacao(3, 17));
    eliminacao.insert(eliminacao.begin() + 12, ItemEliminacao(3, 18));
    eliminacao.insert(eliminacao.begin() + 14, ItemEliminacao(4, 18));
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai colocar outras cores e não vai alterar
    tbbranco.at(0, 15) = gui::Verde;
    tbbranco.at(1, 15) = gui::Verde;
    tbbranco.at(2, 15) = gui::Vermelho;
    tbbranco.at(3, 15) = gui::Verde;
    tbbranco.at(4, 15) = gui::Vermelho;
    tbbranco.at(4, 16) = gui::Verde;
    tbbranco.at(4, 17) = gui::Verde;
    tbbranco.at(4, 19) = gui::Verde;
    //                                           01234
    //                                      15 - vvmvm
    //                                      16 - PzZPv
    //                                      17 - PzPZv
    //                                      18 - PPZZZ
    //                                      19 - PPPPv
    TS_ASSERT_EQUALS(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
}

}
}
