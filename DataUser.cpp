#include <stdio.h>
#include <stdlib.h>
#include "UserData.h"
#include "InterfataAplicatie.h"

DataUser* lista_user = nullptr;

DataUser* CautaUser(char nume[]) {
  DataUser* crt = lista_user;
  while (crt) {
    if (strcmp(crt->nume, nume) == 0)
      return crt;
    crt = crt->next;
  }
  return nullptr; 
}

void InserareUser(DataUser* user) {
  if (lista_user == nullptr)
    lista_user = user;
  else
  {
    DataUser* crt = lista_user;
    while (crt->next)
      crt = crt->next;
    crt->next = user;
  }
}

DataUser* CreareUser() {
  DataUser* user = (DataUser*)malloc(sizeof(DataUser));
  if(user)
    memset(user, 0, sizeof(DataUser));

  return user;
}

void SchimbareSirInLiteraMicaUser(char sir[]) {
  for (size_t i = 0; i < strlen(sir); i++)
    sir[i] = tolower(sir[i]);
}

DataUser* SelectieUtilizatorExistent() {
  DataUser* crt = lista_user;
  Meniu meniuUtilizatoriExistenti;
  strcpy_s(meniuUtilizatoriExistenti.numeMeniu, "Alege unul dintre utilizatori:");
  meniuUtilizatoriExistenti.pozitieSelectataMeniu = 1;
  meniuUtilizatoriExistenti.nrElementeMeniu = 0;
  meniuUtilizatoriExistenti.culoare = 4;
  while (crt) {
    strcpy_s(meniuUtilizatoriExistenti.elementeMeniu[meniuUtilizatoriExistenti.nrElementeMeniu++], crt->nume);
    crt = crt->next;
  }
  AlegeMeniu(meniuUtilizatoriExistenti);
  DataUser* crt_user = lista_user;
  int cnt = 0;
  while (crt_user) {
    cnt++;
    if (cnt == meniuUtilizatoriExistenti.pozitieSelectataMeniu)
      return crt_user;
    crt_user = crt_user->next;
  }

  return nullptr;
}


DataUser* CreeareUtilizatorNou() {
  char sir[100];
  printf("\nIntroduce un nume pentru a creea un utilizator nou: ");
  while (1)
  {
    scanf_s("%s", sir, 100);
    if (CautaUser(sir) == nullptr)
      break;
    printf("\nAlege un nume nou: ");
  }
  DataUser* user = CreareUser();
  strcpy_s(user->nume, sir);
  InserareUser(user);

  system("cls");
  return user;

}
enum TipUtilizator {
  UTILIZATOR_NOU, UTILIZATOR_EXISTENT
};


enum TipUtilizator SelectieTipUtilizatori() {
  SetColor(15);
  DataUser* crt = lista_user;
  Meniu meniuTipUtilizatori{
    "WORDLE",
    {"Creeaza un utilizator nou"},
    1,
    1,
    4
  };

  if (crt != nullptr)
  {
    strcpy_s(meniuTipUtilizatori.elementeMeniu[0], "Foloseste un utilizator existent");
    strcpy_s(meniuTipUtilizatori.elementeMeniu[1], "Creeaza un utilizator nou");
    meniuTipUtilizatori.nrElementeMeniu = 2;
  }
    
  
  AlegeMeniu(meniuTipUtilizatori);

  if (crt == nullptr)
    return UTILIZATOR_NOU;

  switch (meniuTipUtilizatori.pozitieSelectataMeniu)
  {
  case 1:
    return UTILIZATOR_EXISTENT;
  case 2:
    return UTILIZATOR_NOU;
  }
  return UTILIZATOR_NOU;
}

DataUser* CautareSauCreareUser() {
  if (SelectieTipUtilizatori() == UTILIZATOR_NOU)
    return CreeareUtilizatorNou();
  else
    return SelectieUtilizatorExistent();
  
}

void SalvareUtilizator() {
  FILE* fptr;
  errno_t err;
  if ((err = fopen_s(&fptr, "Utilizatori.txt", "w+")) != 0) {
    exit(1);
  }
    
  DataUser* crt = lista_user;
  while(crt)
  {
    fprintf(fptr, "user\n");
    fprintf(fptr, "nume:%s\n", crt->nume);
    fprintf(fptr, "jocuri:%d\n", crt->jucate);
    fprintf(fptr, "castigate:%d\n", crt->castigate);
    fprintf(fptr, "prima:%d\n", crt->ghiciri.prima);
    fprintf(fptr, "doua:%d\n", crt->ghiciri.a_doua);
    fprintf(fptr, "treia:%d\n", crt->ghiciri.a_treia);
    fprintf(fptr, "patra:%d\n", crt->ghiciri.a_patra);
    fprintf(fptr, "cincea:%d\n", crt->ghiciri.a_cincea);
    fprintf(fptr, "sasea:%d\n", crt->ghiciri.a_sasea);
    fprintf(fptr, "castiguri:%d\n", crt->castiguri_neintrerupte);
    fprintf(fptr, "max_castiguri:%d\n", crt->max_castiguri_neintrerupte);
    fprintf(fptr, "nivel_greu:%d\n", crt->nivel_greu ? 1 : 0);
    fprintf(fptr, "enduser\n");

    crt = crt->next;
  }
  fclose(fptr);
}

