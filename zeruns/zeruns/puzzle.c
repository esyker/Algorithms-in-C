
#include <stdio.h>
#include <stdlib.h>

#include "puzzle.h"

enum check{pode, npode};

/*Função:
	.AlocaPuzzle(  int **puzzle ,int max)
  Descrição:
	.Função utilizada para Alocar o puzzle de acordo com o tamanho fornecido como argumento (max)
  Argumentos:
  	.int**puzzle ->duplo ponteiro da main para o puzzle  
  	.int max->tamanho máximo da tabela a alocar
  Valor de Retorno:
 	.Duplo ponteiro para inteiro que na main é atribuído ao ponteiro do puzz (int**puz)
*/

int** AlocaPuzzle(  int **puzzle ,int max)
{
	int i;
	puzzle=(int**) malloc(sizeof(int*)*max);
	if(puzzle==NULL)
	{
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
    		exit ( 0 );
    }
	for(i=0 ; i<max ;i++)
	{
		puzzle[i]=(int*) malloc(sizeof(int)*max);
		if ( puzzle[i] == NULL ) {
      		fprintf ( stderr, "ERROR: not enough memory available!\n" );
      		exit ( 0 );
      	}
	}
	
	return puzzle;

}
/*------------------------------------------------------------------------------------------------------------------------------
Descriçao: 	
 	Função utilizada para alocar a tabela de dispersão com dimensão pelo menos 20%(dimensão=maxHash) maior que o tamanho do puzzle,
pelo que se assegura que a tabela nunca estará cheia a mais do que 80%
	Função retorna um duplo ponteiro para inteiro que na função main é atribuído ao ponteiro **hash

Argumentos:
	.maxhash-> tamanho máximo da tabela de dispersão
	.int **hash->ponteiros da hash da main
------------------------------------------------------------------------------------------------------------------------------*/
int** AlocaHash(int**hash,int maxHash)
{
	int i,j;
	
	hash=(int**) malloc(sizeof(int*)*maxHash);
	if(hash==NULL)
	{
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
    		exit ( 0 );
	}
	for(i=0;i<maxHash;i++){
		hash[i]=(int*) malloc(sizeof(int)*2);
		if ( hash[i] == NULL ) {
      		fprintf ( stderr, "ERROR: not enough memory available!\n" );
      		exit ( 0 );
      	}
	}
	for(i=0;i<maxHash;i++){
		for(j=0;j<2;j++){
			hash[i][j]=0;
		}
	}
	return hash;
}

/* -----------------------------------------------------------------------
	Descrição:
		.Função que preenche o puzzle com os dados do ficheiro de entrada 
 	Argumentos:
 		.FILE *f-> ponteiro para o ficheiro de entrada com extensão .puz
 		.int m->tamanho máximo do puzzle
 		.int**puzzle->duplo ponteiro da main que represnta o puzzle
-------------------------------------------------------------------------------*/
int** PreenchePuzzle(FILE *f,int **puzzle,int m)
{
	int i,j;
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(fscanf( f,"%d",&puzzle[i][j])!=1) exit(0);
				
		}
	}
	
	return puzzle;
}


/*****************************************************************************************
 * Verifica()
 *
 * Argumentos: n-número a colocar 0 ou 1
 *			l-linha a verificar
 *			c-coluna a verificar
 *			**puzzle-tabela
 *			check-diz se é para ver se pode ou não pode pôr
 *			x1
 *			y1
 *			x2
 *			y2
 * Return: v-sinal que indica se pode ou não pôr o número
 *
 * Descrição: Compara os números à volta para saber se é válido colocar na posição [l][c]
 *
 ****************************************************************************************/

int Verifica(int n, int l , int c, int** puzzle,int check, int x1, int y1, int x2, int y2 ){

	if(check==npode){
		if(puzzle[l+y1][c+x1]==n && puzzle[l+y2][c+x2]==n){
			return -1;
		}
	}

	else if (check==pode){
		if(puzzle[l+y1][c+x1]==!n && puzzle[l+y2][c+x2]==!n){
			return 1;
		}
	}

	return 0;
}

