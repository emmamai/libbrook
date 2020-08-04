
ROOTDIR= $(shell pwd)

BROOK_INCLUDE = -I$(ROOTDIR)/include

OBJ_DIRECTORIES = obj obj/event

CFLAGS ?= -Wall -Werror
INCLUDE += $(BROOK_INCLUDE)

LIBBROOK_OBJS := obj/appevent.o
LIBBROOK_OBJS += obj/event/generic_service.o
LIBBROOK_OBJS += obj/event/tick_timer_service.o


SERVICES := bin/BrookUI bin/TickTimerService
EXAMPLES := bin/examples/con_ticktimer

default: lib/libbrook.a $(SERVICES) $(EXAMPLES)

obj/%.o: src/%.c
	mkdir -p $(OBJ_DIRECTORIES)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

lib/libbrook.a: $(LIBBROOK_OBJS)
	mkdir -p lib
	ar rcs $@ $^

bin/%: src/%.c lib/libbrook.a
	mkdir -p bin/
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

bin/%Service: src/services/%Service.c lib/libbrook.a
	mkdir -p bin/
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

bin/examples/%: src/examples/%.c lib/libbrook.a 
	mkdir -p bin/examples
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^
	
bin/BrookUI: src/BrookUI.c lib/libbrook.a
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
		-@rm -r bin obj lib