#
# Created by Marcel Beyer on 21.09.2023.
#

SRC = main.c sincos.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
TGT = sincos
LIBS = -lm

$(TGT): $(OBJ)
	gcc -o $@ $+ $(LIBS)

%.o: %.cc Makefile
	gcc -MMD -Wall -Wextra -c -o $@ $< $(LIBS)

clean:
	rm -f $(OBJ) $(DEP) $(TGT)

-include $(DEP)
