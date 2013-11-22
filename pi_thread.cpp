#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

//g++6 -std=c++0x -o pi_cpp pi_thread.cpp -pthread

using namespace std;

double h;
int n, nth;
double *sum;

void calculo(int num)
{
    int i, t, ini, fin;
    double x;
    ini = (n*num)/nth + 1;
    fin = (n*(num+1))/nth; 
    
    for (i = ini; i <= fin; i++)
    {
      x = h * ((double)i - 0.5);
      sum[num] += 4.0 / (1.0 + x*x);
    }
    sum[num] = h * sum[num];
}


int main(int argc, char *argv[])
{
  std::vector<std::thread> threads;
  double PI25DT = 3.141592653589793238462643;
  double mypi;
  ;
  int j, k, i;
   
  if (argc > 2) {n = atoi(argv[2]); nth = atoi(argv[1]);}
  else if (argc > 1) {n = 100; nth = atoi(argv[1]);}
  else {n= 100; nth = 1;}
  
  sum= new double [nth];
  h = 1.0 / (double) n;
 
  // Inicializar sum
  for(j = 0; j <nth; j++)
  {
	sum[j] = 0.0;
  }	

  auto time1=chrono::high_resolution_clock::now();
  // Creacion de los threads
  for (i=0; i<nth; i++) {
    threads.push_back(thread(calculo,i));
  } 
  
  // Esperamos a que acaben todos los threads
 for (auto &t: threads) {
    t.join();
  }

  //Sumamos los resultados parciales
  for(k = 0; k < nth; k++){
	mypi += sum[k];
  }
  auto time2=chrono::high_resolution_clock::now();

  cout<<"pi es aproximadamente:"<<mypi<<", el error es: "<<fabs(mypi - PI25DT)<<endl;
  
  cout << "Tiempo: " << chrono::duration<double,milli>(time2-time1).count() << " ms, con "<<nth<< " threads." << endl;

  return 0;
}
