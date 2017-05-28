
#include "testePonto.h"
#include "../mck/util/utiltst.h"

#include "gui/Ponto.h"

#include <utility>

namespace gui {
namespace tst {

void TestePonto::testeCriacao() {
    const Ponto p1(1, 2);
    TS_ASSERT_EQUALS(p1.X, 1);
    TS_ASSERT_EQUALS(p1.Y, 2);
    const Ponto p2(231, 222);
    TS_ASSERT_EQUALS(p2.X, 231);
    TS_ASSERT_EQUALS(p2.Y, 222);

    mck::confereAtribuicaoSwap(__FILE__, __LINE__, p1, p2);
}

void TestePonto::testeOperatorIgual() {
    using namespace std::rel_ops;
    const std::vector<Ponto> v = {
        {1, 2},
        {4, 2},
        {1, 3}
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}

}
}
