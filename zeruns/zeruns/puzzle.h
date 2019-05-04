
#ifndef _PUZZLE_H
#define _PUZZLE_H

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int** AlocaPuzzle(int **puzzle,int max);
int** AlocaHash(int**hash,int max);
int** PreenchePuzzle(FILE *f,int **puzzle,int m);
int Verifica_paridadeN(int **puzzle, int n,int l,int c,int m);
int Verifica_paridadeS (int **puzzle, int n,int l,int c,int m);
int VerificaNao(int n, int l,int c, int **puzzle, int max);
int VerificaSim(int n, int l,int c, int **puzzle, int max);
void FreePuzzle (int **puzzle, int m);
void FreeHash(int **hash,int max);
int Verifica_linha_cheia(int **puzzle,int max,int linha);
int Verifica_coluna_cheia(int **puzzle,int max,int coluna);
int SolveByCondition_variante2(int **puzzle, int max,int variante,int **hash,int maxHash);
int VerificaCompleto(int **puzzle,int max);
int SolveByCondition_variante1(int **puzzle, int max);
#endif
