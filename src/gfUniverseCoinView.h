// $Id: gfUniverseCoinView.h 115 2008-07-20 10:09:03Z greg $

#ifndef gfUniverseCoinView_h
#define gfUniverseCoinView_h

#include "gfView.h"
#include "gfUniverse.h"
#include "AnimatedQuarterWidget.h"




class GfExtendedObjectCoinView;

class GfUniverseCoinView : public GfView 
{
 public:
  void update();
  void init();
  GfUniverseCoinView(GfUniverse *univ,AnimatedQuarterWidget *aqw);

 protected:
  AnimatedQuarterWidget *aqw;
  GfUniverse *univ;
  SoSeparator * rootSep;
  //GfExtendedObjectCoinView *firstEOCV;

};


#endif
