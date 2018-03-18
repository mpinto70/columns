
#include "jogo/ControladorTabuleiro.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

namespace jogo {
namespace tst {
namespace {

static void confereCriaPecaInvalida(ControladorTabuleiro& cont,
      const std::string& msg) {
    try {
        const auto piece = cont.criaPeca();
        cont.adicionaPeca(piece);
        FAIL() << "não ocorreu " + msg;
    } catch (std::exception& e) {
        EXPECT_EQ(e.what(), msg);
    }
}

} // unnamed namespace

TEST(TesteControladorTabuleiro, Criacao) {
    piece::Board tabuleiro(10, 20, gui::WHITE);
    ControladorTabuleiro contr(tabuleiro, 4);
    EXPECT_TRUE(contr.temPeca() == false);
}

TEST(TesteControladorTabuleiro, CriacaoInvalida) {
    piece::Board tabuleiro(10, 20, gui::WHITE);
    EXPECT_NO_THROW(ControladorTabuleiro t(tabuleiro, 4));

    // tamanho da peça nula
    EXPECT_THROW(ControladorTabuleiro c(tabuleiro, 0), std::invalid_argument);
}

TEST(TesteControladorTabuleiro, CriaPeca) {
    piece::Board branco(10, 20, gui::WHITE);
    ControladorTabuleiro contr(branco, 4);
    constexpr uint16_t QTD = 5;

    std::vector<piece::Piece> pecas;
    for (uint16_t i = 0; i < QTD; ++i) {
        pecas.push_back(contr.criaPeca());
    }
    uint16_t iguais = 0;
    for (uint16_t i = 0; i < QTD - 1; ++i) {
        if (pecas[i] == pecas[i + 1]) {
            ++iguais;
        }
    }

    EXPECT_LT(iguais, QTD - 1);
}

TEST(TesteControladorTabuleiro, AdicionaPeca) {
    piece::Board branco(10, 20, gui::WHITE);
    ControladorTabuleiro contr(branco, 4);

    const auto piece = contr.criaPeca();

    EXPECT_TRUE(contr.temPeca() == false);
    EXPECT_THROW(contr.posicaoPeca(), std::logic_error);
    EXPECT_THROW(contr.piece(), std::logic_error);

    EXPECT_TRUE(contr.adicionaPeca(piece));

    EXPECT_TRUE(contr.temPeca() == true);
    EXPECT_EQ(contr.piece(), piece);
    EXPECT_EQ(contr.posicaoPeca().row(), 0u);
    EXPECT_EQ(contr.posicaoPeca().sub_row(), 0u);
    EXPECT_LT(contr.posicaoPeca().column(), 10u);
}

TEST(TesteControladorTabuleiro, AdicionaPecaInvalida) {
    piece::Board branco(10, 20, gui::WHITE);
    ControladorTabuleiro contr(branco, 4);

    const auto piece = contr.criaPeca();

    EXPECT_TRUE(contr.adicionaPeca(piece));
    EXPECT_TRUE(contr.temPeca() == true);

    confereCriaPecaInvalida(contr, "ControladorTabuleiro::criaPeca - há peça caindo no tabuleiro");
}

TEST(TesteControladorTabuleiro, Passo) {
    using namespace std::rel_ops;

    const piece::Board b0(10, 20, gui::WHITE);
    ControladorTabuleiro branco(b0, 4);
    EXPECT_TRUE(branco.tabuleiro() == b0);
    const auto piece = branco.criaPeca();

    EXPECT_TRUE(branco.adicionaPeca(piece));
    const uint16_t col = branco.posicaoPeca().column();
    EXPECT_TRUE(branco.tabuleiro() == b0);
    uint16_t linha = 0;
    uint16_t sublinha = 0;
    while (branco.temPeca()) {
        const piece::PiecePosition& posic = branco.posicaoPeca();
        EXPECT_EQ(posic.column(), col);
        EXPECT_EQ(posic.row(), linha);
        EXPECT_EQ(posic.sub_row(), sublinha);
        EXPECT_EQ(posic.max_sub_row(), 4u);
        EXPECT_TRUE(branco.tabuleiro() == b0);
        branco.passo();
        if (sublinha == 3) {
            ++linha;
            sublinha = 0;
        } else {
            ++sublinha;
        }
    }

    EXPECT_TRUE(branco.tabuleiro() != b0);

    std::vector<gui::Color> cores;
    for (unsigned char i = 0; i < piece::PIECE_SIZE; ++i) {
        cores.push_back(branco.tabuleiro().at(col, branco.tabuleiro().height() - piece::PIECE_SIZE + i));
    }
    const piece::Piece fixada(cores);
    EXPECT_EQ(fixada, piece);
}

TEST(TesteControladorTabuleiro, Move) {
    piece::Board tbbranco(10, 20, gui::WHITE);
    ControladorTabuleiro branco(tbbranco, 4);

    const auto piece = branco.criaPeca();
    EXPECT_TRUE(branco.adicionaPeca(piece));

    piece::PiecePosition posic = branco.posicaoPeca();
    EXPECT_LT(posic.column(), tbbranco.width());
    EXPECT_EQ(posic.row(), 0u);
    EXPECT_EQ(posic.sub_row(), 0u);
    EXPECT_EQ(posic.max_sub_row(), 4u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    while (posic.column() < 2u) {
        branco.moveDireita();
        posic = branco.posicaoPeca();
    }
    while (posic.column() > 2u) {
        branco.moveEsquerda();
        posic = branco.posicaoPeca();
    }

    EXPECT_EQ(posic.column(), 2u);
    EXPECT_EQ(posic.row(), 0u);
    EXPECT_EQ(posic.sub_row(), 0u);
    EXPECT_EQ(posic.max_sub_row(), 4u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    EXPECT_EQ(posic.column(), 1u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    EXPECT_EQ(posic.column(), 0u);

    branco.moveEsquerda();

    posic = branco.posicaoPeca();
    EXPECT_EQ(posic.column(), 0u);

    for (uint16_t i = 0; i < 10; ++i) {
        posic = branco.posicaoPeca();
        EXPECT_EQ(posic.column(), i);
        branco.moveDireita();
    }
    posic = branco.posicaoPeca();
    EXPECT_EQ(posic.column(), 9u);
}

TEST(TesteControladorTabuleiro, DeterminaEliminacao) {
    piece::Board tbbranco(10, 20, gui::WHITE);
    ListaEliminacao eliminacao;

    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);

    // situação inicial
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - .....
    // vai preencher as três peças no fundo à esquerda (horizontal)
    tbbranco.at(0, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - p....
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);
    tbbranco.at(1, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //                                      19 - pp...
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 0u);
    tbbranco.at(2, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - .....
    //           essas serão eliminadas --> 19 - PPP..
    eliminacao = ControladorTabuleiro(tbbranco, 4).determinaEliminacao();
    EXPECT_EQ(eliminacao.size(), 3u);
    EXPECT_EQ(eliminacao.at(0).first, 0u);
    EXPECT_EQ(eliminacao.at(0).second, 19u);
    EXPECT_EQ(eliminacao.at(1).first, 1u);
    EXPECT_EQ(eliminacao.at(1).second, 19u);
    EXPECT_EQ(eliminacao.at(2).first, 2u);
    EXPECT_EQ(eliminacao.at(2).second, 19u);

    // vai preencher as três peças no fundo à esquerda (vertical)
    tbbranco.at(0, 18) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - .....
    //                                      18 - p....
    //                                      19 - PPP..
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao().size(), 3u);
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(0, 17) = gui::BLACK;
    //                                           01234
    //  agora serão eliminadas a primeira   15 - .....
    //  linha e a primeira coluna, mas o    16 - .....
    //  preenchiemnto é feito da esquerda   17 - P....
    //  para a direita e de cima para       18 - P....
    //  baixo                               19 - PPP..
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 18));
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 17));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai preencher a diagonal que começa no canto inferior esquerdo
    tbbranco.at(1, 18) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P....
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 3, ItemEliminacao(1, 18));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(2, 17) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - .....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 5, ItemEliminacao(2, 17));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai colocar uma quarta peça na sequência

    tbbranco.at(0, 16) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P....
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 0, ItemEliminacao(0, 16));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(3, 16) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPP..
    eliminacao.insert(eliminacao.begin() + 8, ItemEliminacao(3, 16));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    tbbranco.at(3, 19) = gui::BLACK;
    //                                           01234
    //                                      15 - .....
    //                                      16 - P..P.
    //                                      17 - P.P..
    //                                      18 - PP...
    //                                      19 - PPPP.
    eliminacao.insert(eliminacao.begin() + 9, ItemEliminacao(3, 19));
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai adicionar de outra cor e não vai alterar
    tbbranco.at(1, 16) = gui::BLUE;
    tbbranco.at(2, 16) = gui::BLUE;
    tbbranco.at(1, 17) = gui::BLUE;
    tbbranco.at(3, 17) = gui::BLUE;
    tbbranco.at(2, 18) = gui::BLUE;
    tbbranco.at(3, 18) = gui::BLUE;
    //                                           01234
    //                                      15 - .....
    //                                      16 - PzzP.
    //                                      17 - PzPz.
    //                                      18 - PPzz.
    //                                      19 - PPPP.
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
    // vai adicionar de outra cor que vai acrescentar vários
    tbbranco.at(4, 18) = gui::BLUE;
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
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);

    // vai colocar outras cores e não vai alterar
    tbbranco.at(0, 15) = gui::GREEN;
    tbbranco.at(1, 15) = gui::GREEN;
    tbbranco.at(2, 15) = gui::RED;
    tbbranco.at(3, 15) = gui::GREEN;
    tbbranco.at(4, 15) = gui::RED;
    tbbranco.at(4, 16) = gui::GREEN;
    tbbranco.at(4, 17) = gui::GREEN;
    tbbranco.at(4, 19) = gui::GREEN;
    //                                           01234
    //                                      15 - vvmvm
    //                                      16 - PzZPv
    //                                      17 - PzPZv
    //                                      18 - PPZZZ
    //                                      19 - PPPPv
    EXPECT_EQ(ControladorTabuleiro(tbbranco, 4).determinaEliminacao(), eliminacao);
}
}
}
