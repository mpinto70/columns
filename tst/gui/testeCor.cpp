
#include "testeCor.h"
#include "../mck/util/utiltst.h"

#include "gui/Cor.h"

#include <utility>

namespace gui {
namespace tst {

void TesteCor::testeCriacao() {
    const Cor c1(1, 2, 3);
    TS_ASSERT_EQUALS(c1.R, 1);
    TS_ASSERT_EQUALS(c1.G, 2);
    TS_ASSERT_EQUALS(c1.B, 3);
    const Cor c2(231, 222, 123);
    TS_ASSERT_EQUALS(c2.R, 231);
    TS_ASSERT_EQUALS(c2.G, 222);
    TS_ASSERT_EQUALS(c2.B, 123);

    mck::confereAtribuicaoSwap(__FILE__, __LINE__, c1, c2);
}

void TesteCor::testeOperatorIgual() {
    using namespace std::rel_ops;
    const std::vector<Cor> v = {
        {1, 2, 3},
        {4, 2, 3},
        {4, 5, 3},
        {4, 5, 6}
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}

void TesteCor::testeConstantes() {
    TS_ASSERT_EQUALS(Vermelho, Cor(255, 0, 0));
    TS_ASSERT_EQUALS(Verde, Cor(0, 255, 0));
    TS_ASSERT_EQUALS(Azul, Cor(0, 0, 255));
    TS_ASSERT_EQUALS(Branco, Cor(255, 255, 255));
    TS_ASSERT_EQUALS(Preto, Cor(0, 0, 0));
}

void TesteCor::testeEscurece() {
    const Cor cor1(20, 12, 6);
    TS_ASSERT_EQUALS(escurece(cor1, 50), Cor(10, 6, 3));
    TS_ASSERT_EQUALS(escurece(cor1, 80), Cor(4, 2, 1));
    TS_ASSERT_EQUALS(escurece(cor1, 0), cor1);
    TS_ASSERT_EQUALS(escurece(cor1, 100), Preto);
}

}
}
