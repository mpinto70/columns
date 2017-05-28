
#ifndef TESTEFONTE_H_mhpa
#define TESTEFONTE_H_mhpa

#include <cxxtest/TestSuite.h>

namespace gui {
namespace tst {

class TesteFonte: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeOperatorIgual();
};

}
}
using gui::tst::TesteFonte;

#endif
