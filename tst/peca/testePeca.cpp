
#include "testePeca.h"
#include "../mck/peca/utilpeca.h"

#include "peca/Peca.h"

#include <stdexcept>
#include <algorithm>

namespace peca {
namespace tst {

using gui::Cor;

void TestePeca::testeCriacao() {
    const Peca p1 = mck::criaPecaSequencialCrescente(0);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Cor cor(i, i, i);
        TS_ASSERT_EQUALS(p1[i], cor);
    }
    TS_ASSERT_THROWS(p1[TAMANHO_PECA], std::invalid_argument);

    const Peca p2 = mck::criaPecaSequencialDecrescente(15);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Cor cor(15 - i, 15 - i, 15 - i);
        TS_ASSERT_EQUALS(p2[i], cor);
    }
    TS_ASSERT_THROWS(p2[TAMANHO_PECA], std::invalid_argument);

    Peca p3(p1);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Cor cor(i, i, i);
        TS_ASSERT_EQUALS(p3[i], cor);
    }
    TS_ASSERT_THROWS(p3[TAMANHO_PECA], std::invalid_argument);
    TS_ASSERT_EQUALS(p3, p1);

    p3 = p2;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Cor cor(15 - i, 15 - i, 15 - i);
        TS_ASSERT_EQUALS(p3[i], cor);
    }
    TS_ASSERT_THROWS(p3[TAMANHO_PECA], std::invalid_argument);
    TS_ASSERT_EQUALS(p3, p2);

    Peca p4(p1);
    TS_ASSERT_EQUALS(p4, p1);
    TS_ASSERT_EQUALS(p3, p2);

    p4.swap(p3);
    TS_ASSERT_EQUALS(p4, p2);
    TS_ASSERT_EQUALS(p3, p1);

    p4.swap(p3);
    TS_ASSERT_EQUALS(p4, p1);
    TS_ASSERT_EQUALS(p3, p2);
}

void TestePeca::testeRolar() {
    Peca p(mck::criaPecaSequencialCrescente(0));
    std::vector<unsigned char> cores;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i)
        cores.push_back(i);

    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Cor cor(cores[i], cores[i], cores[i]);
        TS_ASSERT_EQUALS(p[i], cor);
        const Cor cor0(i, i, i);
        TS_ASSERT_EQUALS(p[i], cor0);
    }

    p.rolaParaBaixo();
    for (unsigned char i = TAMANHO_PECA - 1; i > 0; --i) // rolando para baixo
        std::swap(cores[i], cores[i - 1]);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Cor cor(cores[i], cores[i], cores[i]);
        TS_ASSERT_EQUALS(p[i], cor);
    }

    p.rolaParaBaixo();
    for (unsigned char i = TAMANHO_PECA - 1; i > 0; --i) // rolando para baixo
        std::swap(cores[i], cores[i - 1]);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Cor cor(cores[i], cores[i], cores[i]);
        TS_ASSERT_EQUALS(p[i], cor);
    }

    p.rolaParaCima();
    for (unsigned char i = 1; i < TAMANHO_PECA; ++i) // rolando para cima
        std::swap(cores[i - 1], cores[i]);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Cor cor(cores[i], cores[i], cores[i]);
        TS_ASSERT_EQUALS(p[i], cor);
    }

    p.rolaParaCima();

    for (unsigned char i = 1; i < TAMANHO_PECA; ++i) // rolando para cima
        std::swap(cores[i - 1], cores[i]);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Cor cor(cores[i], cores[i], cores[i]);
        TS_ASSERT_EQUALS(p[i], cor);
        const Cor cor0(i, i, i);
        TS_ASSERT_EQUALS(p[i], cor0);
    }
}

static void verificaCores(const int line,
                          const Peca & p,
                          const std::vector<gui::Cor> & cores) {
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const auto & cor = p[i];
        TSM_ASSERT(line, std::find(cores.cbegin(), cores.cend(), cor) != cores.cend());
    }
}

static void verificaCores(const int line,
                          const std::vector<gui::Cor> & cores) {
    for (unsigned char i = 0; i < 100; ++i) {
        const auto p = Peca::cria(cores);
        verificaCores(line, p, cores);
        //mck::printPeca(__FILE__, line, p);
    }
}

void TestePeca::testeCriaPeca() {
    std::vector<gui::Cor> cores;

    cores.emplace_back(1, 2, 3);
    const auto p1 = Peca::cria(cores);
    TS_ASSERT_EQUALS(p1, Peca(std::vector<gui::Cor>(TAMANHO_PECA, {1, 2, 3})));

    verificaCores(__LINE__, cores);

    cores.emplace_back(1, 2, 3);
    TS_ASSERT_EQUALS(Peca::cria(cores), p1);
    verificaCores(__LINE__, cores);

    cores.emplace_back(4, 5, 6);
    verificaCores(__LINE__, cores);

    cores.emplace_back(10, 153, 12);
    verificaCores(__LINE__, cores);
}

}
}
