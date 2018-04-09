#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

no *criaNo(rolamento *p, int prior){
	no *N = malloc(sizeof(no));
	N->rolamento = p;
	N->prox = N->ant = NULL;
	N->prior = prior;
	return N;
}


Fila *criafila(){
	Fila *Fila;
	Fila = malloc(sizeof(Fila));
	Fila->ini = Fila->fim = NULL;
	Fila->tam = 0;
	return Fila;
}

rolamento *obter_fila(Fila *Fil){
	no *k = Fil->ini;
	rolamento *rola = k->rolamento;
	Fil->ini = Fil->ini->prox;
	Fil->tam--;
	return rola;
}


void imprimeFila(Fila *Fila){
	int i=0;
	no *N = Fila->ini;
	//printf("Fila Tamanho: %d \n", Fila->tam);
	while (N!=NULL && i< Fila->tam){
		printf("Impressora rolamento:%s\n", N->rolamento->nome);
		printf("Impressora Tempo:%lf\n", N->rolamento->tempo);
		N = N->prox;
		i++;
	}
	
}


void insere_fila(Fila *fila, rolamento *rola){
	double tempon = rola->tempo;
	no *N = criaNo(rola,rola->prioridade);
	N->rolamento->tempo = tempon;
	
	if(fila->ini == NULL) {		//se nao tiver nenhum na fila
		fila->ini = fila->fim = N;
	}else{ 
		if(fila->ini->prior < rola->prioridade) { //se tiver maior prioridade
			N->prox = fila->ini;
			fila->ini = N;
		}else{
			if(fila->fim->prior >= rola->prioridade) { //se tiver menor prioridade
				fila->fim->prox = N;
				fila->fim = N;
			}else {
				no *k = fila->ini;			//se tiver com prioridade no meio
				while(k->prox->prior >= rola->prioridade) {
					k = k->prox;
				}
				N->prox = k->prox;
				k->prox = N;
			}
		}
	}
	fila->tam++;
}

void destruirFila(Fila *Fila){
	no *k, *N = Fila->ini;
	while(N != NULL){
		k = N->prox;
		free(N);
		N = k;
	}
	Fila->tam = 0;
	Fila->ini = Fila->fim = NULL;
}


