#include "../mck/util/utiltst.h"

#include "gui/Cor.h"

#include "gtest/gtest.h"

#include <utility>

namespace gui {
namespace tst {

TEST(TesteCor, OperatorIgual) {
    using namespace std::rel_ops;
    const std::vector<Cor> v = {
        {1, 2, 3},
        {4, 2, 3},
        {4, 5, 3},
        {4, 5, 6}
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}

TEST(TesteCor, criacao) {
    const Cor c1(1, 2, 3);
    EXPECT_EQ(c1.R, 1);
    EXPECT_EQ(c1.G, 2);
    EXPECT_EQ(c1.B, 3);
    const Cor c2(231, 222, 123);
    EXPECT_EQ(c2.R, 231);
    EXPECT_EQ(c2.G, 222);
    EXPECT_EQ(c2.B, 123);

    mck::confereAtribuicaoSwap(__FILE__, __LINE__, c1, c2);
}

TEST(TesteCor, Constantes) {
    EXPECT_EQ(Vermelho, Cor(255, 0, 0));
    EXPECT_EQ(Verde, Cor(0, 255, 0));
    EXPECT_EQ(Azul, Cor(0, 0, 255));
    EXPECT_EQ(Branco, Cor(255, 255, 255));
    EXPECT_EQ(Preto, Cor(0, 0, 0));
}

TEST(TesteCor, Escurece) {
    const Cor cor1(20, 12, 6);
    EXPECT_EQ(escurece(cor1, 50), Cor(10, 6, 3));
    EXPECT_EQ(escurece(cor1, 80), Cor(4, 2, 1));
    EXPECT_EQ(escurece(cor1, 0), cor1);
    EXPECT_EQ(escurece(cor1, 100), Preto);
}

}
}
