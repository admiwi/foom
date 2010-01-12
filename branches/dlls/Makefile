# set tabstop=4 noexpandtab 
CXX = gcc
FLAGS = -ggdb -Wall -Iheaders
SRCDIRS = src src/foom_classes 
OBJS := $(foreach DIR, $(SRCDIRS), $(patsubst src/%.c,objs/%.o,$(wildcard $(DIR)/*.c)))
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
	${CXX} ${FLAGS} -shared $< -o $@ $(OBJS)

clean:
	rm -f *.exe objs/*.o objs/*/*.o dlls/*.dll *.stackdump 

