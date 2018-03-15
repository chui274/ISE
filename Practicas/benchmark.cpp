//
//  benchmark.cpp
//  
//
//  Created by SOFIA FERNANDEZ MORENO on 19/5/15.
//
//
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

int main(){
    
    clock_t tantes,tdespues;
    double tiempo;
    int puntuacion_cpu, puntuacion_mem, puntuacion_disc;
    
    //Imprimimos presentacion
    cout<<'\n';
    for(int i=0;i<100;i++) cout<<"*";
    cout<<"\n*****      PC BENCHMARK      Autor: Sofia Fernandez Moreno      *****\n";
    for(int i=0;i<100;i++) cout<<"*";
    cout<<endl;
    
    //TEST DE CPU
    
    cout<<"\n### TEST DE CPU ### \n";
    
    int cantidad=0;
    double cantidad2=1.5;
    
    tantes = clock();
    
    cout<<"\nPasando test de CPU..."<<endl;
#pragma omp parallel
    for(int i=0;i<50000000;i++){
        cantidad = cantidad*2;
        cantidad = cantidad/2;
        cantidad++;
        cantidad--;
    }
    for(int i=0;i<5000000;i++)
        cantidad2=cantidad2*1.5;
    for(int i=0;i<5000000;i++)
        cantidad2=cantidad2/1.5;

    
    tdespues = clock();
    
    tiempo = static_cast<double>(tdespues - tantes)/CLOCKS_PER_SEC;
    cout<<"\nTiempo empleado: "<<tiempo<<" segundos"<<endl;
    
    puntuacion_cpu = static_cast<int>(10000/tiempo);
    cout<<"\nPuntuacion obtenida: "<<puntuacion_cpu<<" puntos\n"<<endl;
    
    for(int i=0;i<100;i++) cout<<"-";
    
    //TEST DE MEMORIA
    
    //TEST DE MEMORIA
    cout<<"\n\n### TEST DE MEMORIA ### \n";

	int *vector;
	int aux;
	vector = new int[2500000]; 

	tantes = clock();

	cout<<"\nPasando test de Memoria..."<<endl;
	#pragma omp parallel for
   for(int i=0;i<200;i++){
      //Escritura en vector
      for(int j=0;j<500000;j++)
         for(int k=0;k<2500000;k+=500000)
            vector[k+j]=j;
      //Lectura del vector
      for(int j=0;j<500000;j++)
         for(int k=0;k<2500000;k+=500000)
           aux = vector[j];
   }
	tdespues = clock();
    
    tiempo = static_cast<double>(tdespues - tantes)/CLOCKS_PER_SEC;
    cout<<"\nTiempo empleado: "<<tiempo<<" segundos"<<endl;
    
    puntuacion_mem = static_cast<int>(10000/tiempo);
    cout<<"\nPuntuacion obtenida: "<<puntuacion_mem<<" puntos\n"<<endl;
    
    for(int i=0;i<100;i++) cout<<"-";
    
    //TEST DE DISCO DURO
    
     
   
   cout<<"\n\n### TEST DE DISCO DURO ### \n";
   
   double tiempo_lectura = 0, tiempo_escritura = 0, tiempo_total;
   int elementos=1048576; //El equivalente a un bloque de datos de 4096 Kbytes
   int *dat;
   dat=new int[elementos];
          
   cout<<"\nPasando test de Disco duro..."<<endl;
   
   ofstream salida("temporal.dat", ios::out|ios::binary);

   cout<<"\nEscribiendo en disco..."<<endl;
   for(int i=0;i<100;i++){ 
      for(int i=0;i<elementos;i++) 
      	dat[i] = rand();
      tantes = clock();
      salida.write(reinterpret_cast<const char*>(dat),elementos*sizeof(int)); 
      tdespues = clock();
      tiempo_escritura += static_cast<double>(tdespues - tantes)/CLOCKS_PER_SEC;
   }   
      
   cout<<"\nTiempo empleado en la escritura en disco: "<<tiempo_escritura<<" segundos"<<endl;
   
   tantes = clock();
   
   ifstream entrada("temporal.dat", ios::in|ios::binary);

   cout<<"\nLeyendo de disco..."<<endl;
   for(int i=0;i<100;i++)
      entrada.read(reinterpret_cast<char*>(dat),elementos*sizeof(int)); 
   entrada.close();
   salida.close();
   
   tdespues = clock();
   
   tiempo_lectura = static_cast<double>(tdespues - tantes)/CLOCKS_PER_SEC;
   cout<<"\nTiempo empleado en la lectura de disco: "<<tiempo_lectura<<" segundos"<<endl;
   
   tiempo_total = tiempo_escritura + tiempo_lectura;
   cout<<"\nTiempo total empleado: "<<tiempo_total<<" segundos"<<endl;
}
