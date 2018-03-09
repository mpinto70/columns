#include "../mck/util/utiltst.h"

#include "gui/Fonte.h"

#include "gtest/gtest.h"

#include <utility>

namespace gui {
namespace tst {

TEST(TesteFonte, Criacao) {
    const Fonte f1("fonte 1", 1);
    EXPECT_EQ(f1.nome(), "fonte 1");
    EXPECT_EQ(f1.tamanho(), 1);

    const Fonte f2("fonte 2", 2);
    EXPECT_EQ(f2.nome(), "fonte 2");
    EXPECT_EQ(f2.tamanho(), 2);

    mck::confereAtribuicao(__FILE__, __LINE__, f1, f2);
}

TEST(TesteFonte, OperatorIgual) {
    using namespace std::rel_ops;
    const std::vector<Fonte> v = {
        { "nome 1", 2 },
        { "nome 2", 2 },
        { "nome 1", 3 }
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}
}
}
