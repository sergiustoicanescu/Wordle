#include <string.h>
#include "Wordle.h"

void TabelFrecventa(int tabel[26], char s[6]) {
  for (int i = 0; i < 5; i++) {
    int c = s[i] - 'a';
    tabel[c] ++;
  }
}

short CheckWord(char cuvinte_pentru_verificare[][6], char* search, int index)
{
  for (size_t i = 0; i < index; i++) {
    if (strcmp(cuvinte_pentru_verificare[i], search) == 0)
      return SUCCES;
  }
  return EROARE;
}

int verificareLiteraCuvant(char x, char temp[5]) {
  for (int i = 0; i < 5; i++) {
    if (x == temp[i])
      return 1;
  }
  return 0;
}

int CheckFolosireLitereVerzi(char* temp, int alfabet[], char cuvant[], char prev[], LitereVerziGresite tablou_verzi_gresite[26]) {
  int sw = 1;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 3) {
      int index = 0;
      char c = i + 'a';
      for (int j = 0; j < 5; j++) {
        if (temp[j] != c && cuvant[j] == c && prev[j] == c) {
          sw = 0;
          tablou_verzi_gresite[i].litera = c;
          tablou_verzi_gresite[i].pozitie[index++] = j + 1;
        }
      }
    }
  }
  if(sw == 1)
    return SUCCES;
  return EROARE;
}
int CheckFolosireLiterePortocalii(char* temp, int alfabet[], int tabel_frecventa_p[], LiterePortocaliiGresite tablou_portocalii_gresite[]) {
  bool sw = true;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 2) {
      char c = i + 'a';
      int frec = tabel_frecventa_p[i]; 
      int cnt = 0;
      for(size_t j = 0; j < strlen(temp); j++){
        if (c == temp[j])
          cnt++;
      }
      if (cnt < frec)
      {
        sw = false;
        tablou_portocalii_gresite[i].litera = c;
        tablou_portocalii_gresite[i].cnt = cnt;
      }
    }
  }
  if(sw)
    return SUCCES;
  return EROARE;
}

void CopiereTabel(int a[26], int b[26]) {
  for (int i = 0; i < 26; i++) {
    a[i] = b[i];
  }
}

void GolireTabelFrecventa(int tabel[]) {
  for (int i = 0; i < 25; i++) {
    tabel[i] = 0;
  }
}

void ConstruireAlfabet(char result_temp[5][2], int alfabet[]) {
  for (int i = 0; i < 5; i++) {
    int c = result_temp[i][0] - 'a';
    if (alfabet[c] == 3)
      continue;
    else if (alfabet[c] == 2) {
      if (result_temp[i][1] == 'v')
        alfabet[c] = 3;
      else
        continue;
    }
    else if (result_temp[i][1] == 'g')
      alfabet[c] = 1;
    else if (result_temp[i][1] == 'p')
      alfabet[c] = 2;
    else if (result_temp[i][1] == 'v')
      alfabet[c] = 3;

  }
}

void DeterminareLitereNefolosite(LitereProcesate& litere, int alfabet[]) {
  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 0) {
      char x = i + 'a';
      litere.nefolosite[index++] = x;
    }
  }
  litere.nefolosite[index] = 0;
}
void DeterminareLitereFolositeGri(LitereProcesate& litere, int alfabet[]) {
  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 1) {
      char x = i + 'a';
      litere.gri[index++] = x;
    }
  }
  litere.gri[index] = 0;
}
void DeterminareLitereFolositeP(LitereProcesate& litere, int alfabet[]) {
  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 2) {
      char x = i + 'a';
      litere.portocalii[index++] = x;
    }
  }
  litere.portocalii[index] = 0;
}
void DeterminareLitereFolositeVerzi(LitereProcesate& litere, int alfabet[]) {
  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (alfabet[i] == 3) {
      char x = i + 'a';
      litere.verzi[index++] = x;
    }
  }
  litere.verzi[index] = 0;
}

void DeterminareAlfabet(LitereProcesate& litere, int alfabet[]) {
  DeterminareLitereNefolosite(litere, alfabet);
  DeterminareLitereFolositeGri(litere, alfabet);
  DeterminareLitereFolositeP(litere, alfabet);
  DeterminareLitereFolositeVerzi(litere, alfabet);
}

short VerificareLungimeCuvant(char* temp) {
  size_t lungime = strlen(temp);
  if (lungime != 5) {
    if (lungime < 5)
      return -1;
    return 1;
  }
  return SUCCES;
}

