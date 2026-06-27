/* $Id: gftypes.h 60 2008-05-23 07:00:03Z greg $ */

#include "config.h"

#ifndef __gftypes_h
#define __gftypes_h


#if GFDEBUG > 0
#define GFD(out) out;
#else
#define GFD(out)
#endif

#define GF_TRUE 1
#define GF_FALSE 0



/* You can never have two much pi */

#define TWOPI 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341358

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#ifdef __cplusplus
extern "C" {
#endif


  typedef char* gf_string;
  typedef double gf_double;
  typedef long int gf_int;
  typedef int gf_bool;




  struct vector3 {
    gf_double x;
    gf_double y;
    gf_double z;
  };

  typedef struct vector3 vector3;

  struct quaternion {
    gf_double s;
    gf_double x;
    gf_double y;
    gf_double z;
  };

  typedef struct quaternion quaternion;



  struct mass_element {
    vector3 loc;
    vector3 relative_loc; /* displacement from the local center of mass */
    vector3 absloc; 
    /* Where the thing really is, not it's position relative to it's
       parent eo.  This is computed from both the eo->loc and the
       current spin */

    vector3 vel;
    vector3 acc;
    vector3 force;
    vector3 distance_from_axis;
    gf_double temp;
    gf_double mass;
    gf_string name;
    gf_int id;
    struct mass_element *next;
    struct mass_element *prev;
    struct bond *bonds; 

    /* Back reference to bonds that connect here for when masses collide
       and need to be combined or deleted.  Filled in after the sim
       starts */
  
  };

  typedef struct mass_element mass_element;
  

  struct bond {
    mass_element *a;
    mass_element *b;
    gf_double proper_length;
    gf_double temp;
    gf_double spring_constant;
    gf_string name;
    gf_int id;
    struct bond *next;
    struct bond *prev;
  };

  typedef struct bond bond;

  struct extended_object {

    gf_double bfcc_const;
    gf_double bfcc_thresh_dist;


    vector3 center_of_mass;
    vector3 torque;
    vector3 linear_velocity;
    vector3 linear_acceleration;
    vector3 angular_momentum;
    vector3 angular_velocity;
    //vector3 angular_position;
    vector3 rotation_axis;
    /* Basically just a unit vector version of angular_velocity */

    gf_double angular_velocity_timestep; // AV per one timestep
    //gf_double angular_position_mag;

    quaternion rotation_quaternion;
   

    vector3 loc;
    vector3 vel;
    vector3 acc;
    gf_double moment_of_inertia;
    /* I'm using a scalar for now even though I is supposed to be a tensor */

    bond *last_bond;
    bond *first_bond;
    mass_element *last_mass_element;
    mass_element *first_mass_element;
    struct extended_object *next;
    struct extended_object *prev;
    gf_int mass_element_count;
    gf_int bond_count;
    gf_string name;
    gf_int id;
    gf_double total_mass;
    gf_double bond_damping_coef;
    struct universe *parent_univ; /* what universe are we in */
  }; 

  typedef struct extended_object extended_object;


  struct universe {
    gf_double G; /* Gravitational constant */
    extended_object *first_extended_object;
    extended_object *last_extended_object;
    gf_int extended_object_count;
    gf_double timestep;
    gf_double max_allowed_timestep;
    gf_bool timestep_autoscaling;
    gf_double time; // global time index.
    gf_double bfcc_const;
    gf_double max_acc; // max acceleration found on a given timestep
    gf_double max_allowed_acc; // max acceleration we are willing to allow
  };

  typedef struct universe universe;


  
#ifdef __cplusplus
}
#endif 

#endif
