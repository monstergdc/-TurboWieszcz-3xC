
#######################################
# Turbo Wieszcz ++ in C++ makefile    #
# (c)2022 Noniewicz.com               #
#######################################
# rev.: 2022.05.06

# compiler
CXX = g++

all: main

tw:		tw.cpp tw.h
		$(CXX) -O3 -DLINUX -Wall -c tw.cpp tw.h
		strip turbowieszcz

main:		tw_main.cpp tw.o tw.h
		$(CXX) -O3 -DLINUX -Wall -o turbowieszcz tw_main.cpp tw.o
		strip turbowieszcz

##############################################################

clean:
		rm -f *.o
		rm -f *~
		rm -f turbowieszcz
