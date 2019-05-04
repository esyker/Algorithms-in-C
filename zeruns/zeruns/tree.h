
#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"
#include "hash.h"


typedef struct _Node Node;

Node *AllocNode();
Node *NewNode_variante2(int max,int maxHash);
void FreeNodeRoot_variante2(Node *NodeRoot,int max,int maxHash);
Node *ResolvePuzzle_variante2 (int **puzzle,int max,int variante,int **hash,int maxHash);
Node *NewNode_variante1(int max);
void FreeNodeRoot_variante1(Node *NodeRoot,int max);
Node *ResolvePuzzle_variante1 (int **puzzle,int max);
#endif
