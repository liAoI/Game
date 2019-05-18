#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*
      墙是3  移动的方块是1 没有的为0  不动的为2
    */
    ui->setupUi(this);
//    connect(&Gtime, SIGNAL(timeout()), this, SLOT(slotTimeout()));
//    Gtime.start(1000);
    updateTime = this->startTimer(10);
    MoveTime = this->startTimer(100);
    cube = new Cube();
    cube->createCube();
    score = 0;

    for(int i =0;i<game_C+6;++i)
        for(int j=0;j<game_R+6;++j)
        {
            if(i>=3&&i<=27 && j>=3&&j<=46)
                region[i][j] = 0;
            else
                region[i][j]=3;
        }

    move_block.setX(N);
    move_block.setY(0);
    //产生方格
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            if(cube->a[i][j] == 1)
            region[move_block.x()+j][move_block.y()+i] = cube->a[i][j];
        }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cube;
}

void MainWindow::RemoveBlock(){

    int line_count =0; //消掉的个数
    /*bool full_line = true;*/  //判断满行
    int i=46;
    while(i>=3){
        int count=0;
        for(int j=3;j<=27;++j)
        {
            if(region[j][i]==2)
            {
                ++count;

            }else{
                --i;
                break;
            }

        }
        if(count == 25)
        {
            for(int p=i;p>3;--p)
                for(int q=3;q<=27;++q)
                {
                    region[q][p] = region[q][p-1];
                }
            ++line_count;
        }
    }

    score += line_count*10;

}

void MainWindow::createblock(){
    cube->NextCube();
    move_block.setX(N);
    move_block.setY(0);
    //产生方格
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            if(cube->a[i][j] == 1)
            region[move_block.x()+j][move_block.y()+i] = cube->a[i][j];
        }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


//    for(int i = 0;i<=44;++i)
//        painter.drawLine(QPoint(200,10+i*20),QPoint(700,10+i*20));

//    for(int i = 0;i<=25;++i)
//        painter.drawLine(QPoint(200+i*20,10),QPoint(200+i*20,890));
    //  在整个1000.0*900.0里面在坐标为（200，10）开始画长500，高880的矩形，设置每个小方格为20*20
    painter.setPen(Qt::darkBlue);
    QRectF rectangle(start_x,start_y, 500, 880);
    painter.drawRect(rectangle);


    for(int i =3;i<=27;++i)
        for(int j=3;j<=46;++j)
        {
            if(1==region[i][j])
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                QRectF rectangle(start_x+(i-3)*20, start_y+(j-3)*20, 20, 20);
                painter.drawRect(rectangle);
            }
            if(2 == region[i][j])
            {
                painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                QRectF rectangle(start_x+(i-3)*20, start_y+(j-3)*20, 20, 20);
                painter.drawRect(rectangle);
            }

        }
    //绘制得分
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",14));
        painter.drawText(QRect(start_x+game_C*cell_size+cell_size*N,start_y,cell_size*N,cell_size*N),Qt::AlignCenter," score: "+QString::number(score));

    //绘制预览方格
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
            {
                if(cube->shadow[i][j] == 1)
                {
                    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                    QRectF rectangle(N*10+i*20, N*3+j*20, 20, 20);
                    painter.drawRect(rectangle);
                }

            }
    //绘制功能按键
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",14));
        painter.drawText(QRect(start_x+game_C*cell_size,start_y+cell_size*N,cell_size*N*N,cell_size*N),Qt::AlignCenter," right  >");
        painter.drawText(QRect(start_x+game_C*cell_size,start_y+cell_size*N+cell_size,cell_size*N*N,cell_size*N),Qt::AlignCenter," left  <");
        painter.drawText(QRect(start_x+game_C*cell_size,start_y+cell_size*N+cell_size*2,cell_size*N*N,cell_size*N),Qt::AlignCenter," down  v");
        painter.drawText(QRect(start_x+game_C*cell_size,start_y+cell_size*N+cell_size*3,cell_size*N*N,cell_size*N),Qt::AlignCenter," transform Space");


        if(GetGameState()){
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial",32));
            painter.drawText(QRect(start_x+game_C*cell_size,start_y+cell_size*N*N,cell_size*N*N,cell_size*N),Qt::AlignCenter,"game over");
            this->killTimer(updateTime);
            this->killTimer(MoveTime);
        }
}

