/* $Id: util2.h 116 2008-07-21 07:48:31Z greg $ */



#ifndef util2_h
#define util2_h

#include <stdio.h>
#include <malloc.h>
#include <math.h>


#include "gfMassElement.h"
#include "gfExtendedObject.h"
#include "gfUniverse.h"
#include "gfBond.h"
#include "gfVector.h"




#ifdef __cplusplus
extern "C" {
#endif


  struct ring {
    GfMassElement **outer_masses;
    GfMassElement **inner_masses;
    GfBond **bonds;
  };

  typedef struct ring ring;

  struct massgrid {
    GfMassElement **elements;
    GfBond **bonds;
  };


  typedef struct massgrid massgrid;



  GfVector make_tangential_force(GfMassElement *me, GfExtendedObject *eo, gf_double mag);

  ring make_cylinder(gf_int num_sections, gf_double rad, gf_double width, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo);

  ring make_ring(gf_int num_sections, gf_double outer_r, gf_double inner_r, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo);

  massgrid make_massgrid(gf_double xspacing, gf_double yspacing, gf_double mass, gf_int x_num_masses, gf_int y_num_masses, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo);

#ifdef __cplusplus
}
#endif

#endif



