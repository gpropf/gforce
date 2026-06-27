// $Id: gfView.h 115 2008-07-20 10:09:03Z greg $

#ifndef gfView_h
#define gfView_h

#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/threads/SbThreadAutoLock.h>
#include <Inventor/threads/SbMutex.h>


#include "gfvtktypes2.h"

class GfView {
public:

  GfView *next;
  GfView *firstChild;

  vtkvis_scaling_factors *sf;
  virtual void update()=0;
  virtual void init()=0;
 protected:
    SoSeparator *rootSep;
};


#endif
