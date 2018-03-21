#include "../mck/util/utiltest.h"

#include "piece/Piece.h"
#include "score/Score.h"
#include "score/ScoreBoard.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <stdio.h>

namespace score {
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

    ::mck::check_assignment(__FILE__, __LINE__, sb1, sb2);
    ::mck::check_assignment(__FILE__, __LINE__, sb1, sb3);
    ::mck::check_assignment(__FILE__, __LINE__, sb2, sb3);
}

TEST(ScoreBoardTest, create_invalid) {
    EXPECT_THROW(ScoreBoard p(Score(20), Score(30)), std::invalid_argument);
}

TEST(ScoreBoardTest, compare) {
    const std::vector<ScoreBoard> v = {
        ScoreBoard(Score(2), Score(1)),
        ScoreBoard(Score(3)),
        ScoreBoard(),
    };

    ::mck::check_comparison(__FILE__, __LINE__, v);
    ::mck::check_comparison(__FILE__, __LINE__, v);
    ::mck::check_comparison(__FILE__, __LINE__, v);
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
    ScoreBoard sb(Score(52), Score(34));
    EXPECT_EQ(sb.record(), Score(52));
    EXPECT_EQ(sb.score(), Score(34));

    sb.reset();

    EXPECT_EQ(sb.record(), Score(52));
    EXPECT_EQ(sb.score(), Score(0));
}
}
}
