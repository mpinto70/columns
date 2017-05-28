
#ifndef MCK_UTILTST_H_MHPA
#define MCK_UTILTST_H_MHPA

#include <cxxtest/TestSuite.h>

#include <string>
#include <vector>

namespace mck {
std::string montaMensagem(const std::string & file,
                          int line);

template <typename T>
void confereComparacao(const std::string & file,
                       const int line,
                       const std::vector<T> & ts) {
    const auto msg = montaMensagem(file, line);
    TSM_ASSERT_DIFFERS(msg, ts.size(), 0u);
    for (size_t i = 0; i < ts.size(); ++i) {
        for (size_t j = 0; j < ts.size(); ++j) {
            const auto msgij = msg + " " + std::to_string(i) + "/" + std::to_string(j);
            if (i == j) {
                TSM_ASSERT(msgij, ts[i] == ts[j]);
            } else {
                TSM_ASSERT(msgij, not(ts[i] == ts[j]));
            }
        }
    }
}

template <typename T>
void confereAtribuicaoSwap(const std::string & file,
                           const int line,
                           const T & t1,
                           const T & t2) {
    const auto msg = montaMensagem(file, line);
    TSM_ASSERT(msg, not(t1 == t2));

    auto r1 = t1;
    auto r2 = t2;

    TSM_ASSERT(msg, t1 == r1);
    TSM_ASSERT(msg, t2 == r2);

    TSM_ASSERT(msg, not(t1 == r2));
    TSM_ASSERT(msg, not(t2 == r1));

    r1.swap(r2);

    TSM_ASSERT(msg, t1 == r2);
    TSM_ASSERT(msg, t2 == r1);

    TSM_ASSERT(msg, not(t1 == r1));
    TSM_ASSERT(msg, not(t2 == r2));
}

}
#endif
