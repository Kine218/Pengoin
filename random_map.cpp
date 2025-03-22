#include "random_map.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int a[105][1050];
void cloud_spawn()
{
    int z=1;
    while (z<=400)
   {
      int t=rand()%5+5;
      int m=rand()%3+1;
      z+=t;
      a[m][z]=rand()%2+4;
   }

}
void land_spawn()
{
    int z=1;
   while (z<=400)
   {
      int t=rand()%5+10;          //độ dài dãy land
      int m=rand()%3+8;           //độ cao của land
      for (int x=z;x<z+t;x++)
        for (int y=m;y<=10;y++)
        {
            if (y==m)
            a[y][x]=2+x%2;
            else a[y][x]=1;
            if (x==z+t) a[y][x]=0;
        }
        z+=t+rand()%2+2;
   }
}
void random_map::build()
{
    freopen("map01.dat","w",stdout);
    srand(time(nullptr));
    cloud_spawn();
    land_spawn();

   for (int y=1;y<=10;y++)
   {
       for (int x=1;x<=400;x++)
        cout<<a[y][x]<<' ';
       cout<<endl;
   }
   fclose(stdout);
}

