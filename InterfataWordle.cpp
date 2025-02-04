#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <time.h>
#include <string>
#include <assert.h>
#include <conio.h>
#include "Wordle.h"
#include "InterfataAplicatie.h"

void TestWordle();

void SchimbareSirInLiteraMica(char sir[]) {
  for (size_t i = 0; i < strlen(sir); i++)
    sir[i] = tolower(sir[i]);
}

void CitireCuvinte(char cuvinte[][6]) {
  FILE* fptr;
  errno_t err;
  if ((err = fopen_s(&fptr, "Cuvinte.txt", "r+")) != 0) {
    exit(1);
  }
  char l[6] = {};
  int i = 0;
  while (fscanf_s(fptr, "%s", l, 6) != EOF) {
    strcpy_s(cuvinte[i++], l);
  }
  fclose(fptr);
}

void CitireCuvintePentruVerificare(char cuvinte_pentru_verificare[][6], int& index) {
  FILE* fptr;
  errno_t err;
  if ((err = fopen_s(&fptr, "BaseCuvinte.txt", "r+")) != 0) {
    exit(1);
  }
  char l[6] = {};
  while (fscanf_s(fptr, "%s", l, 6) != EOF) {
    strcpy_s(cuvinte_pentru_verificare[index++], l);
  }
  fclose(fptr);
}

void GetCuvant(char s[], char cuvinte[][6]) {
  srand(static_cast<unsigned int>(time(nullptr)));
  int v = rand() % 977 + 1;
  v--;
  strcpy_s(s, 6, cuvinte[v]);
}

void TextTutorial() {
  printf("\n------------------------------------------------------------------------------\n");
  printf("\nGhiceste cuvantul din 6 incercari. \n");
  printf("\nDupa fiecare incercare, culoarea literelor se schimba si iti arata cat de aproape ai fost de a ghici cuvantul: \n");
  SetColor(2);
  printf("\nC ");
  SetColor(8);
  printf("O P I L\n");
  SetColor(15);
  printf("Litera C exista in cuvant si e in locul corect.\n");
  SetColor(8);
  printf("\nG U ");
  SetColor(14);
  printf("L ");
  SetColor(8);
  printf("E R\n");
  SetColor(15);
  printf("Litera L e in cuvant, dar nu e in locul corect.\n");
  SetColor(2);
  printf("\nH A I ");
  SetColor(8);
  printf("N ");
  SetColor(2);
  printf("E\n");
  SetColor(15);
  printf("Litera N nu e deloc in cuvant.\n");
  printf("\nDaca alegi nivelul GREU orice litera ghicita trebuie folosita in urmatoarea incercare.\n");
  SetColor(2);
  printf("\nDISTRACTIE!\n");
  SetColor(15);
  printf("\n------------------------------------------------------------------------------\n");
}

void AfisareTutorial() {
  system("cls");
  TextTutorial();
  Confirmare();
  
}

bool GetLevel(bool level_curent) {
  Meniu meniuNivel{
    "Alege nivelul usor sau greu:",
    {"Usor", "Greu"},
    2,
    level_curent ? 2 : 1,
    4
  };
  AlegeMeniu(meniuNivel);
  if (meniuNivel.pozitieSelectataMeniu == 1)
    return 0;
  return 1;

}

char* ReturnareCuvantGhicit(int incercare, int incercare_reala, int incercare_prev, int sw) {
  if (incercare_reala == 0)
    if (sw)
      printf("Ati ales nivelul greu!\n");
    else
      printf("Ati ales nivelul usor!\n");
  if (incercare != 0 && incercare != incercare_prev)
  {
    printf("Mai aveti %d incercari!\n", 6 - incercare);
    printf("\n------------------------------------------------------------------------------\n");
  }

  static char cuvant[100] = "";
  memset(cuvant, 0, sizeof(cuvant));
  printf("\nIntroduceti un cuvant...\n");
  scanf_s("%s", cuvant, 100);
  SchimbareSirInLiteraMica(cuvant);
  return cuvant;
}

void afisare_resultat(char a[5][2], int incercare_reala, char result[][13], int incercare, int sw) {
  system("cls");
  if (sw)
    printf("Ati ales nivelul greu!\n");
  else
    printf("Ati ales nivelul usor!\n");
  printf("\n------------------------------------------------------------------------------\n\n");
  SetColor(15);
  for (int i = 0; i < incercare; i++) {
    for (int j = 0; j < 12; j+=2) {
      if (result[i][j + 1] == 'g')
        SetColor(8);
      else if (result[i][j + 1] == 'p')
        SetColor(14);
      else
        SetColor(2);
      printf("%c ", (char)toupper(result[i][j]));
    }
    SetColor(15);
    printf("\n");
  }
  SetColor(15);
  printf("\n");
}

