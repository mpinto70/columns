
#ifndef TESTEPLACAR_H_mhpa
#define TESTEPLACAR_H_mhpa

#include <cxxtest/TestSuite.h>

namespace pontuacao {
namespace tst {

class TestePlacar: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeCriacaoInvalida();
        void testeComparacao();
        void testeAcrescenta();
        void testeZera();
};

}
}
using pontuacao::tst::TestePlacar;

#endif
