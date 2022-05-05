
#######################################
# Turbo Wieszcz ++ in C++ makefile    #
# (c)2022 Noniewicz.com               #
#######################################
# rev.: 2022.05.05

# compiler
CXX = g++

all: tw

tw:		tw.c
		$(CXX) -O3 -DLINUX -Wall -o turbowieszcz tw.cpp
		strip turbowieszcz

##############################################################

clean:
		rm -f *.o
		rm -f *~
		rm -f turbowieszcz
