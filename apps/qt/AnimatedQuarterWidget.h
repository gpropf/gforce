#ifndef ANIMATEDQUARTERWIDGET_H
#define ANIMATEDQUARTERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "Quarter/QuarterWidget.h"
#include "qtimer.h"


int foo(int argc, char **argv);



class Bogus {
 public:
  void testQtWrapper(QMainWindow *qmw);
  Bogus(int argc, char *argv[]);


};


class AnimatedQuarterWidget : public SIM::Coin3D::Quarter::QuarterWidget 
{
  Q_OBJECT;
 public:
  //static AnimatedQuarterWidget *getAQW();
  void (*animationCallback)(void *);
  void *animationCallbackData;
  int timerInterval;
  

  AnimatedQuarterWidget( QWidget *parent=0 );
  ~AnimatedQuarterWidget();
  void startAnimation();
  void stopAnimation();

  //void setAutoMask(bool b);
  
  //protected:
  //void updateMask();
  //void paintEvent( QPaintEvent *);
  //void mousePressEvent( QMouseEvent *);
  //void mouseMoveEvent( QMouseEvent *);
  //void drawClock( QPainter* );
  
  private slots:
    void animate();
  
  public slots:


 private:

  QTimer *internalTimer;
};





#endif
