
#######################################
# Turbo Wieszcz ++ in pure C makefile #
# (c)2022 Noniewicz.com               #
#######################################
# rev.: 2022.05.06

# compiler
CXX = gcc

all: tw

tw:		tw.c
		$(CXX) -O3 -DLINUX -Wall -std=gnu90 -o turbowieszcz tw.c
		strip turbowieszcz

##############################################################

clean:
		rm -f *.o
		rm -f *~
		rm -f turbowieszcz
