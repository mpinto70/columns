
#ifndef TESTEPONTUACAO_H_mhpa
#define TESTEPONTUACAO_H_mhpa

#include <cxxtest/TestSuite.h>

namespace pontuacao {
namespace tst {

class TestePontuacao: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeComparacao();
        void testeAcrescenta();
        void testeAcrescentaInvalido();
        void testeZera();
};

}
}
using pontuacao::tst::TestePontuacao;

#endif
