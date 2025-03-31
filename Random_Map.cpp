#include "Random_Map.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "game_map.h"

using namespace std;
int a[105][10500];
void cloud_spawn()
{
    int z=1;
    while (z<=MAX_MAP_X)
   {
      int t=rand()%5+5;
      int m=rand()%3+1;
      z+=t;
      a[m][z]=rand()%2+4;
   }

}
void land_spawn()
{
    int mm=rand()%3+7;
    int z=1;
   while (z<=MAX_MAP_X)
   {    int m=rand()%3+7;
        if (mm-m==2) m=mm-1;
       int t=rand()%20+1;          //độ dài dãy land
       if (z==1) t+=30;
              //độ cao của land
      for (int x=z;x<z+t;x++)
        for (int y=m;y<=10;y++)
        {
            if (y==m)
            a[y][x]=2+x%2;
            else a[y][x]=1;
            if (x==z+t) a[y][x]=0;
            if (y==10&&y!=m) a[y][x]=6;
        }
        z+=t+rand()%2+2;
        mm=m;
   }
   for (int x=1;x<=MAX_MAP_X;x++)
   {
       if (a[10][x]==0) a[10][x]=10;
   }
}
void clearFile( string filename)
{
    ofstream file(filename, ios::trunc); // Mở file với chế độ xóa nội dung
    if (file.is_open()) {
        cout << "Đã xóa nội dung của tệp: " << filename << endl;
        file.close();
    } else
    {
        cout << "Không thể mở tệp: " << filename << endl;
    }
}

void Random_Map::reset_map()
{
}
void spike_spawn()
{
       for (int x=50;x<=MAX_MAP_X;x++)
   {

        for (int y=2;y<=8;y++)
        {
             if (a[y][x]>=2&&a[y][x]<=3&&a[y][x-1]>=2&&a[y][x-1]<=3&&a[y][x-2]>=2&&a[y][x-2]<=3&&a[y][x+1]>=2&&a[y][x+1]<=3&&a[y][x+2]>=2&&a[y][x+2]<=3&&a[y][x-3]>=2&&a[y][x-3]<=3)
             {
                 int random_spike=rand()%100;
                 if (random_spike<=20)
                 {
                     a[y-1][x]=20;
                     x+=3;
                 }
                 break;
             }
        }

   }
}
void Random_Map::build()
{   clearFile("map01.dat");
    freopen("map01.dat","w",stdout);
   // srand(time(nullptr));
    cloud_spawn();
    land_spawn();
    spike_spawn();
   for (int y=1;y<=10;y++)
   {
       for (int x=1;x<=MAX_MAP_X;x++)
        cout<<a[y][x]<<' ';
       cout<<endl;
   }
   fclose(stdout);
}

