# set tabstop=4 noexpandtab 
CXX = gcc
FLAGS = -ggdb -Wall -Iheaders
SRCDIRS = src src/foom_classes src/foom_libs
OBJS := $(foreach DIR, $(SRCDIRS), $(patsubst src/%.c,obj/%.o,$(wildcard $(DIR)/*.c)))
HDRS := $(wildcard headers/*.h)

all: foom.exe 

foom.exe : $(HDRS) $(OBJS)
	${CXX} ${FLAGS} -o foom.exe $(OBJS)

obj/%.o: src/%.c
	${CXX} ${FLAGS} -c $< -o $@

clean:
	rm -f *.exe obj/*.o obj/*/*.o *.stackdump 

