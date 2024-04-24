#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

bool readDataFromFile(const string& filename, double& S, int& n, double*& w, double*& r)
{
    ifstream file(filename); //apre il file
    if(file.fail()) //controlla se il file esiste
    {
        return 1;
    }

    string header;
    stringstream ss;
    string token;

    getline(file, token, ';'); //legge il primo pezzo della prima riga
    getline(file, token); //legge il valore di S
    ss << token; //inserisce il valore in ss
    ss >> S; //inserisce la ss in S
    ss.clear(); //svuota stringstream

    getline(file, token, ';'); //legge il primo pezzo della la seconda riga
    getline(file, token); //legge il valore di n
    ss << token; //inserisce il valore riga in ss
    ss >> n; //inserisce ss in n
    ss.clear(); //svuota ss

    getline(file, header); //legge la terza riga e la metto in header

    w = new double[n]; //definisce l'array w di lunghezza n
    r = new double[n]; //definisce l'array r di lunghezza n
    int count = 0; //definisce un counter per la posizione degli elementi nell'array
    double wtoken;
    double rtoken;
    string line;

    while (count < n) //dato che ci sono 8 elementi nell'array, ci saranno 8 righe di file da leggere
    {
        getline(file, line, ';'); //legge il primo pezzo della riga in line (fino a ;)
        ss << line;
        ss >> wtoken; //inserisce il valore di w[i]
        w[count] = wtoken;
        ss.clear(); //svuota lo stringstream

        getline(file, line); //legge il secondo pezzo della linea (fino a \n)
        ss << line;
        ss >> rtoken; //inserisce il valore di r[i]
        r[count] = rtoken;
        ss.clear(); //svuota lo stringstream

        count++; //aumenta il counter
    }
    return 0;
}

double computeRateOfReturn(const double* w, const double* r, const int n)
{
    double RateOfReturn = 0.0;
    for (int i = 0; i < n; i++) {
        RateOfReturn += w[i] * r[i]; //calcola la media degli r[i] pesata sui w[i]
    }
    return RateOfReturn;
}

double computeValue(const double* w, const double* r, const int n, const double S)
{
    double V = 0.0;
    for (int i=0; i<n; i++)
    {
        V += (1 + r[i])*w[i]*S;
    }
    return V;
}

void printResults(const double* w, const double* r, const int n, const double S, const double RoR, const double V, const string filename)
{
    //Stampa su file:
    ofstream outfile(filename); //apre il file di scrittura

    outfile << fixed << setprecision(2); //imposta rappresentazione decimale fissa a 2 cifre

    outfile << "S = " << S << ", n = " << n << endl; //stampa S ed n
    outfile << defaultfloat << "w = [ ";
    for (int i = 0; i<n; i++) //stampa w
    {
        outfile << w[i] << " ";
    }
    outfile << "] " << endl << "r = [ ";
    for (int i = 0; i<n; i++) //stampa r
    {
        outfile << r[i] << " ";
    }
    outfile << "] " << endl;

    outfile << fixed << setprecision(4) << "Rate of return of the portfolio: " << RoR << endl;
    outfile << setprecision(2) << "V: " << V << endl;

    outfile.close(); //chiude il file di scrittura

    //Stampa su compiler:
    cout << fixed << setprecision(2);

    cout << "S = " << S << ", n = " << n << endl; //stampa S ed n
    cout << defaultfloat << "w = [ ";
    for (int i = 0; i<n; i++) //stampa w
    {
        cout << w[i] << " ";
    }
    cout << "] " << endl << "r = [ ";
    for (int i = 0; i<n; i++) //stampa r
    {
        cout << r[i] << " ";
    }
    cout << "] " << endl;

    cout << fixed << setprecision(4) << "Rate of return of the portfolio: " << RoR << endl;
    cout << setprecision(2) << "V: " << V << endl;
}
