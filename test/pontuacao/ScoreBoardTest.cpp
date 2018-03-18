#include "../mck/util/utiltst.h"

#include "pontuacao/ScoreBoard.h"

#include "piece/Piece.h"
#include "pontuacao/Score.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <stdio.h>

namespace pontuacao {
namespace tst {

TEST(ScoreBoardTest, create) {
    const Score rc1(20);
    const Score sc1(10);
    const ScoreBoard sb1(rc1, sc1);
    EXPECT_EQ(sb1.score(), sc1);
    EXPECT_EQ(sb1.record(), rc1);

    const Score rc2(50);
    const ScoreBoard sb2(rc2);
    EXPECT_EQ(sb2.score(), Score(0));
    EXPECT_EQ(sb2.record(), rc2);

    const ScoreBoard sb3;
    EXPECT_EQ(sb3.score(), Score(0));
    EXPECT_EQ(sb3.record(), Score(0));

    ::mck::confereAtribuicao(__FILE__, __LINE__, sb1, sb2);
    ::mck::confereAtribuicao(__FILE__, __LINE__, sb1, sb3);
    ::mck::confereAtribuicao(__FILE__, __LINE__, sb2, sb3);
}

TEST(ScoreBoardTest, create_invalid) {
    EXPECT_THROW(ScoreBoard p(Score(20), Score(30)), std::invalid_argument);
}

TEST(ScoreBoardTest, compare) {
    const std::vector<ScoreBoard> v = {
        ScoreBoard(2, 1),
        ScoreBoard(3),
        ScoreBoard(),
    };

    ::mck::confereComparacao(__FILE__, __LINE__, v);
    ::mck::confereComparacao(__FILE__, __LINE__, v);
    ::mck::confereComparacao(__FILE__, __LINE__, v);
}

TEST(ScoreBoardTest, add) {
    Score s(12), r(17);
    ScoreBoard sb(r, s);
    EXPECT_EQ(sb.record(), r);
    EXPECT_EQ(sb.score(), s);

    sb.add(piece::PIECE_SIZE);
    s.add(piece::PIECE_SIZE);

    EXPECT_EQ(sb.record(), r);
    EXPECT_EQ(sb.score(), s);

    sb.add(piece::PIECE_SIZE + 1);
    s.add(piece::PIECE_SIZE + 1);

    EXPECT_EQ(sb.record(), r);
    EXPECT_EQ(sb.record(), s);
    EXPECT_EQ(sb.score(), s);

    sb.add(piece::PIECE_SIZE);
    s.add(piece::PIECE_SIZE);

    EXPECT_NE(sb.record(), r);
    EXPECT_EQ(sb.record(), s);
    EXPECT_EQ(sb.score(), s);
}

TEST(ScoreBoardTest, reset) {
    ScoreBoard sb(52, 34);
    EXPECT_EQ(sb.record(), Score(52));
    EXPECT_EQ(sb.score(), Score(34));

    sb.reset();

    EXPECT_EQ(sb.record(), Score(52));
    EXPECT_EQ(sb.score(), Score(0));
}
}
}
