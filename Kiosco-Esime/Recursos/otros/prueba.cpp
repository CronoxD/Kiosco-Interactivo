#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{

	string cadena[80];
	ifstream ifeventos("eventos.txt");

	int i=0;

	while(!ifeventos.eof()) 
	{
    	ifeventos >> cadena[i];
      	cout << cadena[i] << endl;
      	i++;
   	}
   	cout<<i<<endl;

   	ifeventos.close();

	return 0;
}