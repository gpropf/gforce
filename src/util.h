/* $Id: util.h 60 2008-05-23 07:00:03Z greg $ */

#include <stdio.h>
#include <malloc.h>
#include <math.h>


#ifndef __util_h
#define __util_h

#ifdef __cplusplus
extern "C" {
#endif


  struct ring {
    mass_element **outer_masses;
    mass_element **inner_masses;
    bond **bonds;
  };

  typedef struct ring ring;

  struct massgrid {
    mass_element **elements;
    bond **bonds;
  };


  typedef struct massgrid massgrid;



  vector3 make_tangential_force(mass_element *me, extended_object *eo, gf_double mag);

  ring make_cylinder(gf_int num_sections, gf_double rad, gf_double width, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, extended_object *eo);

  ring make_ring(gf_int num_sections, gf_double outer_r, gf_double inner_r, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, extended_object *eo);

  massgrid make_massgrid(gf_double xspacing, gf_double yspacing, gf_double mass, gf_int x_num_masses, gf_int y_num_masses, gf_double spring_constant, gf_double temp, gf_double zplane, extended_object *eo);



#endif


#ifdef __cplusplus
}
#endif
