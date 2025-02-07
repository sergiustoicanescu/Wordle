#include "GameResults.h"

struct LitereProcesate {
  char nefolosite[26];
  char gri[26];
  char portocalii[6];
  char verzi[6];
};

enum TipVerificare {
  VERIFICARE_LUNGIME_CUVANT, 
  NU_EXISTA_CUVANTUL,
  GHICIT_CUVANT,
  VERIFICARE_NIVEL_GREU_PORTOCALIU,
  NUMAR_VERIFICARE
};

enum {
  SUCCES = 100,
  EROARE = -100
};

struct LitereVerziGresite {
  char litera;
  int pozitie[7];
};

struct LiterePortocaliiGresite {
  char litera;
  int cnt;
};

struct Prezentare {
  bool nivel_greu;
  void (*getCuvant) (char cuvant[6], char cuvinte_baza_data[][6]);
  char* (*getCuvantGhicit) (int incercare, int incercare_reala, int incercare_prev, int sw);
  void (*afisareAlfabet) (const LitereProcesate& litere, int incercare);
  void (*afisareResultat) (char resultat[][2], int incercare_reala, char resultate_joc[][13], int incercare, int sw);
  void (*resultatVerificare[NUMAR_VERIFICARE]) (short valoare_test, int incercare);
  void (*resultatNivelGreuPortocaliu) (short valoare_test, int incercare, int tabel_frecventa_p[26], LiterePortocaliiGresite tablou_portocalii_gresite[26]);
  void (*resultatNivelGreuVerde) (short valoare_test, LitereVerziGresite tablou_verzi_gresite[26], int incercare);
};

void CitireCuvinte(char cuvinte[][6]);
void CitireCuvintePentruVerificare(char cuvinte_pentru_verificare[][6], int& index);
Rezultat Wordle(Prezentare& prezentare);