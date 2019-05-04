
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/* -----------------------------------------------------------------------------------------------------------------
	struct_Node 
Estrutura de um nó da árvore que tem associadas:
	.uma tabela(puzzle)
	.uma tabela de dispersão
	.um ponteiro para a solução em que se coloca 1 numa posição da tabela devido a uma suposição (*one) 
	.um ponteiro para a soução em que se coloca 0 numa posição da tabela devido a uma suposição(*zero)
   É essencial ter associadas ambas estas estruturas dado que se se quiser voltar para o nó anterior da àrvore
 dado que já se visitaram os nós seguintes temos de ter um "backup" de como estava o puzzle antes de termos começado
 a fazer suposições.
 --------------------------------------------------------------------------------------------------------------------*/ 
struct _Node{

	int **tabela;
	int **hash;
	struct _Node *zero,*one;
};


/*----------------------------------------------
Função que aloca memória para um nó da árvore 
-----------------------------------------------*/
Node *AllocNode() {
  return ((Node *) malloc(sizeof(Node)));
}
		/*----------------------------Funções utilizadas para  a Variante 2 -------------------*/
/*---------------------------------------------------------------------------------------------
	Função que aloca memória para um nó da árvore através da função AllocNode e aloca memória 
para o puzzle(tabela) e tabela de dispersão hash do nó alocado.
	Função utilizada para a variante 2 dado que é nessa variante que é necessário alocar memória 
para a tabela de dispersão. 

Argumentos: max->tamanho do puzzle       maxHash->tamanho da tabela de dispersão
Valor de Retorno: ponteiro para o nó alocado
-------------------------------------------------------------------------------------------------*/
Node *NewNode_variante2(int max,int maxHash)
{
	Node *aux;
	int i=0,j=0;
	aux = AllocNode();
	aux->tabela=(int**) malloc(sizeof(int*)*max);
	if(aux->tabela==NULL)
	{
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
    		exit ( 0 );
	}
	for(i=0 ; i<max ;i++)
	{
		aux->tabela[i]=(int*) malloc(sizeof(int)*max);
		if ( aux->tabela[i] == NULL ) {
      		fprintf ( stderr, "ERROR: not enough memory available!\n" );
      		exit ( 0 );
      	}
	}
	aux->hash=(int**) malloc(sizeof(int*)*maxHash);
	if(aux->hash==NULL)
	{
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
    		exit ( 0 );
	}
	for(i=0;i<maxHash;i++){
		aux->hash[i]=(int*) malloc(sizeof(int)*2);
		if ( aux->hash[i] == NULL ) {
      		fprintf ( stderr, "ERROR: not enough memory available!\n" );
      		exit ( 0 );
      	}
	}
	for(i=0;i<maxHash;i++){
		for(j=0;j<2;j++){
			aux->hash[i][j]=0;
		}
	}
	aux->zero = aux->one = NULL;
    
	return aux;
}
/* ---------------------------------------------------------------------------------
	Função que liberta um nó para a variante 2. É necessário libertar o puzzle do nó,
a tabela de dispersão e, por fim a memória do próprio nó.
	Argumentos:
	.NodeRoot->ponteiro para o nó a libertar
	.max->tamaho do puzzle
	.maxHash->tamanho da tabela de dispersão
-------------------------------------------------------------------------------------*/

void FreeNodeRoot_variante2(Node *NodeRoot,int max,int maxHash)
{
	int i=0;
	
	for (i=0; i< max;i++)
  	{
  		free(NodeRoot->tabela[i]);
  	}
  	free(NodeRoot->tabela);
  	
  	for (i=0; i< maxHash;i++)
  	{
  		free(NodeRoot->hash[i]);
  	}
  	free(NodeRoot->hash);
  	free(NodeRoot);
  	
  	return;
}
/*--------------------------------------------------------------------------------------
Descrição:Função recursiva para resolver o puzzle para a variante 2.
			No início da função é alocada memória para um novo nó e resolve-se o puzzle do nó anterior com SolveByCondition:
				.Se o puzzle estiver resolvido retornar ou for impossível de resolver retornar para o nó anterior
				.Se o puzzle não estiver resolvido co+iar o puzzle para o puzzle do nó
				e resolver colocando um 1 numa posição onde tenha nove, chamando de novo a função
				.Se não estiver resolvido colocando 1,libertar memória do nóone e resolver colocando 0 
	Argumentos:
	.puzzle->puzzle associado ao nó
	.max->tamanho do puzzle
	.hash->tabela de dispersão associada ao nó anterior
	.maxHash->tamaho da tabela de dispersão
	.variante->restrição usada, neste caso variante passada será igual a 2
---------------------------------------------------------------------------------------
*/
Node *ResolvePuzzle_variante2 (int **puzzle,int max,int variante,int **hash,int maxHash){
	
	Node *NodeRoot;
	int v;
	int i,j,a,b,f=0;
	
	NodeRoot=NewNode_variante2(max,maxHash);
	
	v=SolveByCondition_variante2(puzzle,max,variante,hash,maxHash);
		
	if(v==0 && VerificaCompleto(puzzle,max)!=1){	
		for(a=0;a<max;a++){
			for(b=0;b<max;b++){
				
				NodeRoot->tabela[a][b]=puzzle[a][b];
			}
		}
		for(a=0;a<maxHash;a++){
			for(b=0;b<2;b++){
			
				NodeRoot->hash[a][b]=hash[a][b];
			}
		}		
		for(i=0;i<max;i++){
			for(j=0;j<max;j++){
				if(puzzle[i][j]==9){
					f=1;
					puzzle[i][j]=1;
					NodeRoot->one=ResolvePuzzle_variante2(puzzle, max,variante,hash,maxHash);
					FreeNodeRoot_variante2(NodeRoot->one,max,maxHash);
					
					if(VerificaCompleto(puzzle,max)!=1){
						for(a=0;a<max;a++){
							for(b=0;b<max;b++){			
								puzzle[a][b]=NodeRoot->tabela[a][b];
							}
						}
						for(a=0;a<maxHash;a++){
							for(b=0;b<2;b++){
			
								hash[a][b]=NodeRoot->hash[a][b];
							}
						}	
						puzzle[i][j]=0;
						NodeRoot->zero=ResolvePuzzle_variante2(puzzle ,max,variante,hash,maxHash);
						FreeNodeRoot_variante2(NodeRoot->zero,max,maxHash);								
							
					}
					
					
					break;
				}
			}
			if(f==1){
				break;
			}
		}
	}
	
	return NodeRoot;
}


                  /*----------------Funções utilizadas para a variante 1-------------------------*/
