
#include "testeSituacao.h"
#include "../mck/peca/utilpeca.h"

#include "jogo/Situacao.h"
#include "peca/Tabuleiro.h"
#include "pontuacao/Placar.h"

#include <type_traits>
#include <utility>

namespace jogo {
namespace tst {

static Situacao criaSituacao(const peca::Tabuleiro & tabuleiro,
                             const pontuacao::Placar & placar) {
    return Situacao(tabuleiro, placar);
}

static Situacao criaSituacao(const peca::Tabuleiro & tabuleiro,
                             const pontuacao::Placar & placar,
                             const peca::Peca & caindo,
                             const peca::PosicaoPeca & posicao,
                             const peca::Peca & proxima) {
    return Situacao(tabuleiro, placar, caindo, posicao, proxima);
}

static Situacao criaSituacao(const peca::Tabuleiro & tabuleiro,
                             const pontuacao::Placar & placar,
                             const ListaEliminacao & eliminacao,
                             const peca::Peca & proxima) {
    return Situacao(tabuleiro, placar, eliminacao, proxima);
}

void TesteSituacao::testeCaracteristicas() {
    TS_ASSERT(std::is_move_assignable<Situacao>::value == true);
    TS_ASSERT(std::is_move_constructible<Situacao>::value == true);
    TS_ASSERT(std::is_copy_assignable<Situacao>::value == false);
    TS_ASSERT(std::is_copy_constructible<Situacao>::value == false);
}

void TesteSituacao::testeCriacao() {
    using namespace std::rel_ops;
    const peca::Tabuleiro tabuleiro1(10, 20, gui::Branco);
    const peca::Tabuleiro tabuleiro2(11, 20, gui::Branco);
    const peca::Tabuleiro tabuleiro3(10, 21, gui::Branco);
    const peca::Tabuleiro tabuleiro4(10, 20, gui::Azul);
    const peca::Tabuleiro tabuleiro5(12, 21, gui::Branco);
    const peca::Tabuleiro tabuleiro6(13, 20, gui::Azul);
    const pontuacao::Placar placar1(25);
    const pontuacao::Placar placar2(38, 34);
    const pontuacao::Placar placar3(38, 35);
    const pontuacao::Placar placar4(39, 34);
    const pontuacao::Placar placar5(40, 35);
    const pontuacao::Placar placar6(41, 34);
    const peca::Peca peca3 = peca::mck::criaPecaSequencialCrescente(12);
    const peca::Peca peca4 = peca::mck::criaPecaSequencialCrescente(15);
    const peca::Peca prox3 = peca::mck::criaPecaSequencialCrescente(17);
    const peca::Peca prox4 = peca::mck::criaPecaSequencialCrescente(23);
    const peca::PosicaoPeca posicao3(tabuleiro3, 2, 4);
    const peca::PosicaoPeca posicao4(tabuleiro4, 3, 4);
    const ListaEliminacao elim5 = { { 1, 2 }, { 3, 4 } };
    const ListaEliminacao elim6 = { { 5, 6 }, { 3, 4 } };
    const peca::Peca prox5 = peca::mck::criaPecaSequencialCrescente(19);
    const peca::Peca prox6 = peca::mck::criaPecaSequencialCrescente(21);

    const Situacao situacao1 = criaSituacao(tabuleiro1, placar1);
    TS_ASSERT(situacao1.tabuleiro() == tabuleiro1);
    TS_ASSERT(situacao1.placar() == placar1);
    TS_ASSERT(situacao1.temPeca() == false);
    TS_ASSERT_THROWS(situacao1.peca(), std::logic_error);
    TS_ASSERT_THROWS(situacao1.posicaoPeca(), std::logic_error);
    TS_ASSERT(situacao1.eliminacao().empty());
    TS_ASSERT(situacao1.temProxima() == false);
    TS_ASSERT_THROWS(situacao1.proxima(), std::logic_error);

    const Situacao situacao2 = criaSituacao(tabuleiro2, placar2);
    TS_ASSERT(situacao2.tabuleiro() == tabuleiro2);
    TS_ASSERT(situacao2.placar() == placar2);
    TS_ASSERT(situacao2.temPeca() == false);
    TS_ASSERT_THROWS(situacao2.peca(), std::logic_error);
    TS_ASSERT_THROWS(situacao2.posicaoPeca(), std::logic_error);
    TS_ASSERT(situacao2.eliminacao().empty());
    TS_ASSERT(situacao2.temProxima() == false);
    TS_ASSERT_THROWS(situacao2.proxima(), std::logic_error);

    const Situacao situacao3 = criaSituacao(tabuleiro3, placar3, peca3, posicao3, prox3);
    TS_ASSERT(situacao3.tabuleiro() == tabuleiro3);
    TS_ASSERT(situacao3.placar() == placar3);
    TS_ASSERT(situacao3.temPeca() == true);
    TS_ASSERT(situacao3.peca() == peca3);
    TS_ASSERT(situacao3.posicaoPeca() == posicao3);
    TS_ASSERT(situacao3.eliminacao().empty());
    TS_ASSERT(situacao3.temProxima() == true);
    TS_ASSERT(situacao3.proxima() == prox3);

    const Situacao situacao4 = criaSituacao(tabuleiro4, placar4, peca4, posicao4, prox4);
    TS_ASSERT(situacao4.tabuleiro() == tabuleiro4);
    TS_ASSERT(situacao4.placar() == placar4);
    TS_ASSERT(situacao4.temPeca() == true);
    TS_ASSERT(situacao4.peca() == peca4);
    TS_ASSERT(situacao4.posicaoPeca() == posicao4);
    TS_ASSERT(situacao4.eliminacao().empty());
    TS_ASSERT(situacao4.temProxima() == true);
    TS_ASSERT(situacao4.proxima() == prox4);

    const Situacao situacao5 = criaSituacao(tabuleiro5, placar5, elim5, prox5);
    TS_ASSERT(situacao5.tabuleiro() == tabuleiro5);
    TS_ASSERT(situacao5.placar() == placar5);
    TS_ASSERT(situacao5.temPeca() == false);
    TS_ASSERT_THROWS(situacao5.peca(), std::logic_error);
    TS_ASSERT_THROWS(situacao5.posicaoPeca(), std::logic_error);
    TS_ASSERT(situacao5.eliminacao() == elim5);
    TS_ASSERT(situacao5.temProxima() == true);
    TS_ASSERT(situacao5.proxima() == prox5);

    const Situacao situacao6 = criaSituacao(tabuleiro6, placar6, elim6, prox6);
    TS_ASSERT(situacao6.tabuleiro() == tabuleiro6);
    TS_ASSERT(situacao6.placar() == placar6);
    TS_ASSERT(situacao6.temPeca() == false);
    TS_ASSERT_THROWS(situacao6.peca(), std::logic_error);
    TS_ASSERT_THROWS(situacao6.posicaoPeca(), std::logic_error);
    TS_ASSERT(situacao6.eliminacao() == elim6);
    TS_ASSERT(situacao6.temProxima() == true);
    TS_ASSERT(situacao6.proxima() == prox6);

    auto p1 = criaSituacao(tabuleiro1, placar1);
    auto p2 = criaSituacao(tabuleiro2, placar2);
    TS_ASSERT(p1 == situacao1);
    TS_ASSERT(p2 == situacao2);
    TS_ASSERT(p1 != situacao2);
    TS_ASSERT(p2 != situacao1);
}

}
}
