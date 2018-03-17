
#include "../mck/peca/utilpeca.h"

#include "peca/Peca.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <stdexcept>

namespace peca {
namespace tst {

using gui::Color;

TEST(TestePeca, criacao) {
    const Peca p1 = mck::criaPecaSequencialCrescente(0);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Color cor(i, i, i);
        EXPECT_EQ(p1[i], cor);
    }
    EXPECT_THROW(p1[TAMANHO_PECA], std::invalid_argument);

    const Peca p2 = mck::criaPecaSequencialDecrescente(15);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Color cor(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(p2[i], cor);
    }
    EXPECT_THROW(p2[TAMANHO_PECA], std::invalid_argument);

    Peca p3(p1);
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Color cor(i, i, i);
        EXPECT_EQ(p3[i], cor);
    }
    EXPECT_THROW(p3[TAMANHO_PECA], std::invalid_argument);
    EXPECT_EQ(p3, p1);

    p3 = p2;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        Color cor(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(p3[i], cor);
    }
    EXPECT_THROW(p3[TAMANHO_PECA], std::invalid_argument);
    EXPECT_EQ(p3, p2);

    Peca p4(p1);
    EXPECT_EQ(p4, p1);
    EXPECT_EQ(p3, p2);
}

TEST(TestePeca, rolar) {
    Peca p(mck::criaPecaSequencialCrescente(0));
    std::vector<unsigned char> cores;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        cores.push_back(i);
    }

    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Color cor(cores[i], cores[i], cores[i]);
        EXPECT_EQ(p[i], cor);
        const Color cor0(i, i, i);
        EXPECT_EQ(p[i], cor0);
    }

    p.rolaParaBaixo();
    for (unsigned char i = TAMANHO_PECA - 1; i > 0; --i) { // rolando para baixo
        std::swap(cores[i], cores[i - 1]);
    }
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Color cor(cores[i], cores[i], cores[i]);
        EXPECT_EQ(p[i], cor);
    }

    p.rolaParaBaixo();
    for (unsigned char i = TAMANHO_PECA - 1; i > 0; --i) { // rolando para baixo
        std::swap(cores[i], cores[i - 1]);
    }
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Color cor(cores[i], cores[i], cores[i]);
        EXPECT_EQ(p[i], cor);
    }

    p.rolaParaCima();
    for (unsigned char i = 1; i < TAMANHO_PECA; ++i) { // rolando para cima
        std::swap(cores[i - 1], cores[i]);
    }
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Color cor(cores[i], cores[i], cores[i]);
        EXPECT_EQ(p[i], cor);
    }

    p.rolaParaCima();

    for (unsigned char i = 1; i < TAMANHO_PECA; ++i) { // rolando para cima
        std::swap(cores[i - 1], cores[i]);
    }
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const Color cor(cores[i], cores[i], cores[i]);
        EXPECT_EQ(p[i], cor);
        const Color cor0(i, i, i);
        EXPECT_EQ(p[i], cor0);
    }
}

static void verificaCores(const int line,
      const Peca& p,
      const std::vector<gui::Color>& cores) {
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        const auto& cor = p[i];
        EXPECT_TRUE(std::find(cores.cbegin(), cores.cend(), cor) != cores.cend()) << line;
    }
}

static void verificaCores(const int line,
      const std::vector<gui::Color>& cores) {
    for (unsigned char i = 0; i < 100; ++i) {
        const auto p = Peca::cria(cores);
        verificaCores(line, p, cores);
        //mck::printPeca(__FILE__, line, p);
    }
}

TEST(TestePeca, cria_peca) {
    std::vector<gui::Color> cores;

    cores.emplace_back(1, 2, 3);
    const auto p1 = Peca::cria(cores);
    EXPECT_EQ(p1, Peca(std::vector<gui::Color>(TAMANHO_PECA, { 1, 2, 3 })));

    verificaCores(__LINE__, cores);

    cores.emplace_back(1, 2, 3);
    EXPECT_EQ(Peca::cria(cores), p1);
    verificaCores(__LINE__, cores);

    cores.emplace_back(4, 5, 6);
    verificaCores(__LINE__, cores);

    cores.emplace_back(10, 153, 12);
    verificaCores(__LINE__, cores);
}
}
}
