#include <iostream>
#include <fstream>

using namespace std;
//Funkciju deklaravimas
void nuskaitymas(int &n, int &m);
void skaiciavimai(int n, int m);
int convert(int h, int min, int s);
void israsymas(int n, int m);
// Slidininko objektas
struct Slidininkas
{
    string vardas;
    int laikas;
};
// slidininku masyvas
Slidininkas pradzia[30]; //slidinku starto masyvas
Slidininkas pabaiga[30]; //pabaigusiu slidininku masyvas
int main(){
    int n, m;
    nuskaitymas(n, m);
    skaiciavimai(n, m);
    israsymas(n, m);
    return 0;
}
// nuskaitom duomenis
void nuskaitymas(int &n, int &m)
{
    int h, min, s;
    ifstream in("U2.txt");
    in >> n;
    for (int i = 0; i < n; i++)
    {
        char eil[20];
        in >> ws;
        in.get(eil, 21);
        pradzia[i].vardas = eil;
        in >> h >> min >> s;
        pradzia[i].laikas = convert(h, min, s); 
    }
    in >> m;
    for (int i = 0; i < m; i++)
    {
        char eil[20];
        in >> ws;
        in.get(eil, 21);
        pabaiga[i].vardas = eil;
        in >> h >> min >> s;
        pabaiga[i].laikas = convert(h, min, s); 
    }
}
// paverciam nuskaityta laika i sekundes kad lengviau butu skaiciuoti
int convert(int h, int min, int s)
{
    return 3600*h+60*min+s;
}
//
void skaiciavimai(int n, int m)
{
    //pradedam iteruoti per pabaigos masyva nes jame maziau elementu
    //taip nebus padarycia operacija su nepabaigusiais dalyviais
    for (int i = 0; i < m; i++)
    {
        for(int j=0; j < n; j++)
        {
            //susirandam dalyvi su vienodu vardu
            //ir suskaiciuojam kiek jam uztruko pravaziuoti
            if(pabaiga[i].vardas == pradzia[j].vardas)
            {
                pabaiga[i].laikas -= pradzia[j].laikas;
            }
        }
    }
    //rusiavimo algoritmas?
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < m; k++)
        {
            if(pabaiga[i].laikas < pabaiga[k].laikas)
            {
                swap(pabaiga[i].laikas, pabaiga[k].laikas);
            }
            else if(pabaiga[i].laikas == pabaiga[k].laikas)
            {
                if (pabaiga[i].vardas < pabaiga[k].vardas)
                {
                    swap(pabaiga[i].laikas, pabaiga[k].laikas);
                }
            }
        }
        
    }
    
}
//
void israsymas(int n, int m)
{
    ofstream out("U2_rez.txt");
    for(int i=0; i < m; i++)
    {
        out<<pabaiga[i].vardas;
        if(pabaiga[i].laikas/3600>0)
        {
            //isspausdinam kiek sveikuju valandu yra musu laike
            out<<pabaiga[i].laikas/3600<<" ";
            //atimam tas valandas is bendro laiko
            pabaiga[i].laikas -= (pabaiga[i].laikas/3600)*60;
        }
        if (pabaiga[i].laikas/60>0)
        {
            //isspausdinam kiek sveikuju minuciu yra musu laike
            out<<pabaiga[i].laikas/60<<" ";
            //atimam tas minutes is bendro laiko
            pabaiga[i].laikas -= (pabaiga[i].laikas/60)*60;
        }
        //kadangi atemem valandas ir minutes mum liko tik sekundes
        //tai jas tiesiog isspausdinam
        out<<pabaiga[i].laikas<<endl;
    }
}
