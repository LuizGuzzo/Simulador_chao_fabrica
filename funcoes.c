#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

machine *cria_machine(){
	machine *maq = malloc(sizeof(machine));
	maq->rolamento = NULL;
	maq->tempo = 0;
	return maq;
}

rolamento *cria_rolamento_conico(double tempo){ 
	rolamento *rolamento = malloc(sizeof(rolamento));
	rolamento->nome = "conico"; //ctz q isso vai dar merda. Tem q ser seta
	rolamento->pos = 0;
	rolamento->tempo = tempo;
	rolamento->prioridade = 1;

	return rolamento;
}

rolamento *cria_rolamento_cilindrico(double tempo){ 
	rolamento *rolamento = malloc(sizeof(rolamento));
	rolamento->nome = "cilindrico" ;
	rolamento->pos = 0;
	rolamento->tempo = tempo;
	rolamento->prioridade = 2;

	return rolamento;
}
rolamento *cria_rolamento_aco(double tempo){ 
	rolamento *rolamento = malloc(sizeof(rolamento));
	rolamento->nome = "aco" ;
	rolamento->pos = 0;
	rolamento->tempo = tempo;
	rolamento->prioridade = 1;

	return rolamento;
}

rolamento *cria_rolamento_titanico(double tempo){ 
	rolamento *rolamento = malloc(sizeof(rolamento));
	rolamento->nome = "titanico" ;
	rolamento->pos = 0;
	rolamento->tempo = tempo;
	rolamento->prioridade = 1;

	return rolamento;
}
int esferico_verifica(){
	int v;
	v = (rand()%100);
	if(v <= 10){
		return 1;
	}else{
		return 0;
	}
}

double chegadaPedido(double param){
double u=0;

do {
	u = (double) (rand()%RAND_MAX) / RAND_MAX; 
} while ((u==0) || (u==1));
return (double) (-param * log (u));
}


double tempoMaquina(double estadia){
	return 2.0 * estadia * rand() / (RAND_MAX + 1.0);
} 

int *rolamento_construido(char *nome_rolamento, int *score){ //recebe o placar de produtos feitos e incrementa o que acabou.
	int num;
	if(strcmp(nome_rolamento,"conico") == 0){
		num = score[0];
		num++;
		score[0]=num;
	}
	if(strcmp(nome_rolamento,"cilindrico") == 0){
		num = score[1];
		num++;
		score[1]=num;
	}
	if(strcmp(nome_rolamento,"aco") == 0){
		num = score[2];
		num++;
		score[2]=num;
	}
	if(strcmp(nome_rolamento,"titanico") == 0){
		num = score[3];
		num++;
		score[3]=num;
	}
	return score;
}

double *rolamento_processo(rolamento *rola, double *placar){ //recebe o placar de produtos feitos e incrementa o que acabou.
	
	if(strcmp(rola->nome,"conico") == 0){
		placar[0] = placar[0] + (rola->tempoSaida - rola->tempo);
	}
	if(strcmp(rola->nome,"cilindrico") == 0){
		placar[1] = placar[1] + (rola->tempoSaida - rola->tempo);
	}
	if(strcmp(rola->nome,"aco") == 0){
		placar[2] = placar[2] + (rola->tempoSaida - rola->tempo);
	}
	if(strcmp(rola->nome,"titanico") == 0){
		placar[3] = placar[3] + (rola->tempoSaida - rola->tempo);
	}
	return placar;
}

double verifica_estadia(rolamento *rola){
	double estadia;
	if(strcmp(rola->nome,"conico") == 0){
		double vet_conico[4] = {1.8,2.1,1.8,0};
		estadia = vet_conico[rola->pos];
	}
	if(strcmp(rola->nome,"cilindrico") == 0){
		double vet_cilin[5] = {0.8,0.5,0.8,1.2,0};
		estadia = vet_cilin[rola->pos];
	}
	if(strcmp(rola->nome,"aco") == 0){
		double vet_aco[4] = {0.5,1.4,1.0,0};
		estadia = vet_aco[rola->pos];
	}
	if(strcmp(rola->nome,"titanico") == 0){
		double vet_titanico[6] = {0.6,1.5,1.6,0.6,1.6,0};		
		estadia = vet_titanico[rola->pos];
	}
	return estadia;
}

int verifica_prox_maquina(rolamento *rola){
	int maquina;
	// 1 - TORNO
	// 2 - FRESA
	// 3 - MANDRIL
	// 4 - END
	if(strcmp(rola->nome,"conico") == 0){
		int vet_conico[4] = {1,3,1,4};
		maquina = vet_conico[rola->pos];
	}
	if(strcmp(rola->nome,"cilindrico") == 0){
		int vet_cilin[5] = {1,2,1,3,4};
		maquina = vet_cilin[rola->pos];
	}
	if(strcmp(rola->nome,"aco") == 0){
		int vet_aco[4] = {2,3,1,4};
		maquina = vet_aco[rola->pos];
	}
	if(strcmp(rola->nome,"titanico") == 0){
		int vet_titanico[6] = {2,3,1,2,1,4};	
		maquina = vet_titanico[rola->pos];
	}
	return maquina;
}