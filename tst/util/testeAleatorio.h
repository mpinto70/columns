
#ifndef TESTEALEATORIO_h_mhpa
#define TESTEALEATORIO_h_mhpa

#include <cxxtest/TestSuite.h>

namespace util {
namespace tst {

class TesteAleatorio: public CxxTest::TestSuite {
    public:
        void testeGeracao();
};

}
}
using util::tst::TesteAleatorio;

#endif