/***************************************************************************************
 * Verifica_paridadeN()
 *
 * Argumentos: **puzzle-tabela
 *			n-número a verificar 0 ou 1
 *			l-linha em que estamos a verificar
 *			c-coluna em que estamos a verificar
 *			m-dimensão da tabela
 * Return: v-sinal que verifica se dá.Se for -1 não se pode pôr o número
 * Efeitos Secundários: nenhum
 *
 * Descrição: Verifica se 1 ou 0 não pode estar naquela posição segundo o número de 1 
 *e 0 já existentes
 *
 **************************************************************************************/
int Verifica_paridadeN(int **puzzle, int n,int l,int c,int m)
{
	int i=0,p=0,y=0,x=0,v=0;
	
	p=m/2;
	for(i=0;i<m;i++){
		if(puzzle[l][i]==n){
			x++;
		}
	}
	for (i=0;i<m;i++){
		if(puzzle[i][c]==n){
			y++;
		}
	}
	if(x>=p || y>=p){
		v=-1;
	}
	return v;
}

/***************************************************************************************
 * Verifica_paridadeS()
 *
 * Argumentos: **puzzle-tabela
 *			n-número a verificar 0 ou 1
 *			l-linha em que estamos a verificar
 *			c-coluna em que estamos a verificar
 *			m-dimensão da tabela
 * Return: v-sinal que verifica se dá.Se for 1 é obrigatório pôr o número
 * Efeitos Secundários: nenhum
 *
 * Descrição: Verifica se 1 ou 0 têm de estar naquela posição segundo o número de 1
 *e 0 já existentes
 *
 **************************************************************************************/
int Verifica_paridadeS (int **puzzle, int n,int l,int c,int m)
{
	int i=0,p=0,y=0,x=0,v=0;
	
	p=m/2;
	if(n==0){
		for(i=0;i<m;i++){
			if(puzzle[l][i]==1){
				x++;
			}
		}
		for (i=0;i<m;i++){
			if(puzzle[i][c]==1){
				y++;
			}
		}
		if(x==p || y==p){
			v=1;
		}
	}
	if(n==1){
		for(i=0;i<m;i++){
			if(puzzle[l][i]==0){
				x++;
			}
		}
		for (i=0;i<m;i++){
			if(puzzle[i][c]==0){
				y++;
			}
		}
		if(x==p || y==p){
			v=1;
		}
	}
	return v;
}

/***************************************************************************************
 * VerificaNao()
 *
 * Argumentos: n-número a verificar 0 ou 1
 *			l-linha em que estamos a verificar
 *			c-coluna em que estamos a verificar
 *			**puzzle-tabela
 *			max-dimensão da tabela
 * Return: v-sinal que verifica se não dá.Se for -1 não se pode pôr o número
 * Efeitos Secundários: nenhum
 *
 * Descrição: Verifica se 1 ou 0 não podem estar naquela posição
 *
 **************************************************************************************/
int VerificaNao (int n , int l, int c, int **puzzle, int max){

	int v=0;

	if(l>0 && l<max-1 ){
		v=Verifica(n, l , c, puzzle, npode , 0, 1, 0, -1); /*meio coluna*/
	}
	if(v!=-1 && c>0 && c<max-1){
		v=Verifica(n, l, c, puzzle, npode,1,0,-1,0); /*meio linha*/
	}
	if(v!=-1 && l<max-2){
		v=Verifica(n,l,c,puzzle,npode,0,1,0,2); /* 2 acima*/
	}
	if(v!=-1 && l>1){
		v=Verifica(n,l,c,puzzle,npode,0,-1,0,-2); /*2 abaixo*/
	}
	if(v!=-1 && c<max-2){
		v=Verifica(n,l,c,puzzle,npode,1,0,2,0);/*2 direita*/
	}
	if(v!=-1 && c>1){
		v=Verifica(n,l,c,puzzle,npode,-1,0,-2,0);/*2 esquerda*/
	}

	return v;

}

/***************************************************************************************
 * VerificaSim()
 *
 * Argumentos: n-número a verificar 0 ou 1
 *			l-linha em que estamos a verificar
 *			c-coluna em que estamos a verificar
 *			**puzzle-tabela
 *			max-dimensão da tabela
 * Return: v-sinal que verifica se dá.Se for 1 é obrigatório pôr o n se for 0 não o é
 * Efeitos Secundários: nenhum
 *
 * Descrição: Verifica se 1 ou 0 é obrigatório estar naquela posição
 *
 **************************************************************************************/
