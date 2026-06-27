// $Id: gfMassElementCoinView.h 115 2008-07-20 10:09:03Z greg $

#ifndef gfMassElementCoinView_h
#define gfMassElementCoinView_h



#include "gfView.h"
#include "gfUniverse.h"
#include "gfUniverseCoinView.h"
#include "gfExtendedObjectCoinView.h"
#include "gfMassElement.h"
#include "AnimatedQuarterWidget.h"



class GfMassElementCoinView : public GfView 
{
 public:
  void update();
  void init();
  GfMassElementCoinView (GfMassElement *me,
			 AnimatedQuarterWidget *aqw,
			 GfExtendedObjectCoinView *parent,
			 SoSeparator *rootSep);

  //GfMassElementCoinView *next;


 protected:
  AnimatedQuarterWidget *aqw;
  GfMassElement *me;
  GfExtendedObjectCoinView *parent;
  SoTransform *soTransform;
};


#endif