void CitireUtilizatori() {
  FILE* fptr;
  errno_t err;
  if ((err = fopen_s(&fptr, "Utilizatori.txt", "r+")) != 0) {
    if ((err = fopen_s(&fptr, "Utilizatori.txt", "w+")) != 0) {
      perror("Error opening file");
      exit(1);
    }
  }
  char sir[200] = {};
  DataUser* crt = nullptr;
  while (fscanf_s(fptr, "%s", sir, 200) != EOF) {
    if (strcmp(sir, "user") == 0)
      crt = CreareUser();
    else if (strcmp(sir, "enduser") == 0)
      InserareUser(crt);
    else if(crt)
    {
      char key[100] = {}, valoare[200] = {};
      char* separator = strchr(sir, ':');
      strncpy_s(key, sir, separator - sir);
      strcpy_s(valoare, separator + 1);
      if (strcmp(key, "nume") == 0)
        strcpy_s(crt->nume, valoare);
      else if (strcmp(key, "jocuri") == 0)
        crt->jucate = atoi(valoare);
      else if (strcmp(key, "castigate") == 0)
        crt->castigate = atoi(valoare);
      else if (strcmp(key, "castiguri") == 0)
        crt->castiguri_neintrerupte = atoi(valoare);
      else if (strcmp(key, "max_castiguri") == 0)
        crt->max_castiguri_neintrerupte = atoi(valoare);
      else if (strcmp(key, "nivel_greu") == 0)
        crt->nivel_greu = atoi(valoare);
      else if (strcmp(key, "prima") == 0)
        crt->ghiciri.prima = atoi(valoare);
      else if (strcmp(key, "doua") == 0)
        crt->ghiciri.a_doua = atoi(valoare);
      else if (strcmp(key, "treia") == 0)
        crt->ghiciri.a_treia = atoi(valoare);
      else if (strcmp(key, "patra") == 0)
        crt->ghiciri.a_patra = atoi(valoare);
      else if (strcmp(key, "cincea") == 0)
        crt->ghiciri.a_cincea = atoi(valoare);
      else if (strcmp(key, "sasea") == 0)
        crt->ghiciri.a_sasea = atoi(valoare);
    }
  }
  fclose(fptr);
}

void SetareInformatiiUser(DataUser* user,const Rezultat& joc) {
  user->jucate++;
  if (joc.rezultat_joc)
    user->castigate++;
  if (joc.rezultat_joc)
  {
    user->castiguri_neintrerupte++;
    if (user->castiguri_neintrerupte > user->max_castiguri_neintrerupte)
      user->max_castiguri_neintrerupte = user->castiguri_neintrerupte;
  }
  else
    user->castiguri_neintrerupte = 0;
  if (joc.rezultat_joc)
  {
    if (joc.nr_incercari == 1)
      user->ghiciri.prima++;
    if (joc.nr_incercari == 2)
      user->ghiciri.a_doua++;
    if (joc.nr_incercari == 3)
      user->ghiciri.a_treia++;
    if (joc.nr_incercari == 4)
      user->ghiciri.a_patra++;
    if (joc.nr_incercari == 5)
      user->ghiciri.a_cincea++;
    if (joc.nr_incercari == 6)
      user->ghiciri.a_sasea++;
  }
}

void AfisareBara(int n) {
  SetColor(2);
  for (int i = 0; i <= n; i++)
    printf("%c%c", 219, 219);;
  SetColor(15);
}

void AfisareDistributie(DataUser* user) {
  printf("\n - Distributia ghicirilor: \n");
  printf("    - 1: ");
  AfisareBara(user->ghiciri.prima);
  printf(" %d\n", user->ghiciri.prima);
  printf("    - 2: ");
  AfisareBara(user->ghiciri.a_doua);
  printf(" %d\n", user->ghiciri.a_doua);
  printf("    - 3: ");
  AfisareBara(user->ghiciri.a_treia);
  printf(" %d\n", user->ghiciri.a_treia);
  printf("    - 4: ");
  AfisareBara(user->ghiciri.a_patra);
  printf(" %d\n", user->ghiciri.a_patra);
  printf("    - 5: ");
  AfisareBara(user->ghiciri.a_cincea);
  printf(" %d\n", user->ghiciri.a_cincea);
  printf("    - 6: ");
  AfisareBara(user->ghiciri.a_sasea);
  printf(" %d\n", user->ghiciri.a_sasea);
}

void AfisareStatistici(DataUser* user) {
  printf("\nStatistici:\n");
  printf("\n - Jucate: %d\n", user->jucate);
  if(user->jucate == 0)
    printf("\n - Procentajul de castig: 0\n");
  else {
    float procentaj = ((float)user->castigate / user->jucate) * 100;
    printf("\n - Procentajul de castig: %.0f%%\n", procentaj);
  }
  printf("\n - Castiguri neintrerupte: %d\n", user->castiguri_neintrerupte);
  printf("\n - Cel mai bun sir de castiguri: %d\n", user->max_castiguri_neintrerupte);
  AfisareDistributie(user);

}