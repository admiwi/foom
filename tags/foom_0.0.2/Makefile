# set tabstop=4 noexpandtab 
CXX = gcc
FLAGS = -ggdb -Wall -Iheaders
SRCDIRS = src src/foom_classes 
CLASSOBJS := $(patsubst src/%.c,objs/%.o,$(wildcard src/foom_classes/*.c))
OBJS := $(patsubst src/%.c,objs/%.o,$(wildcard src/*.c)) $(CLASSOBJS)
LIBFILES = foom_class foom_lib foom_objects foom_hash foom_globals foom_feval
LIBOBJS := $(foreach F, $(LIBFILES), objs/$(F).o) $(CLASSOBJS)
DLLS := $(patsubst src/foom_libs/%.c,dlls/%.dll,$(wildcard src/foom_libs/*.c))
HDRS := $(wildcard headers/*.h)

all: foom.exe 

foom.exe : $(HDRS) $(OBJS) $(DLLS)
	${CXX} ${FLAGS} -o foom.exe $(OBJS)

objs/%.o: src/%.c
	${CXX} ${FLAGS} -c $< -o $@
objs/foom_classes/%.o: src/foom_classes/%.c
	${CXX} ${FLAGS} -c $< -o $@
dlls/%.dll: src/foom_libs/%.c
	${CXX} ${FLAGS} -shared $< -o $@ $(LIBOBJS)

clean:
	rm -f *.exe objs/*.o objs/*/*.o dlls/*.dll *.stackdump 
clean-dlls:
	rm -f *.exe dlls/*.dll 