int VerificaSim(int n, int l, int c, int **puzzle, int max){

	int v=0;

	if(l>0 && l<max-1 ){
		v=Verifica(n, l , c, puzzle, pode , 0, 1, 0, -1); /*meio coluna*/
	}
	if(v!=1 && c>0 && c<max-1){
		v=Verifica(n, l, c, puzzle, pode,1,0,-1,0); /*meio linha*/
	}
	if(v!=1 && l<max-2){
		v=Verifica(n,l,c,puzzle, pode,0,1,0,2); /* 2 acima*/
	}
	if(v!=1 && l>1){
		v=Verifica(n,l,c,puzzle, pode,0,-1,0,-2); /*2 abaixo*/
	}
	if(v!=1 && c<max-2){
		v=Verifica(n,l,c,puzzle, pode,1,0,2,0);/*2 direita*/
	}
	if(v!=1 && c>1){
		v=Verifica(n,l,c,puzzle, pode,-1,0,-2,0);/*2 esquerda*/
	}

	return v;
}

/*Função utilizada para verificar se uma linha do puzzle já está cheia
 Funcção utilizada para verificar se é necessário guardar a linha na tabela de dispersão*/
int Verifica_linha_cheia(int **puzzle,int max,int linha)
{
	int i,n=0;
	for(i=0;i<max;i++){
		if(puzzle[linha][i]!=9){
			n++;
		}
	}
	if(n==max){
		return 1;
	}
	return -1;
}

/*--------------------------------------------------------------------------------------
Função utilizada para verificar se uma linha do puzzle já está cheia
 Utilizada para verificar se é necessário guardar a coluna na tabela de dispersão
 ---------------------------------------------------------------------------------------*/
int Verifica_coluna_cheia(int **puzzle,int max,int coluna)
{
	int i,n=0;
	for(i=0;i<max;i++){
		if(puzzle[i][coluna]!=9){
			n++;
		}
	}
	if(n==max){
		return 1;
	}
	return -1;
}


/*-----------------------------------------------------------------------------------------------------
Função:
		.int SolveByCondition_variante2(int **puzzle, int max,int variante,int **hash,int maxHash)
	Descrição:
		.Função que resolve o puzzle para a restrição 2 
	Argumentos:
		.int **puzzle->puzzle a resolver
		.int **hash->tabela de dispersão que guarda quais linhas já estão preenchidas
		.int variante ->variante do problema( variante=2) 
		.int max-> tamanho do puzzle
		.int maxHash->tamanho da tabela de dispersão
	
-------------------------------------------------------------------------------------------------------*/
int SolveByCondition_variante2(int **puzzle, int max,int variante,int **hash,int maxHash){
	int a , b;
	int v;
	do{	
		v=0;
		for(a=0; a<max;a++){
			for(b=0;b<max;b++){
				if(puzzle[a][b]==9){
					if( (VerificaNao (0,a,b,puzzle, max)==-1 || Verifica_paridadeN(puzzle,0,a,b,max)==-1) && ( VerificaNao(1,a,b,puzzle, max)==-1|| Verifica_paridadeN(puzzle,1,a,b,max)==-1)){
						/*Se não for possível ter um 0 ou 1 na posição desejada devolver que o puzzle é impossível de resolver.
						 Funções chamadas dizem se é impossível devido à existência ou paridade colocar um 1 
						na posição desejada*/
						return -1;
					}		
					
					
					else if(VerificaSim(0, a, b, puzzle, max)==1 ||Verifica_paridadeS(puzzle,0,a,b,max)==1) {
						/*Se for obrigatório colocar  0 numa posição devido às condições de adjacência ou paridade
						 preencher o puzz*/
						puzzle[a][b]=0;
						v=1;
						if(variante==2){/* Verificar se essa linha já está na hash se a linha ficar cheia com o preenchimento*/
							
							if(Verifica_linha_cheia(puzzle,max,a)==1){
								v=Procura_linear(hash,max,Converte_decimal_linha(puzzle,a,max),0,maxHash);
								/*Se essa linha estiver presente na hash devolver que o puzzle é impossível.*/
								if(v==-1){
									puzzle[a][b]=9;
									return -1;
								}
							}
							
							if(Verifica_coluna_cheia(puzzle,max,b)==1 && v!=-1){
								
								v=Procura_linear(hash,max,Converte_decimal_coluna(puzzle,b,max),1,maxHash);
								if(v==-1){
									puzzle[a][b]=9;
									return -1;
								}
							}
							
						}
					}
					else if(VerificaSim(1, a, b, puzzle, max)==1||Verifica_paridadeS(puzzle,1,a,b,max)==1 ){
						puzzle[a][b]=1;
						v=1;
						if(variante==2){
							
							if(Verifica_linha_cheia(puzzle,max,a)==1){
								v=Procura_linear(hash,max,Converte_decimal_linha(puzzle,a,max),0,maxHash);
								if(v==-1){
									puzzle[a][b]=9;
									return -1;
								}
								
							}
						
							if(Verifica_coluna_cheia(puzzle,max,b)==1 && v!=-1){
								v=Procura_linear(hash,max,Converte_decimal_coluna(puzzle,b,max),1,maxHash);
								if(v==-1){
									puzzle[a][b]=9;
									return -1;
								}
								
							}
						}
						
					}
								
				}
			}
		}
	}while(v==1);/* Se tiverem ocorrido mudanças na tabela continuar a tentar preencher, dado que essas mudanças podem implicar 
	outras que ainda não tenham sido verificadas*/
	
	return v;	
}

