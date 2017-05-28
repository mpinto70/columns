
#include "testeFonte.h"
#include "../mck/util/utiltst.h"

#include "gui/Fonte.h"

#include <utility>

namespace gui {
namespace tst {

void TesteFonte::testeCriacao() {
    const Fonte f1("fonte 1", 1);
    TS_ASSERT_EQUALS(f1.nome(), "fonte 1");
    TS_ASSERT_EQUALS(f1.tamanho(), 1);

    const Fonte f2("fonte 2", 2);
    TS_ASSERT_EQUALS(f2.nome(), "fonte 2");
    TS_ASSERT_EQUALS(f2.tamanho(), 2);

    mck::confereAtribuicaoSwap(__FILE__, __LINE__, f1, f2);
}

void TesteFonte::testeOperatorIgual() {
    using namespace std::rel_ops;
    const std::vector<Fonte> v = {
        {"nome 1", 2 },
        {"nome 2", 2 },
        {"nome 1", 3 }
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}

}
}
