
#ifndef TESTEESPERA_h_mhpa
#define TESTEESPERA_h_mhpa

#include <cxxtest/TestSuite.h>

namespace util {
namespace tst {

class TesteEspera: public CxxTest::TestSuite {
    public:
        void testeEspera();
        void testeFim();
};

}
}
using util::tst::TesteEspera;

#endif
