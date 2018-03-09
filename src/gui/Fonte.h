
#pragma once

#include <cstdint>
#include <string>

namespace gui {

/** Responsável por representar uma fonte. */
class Fonte {
public:
    /**
     * @param nome      o nome da fonte (caminho para o arquivo)
     * @param tamanho   o tamanho da fonte
     */
    Fonte(const std::string& nome,
          unsigned char tamanho);
    void swap(Fonte& rhs);
    const std::string& nome() const { return nome_; }
    unsigned char tamanho() const { return tamanho_; }

private:
    std::string nome_;      ///< o nome da fonte (caminho para o arquivo)
    unsigned char tamanho_; ///< o tamanho da fonte
};

bool operator==(const Fonte& lhs, const Fonte& rhs);
bool operator!=(const Fonte& lhs, const Fonte& rhs);
}
