#include "../mck/peca/utilpeca.h"

#include "jogo/Situacao.h"
#include "peca/Board.h"
#include "pontuacao/Placar.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace jogo {
namespace tst {

static Situacao criaSituacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar) {
    return Situacao(tabuleiro, placar);
}

static Situacao criaSituacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const peca::Piece& caindo,
      const peca::PosicaoPeca& posicao,
      const peca::Piece& proxima) {
    return Situacao(tabuleiro, placar, caindo, posicao, proxima);
}

static Situacao criaSituacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const ListaEliminacao& eliminacao,
      const peca::Piece& proxima) {
    return Situacao(tabuleiro, placar, eliminacao, proxima);
}

TEST(TesteSituacao, Caracteristicas) {
    EXPECT_TRUE(std::is_move_assignable<Situacao>::value == true);
    EXPECT_TRUE(std::is_move_constructible<Situacao>::value == true);
    EXPECT_TRUE(std::is_copy_assignable<Situacao>::value == false);
    EXPECT_TRUE(std::is_copy_constructible<Situacao>::value == false);
}

TEST(TesteSituacao, Criacao) {
    using namespace std::rel_ops;
    const peca::Board tabuleiro1(10, 20, gui::WHITE);
    const peca::Board tabuleiro2(11, 20, gui::WHITE);
    const peca::Board tabuleiro3(10, 21, gui::WHITE);
    const peca::Board tabuleiro4(10, 20, gui::BLUE);
    const peca::Board tabuleiro5(12, 21, gui::WHITE);
    const peca::Board tabuleiro6(13, 20, gui::BLUE);
    const pontuacao::Placar placar1(25);
    const pontuacao::Placar placar2(38, 34);
    const pontuacao::Placar placar3(38, 35);
    const pontuacao::Placar placar4(39, 34);
    const pontuacao::Placar placar5(40, 35);
    const pontuacao::Placar placar6(41, 34);
    const peca::Piece peca3 = peca::mck::criaPecaSequencialCrescente(12);
    const peca::Piece peca4 = peca::mck::criaPecaSequencialCrescente(15);
    const peca::Piece prox3 = peca::mck::criaPecaSequencialCrescente(17);
    const peca::Piece prox4 = peca::mck::criaPecaSequencialCrescente(23);
    const peca::PosicaoPeca posicao3(tabuleiro3, 2, 4);
    const peca::PosicaoPeca posicao4(tabuleiro4, 3, 4);
    const ListaEliminacao elim5 = { { 1, 2 }, { 3, 4 } };
    const ListaEliminacao elim6 = { { 5, 6 }, { 3, 4 } };
    const peca::Piece prox5 = peca::mck::criaPecaSequencialCrescente(19);
    const peca::Piece prox6 = peca::mck::criaPecaSequencialCrescente(21);

    const Situacao situacao1 = criaSituacao(tabuleiro1, placar1);
    EXPECT_TRUE(situacao1.tabuleiro() == tabuleiro1);
    EXPECT_TRUE(situacao1.placar() == placar1);
    EXPECT_TRUE(situacao1.temPeca() == false);
    EXPECT_THROW(situacao1.peca(), std::logic_error);
    EXPECT_THROW(situacao1.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao1.eliminacao().empty());
    EXPECT_TRUE(situacao1.temProxima() == false);
    EXPECT_THROW(situacao1.proxima(), std::logic_error);

    const Situacao situacao2 = criaSituacao(tabuleiro2, placar2);
    EXPECT_TRUE(situacao2.tabuleiro() == tabuleiro2);
    EXPECT_TRUE(situacao2.placar() == placar2);
    EXPECT_TRUE(situacao2.temPeca() == false);
    EXPECT_THROW(situacao2.peca(), std::logic_error);
    EXPECT_THROW(situacao2.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao2.eliminacao().empty());
    EXPECT_TRUE(situacao2.temProxima() == false);
    EXPECT_THROW(situacao2.proxima(), std::logic_error);

    const Situacao situacao3 = criaSituacao(tabuleiro3, placar3, peca3, posicao3, prox3);
    EXPECT_TRUE(situacao3.tabuleiro() == tabuleiro3);
    EXPECT_TRUE(situacao3.placar() == placar3);
    EXPECT_TRUE(situacao3.temPeca() == true);
    EXPECT_TRUE(situacao3.peca() == peca3);
    EXPECT_TRUE(situacao3.posicaoPeca() == posicao3);
    EXPECT_TRUE(situacao3.eliminacao().empty());
    EXPECT_TRUE(situacao3.temProxima() == true);
    EXPECT_TRUE(situacao3.proxima() == prox3);

    const Situacao situacao4 = criaSituacao(tabuleiro4, placar4, peca4, posicao4, prox4);
    EXPECT_TRUE(situacao4.tabuleiro() == tabuleiro4);
    EXPECT_TRUE(situacao4.placar() == placar4);
    EXPECT_TRUE(situacao4.temPeca() == true);
    EXPECT_TRUE(situacao4.peca() == peca4);
    EXPECT_TRUE(situacao4.posicaoPeca() == posicao4);
    EXPECT_TRUE(situacao4.eliminacao().empty());
    EXPECT_TRUE(situacao4.temProxima() == true);
    EXPECT_TRUE(situacao4.proxima() == prox4);

    const Situacao situacao5 = criaSituacao(tabuleiro5, placar5, elim5, prox5);
    EXPECT_TRUE(situacao5.tabuleiro() == tabuleiro5);
    EXPECT_TRUE(situacao5.placar() == placar5);
    EXPECT_TRUE(situacao5.temPeca() == false);
    EXPECT_THROW(situacao5.peca(), std::logic_error);
    EXPECT_THROW(situacao5.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao5.eliminacao() == elim5);
    EXPECT_TRUE(situacao5.temProxima() == true);
    EXPECT_TRUE(situacao5.proxima() == prox5);

    const Situacao situacao6 = criaSituacao(tabuleiro6, placar6, elim6, prox6);
    EXPECT_TRUE(situacao6.tabuleiro() == tabuleiro6);
    EXPECT_TRUE(situacao6.placar() == placar6);
    EXPECT_TRUE(situacao6.temPeca() == false);
    EXPECT_THROW(situacao6.peca(), std::logic_error);
    EXPECT_THROW(situacao6.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao6.eliminacao() == elim6);
    EXPECT_TRUE(situacao6.temProxima() == true);
    EXPECT_TRUE(situacao6.proxima() == prox6);

    auto p1 = criaSituacao(tabuleiro1, placar1);
    auto p2 = criaSituacao(tabuleiro2, placar2);
    EXPECT_TRUE(p1 == situacao1);
    EXPECT_TRUE(p2 == situacao2);
    EXPECT_TRUE(p1 != situacao2);
    EXPECT_TRUE(p2 != situacao1);
}
}
}
