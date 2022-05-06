
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
*/

//created: 20220505
//updated: 20220506



#include <cstdio>
#include <string>


using namespace std;


//defines

//count of titles
#define TCNT 33
//count of different rows
#define XLIMIT 32
//count of possible row endings
#define ECNT1 5
#define ECNT2 5


class TurboWieszcz
{
private:

  //consts (data)
  const std::string ENDINGS1[ECNT1] = {".", "...", ".", "!", "."};
  const std::string ENDINGS2[ECNT2] = {"", "...", "", "!", ""};

  const int TRYB2ORDER[3][4] = {{0,1,2,3}, {0,1,3,2}, {0,2,1,3}}; //ABAB, ABBA, AABB

  const std::string TITLES[TCNT] = {
    u8"Zagłada",
    u8"To już koniec",
    u8"Świat ginie",
    u8"Z wizytą w piekle",
    u8"Kataklizm",
    u8"Dzień z życia...",
    u8"Masakra",
    u8"Katastrofa",
    u8"Wszyscy zginiemy...",
    u8"Pokój?",
    u8"Koniec",
    u8"Koniec ludzkości",
    u8"Telefon do Boga",
    u8"Wieczne ciemności",
    u8"Mrok",
    u8"Mrok w środku dnia",
    u8"Ciemność",
    u8"Piorunem w łeb",
    u8"Marsz troli",
    u8"Szyderstwa Złego",
    u8"Okrponości świata",
    u8"Umrzeć po raz ostatni",
    u8"Potępienie",
    u8"Ból mózgu",
    u8"Wieczne wymioty",
    u8"Zatrute dusze",
    u8"Uciekaj",
    u8"Apokalipsa",
    u8"Złudzenie pryska",
    u8"Makabra",
    u8"Zagłada świata",
    u8"Śmierć",
    u8"Spokój"
  };

  //variables (allocated for max possible case)

  int numer[4][XLIMIT];
  int ending[2][XLIMIT];
  std::string data[4][XLIMIT];

  const std::string koniec(int z, int w, std::string s);
  const std::string strofa(int z, int w, int w0);
  const std::string zwrotka(int z, int tryb);
  int checkUniqOK(int z, int w, int value, int powtorzeniaOk);
  void setrndrow(int z, int w, int repeat_ok);

public:
  TurboWieszcz();
  const std::string generate_poem(int cnt, int rym, int repeat_ok);

};

