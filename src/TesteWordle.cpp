#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Wordle.h"
#include "TestsWordle.h"
#include "TestDataWordle.h"

TestWordleData test_wordle;


bool ComparareLitereProcesate(const LitereProcesate& litere, const LitereProcesate& resultat) {
  if (strcmp(litere.portocalii, resultat.portocalii) != 0)
    return false;
  if (strcmp(litere.verzi, resultat.verzi) != 0)
    return false;
  return true;
}

void GetCuvantTest(char s[], char cuvinte[][6]) {
  strcpy_s(s, 6, test_wordle.test_main->cuvant_cautat);
}

void GetInformatiiCuvantCurent(int incercare, bool& este_in_cuvinte_valide, int& pozitie) {
  int pozitie_valida = 0;
  int pozitie_invalida = 0;
  for (int i = 0; i < test_wordle.test_main->numarCuvinte; i++) 
  {
    if (strcmp(test_wordle.test_main->tip_cuvinte[i], "valid") == 0)
    {
      if (i == incercare) 
      {
        este_in_cuvinte_valide = true;
        pozitie = pozitie_valida;
        break;
      }
      pozitie_valida++;
    }
    else 
    {
      if (i == incercare) 
      {
        este_in_cuvinte_valide = false;
        pozitie = pozitie_invalida;
        break;
      }
      pozitie_invalida++;
    }
  }
}

char* ReturnareCuvinteTest(int incercare, int incercare_reala, int incercare_prev, int sw) {
  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare_reala, este_valid, pozitie);
  if (este_valid)
  {
    return test_wordle.cuvinte_valide[pozitie].cuvant;
  }
  else
    return test_wordle.cuvinte_invalide[pozitie].cuvant;
}

bool ComparareLitereProcesate(const LitereProcesate& litere, const CuvinteValide& cuvant) {
  if (strcmp(litere.portocalii, cuvant.portocalli) != 0)
    return false;
  if (strcmp(litere.verzi, cuvant.verzi) != 0)
    return false;
  return true;
}

void TestAlfabet(const LitereProcesate& litere, int incercare) {
  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(este_valid); 

  CuvinteValide& cuvant = test_wordle.cuvinte_valide[pozitie];

  assert(ComparareLitereProcesate(litere, cuvant));
}

void TestResultat(char resultat[5][2], int incercare, char resultate_joc[][13], int incercare_buna, int sw) {
  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(este_valid);

  CuvinteValide& cuvant = test_wordle.cuvinte_valide[pozitie];

  for (int i = 0; i < 5; i++) {
    if (resultat[i][1] != cuvant.tipCaractere[i])
      assert(0);
  }
}

void TestVerificareLungimeCuvant(short rez, int incercare) {
  if (rez == SUCCES)
    return;

  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(!este_valid);

  CuvinteInvalide& cuvant = test_wordle.cuvinte_invalide[pozitie];

  if (rez < 0)
    assert(strcmp(cuvant.lungimeCuvant, "prea scurt") == 0);
  else
    assert(strcmp(cuvant.lungimeCuvant, "prea lung") == 0);
}

void TestVerificareExistentaCuvant(short rez, int incercare) {
  if (rez == SUCCES)
    return;

  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(!este_valid);

  CuvinteInvalide& cuvant = test_wordle.cuvinte_invalide[pozitie];

  if (rez != 0)
    assert(strcmp(cuvant.esteCuvantCorect, "nu exista") == 0);
}

void TestVerificareNivelGreuVerde(short pozitie_litera, LitereVerziGresite tablou_verzi_gresite[], int incercare) {
  if (pozitie_litera == SUCCES)
    return;

  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(!este_valid);

  CuvinteInvalide& cuvant = test_wordle.cuvinte_invalide[pozitie];

  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (tablou_verzi_gresite[i].litera != '\0') {
      char c = tablou_verzi_gresite[i].litera;
      assert(cuvant.esteCaracterInvalidCuvantGreuVerde[index++] == c);
    }
  }

}

void TestVerificareNivelGreuPortocaliu(short rez, int incercare, int frec[26], LiterePortocaliiGresite tablou_portocalii_gresite[]) {
  if (rez == SUCCES)
    return;
  char c = rez + 'a';
  
  bool este_valid = true;
  int pozitie = 0;
  GetInformatiiCuvantCurent(incercare, este_valid, pozitie);
  assert(!este_valid);

  CuvinteInvalide& cuvant = test_wordle.cuvinte_invalide[pozitie];

  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (tablou_portocalii_gresite[i].litera != '\0') {
      char c = tablou_portocalii_gresite[i].litera;
      assert(cuvant.esteCaracterInvalidCuvantGreuPortocaliu[index++] == c);
    }
  }

}

void TestRezultatFinal(const Rezultat& joc) {
  assert(joc.rezultat_joc == test_wordle.test_main->rezultat_joc);
}

Prezentare GetTestPrezentare1(TestMainData& t_main, CuvinteValide* c_valide, CuvinteInvalide* c_invalide) {
  test_wordle.test_main = &t_main;
  test_wordle.cuvinte_valide = c_valide;
  test_wordle.cuvinte_invalide = c_invalide;

  Prezentare user;
  user.nivel_greu = t_main.nivel_greu;
  user.getCuvant = &GetCuvantTest;
  user.getCuvantGhicit = &ReturnareCuvinteTest;
  user.afisareAlfabet = &TestAlfabet;
  user.afisareResultat = &TestResultat;
  user.resultatVerificare[TipVerificare::VERIFICARE_LUNGIME_CUVANT] = &TestVerificareLungimeCuvant;
  user.resultatVerificare[TipVerificare::NU_EXISTA_CUVANTUL] = &TestVerificareExistentaCuvant;
  user.resultatNivelGreuPortocaliu = &TestVerificareNivelGreuPortocaliu;
  user.resultatNivelGreuVerde = &TestVerificareNivelGreuVerde;
  return user;
}
void TestWordle(TestMainData& t_main, CuvinteValide* c_valide, CuvinteInvalide* c_invalide,const char* mesaj) {
  Prezentare user = GetTestPrezentare1(t_main, c_valide, c_invalide);
  Wordle(user);
  printf("Testul pentru cuvantul %s a reusit!\n", mesaj);
}



void TestWordle() {

  TestWordle(TestPacat::mainData, TestPacat::cuvinteValide, TestPacat::cuvinteInvalide, "Pacat");
  TestWordle(TestZeama::mainData, TestZeama::cuvinteValide, nullptr, "Zeama");
  TestWordle(TestMorar::mainData, TestMorar::cuvinteValide, nullptr, "Morar");
  TestWordle(TestPalid::mainData, TestPalid::cuvinteValide, nullptr, "Palid");
  TestWordle(TestMacaz::mainData, TestMacaz::cuvinteValide, nullptr, "Macaz");
  TestWordle(TestValva::mainData, TestValva::cuvinteValide, nullptr, "Valva");
  TestWordle(TestAceea::mainData, TestAceea::cuvinteValide, TestAceea::cuvinteInvalide, "Aceea");
  TestWordle(TestAudia::mainData, TestAudia::cuvinteValide, TestAudia::cuvinteInvalide, "Audia");
  TestWordle(TestAtlas::mainData, TestAtlas::cuvinteValide, TestAtlas::cuvinteInvalide, "Atlas");

}



