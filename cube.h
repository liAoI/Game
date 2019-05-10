#ifndef CUBE_H
#define CUBE_H

#include <QObject>
#include <QtGlobal>
#include<QTime>
#include<QDebug>
#define N 4
class Cube : public QObject
{
    Q_OBJECT
public:
    explicit Cube(QObject *parent = 0);
    void createCube();
    void NextCube();
    void reshape();
    int a[N][N],shadow[N][N];
signals:

public slots:

private:


};

#endif // CUBE_H
