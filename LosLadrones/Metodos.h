#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define executed 1
#define not_exec 0

procesos *OrdenarTL(procesos *pro, int a, int b);

//Algoritmo de planificación First Come First Servered
void FCFS(procesos *pro, int cont){
    printf("\nALgoritmo First Come First Servered\n");
    double tp, tf = 0;
    for(int b = 2; b < cont - 1; b++){
        for(int c = 0; c < cont - b; c++){
            if(pro[c].TLlegada > pro[c+1].TLlegada){
                pro = OrdenarTL(pro, c, c);
	    }
	}
    }
        for(int j = 0; j < cont - 1; j++){   
	tf += pro[j].TEjecucion;
	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %2.1f segundos", pro[j].proceso, tf);
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont-1);
    printf("\nTiempo promedio en FCFS fue de: %2.2f segundos\n", tp);
    printf("---------------------------------------------------------");
}
//Algoritmo de planificación Shortest Job First
void SJF(procesos *pro, int cont){
    printf("\nAlgoritmo Shortest Job First\n");
    double tp, tf = 0;

    for(int d = 2; d < cont - 1; d++){
	    tf = 0;
        for(int e = 1; e < cont - d; e++){
		tf += pro[e-1].TEjecucion;
	    if(pro[e].TEjecucion > pro[e+1].TEjecucion){
		if(tf > pro[e+1].TLlegada){
                    pro = OrdenarTL(pro, e, e);
	        }
	    }
	}
    }

    tf = 0;

    for(int j = 0; j < cont - 1; j++){   
        tf += pro[j].TEjecucion;
	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %2.1f segundos", pro[j].proceso, tf);
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont-1);
    printf("\nTiempo promedio en SJF fue de: %2.2f segundos\n", tp);
    printf("---------------------------------------------------------\n");
}

procesos *OrdenarTL(procesos *pro, int d, int e){
    int aux;
    int aux1;
    char aux2;
    char *aux3;
    char *aux4;
    int aux5;
    int aux6;
    int aux7;
    aux = proc[d].TLlegada;
    aux1 = pro[d].TEjecucion;
    aux3 = pro[d].proceso;
    aux2 = pro[d].Tipo;
    aux4 = pro[d].Type;
    aux5 = pro[d].wt;
    aux6 = pro[d].ft;
    aux7 = pro[d].status;
    pro[d].TLlegada = pro[e+1].TLlegada;
    pro[d].TEjecucion = pro[e+1].TEjecucion;
    pro[d].proceso = pro[e+1].proceso;
    pro[d].Tipo = pro[e+1].Tipo;
    pro[d].Type = pro[e+1].Type;
    pro[d].wt = pro[e+1].wt;
    pro[d].ft = pro[e+1].ft;
    pro[d].status = pro[e+1].status;
    pro[e+1].TLlegada = aux;
    pro[e+1].TEjecucion = aux1;
    pro[e+1].proceso = aux3;
    pro[e+1].Tipo = aux2;
    pro[e+1].Type = aux4;
    pro[e+1].wt = aux5;
    pro[e+1].ft = aux6;
    pro[e+1].status = aux7;
    return pro;
}

///////

void srtf(procesos *pro,int n,float *awt,float *atat)
{
	int i,ct=0,spi;	//ct->tiempo actual,spi->indice del proceso mas corto
	double tp= 0;
	int tf = 0;

       //Inicializa cada proceso como no ejecutado
	
	for(i=0;i<n;i++)
	{
		pro[i].status = not_exec;

		pro[i].wt=0;
		
	}
 	
	do
	{
	        spi=shortestProcess(pro,n,ct); //Indice del proceso más corto

		if(spi==-1) //Si no hay ningun proceso menor
            	break;

		//Aumenta el tiempo de espera de los procesos que han llegado pero no se ejecutan
		for(i=0;i<n;i++)
		{
                  if(i!=spi && pro[i].status!=executed && ct>=pro[i].TLlegada)
                    {                   
                     pro[i].wt = pro[i].wt + 1;
                    }
                }
		
		ct++;		//actualizando el tiempo actual
		pro[spi].ft=ct-pro[spi].TLlegada;		//Tiempo final del proceso ejecutado
        	pro[spi].TEjecucion--; //Actualiza el tiempo de ejecución
                
       		if(pro[spi].TEjecucion<=0) //Revisa que el proceso haya finalizado
        	{
         	   pro[spi].status=executed; //cambia el estado a ejecutado
            	   pro[spi].ft=ct-pro[spi].TLlegada; //actualiza el tiempo de finalización
        	}
	}while(ct);
        //Ordena
	for(int d = 1; d < n; d++){
	    tf = 0;
	   for(int e = 0; e < n - d; e++){
		
	     if(pro[e].ft > pro[e+1].ft){
		
                    pro = OrdenarTL(pro, e, e);
	        
	    }
	}
    }

    tf = 0;

        //Imprimir	
	for(int d = 0; d < n; d++){   
	tf = pro[d].ft;
       	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %i segundos", pro[d].proceso, tf);
        tf = 0;
        }
	printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    	tp = tp / (n);
    	printf("\nTiempo promedio en SRTF fue de: %2.2f segundos\n", tp);
    	printf("---------------------------------------------------------\n");

}
//Devuel el indice del proceso mas corto que llego antes de the current time ct
int shortestProcess(procesos *pro,int n,int ct)
{
	int i,min_bt=99999,min_index=-1;
	for(i=0;i<n;i++)
	{
		if(pro[i].status==not_exec && pro[i].TLlegada<=ct)
		{
			if(pro[i].TEjecucion<min_bt)
			{
			    min_bt=pro[i].TEjecucion;
				min_index=i;
			}
		}
	}
	return min_index;
}

