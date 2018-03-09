#include "../mck/util/utiltst.h"

#include "gui/Ponto.h"

#include "gtest/gtest.h"

namespace gui {
namespace tst {

TEST(TestePonto, criacao) {
    const Ponto p1(1, 2);
    EXPECT_EQ(p1.X, 1);
    EXPECT_EQ(p1.Y, 2);
    const Ponto p2(231, 222);
    EXPECT_EQ(p2.X, 231);
    EXPECT_EQ(p2.Y, 222);

    mck::confereAtribuicao(__FILE__, __LINE__, p1, p2);
}

TEST(TestePonto, OperatorIgual) {
    using namespace std::rel_ops;
    const std::vector<Ponto> v = {
        { 1, 2 },
        { 4, 2 },
        { 1, 3 }
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}
}
}
