// $Id: gfMassElementCoinView.cpp 124 2008-07-27 00:38:42Z greg $

#include "gfMassElementCoinView.h"

using namespace std;

void GfMassElementCoinView::update() {
  SoSFVec3f sovec;
  sovec.setValue(SbVec3f(this->me->loc.x,this->me->loc.y,this->me->loc.z));
  soTransform->translation = sovec;
  //cout << "GfMassElementCoinView::update():me.x:" << this->me->loc.x << endl;
}

void GfMassElementCoinView::init() {
  SoSFVec3f sovec;

  SoSeparator *sep2 = new SoSeparator;
  SoBaseColor * col2 = new SoBaseColor;
  col2->rgb = SbColor(0.8, 1, 0.4);
  sep2->addChild(col2);
  sep2->addChild(soTransform);
  sep2->addChild(new SoSphere);
  //SoTransform * soTransform = new SoTransform();
  sovec.setValue(SbVec3f(this->me->loc.x,this->me->loc.y,this->me->loc.z));
  
  soTransform->translation = sovec;
  rootSep->addChild(sep2);

}

GfMassElementCoinView::GfMassElementCoinView(GfMassElement *me,
					     AnimatedQuarterWidget *aqw,
					     GfExtendedObjectCoinView *parent,
					     SoSeparator *rootSep)
{
  this->me = me;
  this->aqw = aqw;
  this->parent = parent;
  this->rootSep = rootSep;
  this->soTransform = new SoTransform();
}
