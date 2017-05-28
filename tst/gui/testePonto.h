
#ifndef TESTEPONTO_H_mhpa
#define TESTEPONTO_H_mhpa

#include <cxxtest/TestSuite.h>

namespace gui {
namespace tst {

class TestePonto: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeOperatorIgual();
};

}
}
using gui::tst::TestePonto;

#endif