void AfisareAlfabet(const LitereProcesate& litere, int incercare) {
  printf("\nLitere nefolosite:\n");
  for (size_t i = 0; i < strlen(litere.nefolosite); i++) {
    printf("%c ", (char)toupper(litere.nefolosite[i]));
  }
  printf("\nLitere folosite:\n");
  SetColor(8);
  for (size_t i = 0; i < strlen(litere.gri); i++) {
    printf("%c ", (char)toupper(litere.gri[i]));
  }
  SetColor(15);
  printf("\nLitere portocalii:\n");
  SetColor(14);
  for (size_t i = 0; i < strlen(litere.portocalii); i++) {
    printf("%c ", (char)toupper(litere.portocalii[i]));
  }
  SetColor(15);
  printf("\nLitere verzi:\n");
  SetColor(2);
  for (size_t i = 0; i < strlen(litere.verzi); i++) {
    printf("%c ", (char)toupper(litere.verzi[i]));
  }
  SetColor(15);
  printf("\n\n");
}


void VerificareLungimeCuvant(short rez, int incercare){
  if (rez == SUCCES)
    return;
  if (rez < 0)
    printf("\nPrea putine litere\n");
  else
    printf("\nPrea multe litere\n");
}

void VerificareExistentaCuvant(short rez, int incercare) {
  if (rez == SUCCES)
    return;
  printf("\nCuvantul nu a fost gasit in lista\n");
}

void VerificareNivelGreuVerde(short pozitie_litera, LitereVerziGresite tablou_verzi_gresite[26], int incercare) {
  if (pozitie_litera == SUCCES)
    return;
  printf("\nCuvantul trebuie sa contina: \n");
  for (int i = 0; i < 25; i++) {
    if (tablou_verzi_gresite[i].litera != '\0')
    {
      char c = tablou_verzi_gresite[i].litera;
      if (tablou_verzi_gresite[i].pozitie[1] == 0)
        printf(" - litera %c pe pozitia %d", (char)toupper(c), tablou_verzi_gresite[i].pozitie[0]);
      else
      {
        printf(" - litera %c pe pozitiile ", (char)toupper(c));
        for (int j = 0; j < 7; j++) {
          if (tablou_verzi_gresite[i].pozitie[j + 1] == 0) {
            printf(" si %d", tablou_verzi_gresite[i].pozitie[j]);
            break;
          }
          else {
            if (j != 0)
              printf(", ");
            printf("%d", tablou_verzi_gresite[i].pozitie[j]);
          }
        }
      }
      printf("\n");
    }
  }
  printf("\n");
}

void VerificareNivelGreuPortocaliu(short rez, int incercare, int tabel_frec[26], LiterePortocaliiGresite tablou_portocalii_gresite[26]) {
  if (rez == SUCCES)
    return;
  printf("\nCuvantul trebuie sa contina cel putin: \n");
  for (int i = 0; i < 26; i++) {
    if (tablou_portocalii_gresite[i].litera != '\0')
    {
      char c = tablou_portocalii_gresite[i].litera;
      int aparitii = tablou_portocalii_gresite[i].cnt;
      int frec = tabel_frec[i];
      if (aparitii == 0)
      {
        if (frec == 1)
          printf(" - litera %c\n", (char)toupper(c));
        else
          printf(" - litera %c de %d ori\n", (char)toupper(c), frec);
      }
      else
      {
        if (frec - aparitii == 1)
          printf(" - litera %c inca o data\n", (char)toupper(c));
        else
          printf(" - litera %c inca de %d ori\n", (char)toupper(c), frec - aparitii);
      }
    }
  }
  printf("\n");
}

void RezultatFinal(const Rezultat& joc) {
  printf("------------------------------------------------------------------------------\n");
  if (joc.rezultat_joc && joc.nr_incercari == 1)
    printf("\nAi ghicit in o incercare! BRAVO!\n");
  else if (joc.rezultat_joc)
    printf("\nAi ghicit in %d incercari!\n", joc.nr_incercari);
  else
  {
    printf("\nCuvantul este ");
    for (size_t i = 0; i < strlen(joc.cuvant); i++)
      printf("%c", (char)toupper(joc.cuvant[i]));
    printf(".\n");
  }
    

}

bool ContinuareJoc() {
  Meniu continuareJoc{
    "Continuati sa jucati?",
    {"Da", "Nu"},
    2,
    1,
    4
  };
  AlegeMeniu(continuareJoc);
  
  if (continuareJoc.pozitieSelectataMeniu == 1)
    return true;
  return false;
  
}

Prezentare GetUtilizatorPrezentare(bool nivel_greu) {
  Prezentare user;
  user.nivel_greu = nivel_greu;
  user.getCuvant = &GetCuvant;
  user.getCuvantGhicit = &ReturnareCuvantGhicit;
  user.afisareAlfabet = &AfisareAlfabet;
  user.afisareResultat = &afisare_resultat;
  user.resultatVerificare[TipVerificare::VERIFICARE_LUNGIME_CUVANT] =  &VerificareLungimeCuvant;
  user.resultatVerificare[TipVerificare::NU_EXISTA_CUVANTUL] = &VerificareExistentaCuvant;
  user.resultatNivelGreuPortocaliu = &VerificareNivelGreuPortocaliu;
  user.resultatNivelGreuVerde = &VerificareNivelGreuVerde;

  return user;
}