#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int main(){
	srand(time(NULL));
	double Tempo = 0 , menorTempo, tempoTotal, estadia ; // verificador de tempo
	int i, pos=0, ver_E;
	int verMaq = 0; // verificador para ver se tem maquina para ser liberada.
	double vetProdutos[3] = {chegadaPedido(21.5), chegadaPedido(19.1), chegadaPedido(8.0)}; //chegada dos 3 pedidos de tempo random
	
	double tempoSaida[4] = {-1,-1,-1,-1}; // tempo das maquinas finalizar o estagio do rolamento [Torno,Torno,Fresa,Mandril]
	
	int *score = malloc(sizeof(int)*4);
	double *rolamentoTempoProcesso = malloc(sizeof(double)*4);

	// contador de produtos feitos [conico,cilindrico,aco,titanico]
	for(i=0;i<4;i++){
		score[i] = 0;
		rolamentoTempoProcesso[i] = 0;
	}
	
	// tempo total de processamento para cada rolamento [conico,cilindrico,aco,titanio]

	machine *processTorno1 = cria_machine(), *processTorno2 = cria_machine(), *processFresa = cria_machine(), *processMandril = cria_machine();
	
	rolamento *rolamentoAux;
	
	Fila *filaTorno = criafila(), *filaFresa = criafila(), *filaMandril = criafila();
	
	printf("O tempo desejado de funcionamento? \n");
	scanf("%lf", &tempoTotal);


	while (Tempo <= tempoTotal) {

		menorTempo = vetProdutos[0];
		pos = 0;
		verMaq = 0;

		//verifica menor tempo para pegar o primeiro pedido
		for(i=0; i<3; i++){ //verificando o menor
			if(menorTempo > vetProdutos[i]){
				menorTempo = vetProdutos[i];
				pos = i;
				verMaq = 0;
			}
		}
		
		for (i=0;i<4;i++){ //verificando se alguma maquina vai liberar mais cedo do que criar um novo rolamento
			if(tempoSaida[i] != -1){
				if(menorTempo > tempoSaida[i]){ // verificando o menor tempo caso seja uma maquina querendo liberar
					menorTempo = tempoSaida[i];
					pos = i;
					verMaq = 1;
				}
			}
		}
		
		// criando rolamentos.
		if (verMaq == 0){ // se nenhuma maquina liberou um produto.

			if(pos == 0){
				rolamentoAux = cria_rolamento_conico(menorTempo);
				insere_fila(filaTorno,rolamentoAux); // insere na fila torno 2
				vetProdutos[0] = menorTempo + chegadaPedido(21.5);
			}
			if(pos == 1){
				rolamentoAux = cria_rolamento_cilindrico(menorTempo);
				insere_fila(filaTorno,rolamentoAux); // insere na fila torno
				vetProdutos[1] = menorTempo + chegadaPedido(19.1);
			}
			if(pos == 2){
				ver_E = esferico_verifica(); //verifica qual o esferico
				if(ver_E == 0){
					rolamentoAux = cria_rolamento_aco(menorTempo);
				}
		        if(ver_E == 1){
					rolamentoAux = cria_rolamento_titanico(menorTempo);
				}
				insere_fila(filaFresa,rolamentoAux);
				vetProdutos[2] = menorTempo + chegadaPedido(8.0);
			}

		}else{ // se tiver maquina para liberar em vez de criar rolamento
			if(pos == 0){ // maquina Torno 1 acabou o processamento
				processTorno1->tempo = -1;
				tempoSaida[0] = -1; // indicador de maquina vazia
				rolamentoAux = processTorno1->rolamento; // auxiliar segura o ponteiro do rolamento que estava na maquina				
			}
			if(pos == 1){ // maquina Torno 2 acabou o processamento
				processTorno2->tempo = -1;
				tempoSaida[1] = -1; // indicador de maquina vazia
				rolamentoAux = processTorno2->rolamento; // auxiliar segura o ponteiro do rolamento atual			
			}
			if(pos == 2){ // maquina Fresa acabou o processamento
				processFresa->tempo = -1;
				tempoSaida[2] = -1; // indicador de maquina vazia
			}
			if(pos == 3){ // maquina Mandril acabou o processamento
				processMandril->tempo = -1;
				tempoSaida[3] = -1; // indicador de maquina vazia
			}
			rolamentoAux->pos = rolamentoAux->pos + 1; // andando para proxima maquina.
			if (verifica_prox_maquina(rolamentoAux) == 1){ //se a proxima posição for Torno, joga na fila
				insere_fila(filaTorno,rolamentoAux); // insere na fila torno
			}else{
				if  (verifica_prox_maquina(rolamentoAux) == 2){  // se a proxima posição for Fresa, joga na fila
					insere_fila(filaFresa,rolamentoAux);
				}else{
					if (verifica_prox_maquina(rolamentoAux) == 3){ // se a proxima posição for Mandril, joga na fila
						insere_fila(filaMandril,rolamentoAux);
					}else{	// significa que chegou no fim e o rolamento foi feito.
						if(verifica_prox_maquina(rolamentoAux) == 4){  // acho q não precisava pq é oq sobra.
							score = rolamento_construido(rolamentoAux->nome,score); // incrementa o placar para marcar qnts foram feitos
							rolamentoAux->tempoSaida = menorTempo;
							rolamentoTempoProcesso = rolamento_processo(rolamentoAux,rolamentoTempoProcesso); // incrementa o placar com o tempo de processo do rolamento
						}
					}
				}
			}
		}
		if(tempoSaida[0] == -1){ // Se a maquina Torno1 tiver livre.
			if(filaTorno->tam != 0){
				rolamentoAux = obter_fila(filaTorno);
				processTorno1->rolamento = rolamentoAux;
				estadia = verifica_estadia(rolamentoAux);
				processTorno1->tempo = menorTempo + tempoMaquina(estadia); // tempo maquina vai gerar o tempo de processo
				tempoSaida[0] = processTorno1->tempo;
			}
		}
		if(tempoSaida[1] == -1){ // Se a maquina Torno2 tiver livre.
			if(filaTorno->tam != 0){
				rolamentoAux = obter_fila(filaTorno);
				processTorno2->rolamento = rolamentoAux;
				estadia = verifica_estadia(rolamentoAux);
				processTorno2->tempo = menorTempo + tempoMaquina(estadia); // tempo maquina vai gerar o tempo de processo
				tempoSaida[1] = processTorno2->tempo;
			}
		}
		if(tempoSaida[2] == -1){ // Se a maquina Fresa tiver livre.
			if(filaFresa->tam != 0){
				rolamentoAux = obter_fila(filaFresa);
				processFresa->rolamento = rolamentoAux;
				estadia = verifica_estadia(rolamentoAux);
				processFresa->tempo = menorTempo + tempoMaquina(estadia); // tempo maquina vai gerar o tempo de processo
				tempoSaida[2] = processFresa->tempo;
			}
		}
		if(tempoSaida[3] == -1){ // Se a maquina Mandril tiver livre.
			if(filaMandril->tam != 0){
				rolamentoAux = obter_fila(filaMandril);
				processMandril->rolamento = rolamentoAux;
				estadia = verifica_estadia(rolamentoAux);
				processMandril->tempo = menorTempo + tempoMaquina(estadia); // tempo maquina vai gerar o tempo de processo
				tempoSaida[3] = processMandril->tempo;
			}
		}
		
		Tempo = menorTempo;	// tempo RECEBE o tempo que foi usado.
		// explicação: O tempo é incrementado na chegada junto com o random da chegada
		// mesma coisa para saida do produto (saida definida na entrada da maquina)

	}

	printf("Quantidade de rolamentos construidos: \n Conico: %d \n Cilindrico: %d \n Aco: %d \n Titanio: %d \n \n ", score[0], score[1], score[2], score[3]);

	printf("Tempo total de processamento: \n Conico: %lf \n Cilindrico: %lf \n Aco: %lf \n Titanio: %lf \n \n",rolamentoTempoProcesso[0],rolamentoTempoProcesso[1],rolamentoTempoProcesso[2],rolamentoTempoProcesso[3]);

	printf("Tempo medio de cada rolamento: \n Conico: %lf \n Cilindrico: %lf \n Aco: %lf \n Titanio: %lf \n \n", rolamentoTempoProcesso[0]/score[0],rolamentoTempoProcesso[1]/score[1],rolamentoTempoProcesso[2]/score[2],rolamentoTempoProcesso[3]/score[3]);

	destruirFila(filaTorno);
	destruirFila(filaMandril);
	destruirFila(filaFresa);
	free(processTorno1);
	free(processTorno2);
	free(processMandril);
	free(processFresa);
	return 0;
}