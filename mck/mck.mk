
VPATH = .:$(LIBDIR):$(APPDIR):$(MCKBIN)

CXXTEST_INC=$(CXXTEST_ROOT)

MOVE_TO_BINDIR=1

DESTLIBDIR=$(MCKBIN)

NOME_BASE_LIB = lib$(subst /,,$(subst $(COLUNAS_DIR),,$(shell pwd)))
LIBA=$(NOME_BASE_LIB).a
LIBSO=$(NOME_BASE_LIB).so

include $(COLUNAS_DIR)/colunas.mk

CFLAGS +=	-I$(CXXTEST_INC) \
			-DCOLUNAS_DIR="\"$(COLUNAS_DIR)\"" \
			-DCXXTEST_HAVE_STD \
			-DCXXTEST_HAVE_EH \

libsotarget: directory_message $(LIBSO) $(SUBDIRS)

libatarget: directory_message $(LIBA) $(SUBDIRS)

libbothtarget: directory_message $(LIBA) $(LIBSO) $(SUBDIRS)

local: $(LIBA) $(LIBSO)

ifneq ($(LIBA),)
OTHER_DISTCLEAN+= $(MCKBIN)/$(LIBA)
endif
ifneq ($(LIBSO),)
OTHER_DISTCLEAN+= $(MCKBIN)/$(LIBSO)
endif

run_local: run

run:
	$(ECHO) -n ""
