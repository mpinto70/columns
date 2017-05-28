
.SUFFIXES:
.SUFFIXES: .dot .png .dox

PNGS = \

TXTS = \

all: Doxyfile $(PNGS) $(TXTS) $(COLUNAS_DIR)/src
	@echo "Criando documentação..."
	@doxygen

.dot.png:
	@echo "----------> $<"
	@dot -Tpng $< -o $@

clean:
	@echo "limpando a documentação..."
	@rm -rf $(COLUNAS_DIR)/../dox_colunas

view:
	google-chrome $(COLUNAS_DIR)/../dox_colunas/html/index.html &
