

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/*---------------------------------------------------------------------------------
Descirção:Função que aloca memória para os nomes dos ficheiros, sendo qe o 
nome do ficheiro de entrada é igual ao argv1 e o nome do ficheiro de saída é também
igual, mas mudando a extensão para .sol
-----------------------------------------------------------------------------------*/


void AlocaNomeFicheiros(char* argv1, char**nomeFicheiroIn, char**nomeFicheiroOut){
  char* aux;

  *nomeFicheiroIn=(char*)malloc(sizeof(char)*(strlen(argv1)+1));
  strcpy(*nomeFicheiroIn, argv1);

  aux=strstr(argv1, ".puz");/*encontrar a extensão.puz*/
  if(aux==NULL)
    exit(0);
  *aux='\0';
  *nomeFicheiroOut =(char*)malloc(sizeof(char)*(strlen(*nomeFicheiroIn)-strlen(".puz")+strlen(".sol")+1));
  strcpy(*nomeFicheiroOut, argv1);
  strcat(*nomeFicheiroOut, ".sol");
}

/*	-----------------------------------------------------------------------------
  Função:FILE *AbreFicheiro ( char *nome, char *mode )
	Descrição:
		.Função utilizada abrir um ficheiro com um determinado nome e sair do programa
		se essa abertura não tiver sucesso, devolve um ponteiro para o ficheiro.
	Argumentos:
		.char*nome->nome do programa
		.char*mode->modo de abertura do programa
-----------------------------------------------------------------------------------*/
FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *fp;
  fp = fopen ( nome, mode );
  if ( fp == NULL ) {
    
    exit ( 0 );
  }
  return (fp);
}

/*----------------------------------------------------------------------------------
Função:void Usage(char *nomeProg)
Descrição:Função chamada no caso de o programa ser chamado com os argumentos errados
-------------------------------------------------------------------------------------*/
void Usage(char *nomeProg) {
  exit(0);
}
