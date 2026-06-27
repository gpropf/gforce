#include "AnimatedQuarterWidget.h"
#include <iostream>

#include <Inventor/nodes/SoTransform.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/threads/SbThreadAutoLock.h>
#include <Inventor/threads/SbMutex.h>
//#include "ui_gfide.h"


struct gfide_data {
  SoTransform *tr;
  float *num;
};





int foo(int argc, char **argv) {
  std::cout << "foo: There are " << argc << " arguments" << std::endl;
  for(int i=0;i<argc;i++)
    std::cout << argv[i] << std::endl;
}


Bogus::Bogus(int argc, char *argv[]) {
  std::cout << "foo: There are " << argc << " arguments" << std::endl;
  for(int i=0;i<argc;i++)
    std::cout << argv[i] << std::endl;
}

void Bogus::testQtWrapper(QMainWindow *qmw) {
  printf("void Bogus::testQtWrapper(QMainWindow qmw)\n");
}


void AnimatedQuarterWidget::animate()
{
  animationCallback(animationCallbackData);
  internalTimer->setInterval(timerInterval);
}


void AnimatedQuarterWidget::startAnimation() 
{
  internalTimer->start(timerInterval);
}

void AnimatedQuarterWidget::stopAnimation() 
{
  internalTimer->stop();
}

AnimatedQuarterWidget::AnimatedQuarterWidget( QWidget *parent )
    : SIM::Coin3D::Quarter::QuarterWidget( parent )
{
  //time = QTime::currentTime();                // get current time
  internalTimer = new QTimer( this ); // create internal timer
  this->connect( internalTimer, SIGNAL (timeout()), SLOT (animate()) );

}


AnimatedQuarterWidget::~AnimatedQuarterWidget() 
{
}



