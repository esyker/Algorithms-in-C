

#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>

void AlocaNomeFicheiros(char* argv1, char**nomeFicheiroIn, char**nomeFicheiroOut);
FILE *AbreFicheiro ( char *nome, char *mode );
void Usage(char *nomeProg);

#endif
