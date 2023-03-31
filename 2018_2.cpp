#include <iostream>
#include <fstream>

using namespace std;
// declarinam funckija
void skaitymas(int &n);
void deliojimas(int n,int &paskx, int &pasky);
void rasymas(int paskx, int pasky);
void dedam_stack(int px, int py, int dx, int dy, int r, int g, int b);
// plokstumos langelio(koordinates spalva)
struct Langelis{
    int r;
    int g;
    int b;
};
// staciakampio objektas kad lengviau butu
struct Staciakampis{
    int px; //pradzios koordinates x
    int py; //pradzios koordinates y
    int dx; //ilgis x
    int dy; //aukstis y
    //spalva
    int r; 
    int g;
    int b;
};
const int size=100;
// pasidarom plokstuma
Langelis A[size][size];
// pasidarom staciakampiu masyva
Staciakampis stack[size];

int main()
{
    // uzmetem balta spalva
    // ant plokstumos
    for(int i =0; i<100; i++)
    {
        for(int j=0; j<100;j++)
        {
            A[i][j].r = 255;
            A[i][j].g = 255;
            A[i][j].b = 255;
        }
    }
    int n, paskx, pasky; // ziureti aprasyma zemiau
    skaitymas(n);
    //DEBUGAS
    for(int i=0; i<n;i++)
    {
        cout<<stack[i].px <<" "<<stack[i].py <<" "<<stack[i].dx <<" "<<stack[i].dy<<endl;
    }
    for(int i=0; i<n;i++)
    {
        dedam_stack(stack[i].px, stack[i].py, stack[i].dx, stack[i].dy, stack[i].r, stack[i].g, stack[i].b);
    }
    //DEBUGAS @@@@@@@@@@@@@@
    ofstream out("DEBUGAS.txt");
    for(int i=0; i<size;i++)
    {
        for(int j=0; j<size; j++)
        {
            out<<"|"<< A[i][j].r <<" "<< A[i][j].g <<" "<< A[i][j].b<<"|";
        }
        out<<endl;
    }
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    //deliojimas(n, paskx, pasky);
    // paskx = stulpeliu skaicius
    //pasky = eiluciu skaicius
    rasymas(paskx, pasky);
}
// importas
void skaitymas(int &n)
{
    ifstream in("U1.txt");
    in >> n;
    for(int i=0;i<n;i++)
    {
        in >>stack[i].px >> stack[i].py >>stack[i].dx >> stack[i].dy;
        in >>stack[i].r >> stack[i].g >> stack[i].b;
    }
}
void dedam_stack(int px, int py, int dx, int dy, int r, int g, int b)
{
    for(int i=px; i<dx; i++)
    {
        for(int j=py; j<dy; j++)
        {
            A[i][j].r = r;
            A[i][j].g = g;
            A[i][j].b = b;
        }
    }
}
void deliojimas(int n,int &paskx, int &pasky)
{
    // "piesiam staciakampius"
    for(int i=0; i<n;i++)
    {
        for(int j=stack[i].px; j<stack[i].dx; j++)
        {
            for(int k=stack[i].py;k<stack[i].dy; k++)
            {
                A[j][k].r = stack[i].r;
                A[j][k].g = stack[i].g;
                A[j][k].b = stack[i].b;
            }
        }
    }
    paskx = size; // paskutinis x su nuspalvintu langeliu
    pasky = size; // paskutinis y su nuspalvintu langeliu
    //tikrinam stulpelius
    //einam per kekviena stulpeli nuo galo
    for(int i=paskx-1; i>0; i--)
    {
        bool is_white= true;
        //einam per ta stulpeli zemyn ir ieskom bent vieno ne balto langelio
        for(int j=0; j<pasky-1; j++)
        {
            if(A[i][j].r == 255 && A[i][j].g == 255 && A[i][j].b == 255)
            {
                continue;
            }
            else
            {
                is_white = false;
            }
        }
        if(is_white)
        {
            paskx--;
        }
        else
        {
            break;
        }
    }
    //tikrinam eilutes
    //einam per kekviena eilute nuo apacios
    for(int i=pasky-1; i>0; i--)
    {
        bool is_white=true;
        //einam per ta eilute i desine ir ieskom bent vieno ne balto langelio
        for(int j=0; j<paskx-1; j++)
        {
            if(A[j][i].r == 255 && A[j][i].g == 255 && A[j][i].b == 255)
            {
                continue;
            }
            else
            {
                is_white = false;
            }
        }
        if(is_white)
        {
            pasky--;
        }
        else
        {
            break;
        }
    }
    
}

void rasymas(int paskx, int pasky)
{
    ofstream out("U1_rez.txt");
    out<< paskx << " " << pasky << endl;
    // prisimename kad pasky yra eiluciu skaicius
    // o paskx yra stulpeliu skaicius!
    for(int i=0; i<pasky;i++)
    {
        for(int j=0; j<paskx; j++)
        {
            out<<A[i][j].r<<" "<< A[i][j].g<<" "<< A[i][j].b<<endl;
        }
    }
}
