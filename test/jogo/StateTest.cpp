#include "../mck/piece/utilpeca.h"

#include "jogo/State.h"

#include "piece/Board.h"
#include "score/ScoreBoard.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace jogo {
namespace tst {

static State criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar) {
    return State(tabuleiro, placar);
}

static State criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar,
      const piece::Piece& caindo,
      const piece::PiecePosition& posicao,
      const piece::Piece& proxima) {
    return State(tabuleiro, placar, caindo, posicao, proxima);
}

static State criaSituacao(const piece::Board& tabuleiro,
      const score::ScoreBoard& placar,
      const EliminationList& eliminacao,
      const piece::Piece& proxima) {
    return State(tabuleiro, placar, eliminacao, proxima);
}

TEST(TesteSituacao, Caracteristicas) {
    EXPECT_TRUE(std::is_move_assignable<State>::value == true);
    EXPECT_TRUE(std::is_move_constructible<State>::value == true);
    EXPECT_TRUE(std::is_copy_assignable<State>::value == false);
    EXPECT_TRUE(std::is_copy_constructible<State>::value == false);
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
    const EliminationList elim5 = { { 1, 2 }, { 3, 4 } };
    const EliminationList elim6 = { { 5, 6 }, { 3, 4 } };
    const piece::Piece prox5 = piece::mck::criaPecaSequencialCrescente(19);
    const piece::Piece prox6 = piece::mck::criaPecaSequencialCrescente(21);

    const State situacao1 = criaSituacao(tabuleiro1, placar1);
    EXPECT_TRUE(situacao1.board() == tabuleiro1);
    EXPECT_TRUE(situacao1.score_board() == placar1);
    EXPECT_TRUE(situacao1.has_piece_falling() == false);
    EXPECT_THROW(situacao1.piece(), std::logic_error);
    EXPECT_THROW(situacao1.piece_position(), std::logic_error);
    EXPECT_TRUE(situacao1.elimination_list().empty());
    EXPECT_TRUE(situacao1.has_next() == false);
    EXPECT_THROW(situacao1.next(), std::logic_error);

    const State situacao2 = criaSituacao(tabuleiro2, placar2);
    EXPECT_TRUE(situacao2.board() == tabuleiro2);
    EXPECT_TRUE(situacao2.score_board() == placar2);
    EXPECT_TRUE(situacao2.has_piece_falling() == false);
    EXPECT_THROW(situacao2.piece(), std::logic_error);
    EXPECT_THROW(situacao2.piece_position(), std::logic_error);
    EXPECT_TRUE(situacao2.elimination_list().empty());
    EXPECT_TRUE(situacao2.has_next() == false);
    EXPECT_THROW(situacao2.next(), std::logic_error);

    const State situacao3 = criaSituacao(tabuleiro3, placar3, peca3, posicao3, prox3);
    EXPECT_TRUE(situacao3.board() == tabuleiro3);
    EXPECT_TRUE(situacao3.score_board() == placar3);
    EXPECT_TRUE(situacao3.has_piece_falling() == true);
    EXPECT_TRUE(situacao3.piece() == peca3);
    EXPECT_TRUE(situacao3.piece_position() == posicao3);
    EXPECT_TRUE(situacao3.elimination_list().empty());
    EXPECT_TRUE(situacao3.has_next() == true);
    EXPECT_TRUE(situacao3.next() == prox3);

    const State situacao4 = criaSituacao(tabuleiro4, placar4, peca4, posicao4, prox4);
    EXPECT_TRUE(situacao4.board() == tabuleiro4);
    EXPECT_TRUE(situacao4.score_board() == placar4);
    EXPECT_TRUE(situacao4.has_piece_falling() == true);
    EXPECT_TRUE(situacao4.piece() == peca4);
    EXPECT_TRUE(situacao4.piece_position() == posicao4);
    EXPECT_TRUE(situacao4.elimination_list().empty());
    EXPECT_TRUE(situacao4.has_next() == true);
    EXPECT_TRUE(situacao4.next() == prox4);

    const State situacao5 = criaSituacao(tabuleiro5, placar5, elim5, prox5);
    EXPECT_TRUE(situacao5.board() == tabuleiro5);
    EXPECT_TRUE(situacao5.score_board() == placar5);
    EXPECT_TRUE(situacao5.has_piece_falling() == false);
    EXPECT_THROW(situacao5.piece(), std::logic_error);
    EXPECT_THROW(situacao5.piece_position(), std::logic_error);
    EXPECT_TRUE(situacao5.elimination_list() == elim5);
    EXPECT_TRUE(situacao5.has_next() == true);
    EXPECT_TRUE(situacao5.next() == prox5);

    const State situacao6 = criaSituacao(tabuleiro6, placar6, elim6, prox6);
    EXPECT_TRUE(situacao6.board() == tabuleiro6);
    EXPECT_TRUE(situacao6.score_board() == placar6);
    EXPECT_TRUE(situacao6.has_piece_falling() == false);
    EXPECT_THROW(situacao6.piece(), std::logic_error);
    EXPECT_THROW(situacao6.piece_position(), std::logic_error);
    EXPECT_TRUE(situacao6.elimination_list() == elim6);
    EXPECT_TRUE(situacao6.has_next() == true);
    EXPECT_TRUE(situacao6.next() == prox6);

    auto p1 = criaSituacao(tabuleiro1, placar1);
    auto p2 = criaSituacao(tabuleiro2, placar2);
    EXPECT_TRUE(p1 == situacao1);
    EXPECT_TRUE(p2 == situacao2);
    EXPECT_TRUE(p1 != situacao2);
    EXPECT_TRUE(p2 != situacao1);
}
}
}
