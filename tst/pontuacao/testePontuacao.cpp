
#include "testePontuacao.h"
#include "pontuacao/Pontuacao.h"
#include "peca/Peca.h"

#include <stdexcept>

namespace pontuacao {
namespace tst {

void TestePontuacao::testeCriacao() {
    const Pontuacao p1;
    TS_ASSERT_EQUALS(p1.total(), 0u);

    const Pontuacao p2(123);
    TS_ASSERT_EQUALS(p2.total(), 123u);
}

void TestePontuacao::testeComparacao() {
    const Pontuacao p1(1);
    const Pontuacao p2(2);
    const Pontuacao p3(3);

    TS_ASSERT(p1 == p1);
    TS_ASSERT(p2 == p2);
    TS_ASSERT(p3 == p3);

    TS_ASSERT(not(p1 == p2));
    TS_ASSERT(not(p1 == p3));
    TS_ASSERT(not(p2 == p3));

    TS_ASSERT(p1 < p2);
    TS_ASSERT(p1 < p3);
    TS_ASSERT(p2 < p3);

    TS_ASSERT(not(p1 < p1));
    TS_ASSERT(not(p2 < p2));
    TS_ASSERT(not(p3 < p3));

    TS_ASSERT(not(p2 < p1));
    TS_ASSERT(not(p3 < p1));
    TS_ASSERT(not(p3 < p2));
}

static size_t square(const size_t x) {
    return x * x;
}

void TestePontuacao::testeAcrescenta() {
    Pontuacao p;
    TS_ASSERT_EQUALS(p.total(), 0u);

    p.acrescenta(5);
    TS_ASSERT_EQUALS(p.total(), square(5 - peca::TAMANHO_PECA + 1));

    p.acrescenta(peca::TAMANHO_PECA);
    TS_ASSERT_EQUALS(p.total(), square(5 - peca::TAMANHO_PECA + 1) + 1);

    p.acrescenta(peca::TAMANHO_PECA + 1);
    TS_ASSERT_EQUALS(p.total(), square(5 - peca::TAMANHO_PECA + 1) + 1 + 4);
}

void TestePontuacao::testeAcrescentaInvalido() {
    Pontuacao p;
    TS_ASSERT_EQUALS(p.total(), 0u);

    p.acrescenta(peca::TAMANHO_PECA + 2);
    TS_ASSERT_EQUALS(p.total(), 9u);

    for (size_t i = 0; i < peca::TAMANHO_PECA; ++i) {
        TSM_ASSERT_THROWS_EQUALS(i,
                                 p.acrescenta(i),
                                 std::invalid_argument & e,
                                 std::string(e.what()),
                                 "Pontuacao::acrescenta - quantidade inválida de peças unidas");
        TS_ASSERT_EQUALS(p.total(), 9u);
    }

    TS_ASSERT_THROWS_NOTHING(p.acrescenta(peca::TAMANHO_PECA));

    p = Pontuacao(-1); // o máximo valor suportado pelo tipo
    TS_ASSERT_THROWS_EQUALS(p.acrescenta(peca::TAMANHO_PECA),
                            std::invalid_argument & e,
                            std::string(e.what()),
                            "Pontuacao::acrescenta - pontuação ultrapassou o limite");
    TS_ASSERT_EQUALS(p.total(), -1); // o valor não se alterou do máximo suportado
}

void TestePontuacao::testeZera() {
    for (size_t i = 0; i < 5000000; i += 13) {
        Pontuacao p(i);
        TSM_ASSERT_EQUALS(i, p.total(), i);
        p.zera();
        TSM_ASSERT_EQUALS(i, p.total(), 0u);
    }
}

}
}
