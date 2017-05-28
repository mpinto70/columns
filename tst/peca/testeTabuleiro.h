
#ifndef TESTETABULEIRO_h_mhpa
#define TESTETABULEIRO_h_mhpa

#include <cxxtest/TestSuite.h>

namespace peca {
namespace tst {

class TesteTabuleiro: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeCopia();
        void testeCriacaoInvalida();
        void testeAlteracao();
        void testeComparacao();
        void testeElimina();
};

}
}
using peca::tst::TesteTabuleiro;

#endif
