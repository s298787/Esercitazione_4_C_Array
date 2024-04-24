#include "Utils.hpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const string filein = "data.csv";

    double S;
    int n;
    double* w;
    double* r;

    bool checkfile = readDataFromFile(filein, S, n, w, r); //chiama la funzione che legge i dati dal file
    if (checkfile == 1) //se readDataFromFile fallisce stampa un messaggio di errore
    {
        cerr << "Error: file not found" << endl;
        return 1;
    }

    double RoR = computeRateOfReturn(w, r, n); //calcola il tasso di interesse

    double V = computeValue(w, r, n, S); //calcola il valore finale

    const string fileout = "result.txt"; //definisce il nome del file in uscita

    printResults(w, r, n, S, RoR, V, fileout); //stampa su file e compiler

    //cancello w ed r che ho creato con new in readDataFromFile
    delete[] w;
    delete[] r;

    return 0;
}

