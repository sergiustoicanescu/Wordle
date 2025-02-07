#pragma once
#include <Windows.h>

struct Meniu {
  char numeMeniu[100];
  char elementeMeniu[50][100];
  short nrElementeMeniu;
  short pozitieSelectataMeniu;
  short culoare;
};

void maximizeWindow();
BOOL SetConsoleFontSize(const COORD dwFontSize);
void SetColor(int ForgC);
void AlegeMeniu(Meniu& meniu);
void Confirmare();