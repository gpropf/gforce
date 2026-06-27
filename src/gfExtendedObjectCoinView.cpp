// $Id: gfExtendedObjectCoinView.cpp 124 2008-07-27 00:38:42Z greg $

#include "gfExtendedObjectCoinView.h"
#include "gfMassElementCoinView.h"
#include "gfBondCoinView.h"

void GfExtendedObjectCoinView::update() {
  //cout <<"GfExtendedObjectCoinView::update()" << endl;
  GfView *child = this->firstChild;
  int i =0 ;
  while(child) {
    //cout << "Index:" << i++ << endl;
    child->update();
    child = child->next;
  }
}

void GfExtendedObjectCoinView::init() {

  GfMassElement *me = this->eo->first_mass_element;
  GfBond *bnd = this->eo->first_bond;
  cout << "This EO is called:" << this->eo->name << endl;
  GfView *child;


  while(me) {    
    
    if (firstChild == NULL) {
      child =  new GfMassElementCoinView(me,this->aqw,this,this->rootSep);
      
      firstChild = child;
    }
    else {
      child->next =  new GfMassElementCoinView(me,this->aqw,this,this->rootSep);
      child = child->next;
    }      
    child->init();
    cout << "Making new CHILD for ME:" << me->name << endl;
    me = me->next;
  }

  while(bnd) {    
    
    if (firstChild == NULL) {
      child =  new GfBondCoinView(bnd,this->aqw,this,this->rootSep);
      firstChild = child;
    }
    else {
      child->next =  new GfBondCoinView(bnd,this->aqw,this,this->rootSep);
      child = child->next;
    }      
    child->init();
        
    cout << "Making new CHILD for BND:" << bnd->name << endl;
    bnd = bnd->next;
  }
  child->next = NULL;
}

GfExtendedObjectCoinView::GfExtendedObjectCoinView(GfExtendedObject *eo,
						   AnimatedQuarterWidget *aqw,
						   GfUniverseCoinView *parent,
						   SoSeparator *rootSep)
{
  this->eo = eo;
  this->aqw = aqw;
  this->parent = parent;
  this->rootSep = rootSep;
  this->firstChild = NULL;
}
