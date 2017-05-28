
.SUFFIXES:
.SUFFIXES: .cpp .c .o

.PHONY: $(SUBDIRS)

ifeq ($(DEBUG_MAKE),)
SILENT=@
else
SILENT=
endif

# diretórios de destino de programas e bibliotecas
BINDIR = $(COLUNAS_DIR)/bin
LIBDIR = $(COLUNAS_DIR)/bin/lib
APPDIR = $(COLUNAS_DIR)/bin/app
SRCDIR = $(COLUNAS_DIR)/src
TSTDIR = $(COLUNAS_DIR)/tst
TSTBIN = $(TSTDIR)/bin
MCKDIR = $(COLUNAS_DIR)/mck
MCKBIN = $(MCKDIR)/bin

INCDIR =	\
			-I ./ \
			-I $(SRCDIR) \
			-I $(BOOST_ROOT) \

INCLIBDIR = -L$(LIBDIR) \

# miscellaneous OS-dependent stuff
SHELL = /bin/sh
# make
MAKE = make
# nome do seu compilador C
CC = ccache gcc
# nome do compilador c++
CXX = ccache g++
# nome link editor
LD = ld
# comando de criação de arquivo de biblioteca (.a)
AR = ar rc
# segundo passo na criação de uma biblioteca .a (use "touch" se não for necessário)
AR2 = ranlib
# strip de biblioteca
STRIP = strip
# deleção de arquivo
RM = rm -f
# move de arquivo
MV = mv
# echo
ECHO = @echo

CFLAGS += -DRELEASE -DNDEBUG -Wall -Werror -Wparentheses -fpic -Os $(INCDIR)
CPPFLAGS = $(CFLAGS) -fno-enforce-eh-specs -pedantic-errors -Wno-long-long -std=c++11

.cpp.o:
	@echo "$(ECHO_COMP)[C++   ] $< $(ECHO_FIM_COR)"
	$(SILENT)$(CXX) -c $(CPPFLAGS) $(LCPPFLAGS) $< -o $@

.c.o:
	@echo "$(ECHO_COMP)[C     ] $< $(ECHO_FIM_COR)"
	$(SILENT)$(CC) -c $(CFLAGS) $(LCFLAGS) $< -o $@

ifneq ($(LIBA),)
$(LIBA): $(OBJS)
	@echo "$(ECHO_LIB)[AR    ] $@ $(ECHO_FIM_COR)"
	$(SILENT)$(RM) $@
	$(SILENT)$(AR) $@ $(OBJS)
	$(SILENT)$(AR2) $@
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(DESTLIBDIR)/$@
	$(SILENT)$(MV) $@ $(DESTLIBDIR)
endif
endif

ifneq ($(LIBSO),)
$(LIBSO): $(OBJS)
	@echo "$(ECHO_LIB)[SO    ] $@ $(ECHO_FIM_COR)"
	$(SILENT)$(RM) $@
ifdef  PROF
	$(SILENT)$(CXX) -pg -shared -o $@ $(OBJS) $(ARFILES) $(LIBFLAGS)
else
	$(SILENT)$(CXX) -shared -o $@ $(OBJS) $(ARFILES) $(LIBFLAGS)
endif
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(DESTLIBDIR)/$@
	$(SILENT)$(MV) $@ $(DESTLIBDIR)
endif
endif

exetarget: directory_message $(EXE) $(SUBDIRS)

ifneq ($(EXE),)
$(EXE): $(OBJS) $(OTHER_OBJS) $(LIBDIR) $(MAIN_CPP) $(OTHERLIBDIR)
	@echo "$(ECHO_BIN)[EXE   ] $@ $(ECHO_FIM_COR)"
	$(SILENT)$(RM) $@
	$(SILENT)$(CXX) $(EXEFLAGS) -o $@ $(OBJS) $(OTHER_OBJS) $(INCLIBDIR) $(OTHERINCLIBDIR) $(OTHER_EXE_PARMS) $(LIBS)
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(APPDIR)/$(EXE)
	$(SILENT)$(MV) $@ $(APPDIR)
endif
endif

# se há arquivos .o a serem gerados, é gerado o depend.mk
depend: warning_env depend_local $(SUBDIRS)

depend_local:
ifneq ($(strip $(OBJS)),)
	@echo "$(ECHO_DEP)[DEPEND] $(subst $(COLUNAS_DIR),,$(shell pwd)) $(ECHO_FIM_COR)"
	$(SILENT)$(CXX) -MM $(CPPFLAGS) $(LCFLAGS) $(subst .o,.c*,$(OBJS)) > depend.mk

-include depend.mk
endif

format: directory_message format_local $(SUBDIRS)

format_local:
ifneq ($(strip $(shell ls *.h 2>/dev/null)),)
	$(SILENT)astyle.sh *.h
endif
ifneq ($(strip $(shell ls *.cpp 2>/dev/null)),)
	$(SILENT)astyle.sh *.cpp
endif

graph: warning_env graph_local $(SUBDIRS)

graph_local:
ifneq ($(strip $(OBJS)),)
	@echo "$(ECHO_GRAPH)[GRAPH ] $(subst $(COLUNAS_DIR),,$(shell pwd)) $(ECHO_FIM_COR)"
	$(SILENT)$(COLUNAS_DIR)/bin/exe/dependency $(INCDIR) -c$(COLUNAS_DIR) -i/boost/ -i/ClanLib/ $(subst .o,.c*,$(OBJS)) > depend.dot
	$(SILENT)dot -Tps depend.dot -o depend.ps
endif

$(SUBDIRS):
	$(SILENT)$(MAKE) $(MAKECMDGOALS) --no-print-directory -C $@

warning_env:
	@if test "$(COLUNAS_DIR)+set" = "+set" ;\
	then echo "==========================================================="  ;\
	echo "Error: the environment variable COLUNAS_DIR is undefined"     ;\
	echo "       define it and then run the command make"               ;\
	echo "       ex: export COLUNAS_DIR=~/projetos/colunas"             ;\
	echo "==========================================================="  ;\
	exit 1 ; fi ;
	@if test "$(BOOST_ROOT)+set" = "+set" ;\
	then echo "==========================================================="  ;\
	echo "Error: the environment variable BOOST_ROOT is undefined"      ;\
	echo "       define it and then run the command make"               ;\
	echo "       ex: export BOOST_ROOT=/usr/local/boost"                ;\
	echo "==========================================================="  ;\
	exit 1 ; fi ;
	@if test "$(CXXTEST_ROOT)+set" = "+set" ;\
	then echo "==========================================================="  ;\
	echo "Error: the environment variable CXXTEST_ROOT is undefined"    ;\
	echo "       define it and then run the command make"               ;\
	echo "       ex: export CXXTEST_ROOT=~/projetos/cxxtest"            ;\
	echo "==========================================================="  ;\
	exit 1 ; fi ;

directory_message: warning_env
	$(ECHO) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ $(subst $(COLUNAS_DIR),,$(shell pwd))"

clean: warning_env clean_local $(SUBDIRS)

clean_local:
	@echo "$(ECHO_CLEAN)[CLEAN ] $(subst $(COLUNAS_DIR),,$(shell pwd)) $(ECHO_FIM_COR)"
	$(SILENT)$(RM)  \
					*.o \
					core \
					$(EXE) \
					$(LIBA) \
					$(LIBSO) \
					$(OBJS) \
					$(OTHER_CLEAN) \
					depend.dot \

distclean: clean
	$(SILENT)$(RM)  \
					depend.ps \
					$(OTHER_DISTCLEAN) \
	