/*-----------------------------------------------------------------------------------------
Descrição: Função que aloca memória para um nó e para o respetivo puzzle; não é necessário 
alocar memória para a tabela de dispersão dado que a mesma não é utilizada 
Árgumentos: max->tamanho do puzz do nó
------------------------------------------------------------------------------------------*/

Node *NewNode_variante1(int max)
{
	Node *aux;
	int i=0;
	aux = AllocNode();/*Alocar memória para o nó*/
	aux->tabela=(int**) malloc(sizeof(int*)*max);
	if(aux->tabela==NULL)
	{
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
    		exit ( 0 );
	}
	for(i=0 ; i<max ;i++)
	{
		aux->tabela[i]=(int*) malloc(sizeof(int)*max);
		if ( aux->tabela[i] == NULL ) {
      		fprintf ( stderr, "ERROR: not enough memory available!\n" );
      		exit ( 0 );
      	}
	}
	
	aux->zero = aux->one = NULL;
    
	return aux;
}

/*-----------------------------------------------------------------------------------------
Descrição: Função que liberta um nó para a variante 1;apenas é necessário  libertar memória
do puzzle e do próprio nó ,dado que a tabela de dispersão não é alocada

Argumentos: NodeRoot->ponteiro para o nó a libertar     max->tamanho do puzzle do nó
-------------------------------------------------------------------------------------------
*/     
void FreeNodeRoot_variante1(Node *NodeRoot,int max)
{
	int i=0;
	/*Liertar a tabela*/
	for (i=0; i< max;i++)
  	{
  		free(NodeRoot->tabela[i]);
  	}
  	free(NodeRoot->tabela);
  	
  	/*Libertar o nó*/
  	free(NodeRoot);
  	
  	return;
}

/*-------------------------------------------------------------------------------------------------
	Descrição: A mesma que ResolvePuzzle_variante_2, mas em vez de utilizar SolveByCondition_variante2
usa SolveByCondition_variante1
---------------------------------------------------------------------------------------------------*/
Node *ResolvePuzzle_variante1 (int **puzzle,int max)
{
	
	Node *NodeRoot;
	int v;
	int i,j,a,b,f=0;
	
	NodeRoot=NewNode_variante1(max);
	
	v=SolveByCondition_variante1(puzzle,max);
		
	if(v==0 && VerificaCompleto(puzzle,max)!=1){	
		for(a=0;a<max;a++){
			for(b=0;b<max;b++){
				
				NodeRoot->tabela[a][b]=puzzle[a][b];
			}
		}
				
		for(i=0;i<max;i++){
			for(j=0;j<max;j++){
				if(puzzle[i][j]==9){
					f=1;
					puzzle[i][j]=1;
					NodeRoot->one=ResolvePuzzle_variante1 (puzzle, max);
					FreeNodeRoot_variante1(NodeRoot->one,max);
					
					if(VerificaCompleto(puzzle,max)!=1){
						for(a=0;a<max;a++){
							for(b=0;b<max;b++){			
								puzzle[a][b]=NodeRoot->tabela[a][b];
							}
						}
							
						puzzle[i][j]=0;
						NodeRoot->zero=ResolvePuzzle_variante1 (puzzle ,max);
						FreeNodeRoot_variante1(NodeRoot->zero,max);								
							
					}
					
					
					break;
				}
			}
			if(f==1){
				break;
			}
		}
	}
	
	return NodeRoot;
}





