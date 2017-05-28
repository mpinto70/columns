
#ifndef TESTEPECA_H_mhpa
#define TESTEPECA_H_mhpa

#include <cxxtest/TestSuite.h>

namespace peca {
namespace tst {

class TestePeca: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeRolar();
        void testeCriaPeca();
};

}
}
using peca::tst::TestePeca;

#endif
