#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <time.h>
#include <string>
#include <assert.h>
#include "Wordle.h"
#include "UserData.h"
#include "InterfataAplicatie.h"

void TestWordle();
Prezentare GetUtilizatorPrezentare(bool nivel_greu);
void RezultatFinal(const Rezultat& joc);
bool ContinuareJoc();
bool GetLevel(bool level_curent);
void AfisareTutorial();
void AfisareStatistici(DataUser* user);

void Joc(DataUser* user) {
  Prezentare prezentare = GetUtilizatorPrezentare(user->nivel_greu);
  bool jocWordle = true;
  while (jocWordle)
  {
    Rezultat joc = Wordle(prezentare);
    RezultatFinal(joc);
    SetareInformatiiUser(user, joc);
    Confirmare();
    jocWordle = ContinuareJoc();
  }
}

void MeniuPrincipal(DataUser* user)
{
  Meniu meniuPrincipal{
    "MENIU",
    {"Incepe Jocul", "Tutorial", "Alege nivelul", "Statistici utilizator", "Schimba utilizatorul", "Inchide jocul si salveaza datele"},
    6,
    1,
    4
  };
  while (meniuPrincipal.pozitieSelectataMeniu != 6)
  {
    user = CautareSauCreareUser();
    meniuPrincipal.pozitieSelectataMeniu = 1;
    while (meniuPrincipal.pozitieSelectataMeniu < 5)
    {
      AlegeMeniu(meniuPrincipal);
      switch (meniuPrincipal.pozitieSelectataMeniu)
      {
      case 1:
        Joc(user);
        break;
      case 2:
        AfisareTutorial();
        break;
      case 3:
        user->nivel_greu = GetLevel(user->nivel_greu);
        break;
      case 4:
        AfisareStatistici(user);
        Confirmare();
        break;
      case 5:
        break;
      case 6:
        break;
      }
    }
  }
}

void AplicatiePrincipala()
{
  SetConsoleFontSize({ 10, 18});
  maximizeWindow();
  CitireUtilizatori();
  DataUser* user = {};
  MeniuPrincipal(user);
  SalvareUtilizator();
}

int main() 
{
  if (1) 
    AplicatiePrincipala();
  else
    TestWordle();
}