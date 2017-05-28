
#ifndef TESTESITUACAO_h_mhpa
#define TESTESITUACAO_h_mhpa

#include <cxxtest/TestSuite.h>

namespace jogo {
namespace tst {

class TesteSituacao: public CxxTest::TestSuite {
    public:
        void testeCaracteristicas();
        void testeCriacao();
};

}
}
using jogo::tst::TesteSituacao;

#endif