void ConstruireResultate(char result[][13], char result_temp[][2], int incercare) {
  int index = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 2; j++) {
      result[incercare][index++] = result_temp[i][j];
    }
  }

}


Rezultat Wordle(Prezentare& prezentare) 
{

  char cuvinte[1000][6];
  char cuvinte_pentru_verificare[13000][6];
  int alfabet[26] = {};

  char s[6];
  char result[6] = "";

  int indexCuvintePentruVerificare = 0;
  CitireCuvintePentruVerificare(cuvinte_pentru_verificare, indexCuvintePentruVerificare);
  CitireCuvinte(cuvinte);
  prezentare.getCuvant(s, cuvinte);

  int tabel[26] = {};
  TabelFrecventa(tabel, s);

  int incercare = 0;
  int incercare_reala = -1;
  int incercare_prev = 0;

  char prev[100] = "";
  char temp[100] = "";

  char resultate_joc[6][13] = {};

  int tabel_frecventa_p[26] = {};

  
  while (strcmp(result, s) != 0 && incercare < 6)
  {
    incercare_reala++;
    memset(temp, 0, sizeof(temp));
    strcpy_s(temp, prezentare.getCuvantGhicit(incercare, incercare_reala, incercare_prev, prezentare.nivel_greu));
    incercare_prev = incercare;

    char result_temp[5][2] = { "", "", "", "", "" };

    int copie_tabel[26];
    CopiereTabel(copie_tabel, tabel);

    short rez = VerificareLungimeCuvant(temp);
    prezentare.resultatVerificare[TipVerificare::VERIFICARE_LUNGIME_CUVANT](rez, incercare_reala);
    if (rez != SUCCES)
      continue;
    rez = CheckWord(cuvinte_pentru_verificare, temp, indexCuvintePentruVerificare);
    prezentare.resultatVerificare[TipVerificare::NU_EXISTA_CUVANTUL](rez, incercare_reala);
    if (rez != SUCCES) {
      continue;
    }

    if (prezentare.nivel_greu && incercare != 0) {
      int x = 0;
      LitereVerziGresite tablou_verzi_gresite[26] = {};
      x = CheckFolosireLitereVerzi(temp, alfabet, s, prev, tablou_verzi_gresite);
      prezentare.resultatNivelGreuVerde(x, tablou_verzi_gresite, incercare_reala);
      if (x != SUCCES) {
        continue;
      }
      int y = 0;
      LiterePortocaliiGresite tablou_portocalii_gresite[26] = {};
      y = CheckFolosireLiterePortocalii(temp, alfabet, tabel_frecventa_p, tablou_portocalii_gresite);
      prezentare.resultatNivelGreuPortocaliu(y, incercare_reala, tabel_frecventa_p, tablou_portocalii_gresite);
      if (y != SUCCES) {
        continue;
      }
    }
      memset(prev, 0, sizeof(prev));
      strcpy_s(prev, temp);

      GolireTabelFrecventa(tabel_frecventa_p);

      for (int i = 0; i < 5; i++) {
        int c_temp = temp[i] - 'a';
        if (temp[i] == s[i]) {
          result[i] = temp[i];
          result_temp[i][0] = temp[i];
          result_temp[i][1] = 'v';
          copie_tabel[c_temp]--;
        }
      }
      for (int i = 0; i < 5; i++) {
        int c_temp = temp[i] - 'a';
        if (result_temp[i][0] == '\0') {
          if (verificareLiteraCuvant(temp[i], s) == 1 && copie_tabel[c_temp] != 0) {
            copie_tabel[c_temp]--;
            result_temp[i][0] = temp[i];
            result_temp[i][1] = 'p';
            tabel_frecventa_p[c_temp]++;
          }
          else {
            result_temp[i][0] = temp[i];
            result_temp[i][1] = 'g';
          }
        }
      }
      ConstruireResultate(resultate_joc, result_temp, incercare);
      ConstruireAlfabet(result_temp, alfabet);
      incercare++;
      prezentare.afisareResultat(result_temp, incercare_reala, resultate_joc, incercare, prezentare.nivel_greu);
      LitereProcesate litere;
      DeterminareAlfabet(litere, alfabet);
      prezentare.afisareAlfabet(litere, incercare_reala);

    }

    Rezultat joc;
    strcpy_s(joc.cuvant, s);
    joc.nr_incercari = incercare;
    joc.rezultat_joc = strcmp(result, s) == 0 ? true : false;
    
    return joc;

}