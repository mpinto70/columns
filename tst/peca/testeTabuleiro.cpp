
#include "testeTabuleiro.h"
#include "../mck/peca/utilpeca.h"

#include "peca/Tabuleiro.h"

#include <stdexcept>
#include <utility>

namespace peca {
namespace tst {
namespace {

static void confereTabuleiroVazio(const std::string & msg,
                                  uint16_t l,
                                  uint16_t h,
                                  const gui::Cor & cor) {
    TSM_ASSERT(msg, l > 0);
    TSM_ASSERT(msg, h > 0)
    const Tabuleiro tabuleiro(l, h, cor);
    TSM_ASSERT_EQUALS(msg, tabuleiro.largura(), l);
    TSM_ASSERT_EQUALS(msg, tabuleiro.altura(), h);
    TSM_ASSERT_EQUALS(msg, tabuleiro.cor(), cor);

    for (uint16_t i = 0; i < l; ++i) {
        for (uint16_t j = 0; j < h; ++j) {
            TSM_ASSERT_EQUALS(msg, tabuleiro.at(i, j), cor);
        }
    }

    TSM_ASSERT_THROWS(msg, tabuleiro.at(l, 0), std::invalid_argument);
    TSM_ASSERT_THROWS(msg, tabuleiro.at(0, h), std::invalid_argument);
}

} // unnamed namespace

void TesteTabuleiro::testeCriacao() {
    confereTabuleiroVazio("t1", 10, 20, gui::Branco);
    confereTabuleiroVazio("t2", 15, 50, gui::Vermelho);
    confereTabuleiroVazio("t3", 7, 10, gui::Preto);
}

void TesteTabuleiro::testeCopia() {
    Tabuleiro branco(12, 25, gui::Branco);
    Tabuleiro copia(branco);
    TS_ASSERT_EQUALS(branco, copia);

    Tabuleiro preto(12, 25, gui::Preto);
    TS_ASSERT_DIFFERS(preto, copia);

    copia = preto;
    TS_ASSERT_EQUALS(preto, copia);
    TS_ASSERT_DIFFERS(preto, branco);
}

void TesteTabuleiro::testeCriacaoInvalida() {
    TS_ASSERT_THROWS_NOTHING(Tabuleiro(10, 20, gui::Branco));
    uint16_t i;
    for (i = 0; i < TAMANHO_PECA; ++i) {
        TSM_ASSERT_THROWS(i, Tabuleiro(i, 2 * TAMANHO_PECA, gui::Branco), std::invalid_argument);
    }
    TS_ASSERT_THROWS_NOTHING(Tabuleiro(i, 20, gui::Branco));
    for (i = 0; i < 2 * TAMANHO_PECA; ++i) {
        TSM_ASSERT_THROWS(i, Tabuleiro(10, i, gui::Branco), std::invalid_argument);
    }
    TS_ASSERT_THROWS_NOTHING(Tabuleiro(TAMANHO_PECA, i, gui::Branco));
}

void TesteTabuleiro::testeAlteracao() {
    const uint16_t LARGURA = 35;
    const uint16_t ALTURA = 36;

    Tabuleiro tab(LARGURA, ALTURA, gui::Branco);
    TS_ASSERT_EQUALS(tab.cor(), gui::Branco);
    TS_ASSERT_EQUALS(tab.largura(), LARGURA);
    TS_ASSERT_EQUALS(tab.altura(), ALTURA);

    for (uint16_t i = 0; i < LARGURA; ++i) {
        for (uint16_t j = 0; j < ALTURA; ++j) {
            for (uint16_t ii = 0; ii < i; ++ii) { // as colunas anteriores estão coloridas
                for (uint16_t jj = 0; jj < ALTURA; ++jj) {
                    const gui::Cor cor(ii, jj, 0);
                    TS_ASSERT_EQUALS(tab.at(ii, jj), cor);
                }
            }
            for (uint16_t jj = 0; jj < ALTURA; ++jj) { // na coluna atual
                if (jj < j) { // as linhas abaixo de j estão coloridas
                    const gui::Cor cor(i, jj, 0);
                    TS_ASSERT_EQUALS(tab.at(i, jj), cor);
                } else { // as outras ainda estão brancas
                    TS_ASSERT_EQUALS(tab.at(i, jj), gui::Branco);
                }
            }
            for (uint16_t ii = i + 1; ii < LARGURA; ++ii) { // nas colunas posteriores estão brancas
                for (uint16_t jj = 0; jj < ALTURA; ++jj) {
                    TS_ASSERT_EQUALS(tab.at(ii, jj), gui::Branco);
                }
            }

            // troca a cor do elemento
            const gui::Cor cor(i, j, 0);
            tab.at(i, j) = cor;
        }
    }

    TS_ASSERT_EQUALS(tab.cor(), gui::Branco);
    TS_ASSERT_EQUALS(tab.largura(), LARGURA);
    TS_ASSERT_EQUALS(tab.altura(), ALTURA);
}

void TesteTabuleiro::testeComparacao() {
    std::vector<Tabuleiro> vec;
    vec.push_back(Tabuleiro(10, 20, gui::Branco));
    vec.push_back(Tabuleiro(11, 20, gui::Branco));
    vec.push_back(Tabuleiro(11, 21, gui::Branco));
    vec.push_back(Tabuleiro(11, 21, gui::Azul));

    for (uint16_t i = 0; i < vec.size(); ++i) {
        for (uint16_t j = 0; j < vec.size(); ++j) {
            if (i == j) {
                TS_ASSERT_EQUALS(vec[i], vec[j]);
            } else {
                TS_ASSERT_DIFFERS(vec[i], vec[j]);
            }
        }
    }

    const Tabuleiro tab0(10, 20, gui::Preto);
    Tabuleiro tab1(10, 20, gui::Preto);
    for (uint16_t i = 0; i < 10; ++i) {
        for (uint16_t j = 0; j < 10; ++j) {
            TS_ASSERT_EQUALS(tab0, tab1);
            tab1.at(i, j) = gui::Verde;
            TS_ASSERT_DIFFERS(tab0, tab1);
            tab1.at(i, j) = gui::Preto;
            TS_ASSERT_EQUALS(tab0, tab1);
        }
    }
}

void TesteTabuleiro::testeElimina() {
    const uint16_t colunas = 5;
    const uint16_t linhas = 7;
    std::vector<gui::Cor> casas(colunas * linhas, gui::Preto);
    Tabuleiro tab(colunas, linhas, gui::Preto);

    TS_ASSERT_EQUALS(tab.casas(), casas);

    for (uint16_t i = 0; i < colunas; ++i) {
        for (uint16_t j = 0; j < linhas; ++j) {
            const gui::Cor cor(i + 1, j + 1, 0);
            casas.at(j * colunas + i) = tab.at(i, j) = cor;
        }
    }

    TS_ASSERT_EQUALS(tab.casas(), casas);

    //printTabuleiro(tab);

    // ce = coluna a eliminar
    for (uint16_t ce = 0; ce < colunas; ++ce) {
        tab.elimina(ce, 4);
        for (uint16_t le = 4; le > 0; --le) {
            casas.at(le * colunas + ce) = casas.at((le - 1) * colunas + ce);
        }
        casas.at(0 * colunas + ce) = gui::Preto;
        TS_ASSERT_EQUALS(tab.casas(), casas);
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
            TS_ASSERT_EQUALS(tab.casas(), casas);
        }
        //printTabuleiro(tab);
    }
}

}
}
