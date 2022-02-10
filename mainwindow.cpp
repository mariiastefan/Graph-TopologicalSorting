#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graph.h"
#include "arc.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <random>
#include <fstream>
#include <iostream>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


void Sageata(QPainter& painter, QPoint start, QPoint end) {

  painter.setRenderHint(QPainter::Antialiasing, true);

  qreal arrowSize = 20;
  //painter.setPen(QColor(0, 0, 255, 127));
 // painter.setBrush(QColor(0, 0, 255, 127));
  painter.setPen(Qt:: darkCyan);
  painter.setBrush(Qt::darkCyan);
  QLineF line(end, start);

  double angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;
  painter.drawLine(line);
  painter.drawPolygon(arrowHead);

}
MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    QPainter painter(this);
    srand (time(NULL));

        if(button==true)
        {

        for(int index=0;index<8;index++)
        {
            int a= rand()%300+50,b=rand()%300+50;
            if(index>0)
            {
                noduri=g.GetNoduri();
                for(auto &index:noduri)
                  {
                    if(fabs(index.getPoint().rx()-a)<20 && fabs(index.getPoint().ry()-b)<20 )
                    {
                        a+=80;
                        b+=50;
                        break;
                    }

                  }

            }
             QRect y(a,b,25,25);
             QPoint point(a,b);
             Node nod(point);
             g.AddNod(nod);
            painter.setPen(QPen(Qt::black));
            painter.setBrush(Qt::magenta);
            painter.drawEllipse(y);
            painter.drawText(y,Qt::AlignCenter,QString::number(index));
        }
        noduri=g.GetNoduri();
       for(int index=0;index<vect.size();index++)
        {
              int a=vect[index][0];
              int b=vect[index][1];
          Arc arc(noduri[a],noduri[b]);
           g.AddArc(arc);
        }
          arce=g.GetArce();
        for(auto& ind: arce)
                  {
                            int x1 = ind.getFirstPoint().getPoint().x();
                            int x2 = ind.getFirstPoint().getPoint().y();
                            int y1 = ind.getSecondPoint().getPoint().x();
                            int y2 = ind.getSecondPoint().getPoint().y();
                            QPoint x(x1, x2);
                            QPoint y(y1, y2);
                            Sageata(painter,x,y);
                  }
    button=false;
    }
if(button3==true)
{
    arce=g.GetArce();
    noduri=g.GetNoduri();
    for(auto &nod:noduri)
    {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(Qt::magenta);
        painter.drawEllipse(QRect(nod.getPoint().x(),nod.getPoint().y(),25,25));
        painter.drawText(QRect(nod.getPoint().x(),nod.getPoint().y(),25,25),Qt::AlignCenter,QString::number(nod.getNumber()));

    }
    noduri=g.GetNoduri();
    for(auto& ind: arce){

        if(ind.getFirstPoint().getNumber()<ind.getSecondPoint().getNumber())
        {
            int x1 = ind.getFirstPoint().getPoint().x();
            int x2 = ind.getFirstPoint().getPoint().y();
            int y1 = ind.getSecondPoint().getPoint().x();
            int y2 = ind.getSecondPoint().getPoint().y();
            QPoint x(x1, x2);
            QPoint y(y1, y2);
            Sageata(painter,x,y);
        }
              }
}

}

void MainWindow::on_pushButton_clicked()
{
    button=true;
    int n;
    int x;
    QFile file("D:/AG/tema4/lista_ad.txt");
          if(file.open(QIODevice::ReadOnly | QIODevice::Text))
          {
              QTextStream gr(&file);
              gr>>n;
              for(int index=0;index<n;index++)
              {
                  std::vector<int> vect1;
                  for(int index1=0;index1<2;index1++)
                  {
                      gr>>x;
                      vect1.push_back(x);
                  }
                  vect.push_back(vect1);
              }
           }
          update();
          g.adj = new std::list<int>[9];
    for(int i=0;i<vect.size();i++)
       {
                g.adj[vect[i][0]].push_back(vect[i][1]);

       }

}


void MainWindow::on_pushButton_2_clicked()
{
    button2=true;
    std::vector<int> topo;
    if (g.hasCycle())
    {
        QMessageBox msgBox;
        msgBox.setText("Graful contine cicluri");
        msgBox.exec();
    }
    else
    {
        g.topologicalSort(topo);
        QFile file("D:/AG/tema4/topo.txt");
                 if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                 {
                     QTextStream gr(&file);
                         for (auto &ind:topo)
                         {
                            gr << ind << " ";

                         }

                 }

    }
 update();

}


void MainWindow::on_pushButton_3_clicked()
{
    button3=true;
    update();
}

