
#ifndef TESTEPOSICAOPECA_h_mhpa
#define TESTEPOSICAOPECA_h_mhpa

#include <cxxtest/TestSuite.h>

namespace peca {
namespace tst {

class TestePosicaoPeca: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeCriacaoInvalida();
        void testeCaiUmPasso();
        void testeCaiUmPassoInvalido();
        void testeMove();
        void testeMoveInvalido();
        void testeComparacao();
};

}
}
using peca::tst::TestePosicaoPeca;

#endif
