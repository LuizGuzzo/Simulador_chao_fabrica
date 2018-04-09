#ifndef __biblio_h_
#define __biblio_h_
typedef struct rolamento {
	char *nome;
	int prioridade;
	int pos;
	double tempo;
	double tempoSaida;
} rolamento;

typedef struct no {

	struct no *prox, *ant;
	rolamento *rolamento;
	int prior;

} no;


typedef struct Fila {

	no *ini, *fim;
	int tam;

}Fila;

typedef struct machine{
	rolamento *rolamento;
	double tempo;
}machine;
	
no *criaNo(rolamento *p, int prior);
Fila *criafila();
rolamento *obter_fila(Fila *Fil);
void imprimeFila(Fila *Fila);
void insere_fila(Fila *fila, rolamento *rola);
void destruirFila(Fila *Fila);
machine *cria_machine();
rolamento *cria_rolamento_conico(double tempo);
rolamento *cria_rolamento_cilindrico(double tempo);
rolamento *cria_rolamento_aco(double tempo);
rolamento *cria_rolamento_titanico(double tempo);
double chegadaPedido(double param);
double tempoMaquina(double estadia);
int *rolamento_construido(char *nome_rolamento, int *score);
double *rolamento_processo(rolamento *rola, double *placar);
int esferico_verifica();
double verifica_estadia(rolamento *rola);
int verifica_prox_maquina(rolamento *rola);
#endif