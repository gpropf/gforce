// $Id: gfExtendedObjectCoinView.h 115 2008-07-20 10:09:03Z greg $

#ifndef gfExtendedObjectCoinView_h
#define gfExtendedObjectCoinView_h


#include "gfView.h"
#include "gfUniverse.h"
#include "gfUniverseCoinView.h"
#include "AnimatedQuarterWidget.h"



class GfMassElementCoinView;

class GfExtendedObjectCoinView : public GfView 
{
 public:
  void update();
  void init();
  GfExtendedObjectCoinView(GfExtendedObject *eo,
			   AnimatedQuarterWidget *aqw,
			   GfUniverseCoinView *parent,
			   SoSeparator *rootSep);

  //GfExtendedObjectCoinView *next;

 protected:
  AnimatedQuarterWidget *aqw;
  GfExtendedObject *eo;
  GfUniverseCoinView *parent;
  //GfMassElementCoinView *firstMECV;

};


#endif
