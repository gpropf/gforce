// $Id: gfUniverseCoinView.cpp 116 2008-07-21 07:48:31Z greg $

#include "gfUniverseCoinView.h"
#include "gfExtendedObjectCoinView.h"

using namespace std;

GfUniverseCoinView::GfUniverseCoinView(GfUniverse *univ,
				       AnimatedQuarterWidget *aqw)
{
  this->univ = univ;
  this->aqw = aqw;
  this->firstChild = NULL;
  this->rootSep = new SoSeparator();
}


void GfUniverseCoinView::update() {
  GfExtendedObjectCoinView *eocv = static_cast<GfExtendedObjectCoinView *>(this->firstChild);
  while(eocv) {
    eocv->update();
    eocv=static_cast<GfExtendedObjectCoinView *>(eocv->next);
  }
}

void GfUniverseCoinView::init() {

  std::cout << "In C++ code u.extended_object_count is:" << this->univ->extended_object_count << std::endl;

  GfExtendedObject *eo = this->univ->first_extended_object;
  
  GfExtendedObjectCoinView *eocv = NULL;


  while(eo) {
    //if (eocv) {
    //  eocv->next =  new GfExtendedObjectCoinView(eo,this->aqw,this);
    //}
    //else {
    
    if (firstChild == NULL) {
      eocv =  new GfExtendedObjectCoinView(eo,this->aqw,this,this->rootSep);
      
      firstChild = eocv;
    }
    else {
      eocv->next =  new GfExtendedObjectCoinView(eo,this->aqw,this,this->rootSep);
      eocv = static_cast<GfExtendedObjectCoinView *>(eocv->next);
    }      
    eocv->init();
    
    
      //}
    
    cout << "Making new EOCV for EO:" << eo->name << endl;
    eo = eo->next;
  }
  eocv->next = NULL;

  // Scene graph stuff

  
  SoTransform * tr1;
 


  rootSep->ref();


  

  //MyThread mythread;
  //mythread.start();


  SoSeparator *sep1 = new SoSeparator;
  SoSeparator *sep2 = new SoSeparator;
  SoSeparator *sep3 = new SoSeparator;
  SoSeparator *sepC = new SoSeparator;

  SoBaseColor * colC = new SoBaseColor;
  colC->rgb = SbColor(1, 1, 1);

  sepC->addChild(colC);
  sepC->addChild(new SoCylinder);

  tr1 = new SoTransform();  
  SoSFVec3f sovec;
  sovec.setValue(SbVec3f(10,0,0));
  tr1->translation = sovec;
  //tr1->pointAt(SbVec3f (10,1,1), SbVec3f (0,0,0));	 
  
  SoTransform * overallTransform = new SoTransform();  
  sovec.setValue(SbVec3f(0,0,0));
  overallTransform->translation = sovec;

  //


  SoBaseColor * col1 = new SoBaseColor;
  col1->rgb = SbColor(1, 0, 0);

  sep1->addChild(col1);
  sep1->addChild(tr1);
  sep1->addChild(new SoCylinder);

  SoTransform * tr2 = new SoTransform();
  sovec.setValue(SbVec3f(0,10,0));
  tr2->translation = sovec;
  
  SoBaseColor * col2 = new SoBaseColor;
  col2->rgb = SbColor(0, 1, 0);
  sep2->addChild(col2);
  sep2->addChild(tr2);
  sep2->addChild(new SoCylinder);

  SoTransform * tr3 = new SoTransform();
  sovec.setValue(SbVec3f(0,0,-10));
  tr3->translation = sovec;
  
  SoBaseColor * col3 = new SoBaseColor;
  col3->rgb = SbColor(0, 0, 1);
  sep3->addChild(col3);

  sep3->addChild(tr3);
  sep3->addChild(new SoCylinder);

  
  rootSep->addChild(overallTransform);  
  rootSep->addChild(sep1);

  rootSep->addChild(sep2);

  rootSep->addChild(sep3);
  rootSep->addChild(sepC);


  // Use one of the convenient SoQt viewer classes.
  //SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(mainwin);
  //eviewer->setSceneGraph(rootSep);
  //eviewer->show();
  this->aqw->setSceneGraph(rootSep);
  
  
  float f = 0;

  //struct gfide_data qtd;
  //qtd.tr = overallTransform;
  //qtd.num = &f;

  //this->aqw->animationCallback = incnum;
  //this->aqw->animationCallback = incpos;
  //this->aqw->animationCallbackData = (void *)&i;
  //this->aqw->animationCallbackData = (void *)&qtd;
  //this->aqw->timerInterval = 90;
  //this->aqw->startAnimation();



}
