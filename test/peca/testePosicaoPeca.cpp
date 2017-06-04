#include "peca/PosicaoPeca.h"
#include "peca/Tabuleiro.h"

#include "gtest/gtest.h"

#include <stdexcept>

namespace peca {
namespace tst {

namespace {
void confereCriacaoInvalida(const std::string& msg0,
                            const Tabuleiro& tab) {
    for (uint16_t i = 0; i < 2 * tab.largura(); ++i) {
        if (i < tab.largura()) {
            EXPECT_NO_THROW(PosicaoPeca(tab, i, 4)) << msg0;
        } else {
            try {
                PosicaoPeca p(tab, i, 4);
                FAIL() << msg0;
            } catch (std::invalid_argument& e) {
                EXPECT_EQ(std::string(e.what()), "PosicaoPeca - coluna ultrapassa o largura do tabuleiro") << msg0;
            }
        }
    }

    EXPECT_NO_THROW(PosicaoPeca(tab, 0, 4)) << msg0;
    try {
        PosicaoPeca p(tab, 0, 0);
        FAIL() << msg0;
    } catch (std::invalid_argument& e) {
        EXPECT_EQ(std::string(e.what()), "PosicaoPeca - m�xima subdivis�o da posi��o nula") << msg0;
    }
}

void confereCaiUmPassoInvalido(const std::string& msg0,
                               const Tabuleiro& tab) {
    PosicaoPeca p(tab, tab.largura() - 1, 7);
    while (p.linha() != tab.altura() - TAMANHO_PECA) {
        EXPECT_TRUE(not p.chegouAoFundo()) << msg0;
        EXPECT_NO_THROW(p.caiUmPasso()) << msg0;
    }

    EXPECT_TRUE(p.chegouAoFundo()) << msg0;
    EXPECT_EQ(p.linha(), tab.altura() - TAMANHO_PECA) << msg0;
    EXPECT_EQ(p.subLinha(), 0u) << msg0;

    try {
        p.caiUmPasso();
        FAIL() << msg0;
    } catch (std::logic_error& e) {
        EXPECT_EQ(std::string(e.what()), "PosicaoPeca::caiUmPasso - j� est� na posi��o inferior") << msg0;
    }
}

void confereMoveInvalido(const std::string& msg0,
                         const Tabuleiro& tab) {
    PosicaoPeca p(tab, 0, 4);
    for (uint16_t i = 0; i < tab.largura() - 1; ++i) {
        EXPECT_EQ(p.coluna(), i) << msg0;
        EXPECT_EQ(p.linha(), 0u) << msg0;
        EXPECT_EQ(p.subLinha(), 0u) << msg0;
        EXPECT_NO_THROW(p.moveDireita()) << msg0;
        EXPECT_EQ(p.coluna(), i + 1) << msg0;
        EXPECT_EQ(p.linha(), 0u) << msg0;
        EXPECT_EQ(p.subLinha(), 0u) << msg0;
    }

    EXPECT_EQ(p.coluna(), tab.largura() - 1) << msg0;
    EXPECT_EQ(p.linha(), 0u) << msg0;
    EXPECT_EQ(p.subLinha(), 0u) << msg0;
    EXPECT_THROW(p.moveDireita(), std::logic_error) << msg0;
    EXPECT_EQ(p.coluna(), tab.largura() - 1) << msg0;
    EXPECT_EQ(p.linha(), 0u) << msg0;
    EXPECT_EQ(p.subLinha(), 0u) << msg0;

    for (uint16_t i = tab.largura(); i > 1; --i) {
        EXPECT_EQ(p.coluna(), i - 1) << msg0;
        EXPECT_EQ(p.linha(), 0u) << msg0;
        EXPECT_EQ(p.subLinha(), 0u) << msg0;
        EXPECT_NO_THROW(p.moveEsquerda()) << msg0;
        EXPECT_EQ(p.coluna(), i - 2) << msg0;
        EXPECT_EQ(p.linha(), 0u) << msg0;
        EXPECT_EQ(p.subLinha(), 0u) << msg0;
    }

    EXPECT_EQ(p.coluna(), 0u) << msg0;
    EXPECT_EQ(p.linha(), 0u) << msg0;
    EXPECT_EQ(p.subLinha(), 0u) << msg0;
    EXPECT_THROW(p.moveEsquerda(), std::logic_error) << msg0;
    EXPECT_EQ(p.coluna(), 0u) << msg0;
    EXPECT_EQ(p.linha(), 0u) << msg0;
    EXPECT_EQ(p.subLinha(), 0u) << msg0;
}

} // unnamed namespace

TEST(TestePosicaoPeca, Criacao) {
    const Tabuleiro tab1(7, 25, gui::Branco);
    const Tabuleiro tab2(8, 15, gui::Branco);

    const PosicaoPeca p1(tab1, 5, 4);
    EXPECT_EQ(p1.coluna(), 5u);
    EXPECT_EQ(p1.linha(), 0u);
    EXPECT_EQ(p1.subLinha(), 0u);
    EXPECT_EQ(p1.maxColuna(), 7u);

    const PosicaoPeca p2(tab2, 3, 4);
    EXPECT_EQ(p2.coluna(), 3u);
    EXPECT_EQ(p2.linha(), 0u);
    EXPECT_EQ(p2.subLinha(), 0u);
    EXPECT_EQ(p2.maxColuna(), 8u);

    PosicaoPeca p3(p1);
    EXPECT_EQ(p3.coluna(), 5u);
    EXPECT_EQ(p3.linha(), 0u);
    EXPECT_EQ(p3.subLinha(), 0u);
    EXPECT_EQ(p3.maxColuna(), 7u);

    p3 = p2;
    EXPECT_EQ(p3.coluna(), 3u);
    EXPECT_EQ(p3.linha(), 0u);
    EXPECT_EQ(p3.subLinha(), 0u);
    EXPECT_EQ(p3.maxColuna(), 8u);
}

TEST(TestePosicaoPeca, CriacaoInvalida) {
    confereCriacaoInvalida("t1", Tabuleiro(7, 25, gui::Branco));
    confereCriacaoInvalida("t2", Tabuleiro(12, 50, gui::Branco));
}

TEST(TestePosicaoPeca, CaiUmPasso) {
    const Tabuleiro tab(7, 25, gui::Branco);

    PosicaoPeca p(tab, 5, 6);
    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 1u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 2u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 3u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 4u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 5u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 1u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 6u);

