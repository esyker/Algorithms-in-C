
#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>

#define PESO 17

int Converte_decimal_linha(int **puzzle, int linha,int max);
int Converte_decimal_coluna(int **puzzle, int coluna,int max);
int Disperse(int decimal,int max);
int Procura_linear(int **hash,int max,int decimal,int j,int maxHash);
int VerificaLinhaCheia(int **puzzle, int max,int linha);
int VerificaColunaCheia(int **puzzle, int max, int coluna);
int Procura_linear2(int **hash,int max,int decimal,int j,int maxHash);
int** PreencheHashInicial(int **hash,int **puzzle, int max);

#endif
