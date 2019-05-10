#include "cube.h"

Cube::Cube(QObject *parent) : QObject(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int shape =  qrand()%5;
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
            a[i][j] = 0;
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
            shadow[i][j] = 0;

    switch (shape) {
    case 0:a[1][1] = 1;
           a[1][2] = 1;
           a[2][1] = 1;
           a[2][2] = 1;break;
    case 1:a[0][1] =1;
        a[1][1] =1;
        a[2][1] =1;
        a[2][2] =1;break;
    case 2:a[0][2]=1;
        a[1][1]=1;
        a[1][2]=1;
        a[2][1]=1;break;
    case 3:a[1][2]=1;
        a[2][1]=1;
        a[2][2]=1;
        a[2][3]=1;break;
    case 4:a[0][2]=1;
        a[1][2]=1;
        a[2][2]=1;
        a[3][2]=1;break;
    default:break;
    }
    createCube();

}
/* 0代表田 1代表L 2代表S 3代表山 4代表长条
*/
void Cube::createCube(){

     int shape =  qrand()%5;
     for(int i=0;i<N;++i)
         for(int j=0;j<N;++j)
             shadow[i][j] = 0;

     switch (shape) {
     case 0:shadow[1][1] = 1;
            shadow[1][2] = 1;
            shadow[2][1] = 1;
            shadow[2][2] = 1;break;
     case 1:shadow[0][1] =1;
         shadow[1][1] =1;
         shadow[2][1] =1;
         shadow[2][2] =1;break;
     case 2:shadow[0][2]=1;
         shadow[1][1]=1;
         shadow[1][2]=1;
         shadow[2][1]=1;break;
     case 3:shadow[1][2]=1;
         shadow[2][1]=1;
         shadow[2][2]=1;
         shadow[2][3]=1;break;
     case 4:shadow[0][2]=1;
         shadow[1][2]=1;
         shadow[2][2]=1;
         shadow[3][2]=1;break;
     default:break;
     }

}

void Cube::NextCube(){

    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
            a[i][j] = shadow[i][j];
    createCube();
}

void Cube::reshape(){
    int b[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
    {
        b[j][N-1-i] = a[i][j];
    }
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            a[i][j] = b[i][j];
        }

}
