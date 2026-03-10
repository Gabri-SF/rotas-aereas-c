#include "matematica.h"

double converte_graus_rad (double a){
	a = a * PI / 180.0;
	return a;
}

double calcula_x (double lat, double lon){
	lat = cos(lat)*cos(lon);
	return lat;
}

double calcula_y (double lat, double lon){
	lat = cos(lat)*sin(lon);
	return lat;
}

double calcula_norma(double x, double y, double z){
	x = sqrt(x*x + y*y + z*z);
	return x;
}

double calcula_distancia_aeroportos (AEROPORTO a1, AEROPORTO a2){
	double R = 6381, pi = 0;
	double lat1 = 0, lon1 = 0;
	double lat2 = 0, lon2 = 0;
	double x1=0, y1=0, z1=0;
	double x2=0, y2=0, z2=0;
	double norma1=0, norma2=0;
	double alpha = 0, dist = 0;
	
	lat1 = a1.lat_deg + a1.lat_min / 60.0 + a1.lat_seg / 3600.0;
	lon1 = a1.lon_deg + a1.lon_min / 60.0 + a1.lon_seg / 3600.0;
	
	lat2 = a2.lat_deg + a2.lat_min / 60.0 + a2.lat_seg / 3600.0;
	lon2 = a2.lon_deg + a2.lon_min / 60.0 + a2.lon_seg / 3600.0;

	if (a1.lat_dir == 'S') lat1 = -lat1; 
	if (a2.lat_dir == 'S') lat2 = -lat2;
	if (a1.lon_dir == 'W') lon1 = -lon1; 
	if (a2.lon_dir == 'W') lon2 = -lon2;
	
	lat1 = converte_graus_rad (lat1);
	lon1 = converte_graus_rad (lon1);
	lat2 = converte_graus_rad (lat2);
	lon2 = converte_graus_rad (lon2);
	
	x1 = R * calcula_x(lat1, lon1);
	y1 = R * calcula_y(lat1, lon1);
	z1 = R * sin(lat1);
	x2 = R * calcula_x(lat2, lon2);
	y2 = R * calcula_y(lat2, lon2);
	z2 = R * sin(lat2);
	
	norma1 = calcula_norma(x1,y1,z1);
	norma2 = calcula_norma(x2,y2,z2);
	pi = x1*x2 + y1*y2 + z1*z2;
	
	alpha = acos(pi/norma1/norma2);
	dist = R*alpha;
	
	return dist;
}

void calcula_distancia_rotas (LISTA* topo_aer, BLOCO* topo_rotas){
	AEROPORTO aer1, aer2;
	LISTA* atual_aer = topo_aer;

	if ((topo_aer != NULL) && (topo_rotas != NULL)){
		while (topo_rotas != NULL){
			while(topo_aer != NULL){
				if(strcmp(topo_rotas->rota.IATA_p, topo_aer->aer.IATA)==0)
					aer1 = topo_aer->aer;
				if(strcmp(topo_rotas->rota.IATA_c, topo_aer->aer.IATA)==0)
					aer2 = topo_aer->aer;
				
				topo_aer = topo_aer->prox;
			}
			topo_aer = atual_aer;
			topo_rotas->rota.distancia = calcula_distancia_aeroportos(aer1, aer2);
			topo_rotas = topo_rotas->prox;
		}
	}
}