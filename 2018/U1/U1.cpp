#include <iostream>
#include <fstream>

using namespace std;
//funkciju deklaravimas
void nuskaitymas(int &n);
int skaiciavimai(int n);
void rasymas(int n);
//masyvai
char spalvos[3] = {'G', 'Z', 'R'};
int kiekis[3] = {0};

int main()
{
    int n;
    nuskaitymas(n);
    for (int i = 0; i < 3; i++)
    {
        cout<<kiekis[i]<<endl;
    }
    
    rasymas(n);
}

void nuskaitymas(int &n)
{
    ifstream in("U1.txt");
    in>> n;
    for(int i=0; i<n; i++)
    {
        char raide;
        int skaicius;
        in>>raide>>skaicius;
        // surandam atitinkamos spalvos kieki ir ten pridedam skaiciu
        // is kiekvienos kruveles
        for (int k = 0; k < 3; k++)
        {
            if (raide == spalvos[k])
            {
                kiekis[k] += skaicius;
            }           
        }
    }
}
int skaiciavimai(int n)
{
    int veliaveliu_sk=0;
    // daugiau uz 1, nes kiekvienos spalvos turi buti bent 2
    // kad galima butu suformuoti veliavele
    while (kiekis[0]> 1 && kiekis[1]> 1 && kiekis[2]> 1 )
    {
        veliaveliu_sk++;
        kiekis[0]-=2;
        kiekis[1]-=2;
        kiekis[2]-=2;
    }
    return veliaveliu_sk;
}
void rasymas(int n)
{
    ofstream out("U1_rez.txt");
    //iskarto issprintinam gauta rezultata
    out<<skaiciavimai(n)<<endl;
    for(int i=0; i<3; i++)
    {
        out<<spalvos[i]<<" = "<<kiekis[i]<<endl;
    }
}
