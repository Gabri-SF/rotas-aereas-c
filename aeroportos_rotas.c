#include "aeroportos_rotas.h"

void insere_na_lista_aeroportos(LISTA **topo, AEROPORTO aer, int escreve) {
    LISTA *aux = *topo;
    LISTA *novo;

    while (aux != NULL) {
        if (strcmp(aux->aer.ICAO, aer.ICAO) == 0 || strcmp(aux->aer.IATA, aer.IATA) == 0) {
        	if(escreve){ 
            	printf("Aeroporto com ICAO ou IATA duplicado encontrado. Não inserido na lista:\n");
            	printf("%s %s %d %d %d %c %d %d %d %c %s %d\n\n", aer.ICAO, aer.IATA, 
					aer.lat_deg, aer.lat_min, aer.lat_seg, aer.lat_dir, aer.lon_deg,
					aer.lon_min, aer.lon_seg, aer.lon_dir, aer.CIDADE, aer.tz);
			}
		return;
        }
        aux = aux->prox;   
     }

    novo = (LISTA*) calloc(1, sizeof(LISTA));
    if (novo != NULL) {
        novo->aer = aer;
        novo->prox = NULL;
        if (*topo == NULL)
            *topo = novo;
        else {
            aux = *topo;
            while (aux->prox)
                aux = aux->prox;
            aux->prox = novo;
        }
    } else {
        printf("Erro -- calloc -- insere_na_lista_aeroportos!\n");
    }
}

void imprime_lista_aeroportos (LISTA* topo){
	printf("\nLista de Aeroportos: \n");
	while (topo != NULL){
		printf("%s %s %d %d %d %c %d %d %d %c %s %d\n", topo->aer.ICAO, topo->aer.IATA, 
		topo->aer.lat_deg, topo->aer.lat_min, topo->aer.lat_seg, topo->aer.lat_dir, topo->aer.lon_deg,
		topo->aer.lon_min, topo->aer.lon_seg, topo->aer.lon_dir, topo->aer.CIDADE, topo->aer.tz);
		topo = topo->prox;
		}
}