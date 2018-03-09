#include "peca/Peca.h"
#include "pontuacao/Placar.h"
#include "pontuacao/Pontuacao.h"

#include "gtest/gtest.h"

#include <stdexcept>
#include <stdio.h>

namespace pontuacao {
namespace tst {

TEST(TestePlacar, Criacao) {
    const Pontuacao rc1(20);
    const Pontuacao pt1(10);
    const Placar p1(rc1, pt1);
    EXPECT_EQ(p1.pontuacao(), pt1);
    EXPECT_EQ(p1.recorde(), rc1);

    const Pontuacao rc2(50);
    const Placar p2(rc2);
    EXPECT_EQ(p2.pontuacao(), Pontuacao(0));
    EXPECT_EQ(p2.recorde(), rc2);

    const Placar p3;
    EXPECT_EQ(p3.pontuacao(), Pontuacao(0));
    EXPECT_EQ(p3.recorde(), Pontuacao(0));
}

TEST(TestePlacar, CriacaoInvalida) {
    EXPECT_THROW(Placar p(Pontuacao(20), Pontuacao(30)), std::invalid_argument);
}

TEST(TestePlacar, Comparacao) {
    const Placar p1(2, 1);
    const Placar p2(3);
    const Placar p3;

    EXPECT_TRUE(p1 == p1);
    EXPECT_TRUE(p2 == p2);
    EXPECT_TRUE(p3 == p3);

    EXPECT_TRUE(not(p1 == p2));
    EXPECT_TRUE(not(p1 == p3));
    EXPECT_TRUE(not(p2 == p3));
}

TEST(TestePlacar, Acrescenta) {
    Pontuacao p(12), r(17);
    Placar pl(r, p);
    EXPECT_EQ(pl.recorde(), r);
    EXPECT_EQ(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA); //13
    p.acrescenta(peca::TAMANHO_PECA);

    EXPECT_EQ(pl.recorde(), r);
    EXPECT_EQ(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA + 1); //17 == r
    p.acrescenta(peca::TAMANHO_PECA + 1);

    EXPECT_EQ(pl.recorde(), r);
    EXPECT_EQ(pl.recorde(), p);
    EXPECT_EQ(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA); //p > r
    p.acrescenta(peca::TAMANHO_PECA);

    EXPECT_NE(pl.recorde(), r);
    EXPECT_EQ(pl.recorde(), p);
    EXPECT_EQ(pl.pontuacao(), p);
}

TEST(TestePlacar, Zera) {
    Placar pl(52, 34);
    EXPECT_EQ(pl.recorde(), Pontuacao(52));
    EXPECT_EQ(pl.pontuacao(), Pontuacao(34));

    pl.zera();

    EXPECT_EQ(pl.recorde(), Pontuacao(52));
    EXPECT_EQ(pl.pontuacao(), Pontuacao(0));
}
}
}
