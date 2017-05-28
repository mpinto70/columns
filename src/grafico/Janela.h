
#ifndef JANELA_H_mhpa
#define JANELA_H_mhpa

#include "gui/Cor.h"
#include "gui/Ponto.h"
#include "gui/Fonte.h"
#include "gui/Retangulo.h"

#include <cstdint>
#include <memory>
#include <string>

/** namespace das entidades relacionadas à biblioteca gráfica. */
namespace grafico {

/** Responsável por gerenciar a janela. */
class Janela {
    public:
        /** Cria a janela informando seu nome, seu canto superior esquerdo,
         * sua largura e sua altura em pixels
         * @param nome      o nome da janela
         * @param largura   a largura da janela
         * @param altura    a altura da janela
         */
        Janela(const std::string & nome,
               uint16_t largura,
               uint16_t altura);
        Janela(const Janela&) = delete;
        Janela& operator=(const Janela&) = delete;
        /** Destrói a janela. */
        virtual ~Janela();
        /** @return a largura da janela. */
        const std::string & nome() const { return nome_; }
        /** @return a largura da janela. */
        uint16_t largura() const { return largura_; }
        /** @return a altura da janela. */
        uint16_t altura() const { return altura_; }
        /** limpa a janela. */
        virtual void limpa() = 0;
        /** mostra a janela. */
        virtual void atualiza() = 0;
        /** desenha uma linha.
         * @param ini   ponto inicial
         * @param fim   ponto final
         * @param cor   cor
         */
        void linha(const gui::Ponto & ini,
                   const gui::Ponto & fim,
                   const gui::Cor & cor);
        /** desenha um retângulo.
         * @param ret   o retângulo
         * @param cor   cor
         */
        void retangulo(const gui::Retangulo & ret,
                       const gui::Cor & cor);
        /** desenha um retângulo.
         * @param te    canto superior esquerdo
         * @param fd    canto inferior direito
         * @param cor   cor
         */
        void retangulo(const gui::Ponto & te,
                       const gui::Ponto & fd,
                       const gui::Cor & cor);
        /** preenche um retângulo.
         * @param ret   o retângulo
         * @param cor   cor
         */
        void preenche(const gui::Retangulo & ret,
                      const gui::Cor & cor);
        /** preenche um retângulo.
         * @param te    canto superior esquerdo
         * @param fd    canto inferior direito
         * @param cor   cor
         */
        void preenche(const gui::Ponto & te,
                      const gui::Ponto & fd,
                      const gui::Cor & cor);
        /** escreve um texto.
         * @param texto o texto a ser escrito
         * @param pt    o ponto na tela
         * @param fonte a fonte
         * @param cor   a cor
         * @returns o retângulo que envolve o texto
         */
        gui::Retangulo escreve(const std::string & texto,
                               const gui::Ponto & pt,
                               const gui::Fonte & fonte,
                               const gui::Cor & cor);
    private:
        std::string nome_;  ///< o nome da janela
        uint16_t largura_;  ///< a largura
        uint16_t altura_;   ///< a altura
        /** desenha uma linha.
         * @param x1    coordenada x do ponto inicial
         * @param y1    coordenada y do ponto inicial
         * @param x2    coordenada x do ponto final
         * @param y2    coordenada y do ponto final
         * @param cor   cor
         */
        virtual void linha_(uint16_t x1,
                            uint16_t y1,
                            uint16_t x2,
                            uint16_t y2,
                            const gui::Cor & cor) = 0;
        /** desenha um retângulo.
         * @param x1    coordenada x do canto superior esquerdo
         * @param y1    coordenada y do canto superior esquerdo
         * @param x2    coordenada x do canto inferior direito
         * @param y2    coordenada y do canto inferior direito
         * @param cor   cor
         */
        virtual void retangulo_(uint16_t x1,
                                uint16_t y1,
                                uint16_t x2,
                                uint16_t y2,
                                const gui::Cor & cor) = 0;
        /** preenche um retângulo.
         * @param x1    coordenada x do canto superior esquerdo
         * @param y1    coordenada y do canto superior esquerdo
         * @param x2    coordenada x do canto inferior direito
         * @param y2    coordenada y do canto inferior direito
         * @param cor   cor
         */
        virtual void preenche_(uint16_t x1,
                               uint16_t y1,
                               uint16_t x2,
                               uint16_t y2,
                               const gui::Cor & cor) = 0;
        /** escreve um texto.
         * @param texto o texto a ser escrito
         * @param x     coordenada x do ponto de escrita
         * @param y     coordenada y do ponto de escrita
         * @param fonte a fonte
         * @param cor   a cor
         * @returns o retângulo que envolve o texto
         */
        virtual gui::Retangulo escreve_(const std::string & texto,
                                        uint16_t x,
                                        uint16_t y,
                                        const gui::Fonte & fonte,
                                        const gui::Cor & cor) = 0;
};

/// O ponteiro compartilhado de Janela
typedef std::shared_ptr<Janela> SharedJanela;

}

#endif
