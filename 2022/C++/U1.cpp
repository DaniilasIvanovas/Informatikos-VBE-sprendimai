#include <iostream>
#include <fstream>

using namespace std;
//funckijos 
void skaitymas(int &n);
void skaiciavimas(int n, int &max_taskai);
void rasymas(int n, int max_taskai);

// dalyvio objektas
struct Dalyvis
{
    string vardas;
    int uzdaviniai[12]; // masyvas su uzdaviniu laikais
    int total_taskai;
    int total_uzd;
};

// masyvai
int laikas[12];
int taskai[12];
Dalyvis dalyviai[5]; // finalo dalyviu masyvas

int main()
{
    int n, max_taskai;
    skaitymas(n);
    skaiciavimas(n, max_taskai);
    rasymas(n, max_taskai);
    return 0;
}

void skaitymas(int &n)
{
    ifstream in("U1.txt");
    in >> n;
    //isirasom laiko limita
    for(int i=0; i<n; i++)
    {
        in >> laikas[i];
    }
    // isirasom uzduociu max vertinima
    for(int i=0; i<n; i++)
    {
        in >> taskai[i];
    }
    // isirasom penkis finalo dalyvius
    for (int i = 0; i < 5; i++) // i < 5 nes max 5 dalyviai finale
    {
        char eil[10];
        in >> ws;
        in.get(eil, 11);
        dalyviai[i].vardas = eil;
        for (int j = 0; j < n; j++)
        {
            in >> dalyviai[i].uzdaviniai[j];
        }
    }
}

void skaiciavimas(int n, int &max_taskai)
{
    // duodam dalyviam taskus uz uzdavinius
    for(int i=0; i<5; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dalyviai[i].uzdaviniai[j]!=0){
                if (dalyviai[i].uzdaviniai[j]<=laikas[j])
                {
                    dalyviai[i].total_taskai += taskai[j];
                    dalyviai[i].total_uzd++;
                }
                else if(dalyviai[i].uzdaviniai[j]>laikas[j])
                {
                    dalyviai[i].total_taskai += taskai[j]/2;
                    dalyviai[i].total_uzd++;
              }
            }
            
        }
    }
    // paiemam pirmo dalyvio taskus kaip maxa
    max_taskai = dalyviai[0].total_taskai;
    // lyginam pirmo dalyvio taskus su likusiais dalyviais
    // kad rasti didziausia tasku skaiciu
    for(int i=1; i<5; i++)
    {
        if (dalyviai[i].total_taskai > max_taskai)  
        {
            max_taskai = dalyviai[i].total_taskai;
        }
    }
    // surusiuojame masyva pagal issprestu uzduociu skaiciu
    for(int i=0; i<5;i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (dalyviai[i].total_uzd < dalyviai[j].total_uzd)
            {
                swap(dalyviai[i], dalyviai[j]);
            }
        }
    }
}

void rasymas(int n, int max_taskai)
{
    ofstream out("U1_rez.txt");
    out << max_taskai << endl;
    for(int i=0; i<5; i++)
    {
        out << dalyviai[i].vardas << " "<<dalyviai[i].total_uzd << " ";
        // kad atskirai neskaiciuot iskarto outputinam sugaista uzdaviniam laika
        int sugaistas_laikas=0;
        for (int j = 0; j < n; j++)
        {
            sugaistas_laikas += dalyviai[i].uzdaviniai[j];
        }
        out << sugaistas_laikas << endl;
    }
}
