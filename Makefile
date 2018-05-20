CROSS_COMPILE ?= 
CFLAGS  += -Wall -O0 -g -std=c99 -D_GNU_SOURCE -pipe
NO_AS_NEEDED = -Wl,--no-as-needed
LDFLAGS = -fPIC $(NO_AS_NEEDED) -lpthread
INC     = -Iinclude
PIC     = -fPIC
AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib

SRCS = $(sort $(wildcard src/*.c))
OBJS = $(SRCS:.c=.o)
LOBJS = $(OBJS)

LDSO_SUFFIX = so
LD_SET_SONAME = -Wl,-soname=
LDSO_PATHNAME = libbrblue.$(LDSO_SUFFIX)

LDA_SUFFIX = a
LDA_PATHNAME = libbrblue.$(LDA_SUFFIX)

STATIC_LIBS = $(LDA_PATHNAME)
SHARED_LIBS = $(LDSO_PATHNAME)
ALL_LIBS = $(SHARED_LIBS) $(STATIC_LIBS)

CFLAGS+=$(USER_CFLAGS) $(MAC_CFLAGS)

all: $(ALL_LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(PIC) -c -o $@ $<

$(LDSO_PATHNAME): $(LOBJS)
	$(CC) $(LDFLAGS) $(LD_SET_SONAME)$(LDSO_PATHNAME) $(USER_LDFLAGS) \
		-shared -o $@ $(LOBJS)

$(LDA_PATHNAME): $(LOBJS)
	$(AR) rcu $@ $+
	$(RANLIB) $@