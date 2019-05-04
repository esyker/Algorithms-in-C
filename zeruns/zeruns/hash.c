
#include <stdio.h>
#include <stdlib.h>


#include "hash.h"


/*****************************************************************************************
 * Converte_decimal_linha
 *
 * Argumentos: puzzle-tabela
 *			   i-linha para ser convertida
 *			   max-tamanho da tabela
 *
 * Return: número em decimal
 *
 * Descrição: Converte a linha i já toda preenchida num número decimal para se
 *		colocar numa tabela.
 *
 ****************************************************************************************/
 
int Converte_decimal_linha(int **puzzle, int linha,int max)
{
	int j,n=0;
	
	for(j=0;j<max;j++){
		n+=(puzzle[linha][j]<<j);
		
	}
	return n;
}

/*****************************************************************************************
 * Converte_decimal_coluna
 *
 * Argumentos: puzzle-tabela
 *			j-coluna para ser convertida
 *			max-tamanho da tabela
 *
 * Return: número em decimal
 *
 * Descrição: Converte a coluna j já toda preenchida num número deciaml para se
 *		colocar numa tabela.
 *
 ****************************************************************************************/
 
int Converte_decimal_coluna(int **puzzle, int coluna,int max)
{
	int i,n=0;
	
	for(i=0;i<max;i++){
		n+=puzzle[i][coluna]<<i;
		
		
	}
	return n;
}

int Disperse(int decimal,int max)
{
	return (decimal*PESO) %max;
}

int Procura_linear(int **hash,int max,int decimal,int j,int maxHash)
{
	int i;
	
	
	i=Disperse(decimal,max);
	
	if(hash[i][j]==decimal){
		return -1;
	}
	
	else if(hash[i][j]==0){
		hash[i][j]=decimal;
		return 1;
	}
	
	
	else{
		while(hash[i][j]!=0 && hash[i][j]!=decimal){
			i=(i+1)%maxHash;	
		}
		if(hash[i][j]==decimal){
			return -1;
		}
		else{
			hash[i][j]=decimal;
			return 1;
		}	
	}	
	return 1;
}

int VerificaLinhaCheia(int **puzzle, int max,int linha){
	int i;
	for(i=0;i<max;i++){
		if(puzzle[linha][i]==9)
			return 0;
	}
	return 1;
}

int VerificaColunaCheia(int **puzzle, int max, int coluna){
	int i;
	for(i=0;i<max;i++){
		if(puzzle[i][coluna]==9)
			return 0;
	}
	return 1;
}

int Procura_linear2(int **hash,int max,int decimal,int j,int maxHash)
{
	int i;
	
	
	i=Disperse(decimal,max);
	
	if(hash[i][j]==decimal){
		return -1;
	}
	
	else if(hash[i][j]==0){
		hash[i][j]=decimal;
		return 1;
	}
	
	
	else{
		while(hash[i][j]!=0 && hash[i][j]!=decimal){
			i=(i+1)%maxHash;	
		}
		if(hash[i][j]==decimal){
			return -1;
		}
		else{
			hash[i][j]=decimal;
			return 1;
		}	
	}	
	return 1;
}

int** PreencheHashInicial(int** hash,int **puzzle, int max){
	int i,j;
	for(i=0;i<max;i++){
		for(j=0;j<max;j++){
			if(VerificaLinhaCheia(puzzle,max,i)==1)
				Procura_linear2(hash,max,Converte_decimal_linha(puzzle,i,max),0,(max/0.8)+1);
			
		
			if(VerificaColunaCheia(puzzle,max,j)==1)
				Procura_linear2(hash,max,Converte_decimal_coluna(puzzle,j,max),1,(max/0.8)+1);
		}
	}
	return hash;
}






