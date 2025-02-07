#pragma once

struct TestMainData
{
  const char cuvant_cautat[6];
  bool nivel_greu;
  short numarCuvinte;
  const char tip_cuvinte[7][10];
  bool rezultat_joc;
};

struct CuvinteValide
{
  char cuvant[6];
  const char portocalli[6];
  const char verzi[6];
  const char tipCaractere[6];
};

struct CuvinteInvalide
{
  char cuvant[100];
  const char lungimeCuvant[10];
  const char esteCuvantCorect[20];
  const char esteCaracterInvalidCuvantGreuPortocaliu[26];
  const char esteCaracterInvalidCuvantGreuVerde[26];

};

struct TestWordleData {
  TestMainData* test_main;
  CuvinteValide* cuvinte_valide;
  CuvinteInvalide* cuvinte_invalide;
};