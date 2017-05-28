
#include "testePlacar.h"

#include "pontuacao/Placar.h"
#include "pontuacao/Pontuacao.h"
#include "peca/Peca.h"

#include <stdio.h>
#include <stdexcept>

namespace pontuacao {
namespace tst {

void TestePlacar::testeCriacao() {
    const Pontuacao rc1(20);
    const Pontuacao pt1(10);
    const Placar p1(rc1, pt1);
    TS_ASSERT_EQUALS(p1.pontuacao(), pt1);
    TS_ASSERT_EQUALS(p1.recorde(), rc1);

    const Pontuacao rc2(50);
    const Placar p2(rc2);
    TS_ASSERT_EQUALS(p2.pontuacao(), Pontuacao(0));
    TS_ASSERT_EQUALS(p2.recorde(), rc2);

    const Placar p3;
    TS_ASSERT_EQUALS(p3.pontuacao(), Pontuacao(0));
    TS_ASSERT_EQUALS(p3.recorde(), Pontuacao(0));
}

void TestePlacar::testeCriacaoInvalida() {
    TS_ASSERT_THROWS_EQUALS(Placar p(Pontuacao(20), Pontuacao(30)),
                            std::exception & e,
                            std::string(e.what()),
                            "Placar - recorde (20) é inferior à pontuação (30)");
}

void TestePlacar::testeComparacao() {
    const Placar p1(2, 1);
    const Placar p2(3);
    const Placar p3;

    TS_ASSERT(p1 == p1);
    TS_ASSERT(p2 == p2);
    TS_ASSERT(p3 == p3);

    TS_ASSERT(not(p1 == p2));
    TS_ASSERT(not(p1 == p3));
    TS_ASSERT(not(p2 == p3));
}

void TestePlacar::testeAcrescenta() {
    Pontuacao p(12), r(17);
    Placar pl(r, p);
    TS_ASSERT_EQUALS(pl.recorde(), r);
    TS_ASSERT_EQUALS(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA); //13
    p.acrescenta(peca::TAMANHO_PECA);

    TS_ASSERT_EQUALS(pl.recorde(), r);
    TS_ASSERT_EQUALS(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA + 1); //17 == r
    p.acrescenta(peca::TAMANHO_PECA + 1);

    TS_ASSERT_EQUALS(pl.recorde(), r);
    TS_ASSERT_EQUALS(pl.recorde(), p);
    TS_ASSERT_EQUALS(pl.pontuacao(), p);

    pl.acrescenta(peca::TAMANHO_PECA); //p > r
    p.acrescenta(peca::TAMANHO_PECA);

    TS_ASSERT_DIFFERS(pl.recorde(), r);
    TS_ASSERT_EQUALS(pl.recorde(), p);
    TS_ASSERT_EQUALS(pl.pontuacao(), p);
}

void TestePlacar::testeZera() {
    Placar pl(52, 34);
    TS_ASSERT_EQUALS(pl.recorde(), Pontuacao(52));
    TS_ASSERT_EQUALS(pl.pontuacao(), Pontuacao(34));

    pl.zera();

    TS_ASSERT_EQUALS(pl.recorde(), Pontuacao(52));
    TS_ASSERT_EQUALS(pl.pontuacao(), Pontuacao(0));
}

}
}
