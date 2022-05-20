
ifeq ($(OS),Windows_NT)

else

ifeq ($(shell uname),Darwin)

	CC := clang
	LD := clang
endif

ifeq ($(shell uname),Linux)

	CC := gcc 
	LD := gcc 
endif

endif


CCFLAGS = -x c -c -g -std=c11 -pg -O0  
LDFLAGS = -std=c11 -lm -pg

CCFLAGS += -D DEBUG
CCFLAGS += -D DBG_LEVL=0

#CCFLAGS += -Wextra -pedantic


all : pcbtool

pcbtool : pcbtool.o pcbtool_errors.o pcbtool_lib.o
	$(LD) $(LDFLAGS) -o $@  $^

pcbtool.o : pcbtool.c
	$(CC) $(CCFLAGS) -c -o $@ $^

pcbtool_errors.o : pcbtool_errors.c
	$(CC) $(CCFLAGS) -c -o $@ $^

pcbtool_lib.o : pcbtool_lib.c
	$(CC) $(CCFLAGS) -c -o $@ $^



pcbtool.o : pcbtool.c



.PHONY : all 


.PHONY : clean
clean : 
	rm -rf *.o *.out prep core pcbtool


run : all
	@./main.out

prep : main.c 
	rm -rf prep
	$(CC) -E -D DEBUG -o $@ $^	


