
#######################################
# Turbo Wieszcz ++ in pure C makefile #
# (c)2022 Noniewicz.com               #
#######################################
# rev.: 2022.05.04

# compiler
CXX = gcc

all: tw

tw:		tw.c
		$(CXX) -O3 -DLINUX -Wall -o turbowieszcz tw.c
		strip turbowieszcz

##############################################################

clean:
		rm -f *.o
		rm -f *~
		rm -f turbowieszcz
