SRC = cracker.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
TGT = cracker

$(TGT): $(OBJ)
	g++ -std=c++17 -o $@ $+

%.o: %.cpp Makefile
	g++ -std=c++17 -MMD -Wall -Werror -c -o $@ $<

all: $(TGT)

clean:
	rm -f $(OBJ) $(DEP) $(TGT)
