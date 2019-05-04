#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "utils.h"
#include "puzzle.h"
#include "tree.h"
#include "hash.h"

/* Estrutura que guarda os dados para cada um dos puzzles num ficheiro(tamanho e restrição)*/
typedef struct dados{
	int tamanho;
	int restricao;
}dados;

int main(int argc, char *argv[])
{
	dados dados;/* guarda-se os dados para cada um dos puzzles nesta estrutura*/
	Node *root=NULL;/* ponteiro para a raiz da árvore binária que apresenta a solução para cada um dos do puzzles*/ 
	int **puzzle=NULL;/* ponteiro para o puzzle ,preecnchido de acordo com os dados dos ficheiros de entrada*/
	int **hash=NULL;/*ponteiro para a tabela de dispersão usada para registar as linhas e colunas já utilizadas na resolução*/
	int maxHash=0;/*tamanho da tabela de dispersão*/
	
	
	
	char *nomeProg, *nomeFicheiroIn, *nomeFicheiroOut;/* *aux;*/
	FILE *fin, *fout;

	nomeProg=argv[0];

	if (argc!=2)
	{
		Usage(nomeProg);
	}
	nomeProg=argv[0];
	
	AlocaNomeFicheiros(argv[1], &nomeFicheiroIn, &nomeFicheiroOut);/*alocar memória para os nomes dos ficheiros*/
	
	fin= AbreFicheiro(nomeFicheiroIn,"r");/*Abertura do ficheiro de entrada*/
	fout=AbreFicheiro(nomeFicheiroOut, "w");/*Abertura do ficheiro de saída*/
	
	
	
	
	while(fscanf(fin , "%d %d ", &dados.tamanho,&dados.restricao)==2){
	
		int v=0;/*variável que guarda a solução para o problema v=1(Problema Solucionável) v=-1(Problema sem Solução)*/	
		int a, b,i,c; /*variáveis auxiliares*/
		
		if(dados.restricao!=1 && dados.restricao!=2){/*Se a restrição não estiver correta não se resolve o puzzle*/		
				for(i=0;i<(dados.tamanho*dados.tamanho); i++)
					if(fscanf(fin, "%d", &c)!=1) exit(0);			
				fprintf(fout, "%d %d \n\n", dados.tamanho, dados.restricao);
				continue;
		}	
		
		
		puzzle = AlocaPuzzle(puzzle,dados.tamanho);/* Alocação do Puzzle com o tamanho definido*/
		puzzle = PreenchePuzzle(fin,puzzle,dados.tamanho);/* Preenchimento do puzzle com os dados do ficheiro*/
		if(dados.restricao==2){
			maxHash=(dados.tamanho/0.8)+1;
			hash=AlocaHash(hash,maxHash);
			hash=PreencheHashInicial(hash,puzzle,dados.tamanho);
			
		}	
		
		if (dados.restricao==1){/*Resolução para a variante 1*/
		
			root = ResolvePuzzle_variante1 (puzzle, dados.tamanho);
		}
		if(dados.restricao==2){/*Resolução para a variante 2*/
			
			root = ResolvePuzzle_variante2 (puzzle, dados.tamanho,dados.restricao,hash,maxHash);
		}
		if(VerificaCompleto(puzzle, dados.tamanho)==0){/* Se o puzzle não estiver completo significa que não há resolução(v=-1)*/
			v=-1;
		}
		else/*Se o puzzle estiver completo significa que há resolução(v=1)*/
			v=1;
		
		if(v!=-1){/*Escrita para o ficheiro de saída da primeira linha e do puzzle*/  
			fprintf(fout, "%d %d %d\n", dados.tamanho, dados.restricao,v);
			for(a=0;a<dados.tamanho;a++){
				for(b=0;b<dados.tamanho;b++){
					fprintf(fout, "%d ", puzzle[a][b]);		
				}
				fprintf(fout, "\n");
			}
			fprintf(fout, "\n");
		}
		else/*Se o puzzle não tier solução apenas se escreve a primeira linha*/
			fprintf(fout, "%d %d %d\n\n", dados.tamanho, dados.restricao,v);
		
		
		
		FreePuzzle(puzzle,dados.tamanho);
		if(dados.restricao==1){
			FreeNodeRoot_variante1( root,dados.tamanho);
		}
		if(dados.restricao==2){
			FreeHash(hash,maxHash);
			FreeNodeRoot_variante2( root,dados.tamanho,maxHash);
		}
	}

	fclose(fin);
	fclose(fout);
	
	
	free(nomeFicheiroIn);
	free(nomeFicheiroOut);
	return 0;
}
