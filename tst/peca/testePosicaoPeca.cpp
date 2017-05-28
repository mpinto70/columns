
#include "testePosicaoPeca.h"
#include "peca/PosicaoPeca.h"
#include "peca/Tabuleiro.h"

#include <stdexcept>

namespace peca {
namespace tst {

namespace {
void confereCriacaoInvalida(const std::string & msg0,
                            const Tabuleiro & tab) {
    for (uint16_t i = 0; i < 2 * tab.largura(); ++i) {
        if (i < tab.largura()) {
            TSM_ASSERT_THROWS_NOTHING(msg0, PosicaoPeca(tab, i, 4));
        } else {
            try {
                PosicaoPeca p(tab, i, 4);
                TS_FAIL(msg0);
            } catch (std::invalid_argument & e) {
                TSM_ASSERT_EQUALS(msg0, std::string(e.what()), "PosicaoPeca - coluna ultrapassa o largura do tabuleiro");
            }
        }
    }

    TSM_ASSERT_THROWS_NOTHING(msg0, PosicaoPeca(tab, 0, 4));
    try {
        PosicaoPeca p(tab, 0, 0);
        TS_FAIL(msg0);
    } catch (std::invalid_argument & e) {
        TSM_ASSERT_EQUALS(msg0, std::string(e.what()), "PosicaoPeca - máxima subdivisão da posição nula");
    }
}

void confereCaiUmPassoInvalido(const std::string & msg0,
                               const Tabuleiro & tab) {
    PosicaoPeca p(tab, tab.largura() - 1, 7);
    while (p.linha() != tab.altura() - TAMANHO_PECA) {
        TSM_ASSERT(msg0, not p.chegouAoFundo());
        TSM_ASSERT_THROWS_NOTHING(msg0, p.caiUmPasso());
    }

    TSM_ASSERT(msg0, p.chegouAoFundo());
    TSM_ASSERT_EQUALS(msg0, p.linha(), tab.altura() - TAMANHO_PECA);
    TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);

    try {
        p.caiUmPasso();
        TS_FAIL(msg0);
    } catch (std::logic_error & e) {
        TSM_ASSERT_EQUALS(msg0, std::string(e.what()), "PosicaoPeca::caiUmPasso - já está na posição inferior");
    }
}

void confereMoveInvalido(const std::string & msg0,
                         const Tabuleiro & tab) {
    PosicaoPeca p(tab, 0, 4);
    for (uint16_t i = 0; i < tab.largura() - 1; ++i) {
        TSM_ASSERT_EQUALS(msg0, p.coluna(), i);
        TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
        TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
        TSM_ASSERT_THROWS_NOTHING(msg0, p.moveDireita());
        TSM_ASSERT_EQUALS(msg0, p.coluna(), i + 1);
        TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
        TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
    }

    TSM_ASSERT_EQUALS(msg0, p.coluna(), tab.largura() - 1);
    TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
    TSM_ASSERT_THROWS(msg0, p.moveDireita(), std::logic_error);
    TSM_ASSERT_EQUALS(msg0, p.coluna(), tab.largura() - 1);
    TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);

    for (uint16_t i = tab.largura(); i > 1; --i) {
        TSM_ASSERT_EQUALS(msg0, p.coluna(), i - 1);
        TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
        TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
        TSM_ASSERT_THROWS_NOTHING(msg0, p.moveEsquerda());
        TSM_ASSERT_EQUALS(msg0, p.coluna(), i - 2);
        TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
        TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
    }

