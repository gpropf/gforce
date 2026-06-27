// $Id: gfBondCoinView.h 127 2008-07-28 05:21:08Z greg $

#ifndef gfBondCoinView_h
#define gfBondCoinView_h



#include "gfView.h"
#include "gfUniverse.h"
#include "gfUniverseCoinView.h"
#include "gfExtendedObjectCoinView.h"
#include "gfBond.h"
#include "gfMassElement.h"
#include "AnimatedQuarterWidget.h"



class GfBondCoinView : public GfView 
{
 public:
  void update();
  void init();
  GfBondCoinView (GfBond *bnd,
			 AnimatedQuarterWidget *aqw,
			 GfExtendedObjectCoinView *parent,
			 SoSeparator *rootSep);

  //GfBondCoinView *next;


 protected:
  AnimatedQuarterWidget *aqw;
  GfBond *bnd;
  GfExtendedObjectCoinView *parent;
  SoTransform *pointingTr;
  SoTransform *offsetTr;
  SoTransform *baseTr;
  SoCylinder *bndCyl;

};


#endif
