SRC = myshell.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
TGT = myshell

$(TGT): $(OBJ)
	g++ -std=c++17 -o $@ $+ -lreadline

%.o: %.cpp Makefile
	g++ -std=c++17 -MMD -Wall -Werror -c -o $@ $<

clean:
	rm -f $(OBJ) $(DEP) $(TGT)

-include $(DEP)