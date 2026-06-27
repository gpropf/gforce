
#ifndef GFUNIVERSE_H
#define GFUNIVERSE_H

#include "gftypes.h"
#include <ostream>

class GfExtendedObject;
static const gf_double G_CONST = 6.67428e-11; /* Universal Gravitational constant */

class GfUniverse {
 public:
    gf_double G; /* Gravitational constant */
    GfExtendedObject *first_extended_object;
    GfExtendedObject *last_extended_object;
    gf_int extended_object_count;
    gf_double timestep;
    gf_double max_allowed_timestep;
    gf_bool timestep_autoscaling;
    gf_double time; // global time index.
    gf_double bfcc_const;
    gf_double max_acc; // max acceleration found on a given timestep
    gf_double max_allowed_acc; // max acceleration we are willing to allow

    void compute_timestep_univ();
    void iterate();
    GfUniverse(); 

  };



#endif
