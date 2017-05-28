
#ifndef TESTECOR_H_mhpa
#define TESTECOR_H_mhpa

#include <cxxtest/TestSuite.h>

namespace gui {
namespace tst {

class TesteCor: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeOperatorIgual();
        void testeEscurece();
        void testeConstantes();
};

}
}
using gui::tst::TesteCor;

#endif
