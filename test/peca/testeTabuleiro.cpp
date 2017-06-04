#include "../mck/peca/utilpeca.h"

#include "peca/Tabuleiro.h"

#include "gtest/gtest.h"

#include <stdexcept>
#include <utility>

namespace peca {
namespace tst {
namespace {

static void confereTabuleiroVazio(const std::string& msg,
                                  uint16_t l,
                                  uint16_t h,
                                  const gui::Cor& cor) {
    EXPECT_TRUE(l > 0) << msg;
    EXPECT_TRUE(h > 0) << msg;
    const Tabuleiro tabuleiro(l, h, cor);
    EXPECT_EQ(tabuleiro.largura(), l) << msg;
    EXPECT_EQ(tabuleiro.altura(), h) << msg;
    EXPECT_EQ(tabuleiro.cor(), cor) << msg;

    for (uint16_t i = 0; i < l; ++i) {
        for (uint16_t j = 0; j < h; ++j) {
            EXPECT_EQ(tabuleiro.at(i, j), cor) << msg;
        }
    }

    EXPECT_THROW(tabuleiro.at(l, 0), std::invalid_argument) << msg;
    EXPECT_THROW(tabuleiro.at(0, h), std::invalid_argument) << msg;
}

} // unnamed namespace

TEST(TesteTabuleiro, Criacao) {
    confereTabuleiroVazio("t1", 10, 20, gui::Branco);
    confereTabuleiroVazio("t2", 15, 50, gui::Vermelho);
    confereTabuleiroVazio("t3", 7, 10, gui::Preto);
}

TEST(TesteTabuleiro, Copia) {
    Tabuleiro branco(12, 25, gui::Branco);
    Tabuleiro copia(branco);
    EXPECT_EQ(branco, copia);

    Tabuleiro preto(12, 25, gui::Preto);
    EXPECT_NE(preto, copia);

    copia = preto;
    EXPECT_EQ(preto, copia);
    EXPECT_NE(preto, branco);
}

TEST(TesteTabuleiro, CriacaoInvalida) {
    EXPECT_NO_THROW(Tabuleiro(10, 20, gui::Branco));
    uint16_t i;
    for (i = 0; i < TAMANHO_PECA; ++i) {
        EXPECT_THROW(Tabuleiro(i, 2 * TAMANHO_PECA, gui::Branco), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Tabuleiro(i, 20, gui::Branco));
    for (i = 0; i < 2 * TAMANHO_PECA; ++i) {
        EXPECT_THROW(Tabuleiro(10, i, gui::Branco), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Tabuleiro(TAMANHO_PECA, i, gui::Branco));
}

TEST(TesteTabuleiro, Alteracao) {
    const uint16_t LARGURA = 35;
    const uint16_t ALTURA = 36;

    Tabuleiro tab(LARGURA, ALTURA, gui::Branco);
    EXPECT_EQ(tab.cor(), gui::Branco);
    EXPECT_EQ(tab.largura(), LARGURA);
    EXPECT_EQ(tab.altura(), ALTURA);

    for (uint16_t i = 0; i < LARGURA; ++i) {
        for (uint16_t j = 0; j < ALTURA; ++j) {
            for (uint16_t ii = 0; ii < i; ++ii) { // as colunas anteriores estão coloridas
                for (uint16_t jj = 0; jj < ALTURA; ++jj) {
                    const gui::Cor cor(ii, jj, 0);
                    EXPECT_EQ(tab.at(ii, jj), cor);
                }
            }
            for (uint16_t jj = 0; jj < ALTURA; ++jj) { // na coluna atual
                if (jj < j) { // as linhas abaixo de j estão coloridas
                    const gui::Cor cor(i, jj, 0);
                    EXPECT_EQ(tab.at(i, jj), cor);
                } else { // as outras ainda estão brancas
                    EXPECT_EQ(tab.at(i, jj), gui::Branco);
                }
            }
            for (uint16_t ii = i + 1; ii < LARGURA; ++ii) { // nas colunas posteriores estão brancas
                for (uint16_t jj = 0; jj < ALTURA; ++jj) {
                    EXPECT_EQ(tab.at(ii, jj), gui::Branco);
                }
            }

            // troca a cor do elemento
            const gui::Cor cor(i, j, 0);
            tab.at(i, j) = cor;
        }
    }

    EXPECT_EQ(tab.cor(), gui::Branco);
    EXPECT_EQ(tab.largura(), LARGURA);
    EXPECT_EQ(tab.altura(), ALTURA);
}

TEST(TesteTabuleiro, Comparacao) {
    std::vector<Tabuleiro> vec;
    vec.push_back(Tabuleiro(10, 20, gui::Branco));
    vec.push_back(Tabuleiro(11, 20, gui::Branco));
    vec.push_back(Tabuleiro(11, 21, gui::Branco));
    vec.push_back(Tabuleiro(11, 21, gui::Azul));

    for (uint16_t i = 0; i < vec.size(); ++i) {
        for (uint16_t j = 0; j < vec.size(); ++j) {
            if (i == j) {
                EXPECT_EQ(vec[i], vec[j]);
            } else {
                EXPECT_NE(vec[i], vec[j]);
            }
        }
    }

    const Tabuleiro tab0(10, 20, gui::Preto);
    Tabuleiro tab1(10, 20, gui::Preto);
    for (uint16_t i = 0; i < 10; ++i) {
        for (uint16_t j = 0; j < 10; ++j) {
            EXPECT_EQ(tab0, tab1);
            tab1.at(i, j) = gui::Verde;
            EXPECT_NE(tab0, tab1);
            tab1.at(i, j) = gui::Preto;
            EXPECT_EQ(tab0, tab1);
        }
    }
}

TEST(TesteTabuleiro, Elimina) {
    const uint16_t colunas = 5;
    const uint16_t linhas = 7;
    std::vector<gui::Cor> casas(colunas * linhas, gui::Preto);
    Tabuleiro tab(colunas, linhas, gui::Preto);

    EXPECT_EQ(tab.casas(), casas);

    for (uint16_t i = 0; i < colunas; ++i) {
        for (uint16_t j = 0; j < linhas; ++j) {
            const gui::Cor cor(i + 1, j + 1, 0);
            casas.at(j * colunas + i) = tab.at(i, j) = cor;
        }
    }

    EXPECT_EQ(tab.casas(), casas);

    //printTabuleiro(tab);

    // ce = coluna a eliminar
    for (uint16_t ce = 0; ce < colunas; ++ce) {
        tab.elimina(ce, 4);
        for (uint16_t le = 4; le > 0; --le) {
            casas.at(le * colunas + ce) = casas.at((le - 1) * colunas + ce);
        }
        casas.at(0 * colunas + ce) = gui::Preto;
        EXPECT_EQ(tab.casas(), casas);
    }

    //printTabuleiro(tab);

    for (uint16_t i = 0; i < colunas; ++i) {
        for (uint16_t j = 0; j < linhas; ++j) {
            const gui::Cor cor(i + 1, j + 1, 0);
            casas.at(j * colunas + i) = tab.at(i, j) = cor;
        }
    }

    for (uint16_t le = linhas - 1; le > 0; --le) {
        for (uint16_t ce = 0; ce < colunas; ++ce) {
            tab.elimina(ce, le);
            for (uint16_t LE = le; LE > 0; --LE) {
                casas.at(LE * colunas + ce) = casas.at((LE - 1) * colunas + ce);
            }
            casas.at(0 * colunas + ce) = gui::Preto;
            EXPECT_EQ(tab.casas(), casas);
        }
        //printTabuleiro(tab);
    }
}

}
}