    p.caiUmPasso();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 1u);
    EXPECT_EQ(p.subLinha(), 1u);
    EXPECT_EQ(p.maxSubLinha(), 6u);
}

TEST(TestePosicaoPeca, CaiUmPassoInvalido) {
    confereCaiUmPassoInvalido("t1", Tabuleiro(12, 50, gui::Preto));
    confereCaiUmPassoInvalido("t2", Tabuleiro(7, 25, gui::Preto));
}

TEST(TestePosicaoPeca, Move) {
    const Tabuleiro tab(7, 25, gui::Branco);

    PosicaoPeca p(tab, 3, 4);
    EXPECT_EQ(p.coluna(), 3u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 4u);


    p.moveDireita();

    EXPECT_EQ(p.coluna(), 4u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 4u);

    p.moveDireita();

    EXPECT_EQ(p.coluna(), 5u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 4u);

    p.moveEsquerda();

    EXPECT_EQ(p.coluna(), 4u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 4u);

    p.moveEsquerda();

    EXPECT_EQ(p.coluna(), 3u);
    EXPECT_EQ(p.linha(), 0u);
    EXPECT_EQ(p.subLinha(), 0u);
    EXPECT_EQ(p.maxSubLinha(), 4u);
}

TEST(TestePosicaoPeca, MoveInvalido) {
    confereMoveInvalido("t1", Tabuleiro(12, 50, gui::Preto));
    confereMoveInvalido("t2", Tabuleiro(7, 25, gui::Preto));
}

TEST(TestePosicaoPeca, Comparacao) {
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
                EXPECT_EQ(posics[i], posics[j]);
            } else {
                EXPECT_NE(posics[i], posics[j]);
            }
        }
    }

    Tabuleiro t2(17, 50, gui::Branco);
    EXPECT_EQ(posics[0], PosicaoPeca(t2, 4, 4));
    EXPECT_EQ(posics[1], PosicaoPeca(t2, 5, 4));
}

}
}
