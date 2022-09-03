
/*
TurboWieszcz++ in pure C, v1.0
(c)2022 Noniewicz.com, Jakub Noniewicz aka MoNsTeR/GDC

based directly on (translated from): previous version written in Lazarus
which was based directly on:
previous version written for Commodore C-64 sometime in 1993
by me (Jakub Noniewicz) and Freeak (Wojtek Kaczmarek)
which was based on:
idea presented in "Magazyn Amiga" magazine and implemented by Marek Pampuch.
also inspired by version written for iPhone by Tomek (Grych) Gryszkiewicz.

Tested (compiled and run):
- Linux Debian 4.19.37-5+deb10u1 / gcc version 8.3.0
- FreeBSD 6.3-RELEASE / gcc version 3.4.6
- Windows 7 / MinGW / gcc version 6.3.0
*/

//created: 20220503
//updated: 20220504, 05, 06, 13
//updated: 20220903


/* TODO:
- all seems done
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif


//defines

//count of titles
#define TCNT 33
//count of different rows
#define XLIMIT 32
//count of possible row endings
#define ECNT1 5
#define ECNT2 5
//static buffer
#define BUFSIZE 256

#define TWNAME "TurboWieszcz++ - wersja w czystym C, v1.0\n"
#define TWMORE "Generator poezji (FREEWARE)\n(c)2022 Noniewicz.com, Jakub Noniewicz aka MoNsTeR/GDC\nhttp://www.noniewicz.com/\n"

//consts (data)

const char *ENDINGS1[ECNT1] = {".", "...", ".", "!", "."};
const char *ENDINGS2[ECNT2] = {"", "...", "", "!", ""};

const int TRYB2ORDER[3][4] = {{0,1,2,3}, {0,1,3,2}, {0,2,1,3}}; //ABAB, ABBA, AABB

const char *TITLES[TCNT] = {
    "Zagłada",
    "To już koniec",
    "Świat ginie",
    "Z wizytą w piekle",
    "Kataklizm",
    "Dzień z życia...",
    "Masakra",
    "Katastrofa",
    "Wszyscy zginiemy...",
    "Pokój?",
    "Koniec",
    "Koniec ludzkości",
    "Telefon do Boga",
    "Wieczne ciemności",
    "Mrok",
    "Mrok w środku dnia",
    "Ciemność",
    "Piorunem w łeb",
    "Marsz troli",
    "Szyderstwa Złego",
    "Okrponości świata",
    "Umrzeć po raz ostatni",
    "Potępienie",
    "Ból mózgu",
    "Wieczne wymioty",
    "Zatrute dusze",
    "Uciekaj",
    "Apokalipsa",
    "Złudzenie pryska",
    "Makabra",
    "Zagłada świata",
    "Śmierć",
    "Spokój"
};

//global variables (allocated for max possible case)

int numer[4][XLIMIT];
int ending[2][XLIMIT];
char *data[4][XLIMIT];


void initdata()
{
//note: this could have been done differently, but copy/paste from Lazarus code was more efficient

///////////////////////////////////////////////
//po 10
  data[0][0]  = "Czy na te zbrodnie nie będzie kary?"; //updated
  data[0][1]  = "Opustoszały bagna, moczary";
  data[0][2]  = "Na nic się modły zdadzą ni czary";
  data[0][3]  = "Z krwi mordowanych sączą puchary";
  data[0][4]  = "To nietoperze, węże, kalmary";
  data[0][5]  = "Próżno nieszczęśni sypią talary";
  data[0][6]  = "Za co nam znosić takie ciężary";
  data[0][7]  = "Złowrogo iskrzą kóbr okulary";
  data[0][8]  = "Próżno swe modły wznosi wikary";	//new
  data[0][9]  = "Pustoszą sny twoje złe nocne mary";	//new
  data[0][10] = "Próżno nieszczęśnik sypie talary"; //grych
  data[0][11] = "Przedziwnie tka się życia logarytm"; //grych
  data[0][12] = "Już Strach wypuścił swoje ogary"; //grych
  data[0][13] = "Niebawem zginiesz w szponach poczwary"; //grych
  data[0][14] = "Wbijają pale złote kafary"; //grych
  data[0][15] = "Życie odkrywa swoje przywary"; //grych
  data[0][16] = "Na dnie ponurej, pustej pieczary"; //grych
  data[0][17] = "Apokalipsy nadeszły czary"; //frk
  data[0][18] = "Upadły anioł wspomina chwałę"; //frk
  data[0][19] = "Życie ukrywa swoje przywary"; //grych LAME but used
  data[0][20] = "Dziwnych owadów wzlatują chmary"; //new 201505
  data[0][21] = "Bombowce biorą nasze namiary"; //201505 restored
  data[0][22] = "Nie da się chwycić z czartem za bary"; //201505 restored
  data[0][23] = "Próżno frajerzy sypią talary";
  data[0][24] = "Nie da sie wyrwać czartom towaru";
  data[0][25] = "Po co nam sączyć podłe browary";
  data[0][26] = "Diler już nie dostarczy towaru";
  data[0][27] = "Lokomotywa nie ma już pary";
  data[0][28] = "Gdy nie każdego stać na browary";
  data[0][29] = "Pożarł Hilary swe okulary";
  data[0][30] = "Spowiły nas trujące opary";
  data[0][31] = "To nie jest całka ani logarytm";

///////////////////////////////////////////////
//po 8
  data[1][0]  = "Już na arenę krew tryska";
  data[1][1]  = "Już piana cieknie im z pyska";
  data[1][2]  = "Już hen w oddali gdzieś błyska";
  data[1][3]  = "Śmierć w kącie czai się bliska";
  data[1][4]  = "Niesamowite duchów igrzyska";
  data[1][5]  = "Już zaciskając łapiska";
  data[1][6]  = "Zamiast pozostać w zamczyskach";
  data[1][7]  = "Rzeka wylewa z łożyska";
  data[1][8]  = "Nieszczęść wylała się miska";	//new
  data[1][9]  = "Już zaciskając zębiska"; //my
  data[1][10] = "Otwarta nieszczęść walizka"; //grych
  data[1][11] = "Niczym na rzymskich boiskach"; //grych
  data[1][12] = "Czart wznieca swe paleniska"; //my
  data[1][13] = "A w mroku świecą zębiska"; //grych - fix
  data[1][14] = "Zewsząd dochodzą wyzwiska"; //grych
  data[1][15] = "Świętych głód wiary przyciska"; //my
  data[1][16] = "Ponuro patrzy z ich pyska"; //grych
  data[1][17] = "Mgła stoi na uroczyskach"; //frk
  data[1][18] = "Kości pogrzebią urwiska"; //frk
  data[1][19] = "Głód wiary tak nas przyciska"; //grych - BAD - fixed
  data[1][20] = "Runęły skalne zwaliska";
  data[1][21] = "Czart rozpala paleniska"; //grych - BAD fixed 201505
  data[1][22] = "A w mroku słychać wyzwiska"; //added 20151129
  data[1][23] = "Znów pusta żebraka miska";
  data[1][24] = "Diabelskie to są igrzyska";
  data[1][25] = "Nie powiedz diabłu nazwiska";
  data[1][26] = "Najgłośniej słychać wyzwiska";
  data[1][27] = "Diabelskie mają nazwiska";
  data[1][28] = "Tam uciekają ludziska";
  data[1][29] = "Tak rzecze stara hipiska";
  data[1][30] = "Gdzie dawne ludzi siedliska";
  data[1][31] = "Najgłośniej piszczy hipiska";

///////////////////////////////////////////////
//po 10
  data[2][0]  = "Rwą pazurami swoje ofiary";
  data[2][1]  = "Nic nie pomoże tu druid stary";
  data[2][2]  = "To nocne zjawy i senne mary";
  data[2][3]  = "Niegroźne przy nich lwowskie batiary";
  data[2][4]  = "Pod wodzą księżnej diablic Tamary";
  data[2][5]  = "Z dala straszliwe trąbia fanfary";
  data[2][6]  = "Skąd ich przywiodły piekła bezmiary";
  data[2][7]  = "Zaś dookoła łuny, pożary";
  data[2][8]  = "A twoje ciało rozszarpie Wilk Szary";	//new
  data[2][9]  = "Tu nie pomoże już siła wiary"; //my
  data[2][10] = "Tak cudzych nieszczęść piją nektary"; //grych
  data[2][11] = "Wszystko zalewa wrzący liparyt"; //grych
  data[2][12] = "Zabójcze są ich niecne zamiary"; //my
  data[2][13] = "Zatrute dusze łączą się w pary"; //grych
  data[2][14] = "Świat pokazuje swoje wymiary"; //grych
  data[2][15] = "Z życiem się teraz weźmiesz za bary"; //my
  data[2][16] = "Brak uczuć, chęci, czasem brak wiary"; //grych
  data[2][17] = "Wspomnij, co mówił Mickiewicz stary"; //frk
  data[2][18] = "Spalonych lasów straszą hektary"; //frk
  data[2][19] = "Z życiem się dzisiaj weźmiesz za bary"; //grych - BAD - fixed
  data[2][20] = "Ksiądz pozostaje nagle bez wiary"; //jn 201505 new
  data[2][21] = "Papież zaczyna odprawiać czary"; //jn 201505 new
  data[2][22] = "Tu nie pomoże paciorek, stary"; //jn 201505 new
  data[2][23] = "Niegroźne przy nich nawet Atari";
  data[2][24] = "Takie są oto piekła bezmiary";
  data[2][25] = "A teraz nagle jesteś już stary";
  data[2][26] = "Mordercy liczą swoje ofiary";
  data[2][27] = "I bez wartości są już dolary";
  data[2][28] = "Gdzie się podziały te nenufary";
  data[2][29] = "Upada oto dąb ten prastary";
  data[2][30] = "Bystro śmigają nawet niezdary";
  data[2][31] = "Już nieruchome ich awatary";

///////////////////////////////////////////////
//po 8
  data[3][0]  = "Wnet na nas też przyjdzie kryska";
  data[3][1]  = "Znikąd żadnego schroniska";
  data[3][2]  = "Powietrze tnie świst biczyska";
  data[3][3]  = "Rodem z czarciego urwiska";
  data[3][4]  = "I swąd nieznośny się wciska";
  data[3][5]  = "Huk, jak z wielkiego lotniska";
  data[3][6]  = "Złowroga brzmią ich nazwiska";
  data[3][7]  = "W kącie nieśmiało ktoś piska";
  data[3][8]  = "Ktoś obok morduje liska";	//new
  data[3][9]  = "Krwią ociekają zębiska"; //my
  data[3][10] = "Wokoło dzikie piarżyska"; //grych, 20151129 fix JN
  data[3][11] = "I żądza czai się niska"; //grych
  data[3][12] = "Diabeł cię dzisiaj wyzyska"; //grych
  data[3][13] = "Płoną zagłady ogniska"; //grych
  data[3][14] = "Gwałt niech się gwałtem odciska!"; //grych
  data[3][15] = "Stoisz na skraju urwiska"; //my
  data[3][16] = "Tam szatan czarta wyiska"; //grych
  data[3][17] = "Uciekaj, przyszłość jest mglista"; //frk, 20151025 changed
  data[3][18] = "Nadziei złudzenie pryska"; //frk
  data[3][19] = "Wydziobią oczy ptaszyska"; //grych - BAD fixed
  data[3][20] = "Padają łby na klepisko"; //new 201505 - restored
  data[3][21] = "Śmierć zbiera żniwo w kołyskach"; //new 201505 - restored
  data[3][22] = "Coś znowu zgrzyta w łożyskach"; //jn new 201505
  data[3][23] = "Spadasz z wielkiego urwiska";
  data[3][24] = "Lawa spod ziemi wytryska";
  data[3][25] = "Wokoło grzmi albo błyska";
  data[3][26] = "Fałszywe złoto połyska";
  data[3][27] = "Najwięcej czart tu uzyska";
  data[3][28] = "Owieczki Zły tu pozyska";
  data[3][29] = "Owieczki spadły z urwiska";
  data[3][30] = "Snują się dymy z ogniska";
  data[3][31] = "To czarne lecą ptaszyska";
}

const char *koniec(int z, int w, char *s)
{
  int chk = 1;
  if ((s != NULL) && (strlen(s) > 0))
  {
    char last = s[strlen(s)-1];
    if ((last == '?') || (last == '!')) chk = 0;
  }
  if ((w == 1) && chk) return ENDINGS2[ending[0][z]];
  if ((w == 3) && chk) return ENDINGS1[ending[1][z]];
  return "";
}

const char *strofa(int z, int w, int w0)
{
  static char buffer[BUFSIZE]; //note: const size, but properly oversized
  int n = numer[w][z];
  char *s = data[w][n];
  snprintf(buffer, sizeof(buffer), "%s%s\n", s, koniec(z, w0, s));
  return buffer;
}

const char *zwrotka(int z, int tryb)
{
  int p = 0;
  static char buffer[BUFSIZE*4]; //note: const size, but properly oversized
  p += snprintf(buffer+p, sizeof(buffer)-p, "%s", strofa(z, TRYB2ORDER[tryb][0], 0));
  p += snprintf(buffer+p, sizeof(buffer)-p, "%s", strofa(z, TRYB2ORDER[tryb][1], 1));
  p += snprintf(buffer+p, sizeof(buffer)-p, "%s", strofa(z, TRYB2ORDER[tryb][2], 2));
  p += snprintf(buffer+p, sizeof(buffer)-p, "%s", strofa(z, TRYB2ORDER[tryb][3], 3));
  return buffer;
}

int checkUniqOK(int z, int w, int value, int powtorzeniaOk)
{
  int i;
  for (i=0;(i<z)&&(!powtorzeniaOk);i++)
  {
    if (numer[w][i] == value) return 0;
  }
  return 1;
}

void setrndrow(int z, int w, int repeat_ok)
{
  do
  {
    numer[w][z] = rand() % XLIMIT;
  }
  while ((z != 0) && !checkUniqOK(z, w, numer[w][z], repeat_ok));
}

char *generate_poem(int cnt, int rym, int repeat_ok)
{
  int z, w, ttid, p;
  static char buffer[BUFSIZE*4*XLIMIT+1024]; //note: const size, but properly oversized

  if ((cnt < 1) || (cnt > XLIMIT)) return "";
  if ((rym < 0) || (rym > 2)) return "";

  ttid = rand() % TCNT;
  for (z=0;z<cnt;z++)
  {
      for (w=0;w<=3;w++) numer[w][z] = -1;
      ending[0][z] = rand() % ECNT2;
      ending[1][z] = rand() % ECNT1;
  }
  for (z=0;z<cnt;z++)
  {
    for (w=0;w<=3;w++)
    {
      setrndrow(z, w, repeat_ok);
    }
  }

  //build output
  p = snprintf(buffer, sizeof(buffer), "\n%s\n\n", TITLES[ttid]);
  for (z=0;z<cnt;z++)
  {
    p += snprintf(buffer+p, sizeof(buffer)-p, "%s\n", zwrotka(z, rym));
  }
  return buffer;
}

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
  const char *s = "Dodatkowe strofy (c): Grych, Freeak, Monster, Fred i Marek Pampuch.\n\
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
\n\
Historia programu została opisana w magazynie Ha!art 47 3/2014:\n\
http://www.ha.art.pl/czasopismo/numery-czasopisma/4054-ha-art-47-3-2014";

  printf(TWNAME);
  printf(TWMORE);
  printf("\n%s\n", s);
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

  initdata();
  srand(time(NULL));
  printf(generate_poem(ile, tryb_rym, powtorzeniaOk));
  return 0;
}
