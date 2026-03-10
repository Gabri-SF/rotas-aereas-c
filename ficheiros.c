#include "ficheiros.h"

int testa_abertura_dos_ficheiros(FILE* fp1, FILE* fp2){
    if (fp1 == NULL) {
        fprintf(stderr, "\nErro ao abrir o ficheiro aeroportos.txt.\n");
        return 1;
    }
    if (fp2 == NULL) {
        fprintf(stderr, "\nErro ao abrir o ficheiro rotas.txt.\n");
        return 1;
    }
    return 0;
}

AEROPORTO le_dados_aeroportos(FILE* fp, int* nconv) {
    AEROPORTO aer;
  	char linha[DIM] = {0};
  	char erro[DIM] = {0}; 
  	
    do {
        if (fgets(linha, DIM, fp) == NULL)
            break; 
    } while (linha[0] == '\0' || linha[0] == '\n');    
    	
   	*nconv = sscanf(linha, "%s %s %d %d %d %c %d %d %d %c %s %d %s",
    aer.ICAO, aer.IATA, &aer.lat_deg, &aer.lat_min, &aer.lat_seg,
    &aer.lat_dir, &aer.lon_deg, &aer.lon_min, &aer.lon_seg, &aer.lon_dir, 
    aer.CIDADE, &aer.tz, erro);

    return aer;
}

ROTA le_dados_rotas(FILE* fp, int* nconv) {
    ROTA rota;
    char linha[DIM] = {0};
    char erro[DIM] = {0}; 
    
    do {
        if (fgets(linha, DIM, fp) == NULL)
            break; 
    } while (strncmp(linha, "AIRLINE:", 8) == 0 || linha[0] == '\n');

    if ((*linha != '\0') && (*linha !='\n')) {
        *nconv = sscanf(linha, "%s %s %d:%d %s %d:%d %s", rota.codigo, rota.IATA_p, &(rota.hora_p),
                    &(rota.min_p), rota.IATA_c, &(rota.hora_c), &(rota.min_c), erro);
    }
    return rota;
}

int validar_aeroporto(AEROPORTO *aeroporto) {
    if (strlen(aeroporto->ICAO) != 4 || strlen(aeroporto->IATA) != 3) return 0;
    if (aeroporto->lat_deg < 0 || aeroporto->lat_deg > 90 || aeroporto->lon_deg < 0 || aeroporto->lon_deg > 180) return 0;
    if (aeroporto->lat_min < 0 || aeroporto->lat_min >= 60 || aeroporto->lat_seg < 0 || aeroporto->lat_seg >= 60 ||
        aeroporto->lon_min < 0 || aeroporto->lon_min >= 60 || aeroporto->lon_seg < 0 || aeroporto->lon_seg >= 60) return 0;
    if (aeroporto->lat_dir != 'N' && aeroporto->lat_dir != 'S' && aeroporto->lat_dir != 'E' && aeroporto->lat_dir != 'W') return 0;
    if (aeroporto->lon_dir != 'N' && aeroporto->lon_dir != 'S' && aeroporto->lon_dir != 'E' && aeroporto->lon_dir != 'W') return 0;
    if (aeroporto->tz < -12 || aeroporto->tz > 14) return 0;

    return 1;
}

int validar_rota(ROTA *rota) {
    if (strlen(rota->codigo) == 0 || strlen(rota->IATA_p) != 3 || strlen(rota->IATA_c) != 3) return 0;
    if (rota->hora_p < 0 || rota->hora_p > 23 || rota->min_p < 0 || rota->min_p > 59 ||
        rota->hora_c < 0 || rota->hora_c > 23 || rota->min_c < 0 || rota->min_c > 59) return 0;

    return 1;
}