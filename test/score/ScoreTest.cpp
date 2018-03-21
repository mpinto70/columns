#include "../mck/util/utiltest.h"

#include "piece/Piece.h"
#include "score/Score.h"

#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>

namespace score {
namespace tst {

TEST(ScoreTest, create) {
    const Score s1;
    EXPECT_EQ(s1.total(), 0u);

    const Score s2(123);
    EXPECT_EQ(s2.total(), 123u);
}

TEST(ScoreTest, compare) {
    const Score s1(1);
    const Score s2(2);

    ::mck::check_assignment(__FILE__, __LINE__, s1, s2);
    ::mck::check_total_ordering<Score>(__FILE__, __LINE__, { s1, s2 });

    static_assert(Score(1) == Score(1), "Oops");
    static_assert(Score(1) != Score(2), "Oops");
    static_assert(Score(1) < Score(2), "Oops");
}

static size_t square(const size_t x) {
    return x * x;
}

TEST(ScoreTest, add) {
    Score s;
    EXPECT_EQ(s.total(), 0u);

    s.add(5);
    EXPECT_EQ(s.total(), square(5 - piece::PIECE_SIZE + 1));

    s.add(piece::PIECE_SIZE);
    EXPECT_EQ(s.total(), square(5 - piece::PIECE_SIZE + 1) + 1);

    s.add(piece::PIECE_SIZE + 1);
    EXPECT_EQ(s.total(), square(5 - piece::PIECE_SIZE + 1) + 1 + 4);
}

TEST(ScoreTest, add_invalid) {
    Score p;
    EXPECT_EQ(p.total(), 0u);

    p.add(piece::PIECE_SIZE + 2);
    EXPECT_EQ(p.total(), 9u);

    for (size_t i = 0; i < piece::PIECE_SIZE; ++i) {
        EXPECT_THROW(p.add(i), std::invalid_argument) << i;
        EXPECT_EQ(p.total(), 9u);
    }

    EXPECT_NO_THROW(p.add(piece::PIECE_SIZE));

    p = Score(std::numeric_limits<size_t>::max());
    EXPECT_THROW(p.add(piece::PIECE_SIZE), std::invalid_argument);
    EXPECT_EQ(p.total(), std::numeric_limits<size_t>::max());
}

TEST(ScoreTest, reset) {
    for (size_t i = 0; i < 5000000; i += 13) {
        Score s(i);
        EXPECT_EQ(s.total(), i) << i;
        s.reset();
        EXPECT_EQ(s.total(), 0u) << i;
    }
}
}
}