void MainWindow::timerEvent(QTimerEvent*e){
    if(updateTime == e->timerId())
        update();

    if(MoveTime == e->timerId())
        if(check(Qt::Key_Down))
            Move(Qt::Key_Down);
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug()<<event->key();
    switch (event->key()) {
        case Qt::Key_Right:
       if(check(Qt::Key_Right))
       {

            Move(Qt::Key_Right);
       }
         break;
    case Qt::Key_Down:
            if(check(Qt::Key_Down))
            {

                Move(Qt::Key_Down);
            }

         break;
    case Qt::Key_Left:
            if(check(Qt::Key_Left))
            {
                qDebug()<<"true";
                Move(Qt::Key_Left);
            }
        break;
    case Qt::Key_Space:
        if(check(Qt::Key_Space))
        {
            cube->reshape();
            Move(Qt::Key_Space);
        }
        break;
    default:break;
            }
}
void MainWindow::Move(int d){

    /*移动 方格为0的可以忽略，不移动。方格为1的覆盖0的，*/
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            //移动
            if(region[move_block.x()+i][move_block.y()+j] == 1)
                region[move_block.x()+i][move_block.y()+j]=0;
        }
    switch (d) {
        case Qt::Key_Right:
            move_block.setX(move_block.x()+1);
        break;
        case Qt::Key_Down:
            move_block.setY(move_block.y()+1);
        break;
        case Qt::Key_Left:
            move_block.setX(move_block.x()-1);
        break;
        case Qt::Key_Space:break;

        default:break;
    }
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
            {
                //移动
                if(cube->a[i][j] == 1)
                    region[move_block.x()+j][move_block.y()+i]=cube->a[i][j];
            }


}

bool MainWindow::check(int d){

    switch(d){
    case Qt::Key_Right:   //判断方块最右一列和外边是否出现1：2或者1：3，只要碰到墙和不可移动方块就不能向右移动
        if(move_block.x()+3 >= 30)
            return false;
            for(int i=0;i<N;++i)
                for(int j=0;j<N;++j)
            {
                if(region[move_block.x()+i][move_block.y()+j]==1)
                {

                    if( region[move_block.x()+i+1][move_block.y()+j]==2 || region[move_block.x()+i+1][move_block.y()+j]==3)
                        return false;
                }
            }

        break;
    case Qt::Key_Left:
        if(move_block.x() == 0)
            return false;
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
        {

            if(region[move_block.x()+i][move_block.y()+j]==1)
            {
                if(region[move_block.x()+i-1][move_block.y()+j]==2 || region[move_block.x()+i-1][move_block.y()+j]==3)
                    {
                        return false;
                    }

            }
        }

        break;
    case Qt::Key_Down:
        if(move_block.y()+3>=49)
            return false;
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
        {
            if(region[move_block.x()+i][move_block.y()+j]==1)
            {
                if(region[move_block.x()+i][move_block.y()+j+1]==2 || region[move_block.x()+i][move_block.y()+j+1]==3)
                {
                    changestate();
                    RemoveBlock();
                    if(!GetGameState())
                        createblock();
                    else
                        EndGame();
                    return false;
                }//判断方块是否全部变为2，只要1的下方有个2或者3，那么再向下移动就会固定不动，并把1全部变为2

            }
        }
        break;
    case Qt::Key_Space:
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
        {
                if(region[move_block.x()+j][move_block.y()+i] == 1)
                {

                    if( region[move_block.x()+N-1-i][move_block.y()+j]==2 || region[move_block.x()+N-1-i][move_block.y()+j]==3)
                        return false;
                }
        }
        break;
    default:break;
    }
    return true;
}

void MainWindow::changestate(){
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            if(region[move_block.x()+j][move_block.y()+i] == 1)
                region[move_block.x()+j][move_block.y()+i] = 2;
        }

}

bool MainWindow::GetGameState(){

    for(int i=3;i<=27;++i)
    {
       if(region[i][3] == 2)
           return true;
    }

    return false;
}

void MainWindow::EndGame(){


}

