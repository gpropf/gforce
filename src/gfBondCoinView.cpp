// $Id: gfBondCoinView.cpp 127 2008-07-28 05:21:08Z greg $

#include "gfBondCoinView.h"
#include "gfVector.h"

using namespace std;

void GfBondCoinView::update() {
  SoSFVec3f sovec;
  SbVec3f fromVec(this->bnd->a->loc.x,
		  this->bnd->a->loc.y,
		  this->bnd->a->loc.z);
  SbVec3f toVec(this->bnd->b->loc.x,
		this->bnd->b->loc.y,
		this->bnd->b->loc.z);
  this->pointingTr->pointAt(fromVec,toVec);

  gf_double bondLength = (this->bnd->a->loc - this->bnd->b->loc).mag();
  sovec.setValue(SbVec3f(0,-bondLength/2,0));
  //cout << bondLength/2 << endl;
  //sovec.setValue(SbVec3f(0,0,0));
  this->offsetTr->translation = sovec;
  //offsetTr->recenter(SbVec3f(0,-bondLength/2,0));
  this->bndCyl->height = bondLength;


  
}

void GfBondCoinView::init() {
  SoSFVec3f sovec;

  SoSeparator *sep = new SoSeparator;
  SoBaseColor * col = new SoBaseColor;
  col->rgb = SbColor(0.1, 0.3, 0.9);



  
  this->bndCyl->radius = 0.25;
  
  
  
  
  this->baseTr->rotation.setValue(SbVec3f(1, 0, 0), 1.5707963f);
 
  gf_double bondLength = (this->bnd->a->loc - this->bnd->b->loc).mag();
  sovec.setValue(SbVec3f(0,-bondLength/2,0));
  //sovec.setValue(SbVec3f(0,0,0));
  

  this->bndCyl->height = bondLength;

  sep->addChild(col);
  
  sep->addChild(pointingTr);
  
  sep->addChild(baseTr);
  sep->addChild(offsetTr);    
  sep->addChild(bndCyl);

  SbVec3f fromVec(this->bnd->a->loc.x,
		  this->bnd->a->loc.y,
		  this->bnd->a->loc.z);
  SbVec3f toVec(this->bnd->b->loc.x,
		this->bnd->b->loc.y,
		this->bnd->b->loc.z);
  this->pointingTr->pointAt(fromVec,toVec);
  this->offsetTr->translation = sovec;
  //offsetTr->recenter(SbVec3f(0,-bondLength/2,0));
  this->rootSep->addChild(sep);

}

GfBondCoinView::GfBondCoinView(GfBond *bnd,
			       AnimatedQuarterWidget *aqw,
			       GfExtendedObjectCoinView *parent,
			       SoSeparator *rootSep)
{
  this->bnd = bnd;
  this->aqw = aqw;
  this->parent = parent;
  this->rootSep = rootSep;
  this->pointingTr = new SoTransform();
  this->offsetTr = new SoTransform();
  this->bndCyl = new SoCylinder();
  this->baseTr = new SoTransform();
  this->offsetTr = new SoTransform();
}
