
/*
TurboWieszcz++ in C++, v1.0
(c)2022 Noniewicz.com, Jakub Noniewicz aka MoNsTeR/GDC

based on (translated from): previous version written pure C
which was based on: previous version written in Lazarus
which was based on: previous version written for Commodore C-64 sometime in 1993
by me (Jakub Noniewicz) and Freeak (Wojtek Kaczmarek)
which was based on:
idea presented in "Magazyn Amiga" magazine and implemented by Marek Pampuch.
also inspired by version written for iPhone by Tomek (Grych) Gryszkiewicz.

Tested (compiled and run):
- Linux Debian 4.19.37-5+deb10u1 / gcc (g++) version 8.3.0
x- FreeBSD 6.3-RELEASE / gcc (g++) version ?
*- Windows 7 / MinGW / gcc (g++) version 6.3.0
*/

//created: 20220505
//updated: 20220506


/* TODO:
- all done
*/


#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "tw.h"


using namespace std;


//defines

#define TWNAME "TurboWieszcz++ - wersja w C++, v1.0\n"
#define TWMORE "Generator poezji (FREEWARE)\n(c)2022 Noniewicz.com, Jakub Noniewicz aka MoNsTeR/GDC\nhttp://www.noniewicz.com/\n"


void help(char *exe)
{
  fprintf(stderr, TWNAME);
  fprintf(stderr, TWMORE);
  fprintf(stderr, "\nużycie:\n");
  fprintf(stderr, "\t%s [-c liczba] [-r] [-m liczba]\n", exe);
  fprintf(stderr, "\t%s [-a]\n", exe);
  fprintf(stderr, "\t%s [-h]\n\n", exe);
  fprintf(stderr, "gdzie:\n");
  fprintf(stderr, "-h - ninejsza pomoc\n");
  fprintf(stderr, "-a - o programie\n");
  fprintf(stderr, "-c <liczba> - ilość zwrotek (1-%d, domyślnie 4)\n", XLIMIT);
  fprintf(stderr, "-r - powtórzenia dopuszczalne\n");
  fprintf(stderr, "-m <liczba> - rodzaj rymów (0=ABAB, 1=ABBA, 2=AABB)\n");
  fprintf(stderr, "\n");
}

void about()
{
#define ABOUT "\n\
Dodatkowe strofy (c): Grych, Freeak, Monster, Fred i Marek Pampuch.\n\
\n\
Oparty na (przetłumaczony z) poprzedniej wersji napisanej w Lazarusie\n\
opartej z kolei na wersji napisanej na Commodore C-64\n\
gdzieś w 1993 przeze mnie i Wojtka (Freeak-a) Kaczmarka,\n\
opartej z kolei na pomyśle zaprezentowanym w czasopiśmie\n\
\"Magazyn Amiga\" autorstwa Marka Pampucha.\n\
\n\
Zainspirowany również wersją napisaną na iPhone-a przez Tomka (Grycha) Gryszkiewicza.\n\
\n\
Inne wersje (stan na maj 2022):\n\
- Commodore C-64\n\
- Android\n\
- ZX Spectrum\n\
- ZX81\n\
- Amstrad CPC\n\
- Python\n\
- Fortran\n\
- Arduino\n\
- Windows / Raspberry PI / Linux / Windows CE\n\
- Octave / Matlab\n\
- LUA\n\
- konsola Playdate (LUA)\n\
- w C\n\
\n\
Historia programu została opisana w magazynie Ha!art 47 3/2014:\n\
http://www.ha.art.pl/czasopismo/numery-czasopisma/4054-ha-art-47-3-2014\n"

  printf(TWNAME);
  printf(TWMORE);
  printf(ABOUT);
}


int main(int argc, char **argv)
{
  //defaults
  int ile = 4;
  int tryb_rym = 0; //ABAB, ABBA, AABB
  int powtorzeniaOk = 0;


#if defined(_WIN32) || defined(_WIN64)
  SetConsoleOutputCP(65001); //display UTF-8 properly in console on windows
#endif

  //parse shell parameters
  char op1;
  opterr = 0;
  while ((op1 = getopt(argc, argv, "hac:rm:")) != -1)
  {
    switch(op1)
    {
      case 'h': help(argv[0]);
                return 0;
                break;
      case 'a': about();
                return 0;
                break;
      case 'c': if (optarg != NULL)
                {
                  ile = strtol(optarg, NULL, 10);
                  if ((ile < 1) || (ile > XLIMIT))
                  {
                    fprintf(stderr, "Ilość zwrotek musi być w zakresie 1-%d\n", XLIMIT);
                    return -1;
                  }
                }
                else
                {
                  fprintf(stderr, "Opcja -c wymaga podania wartości.");
                  return -1;
                }
                break;
      case 'r': powtorzeniaOk = 1;
                break;
      case 'm': if (optarg != NULL)
                {
                  tryb_rym = strtol(optarg, NULL, 10);
                  if ((tryb_rym < 0) || (tryb_rym > 2))
                  {
                    fprintf(stderr, "Rodzaj rymów musi być w zakresie 0-2\n");
                    return -1;
                  }
                }
                else
                {
                  fprintf(stderr, "Opcja -m wymaga podania wartości.");
                  return -1;
                }
                break;
      default: break;
    }
  }

  srand(time(NULL));
  TurboWieszcz tw;
  printf(tw.generate_poem(ile, tryb_rym, powtorzeniaOk).c_str());

  return 0;
}
