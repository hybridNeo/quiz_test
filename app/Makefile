# Normally this makefile shouldn't be called directly and we expect the output
# path to be on a certain location to fit together with the other OP-TEE
# gits and helper scripts.
ifeq ($O,)
$(error output path should be specified when calling this makefile)
endif

include $(TA_DEV_KIT_DIR)/host_include/conf.mk

# By default we expect optee_client exported folder to be on a certain relative
# path, but if the client specifies the OPTEE_CLIENT_EXPORT then that path will
# be used instead.
OPTEE_CLIENT_EXPORT ?= ../../../optee_client/out/export

CC		:= $(CROSS_COMPILE)gcc
CPP		:= $(CROSS_COMPILE)cpp
LD		:= $(CROSS_COMPILE)ld
AR		:= $(CROSS_COMPILE)ar
NM		:= $(CROSS_COMPILE)nm
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CROSS_COMPILE)objdump
READELF		:= $(CROSS_COMPILE)readelf

ifdef CFG_GP_PACKAGE_PATH
GP := _gp
endif

srcs := quiz.c 

ifdef CFG_GP_PACKAGE_PATH
CFLAGS += -DWITH_GP_TESTS


endif

objs 	:= $(patsubst %.c,$(O)/%.o, $(srcs))

CFLAGS += -I./


CFLAGS += -I$(OPTEE_CLIENT_EXPORT)/include
CFLAGS += -I$(TA_DEV_KIT_DIR)/host_include




# FIXME: Check if and why we need this flag?
CFLAGS += -DUSER_SPACE
ifeq ($(CFG_ENC_FS),y)
CFLAGS += -DCFG_ENC_FS
endif

ifndef CFG_GP_PACKAGE_PATH
CFLAGS += -Wall -Wcast-align -Werror \
	  -Werror-implicit-function-declaration -Wextra -Wfloat-equal \
	  -Wformat-nonliteral -Wformat-security -Wformat=2 -Winit-self \
	  -Wmissing-declarations -Wmissing-format-attribute \
	  -Wmissing-include-dirs -Wmissing-noreturn \
	  -Wmissing-prototypes -Wnested-externs -Wpointer-arith \
	  -Wshadow -Wstrict-prototypes -Wswitch-default \
	  -Wwrite-strings \
	  -Wno-missing-field-initializers -Wno-format-zero-length
endif

LDFLAGS += -L$(OPTEE_CLIENT_EXPORT)/lib -lteec
LDFLAGS += -lpthread
CFLAGS += -I../ta/ta_quiz/include
.PHONY: all
all: qtest

qtest: $(objs)
	@echo "  LD      $(O)/$@"
	$(q)@$(CC) -o $(O)/$@ $+ $(LDFLAGS)

$(O)/%.o: $(CURDIR)/%.c
	$(q)mkdir -p $(O)/adbg/src
	@echo '  CC      $<'
	$(q)$(CC) $(CFLAGS) -c $< -o $@