/*.Verifica se o puzzle já foi totalmente preenchido*/
int VerificaCompleto(int **puzzle,int max)
{
	int i,j;
	
	for(i=0;i<max;i++){
		for(j=0;j<max;j++){
			if(puzzle[i][j]==9){
				return 0;
				
			}
		}
	}
	
	return 1;
}

/*.Liberta a memória alocada para o puzzle
  .m->tamanho do puzzle
  */
void FreePuzzle (int **puzzle, int m)
{
	int i;

	for (i=0; i< m;i++)
  	{
  		free(puzzle[i]);
  	}
  	free(puzzle);
  	
  	return;
}

/*Liberta a memória alocada para a tabela de dispersão
  .maxHash->uma das dimensões da tabela de dispersão
  .tabela de dispersão tem dimensão maxHash*2
*/
void FreeHash(int **hash,int maxHash)
{
	int i;
	for (i=0; i< maxHash;i++)
  	{
  		free(hash[i]);
  	}
  	free(hash);
	return;
}

/*------Função que preenche o puzzle de acordo com a variante 1----------*/
int SolveByCondition_variante1(int **puzzle, int max)
{
	int a , b;
	int v;/*ariável que indica que ocorreram mudanças na tabela*/
	do{	
		v=0;
		for(a=0; a<max;a++){
			for(b=0;b<max;b++){
				if(puzzle[a][b]==9){
					if( (VerificaNao (0,a,b,puzzle, max)==-1 || Verifica_paridadeN(puzzle,0,a,b,max)==-1) && ( VerificaNao(1,a,b,puzzle, max)==-1|| Verifica_paridadeN(puzzle,1,a,b,max)==-1)){
						/* Se não se puder colocar nem um 0 nem um 1 o puzzle é impossível*/
						return -1;
					}		
					
					
					else if(VerificaSim(0, a, b, puzzle, max)==1 ||Verifica_paridadeS(puzzle,0,a,b,max)==1) {
						/*Se for obrigatório estar na posição um 0 devido à paridade ou adjacência colocar no puzzle 0*/
						puzzle[a][b]=0;
						v=1;
						
							
					}
					else if(VerificaSim(1, a, b, puzzle, max)==1||Verifica_paridadeS(puzzle,1,a,b,max)==1 ){
						/*Se for obrigatório estar na posição um 1 devido à paridade ou adjacência colocar no puzzle 1*/
						puzzle[a][b]=1;
						v=1;
						
						
					}
								
				}
			}
		}
	}while(v==1);/* Se tiverem ocorrido mudanças na tabela continuar a tentar preencher, 
	dado que essas mudanças podem implicar outras que ainda não tenham sido verificadas*/
	
	return v;	
}
