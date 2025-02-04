#pragma once
#include "GameResults.h"

struct DistributiaGhicirilor {
  int prima;
  int a_doua;
  int a_treia;
  int a_patra;
  int a_cincea;
  int a_sasea;
};

struct DataUser {
  char nume[40];
  int jucate;
  int castigate;
  DistributiaGhicirilor ghiciri;
  int castiguri_neintrerupte;
  int max_castiguri_neintrerupte;
  bool nivel_greu;
  DataUser* next;
};

DataUser* CautareSauCreareUser();
void SalvareUtilizator();
void CitireUtilizatori();
void SetareInformatiiUser(DataUser* user,const Rezultat& joc);
void AfisareUser(DataUser* user);