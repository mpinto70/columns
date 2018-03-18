#include "../mck/piece/utilpeca.h"

#include "jogo/Situacao.h"
#include "piece/Board.h"
#include "score/ScoreBoard.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace jogo {
namespace tst {

static Situacao criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar) {
    return Situacao(tabuleiro, placar);
}

static Situacao criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar,
      const piece::Piece& caindo,
      const piece::PiecePosition& posicao,
      const piece::Piece& proxima) {
    return Situacao(tabuleiro, placar, caindo, posicao, proxima);
}

static Situacao criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar,
      const ListaEliminacao& eliminacao,
      const piece::Piece& proxima) {
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
    const piece::Board tabuleiro1(10, 20, gui::WHITE);
    const piece::Board tabuleiro2(11, 20, gui::WHITE);
    const piece::Board tabuleiro3(10, 21, gui::WHITE);
    const piece::Board tabuleiro4(10, 20, gui::BLUE);
    const piece::Board tabuleiro5(12, 21, gui::WHITE);
    const piece::Board tabuleiro6(13, 20, gui::BLUE);
    const score::ScoreBoard placar1(25);
    const score::ScoreBoard placar2(38, 34);
    const score::ScoreBoard placar3(38, 35);
    const score::ScoreBoard placar4(39, 34);
    const score::ScoreBoard placar5(40, 35);
    const score::ScoreBoard placar6(41, 34);
    const piece::Piece peca3 = piece::mck::criaPecaSequencialCrescente(12);
    const piece::Piece peca4 = piece::mck::criaPecaSequencialCrescente(15);
    const piece::Piece prox3 = piece::mck::criaPecaSequencialCrescente(17);
    const piece::Piece prox4 = piece::mck::criaPecaSequencialCrescente(23);
    const piece::PiecePosition posicao3(tabuleiro3, 2, 4);
    const piece::PiecePosition posicao4(tabuleiro4, 3, 4);
    const ListaEliminacao elim5 = { { 1, 2 }, { 3, 4 } };
    const ListaEliminacao elim6 = { { 5, 6 }, { 3, 4 } };
    const piece::Piece prox5 = piece::mck::criaPecaSequencialCrescente(19);
    const piece::Piece prox6 = piece::mck::criaPecaSequencialCrescente(21);

    const Situacao situacao1 = criaSituacao(tabuleiro1, placar1);
    EXPECT_TRUE(situacao1.tabuleiro() == tabuleiro1);
    EXPECT_TRUE(situacao1.placar() == placar1);
    EXPECT_TRUE(situacao1.temPeca() == false);
    EXPECT_THROW(situacao1.piece(), std::logic_error);
    EXPECT_THROW(situacao1.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao1.eliminacao().empty());
    EXPECT_TRUE(situacao1.temProxima() == false);
    EXPECT_THROW(situacao1.proxima(), std::logic_error);

    const Situacao situacao2 = criaSituacao(tabuleiro2, placar2);
    EXPECT_TRUE(situacao2.tabuleiro() == tabuleiro2);
    EXPECT_TRUE(situacao2.placar() == placar2);
    EXPECT_TRUE(situacao2.temPeca() == false);
    EXPECT_THROW(situacao2.piece(), std::logic_error);
    EXPECT_THROW(situacao2.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao2.eliminacao().empty());
    EXPECT_TRUE(situacao2.temProxima() == false);
    EXPECT_THROW(situacao2.proxima(), std::logic_error);

    const Situacao situacao3 = criaSituacao(tabuleiro3, placar3, peca3, posicao3, prox3);
    EXPECT_TRUE(situacao3.tabuleiro() == tabuleiro3);
    EXPECT_TRUE(situacao3.placar() == placar3);
    EXPECT_TRUE(situacao3.temPeca() == true);
    EXPECT_TRUE(situacao3.piece() == peca3);
    EXPECT_TRUE(situacao3.posicaoPeca() == posicao3);
    EXPECT_TRUE(situacao3.eliminacao().empty());
    EXPECT_TRUE(situacao3.temProxima() == true);
    EXPECT_TRUE(situacao3.proxima() == prox3);

    const Situacao situacao4 = criaSituacao(tabuleiro4, placar4, peca4, posicao4, prox4);
    EXPECT_TRUE(situacao4.tabuleiro() == tabuleiro4);
    EXPECT_TRUE(situacao4.placar() == placar4);
    EXPECT_TRUE(situacao4.temPeca() == true);
    EXPECT_TRUE(situacao4.piece() == peca4);
    EXPECT_TRUE(situacao4.posicaoPeca() == posicao4);
    EXPECT_TRUE(situacao4.eliminacao().empty());
    EXPECT_TRUE(situacao4.temProxima() == true);
    EXPECT_TRUE(situacao4.proxima() == prox4);

    const Situacao situacao5 = criaSituacao(tabuleiro5, placar5, elim5, prox5);
    EXPECT_TRUE(situacao5.tabuleiro() == tabuleiro5);
    EXPECT_TRUE(situacao5.placar() == placar5);
    EXPECT_TRUE(situacao5.temPeca() == false);
    EXPECT_THROW(situacao5.piece(), std::logic_error);
    EXPECT_THROW(situacao5.posicaoPeca(), std::logic_error);
    EXPECT_TRUE(situacao5.eliminacao() == elim5);
    EXPECT_TRUE(situacao5.temProxima() == true);
    EXPECT_TRUE(situacao5.proxima() == prox5);

    const Situacao situacao6 = criaSituacao(tabuleiro6, placar6, elim6, prox6);
    EXPECT_TRUE(situacao6.tabuleiro() == tabuleiro6);
    EXPECT_TRUE(situacao6.placar() == placar6);
    EXPECT_TRUE(situacao6.temPeca() == false);
    EXPECT_THROW(situacao6.piece(), std::logic_error);
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
