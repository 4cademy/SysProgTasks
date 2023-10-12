SRC = find.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
TGT = find

$(TGT): $(OBJ)
	g++ -std=c++17 -o $@ $+

%.o: %.c Makefile
	g++ -std=c++17 -MMD -Wall -Werror -c -o $@ $<

clean:
	rm -f $(OBJ) $(DEP) find

-include $(DEP)