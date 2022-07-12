#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void CambioUnidadesr(double r[], int n);
double CambioUnidadest (double t);
void CambioUnidadesV (double v[], int n );
void CalculoAceleracion (double ax[], double ay[], double m[],double x[], double y[] ,int n);
void CambioUnidadesM (double m[], int n);
double CalculoEnergia (double vx[], double vy[], double x[], double y[], double m[], int n);

double G=6.67*pow(10,-11);
double Ms=1.99*pow(10,30);
double c=1.496*pow(10,11);

int main ()
{
    int i, j, k, n=9;
    double m[n], ax[n],ay[n], x[n], y[n],vx[n],vy[n],wx[n], wy[n], suma[n], t=0, h=0.01, E, p[n];
    ofstream fich, energia, geocentrico, periodo;
    bool contador[n], condicion[n], comprobar[n];

    //Definimos valores iniciales

    x[0]=0;
    y[0]=0;
    x[1]=57910000000;
    x[2]=108200000000;
    x[3]=146600000000;
    x[4]=227940000000;
    x[5]= 778330000000;
    x[6]=1429400000000;
    x[7]=2870990000000;
    x[8]=4504300000000;
    y[1]=0;
    y[2]=0;
    y[3]=0;
    y[4]=0;
    y[5]=0;
    y[6]=0;
    y[7]=0;
    y[8]=0;

    vx[0]=0;
    vy[0]=0;
    vx[1]=0;
    vx[2]=0;
    vx[3]=0;
    vx[4]=0;
    vx[5]=0;
    vx[6]=0;
    vx[7]=0;
    vx[8]=0;
    vy[1]=48920;
    vy[2]=35020;
    vy[3]=29780;
    vy[4]=24070;
    vy[5]=13050;
    vy[6]=9640;
    vy[7]=6810;
    vy[8]=5430;


    m[0]=Ms;
    m[1]=3.28*pow(10,23);
    m[2]=4.83*pow(10,24);
    m[3]=5.98*pow(10,24);
    m[4]=6.4*pow(10,23);
    m[5]=1.9*pow(10,27);
    m[6]=5.98*pow(10,26);
    m[7]=8.67*pow(10,25);
    m[8]=1.05*pow(10,26);

 
 //Reescalamos los parámetros

    CambioUnidadesM (m, n);

    CambioUnidadesr (x, n);

    CambioUnidadesr (y, n);

    CambioUnidadesV (vx,n);

    CambioUnidadesV (vy,n);

    //Calculamos las aceleraciones 

    CalculoAceleracion(ax, ay, m, x, y, n);

fich.open("planetasdatos.data");
energia.open("energia.dat");
geocentrico.open("geocentrico.dat");
periodo.open("periodo.dat");

for ( i = 0; i < n; i++)
{
    condicion[i]=false;
    contador[i]=false;
    comprobar[i]=false;
}


for ( t = 0; t <2000000 ; t=t+h){

     E=CalculoEnergia(vx,vy,x, y, m,n);

        energia << t << " " << E << endl;


      for ( i = 0; i < n; i++){

        //ENERGIA

       


      //PERIODOS

      if(y[i]<0){

        condicion[i]=true;
        p[i]=i;
      }

      if(condicion[i]==true && y[i]>0){

        contador[i]=true;
      }

      if(condicion[i]==true && contador[i]==true && comprobar[i]==false){

        if (y[i]<0)
        {
            periodo << (t-p[i])*58.1 << "i" << endl;
            comprobar[i]=true;
        }
        
      }
   
       fich << x[i] <<", " << y[i] << endl;

       geocentrico << x[i]-x[3] << "," << y[i]-y[3] << endl;

         x[i]=x[i]+(h*vx[i])+(ax[i]*((h*h)/2));
         y[i]=y[i]+(h*vy[i])+(ay[i]*((h*h)/2));

        
    }
     for ( i = 0; i < n; i++){

     wx[i]= vx[i]+((h/2)*ax[i]);
        wy[i]= vy[i]+((h/2)*ay[i]);

     }
     fich << endl;
     geocentrico << endl;
     CalculoAceleracion (ax, ay, m, x, y, n);
      for ( i = 0; i < n; i++){

        vx[i]=wx[i]+((h/2)*ax[i]);
        vy[i]=wy[i]+((h/2)*ay[i]);

      }
}

  fich.close();
  energia.close();
  periodo.close();
  geocentrico.close();


    return 0 ;
}

//Vamos a declarar funciones



void CalculoAceleracion(double ax[], double ay[], double m[],double x[], double y[] ,int n){

    int i, j;
    double r[n];


    for ( i = 0; i < n; i++)
    {
        ax[i]=0;
        ay[i]=0;

        r[i]=sqrt(x[i]*x[i]+y[i]*y[i]);
    }

    
    


    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < i; j++)
        {

            if(j!=i){
            ax[i]=ax[i]-m[j]*(x[i]-x[j])/(pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
            ay[i]=ay[i]-m[j]*(y[i]-y[j])/(pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
            }

            else{

            ax[i]=0;
            ay[i]=0;

            }            
            
        }

      
        
        
    }
    

    return;

}


void CambioUnidadesr(double r[], int n){

    int
     i ;
    
    

    for ( i = 0; i < n; i++)
    {
        r[i]=r[i]/c;
    }
    
return ;

}

void CambioUnidadesM (double m[], int n){

    int i;
    
    

    for ( i = 0; i < n; i++)
    {
        m[i]=m[i]/Ms;
    }
    
    return;
}

double CambioUnidadest (double t){


   
        t=t*sqrt((G*Ms)/pow(c,3));
        
        
  
    
return t;
    
}

void CambioUnidadesV (double v[], int n ){

    int i;
for ( i = 0; i < n; i++)
{
    v[i]=v[i]*(1/c)/(sqrt((G*Ms)/pow(c,3)));
}

      

    return;    
    
}

double CalculoEnergia (double vx[], double vy[], double x[], double y[], double m[], int n){

    int i;
    double E=0, G, c=1.946*pow(10,11), Ms;

     G=6.67*pow(10,-11);
     Ms=1.99*pow(10,30);

    for ( i = 1; i < n; i++)
    {
        E=E+(0.5*m[i]*abs((vx[i]*vx[i]+vy[i]*vy[i]))-Ms*G*m[i]/(sqrt(pow(x[i],2)+pow(y[i],2))));

    }


    return E;
    

    
}








   
    

    

