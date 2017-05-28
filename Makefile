
default: subdirs

SUBDIRS = src tst mck

subdirs: $(SUBDIRS)

$(MAKECMDGOALS): $(SUBDIRS)

tst: src mck

include colunas.mk
