# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""
	@ln -fs bin/cb

# optimized version
bin/cb	: cbSolver.o main.o lib
			$(CC) $(OPTFLAGS) cbSolver.o main.o -ltm_usage -Llib -o bin/cb
main.o 	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
cbSolver.o	: src/cbSolver.cpp src/cbSolver.h src/graphDef.h src/dset.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

