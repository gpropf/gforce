// $Id: gfMassElement.h 81 2008-06-09 07:27:19Z greg $

#ifndef GFMASSELEMENT_H
#define GFMASSELEMENT_H

#include "gftypes.h"
#include "gfVector.h"

class GfBond;
class GfExtendedObject;


class GfMassElement {
 public:   
  GfVector loc;
    GfVector relativeLoc; /* displacement from the local center of mass */
    GfVector absLoc; 
    /* Where the thing really is, not it's position relative to it's
       parent eo.  This is computed from both the eo->loc and the
       current spin */

    GfVector vel;
    GfVector acc;
    GfVector force;
    GfVector distanceFromAxis;
    gf_double temp;
    gf_double mass;
    gf_string name;
    gf_int id;
     GfMassElement *next;
     GfMassElement *prev;
     GfBond *bonds; 

    /* Back reference to bonds that connect here for when masses collide
       and need to be combined or deleted.  Filled in after the sim
       starts */
  
     GfMassElement(GfExtendedObject &eo, GfVector loc,
		   GfVector vel, GfVector acc, gf_double mass,
		   gf_double temp, gf_string name, gf_int id);







  };

#endif