    TSM_ASSERT_EQUALS(msg0, p.coluna(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
    TSM_ASSERT_THROWS(msg0, p.moveEsquerda(), std::logic_error);
    TSM_ASSERT_EQUALS(msg0, p.coluna(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.linha(), 0u);
    TSM_ASSERT_EQUALS(msg0, p.subLinha(), 0u);
}

} // unnamed namespace

void TestePosicaoPeca::testeCriacao() {
    const Tabuleiro tab1(7, 25, gui::Branco);
    const Tabuleiro tab2(8, 15, gui::Branco);

    const PosicaoPeca p1(tab1, 5, 4);
    TS_ASSERT_EQUALS(p1.coluna(), 5u);
    TS_ASSERT_EQUALS(p1.linha(), 0u);
    TS_ASSERT_EQUALS(p1.subLinha(), 0u);
    TS_ASSERT_EQUALS(p1.maxColuna(), 7u);

    const PosicaoPeca p2(tab2, 3, 4);
    TS_ASSERT_EQUALS(p2.coluna(), 3u);
    TS_ASSERT_EQUALS(p2.linha(), 0u);
    TS_ASSERT_EQUALS(p2.subLinha(), 0u);
    TS_ASSERT_EQUALS(p2.maxColuna(), 8u);

    PosicaoPeca p3(p1);
    TS_ASSERT_EQUALS(p3.coluna(), 5u);
    TS_ASSERT_EQUALS(p3.linha(), 0u);
    TS_ASSERT_EQUALS(p3.subLinha(), 0u);
    TS_ASSERT_EQUALS(p3.maxColuna(), 7u);

    p3 = p2;
    TS_ASSERT_EQUALS(p3.coluna(), 3u);
    TS_ASSERT_EQUALS(p3.linha(), 0u);
    TS_ASSERT_EQUALS(p3.subLinha(), 0u);
    TS_ASSERT_EQUALS(p3.maxColuna(), 8u);
}

void TestePosicaoPeca::testeCriacaoInvalida() {
    confereCriacaoInvalida("t1", Tabuleiro(7, 25, gui::Branco));
    confereCriacaoInvalida("t2", Tabuleiro(12, 50, gui::Branco));
}

void TestePosicaoPeca::testeCaiUmPasso() {
    const Tabuleiro tab(7, 25, gui::Branco);

    PosicaoPeca p(tab, 5, 6);
    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 1u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 2u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 3u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 4u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 5u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 1u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 1u);
    TS_ASSERT_EQUALS(p.subLinha(), 1u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 6u);
}

void TestePosicaoPeca::testeCaiUmPassoInvalido() {
    confereCaiUmPassoInvalido("t1", Tabuleiro(12, 50, gui::Preto));
    confereCaiUmPassoInvalido("t2", Tabuleiro(7, 25, gui::Preto));
}

void TestePosicaoPeca::testeMove() {
    const Tabuleiro tab(7, 25, gui::Branco);

    PosicaoPeca p(tab, 3, 4);
    TS_ASSERT_EQUALS(p.coluna(), 3u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 4u);


    p.moveDireita();

    TS_ASSERT_EQUALS(p.coluna(), 4u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 4u);

    p.moveDireita();

    TS_ASSERT_EQUALS(p.coluna(), 5u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 4u);

    p.moveEsquerda();

    TS_ASSERT_EQUALS(p.coluna(), 4u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 4u);

    p.moveEsquerda();

    TS_ASSERT_EQUALS(p.coluna(), 3u);
    TS_ASSERT_EQUALS(p.linha(), 0u);
    TS_ASSERT_EQUALS(p.subLinha(), 0u);
    TS_ASSERT_EQUALS(p.maxSubLinha(), 4u);
}

void TestePosicaoPeca::testeMoveInvalido() {
    confereMoveInvalido("t1", Tabuleiro(12, 50, gui::Preto));
    confereMoveInvalido("t2", Tabuleiro(7, 25, gui::Preto));
}

void TestePosicaoPeca::testeComparacao() {
    Tabuleiro t1(12, 50, gui::Preto);

    std::vector<PosicaoPeca> posics;
    posics.push_back(PosicaoPeca(t1, 4, 4));
    posics.push_back(PosicaoPeca(t1, 5, 4));
    posics.push_back(PosicaoPeca(t1, 5, 6));
    posics.push_back(PosicaoPeca(t1, 5, 6));
    posics.back().caiUmPasso();

    for (uint16_t i = 0; i < posics.size(); ++i) {
        for (uint16_t j = 0; j < posics.size(); ++j) {
            if (i == j) {
                TS_ASSERT_EQUALS(posics[i], posics[j]);
            } else {
                TS_ASSERT_DIFFERS(posics[i], posics[j]);
            }
        }
    }

    Tabuleiro t2(17, 50, gui::Branco);
    TS_ASSERT_EQUALS(posics[0], PosicaoPeca(t2, 4, 4));
    TS_ASSERT_EQUALS(posics[1], PosicaoPeca(t2, 5, 4));
}

}
}
