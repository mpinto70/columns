
#ifndef TESTECONTROLADORTABULEIRO_h_mhpa
#define TESTECONTROLADORTABULEIRO_h_mhpa

#include <cxxtest/TestSuite.h>

namespace jogo {
namespace tst {

class TesteControladorTabuleiro: public CxxTest::TestSuite {
    public:
        void testeCriacao();
        void testeCriacaoInvalida();
        void testeCriaPeca();
        void testeAdicionaPeca();
        void testeAdicionaPecaInvalida();
        void testePasso();
        void testeMove();
        void testeDeterminaEliminacao();
};

}
}
using jogo::tst::TesteControladorTabuleiro;

#endif
