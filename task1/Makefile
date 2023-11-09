#
# Created by Marcel Beyer on 21.09.2023.
#

sincos: sincos.o main.o
	gcc sincos.o main.o -o sincos -lm

sincos.o: sincos.c sincos.h Makefile
	gcc -MMD -Wall -Wextra -c sincos.c -o sincos.o -lm

main.o: main.c sincos.h Makefile
	gcc -MMD -Wall -Wextra -c main.c -o main.o -lm

clean:
	rm -f sincos sincos.o main.o sincos.d main.d

-include sincos.d main.d