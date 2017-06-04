#include "pontuacao/Pontuacao.h"
#include "peca/Peca.h"

#include "gtest/gtest.h"

#include <stdexcept>

namespace pontuacao {
namespace tst {

TEST(TestePontuacao, Criacao) {
    const Pontuacao p1;
    EXPECT_EQ(p1.total(), 0u);

    const Pontuacao p2(123);
    EXPECT_EQ(p2.total(), 123u);
}

TEST(TestePontuacao, Comparacao) {
    const Pontuacao p1(1);
    const Pontuacao p2(2);
    const Pontuacao p3(3);

    EXPECT_TRUE(p1 == p1);
    EXPECT_TRUE(p2 == p2);
    EXPECT_TRUE(p3 == p3);

    EXPECT_TRUE(not(p1 == p2));
    EXPECT_TRUE(not(p1 == p3));
    EXPECT_TRUE(not(p2 == p3));

    EXPECT_TRUE(p1 < p2);
    EXPECT_TRUE(p1 < p3);
    EXPECT_TRUE(p2 < p3);

    EXPECT_TRUE(not(p1 < p1));
    EXPECT_TRUE(not(p2 < p2));
    EXPECT_TRUE(not(p3 < p3));

    EXPECT_TRUE(not(p2 < p1));
    EXPECT_TRUE(not(p3 < p1));
    EXPECT_TRUE(not(p3 < p2));
}

static size_t square(const size_t x) {
    return x * x;
}

TEST(TestePontuacao, Acrescenta) {
    Pontuacao p;
    EXPECT_EQ(p.total(), 0u);

    p.acrescenta(5);
    EXPECT_EQ(p.total(), square(5 - peca::TAMANHO_PECA + 1));

    p.acrescenta(peca::TAMANHO_PECA);
    EXPECT_EQ(p.total(), square(5 - peca::TAMANHO_PECA + 1) + 1);

    p.acrescenta(peca::TAMANHO_PECA + 1);
    EXPECT_EQ(p.total(), square(5 - peca::TAMANHO_PECA + 1) + 1 + 4);
}

TEST(TestePontuacao, AcrescentaInvalido) {
    Pontuacao p;
    EXPECT_EQ(p.total(), 0u);

    p.acrescenta(peca::TAMANHO_PECA + 2);
    EXPECT_EQ(p.total(), 9u);

    for (size_t i = 0; i < peca::TAMANHO_PECA; ++i) {
        EXPECT_THROW(p.acrescenta(i), std::invalid_argument) << i;
        EXPECT_EQ(p.total(), 9u);
    }

    EXPECT_NO_THROW(p.acrescenta(peca::TAMANHO_PECA));

    p = Pontuacao(-1); // o máximo valor suportado pelo tipo
    EXPECT_THROW(p.acrescenta(peca::TAMANHO_PECA), std::invalid_argument);
    EXPECT_EQ(p.total(), size_t(-1)); // o valor não se alterou do máximo suportado
}

TEST(TestePontuacao, Zera) {
    for (size_t i = 0; i < 5000000; i += 13) {
        Pontuacao p(i);
        EXPECT_EQ(p.total(), i) << i;
        p.zera();
        EXPECT_EQ(p.total(), 0u) << i;
    }
}

}
}
