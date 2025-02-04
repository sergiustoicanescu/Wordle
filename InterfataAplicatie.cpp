#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "InterfataAplicatie.h"

void SetColor(int ForgC) {
  WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
  {
    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }
}

void maximizeWindow() {
  HWND hwnd = GetConsoleWindow();
  ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

BOOL SetConsoleFontSize(const COORD dwFontSize) {
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
  if (!GetCurrentConsoleFontEx(output, false, &info))
    return FALSE;
  info.dwFontSize = dwFontSize;
  return SetCurrentConsoleFontEx(output, false, &info);
  return TRUE;
}

void SageataAici(int pozitieReala, int pozitieSageata, int culoare) {
  if (pozitieReala == pozitieSageata)
  {
    SetColor(culoare);
    printf(" --> ");
  }

  else
  {
    SetColor(15);
    printf("     ");
  }

}

void AlegeMeniu(Meniu& meniu) {
  SetColor(15);
  system("cls");
  int tastaApasata = 0;
  bool refresh = true;

  while (tastaApasata != 13) {
    if (refresh)
    {
      system("cls");

      SetColor(15);
      printf("\n      %s\n\n", meniu.numeMeniu);
      int culoare = meniu.culoare;
      for (int i = 1; i <= meniu.nrElementeMeniu; i++)
      {
        SageataAici(i, meniu.pozitieSelectataMeniu, culoare);
        printf(" %s\n", meniu.elementeMeniu[i - 1]);
      }
      refresh = false;
    }
    
    tastaApasata = _getch();

    if (tastaApasata == 80 && meniu.pozitieSelectataMeniu != meniu.nrElementeMeniu) {
      meniu.pozitieSelectataMeniu++;
      refresh = true;
    }
    else if (tastaApasata == 72 && meniu.pozitieSelectataMeniu != 1)
    {
      meniu.pozitieSelectataMeniu--;
      refresh = true;
    }
      
  }
  SetColor(15);
  system("cls");

}

void Confirmare() {
  SetColor(4);
  printf("\nApasa orice tasta pentru a continua\n");
  SetColor(15);
  int tastaApasata = 0;
  //while (tastaApasata == 0)
  tastaApasata = _getch();
  system("cls");

}