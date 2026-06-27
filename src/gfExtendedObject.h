

#ifndef GFEXTENDEDOBJECT_H
#define GFEXTENDEDOBJECT_H

#include "gftypes.h"

#include "gfQuaternion.h"
#include "gfVector.h"

class GfUniverse;
class GfMassElement;
class GfBond;


class GfExtendedObject {
 public:
  gf_double bfcc_const;
  gf_double bfcc_thresh_dist;


  GfVector center_of_mass;
  GfVector torque;
  GfVector linear_velocity;
  GfVector linear_acceleration;
  GfVector angular_momentum;
  GfVector angular_velocity;
  //GfVector angular_position;
  GfVector rotation_axis;
  /* Basically just a unit vector version of angular_velocity */

  gf_double angular_velocity_timestep; // AV per one timestep
  //gf_double angular_position_mag;

  GfQuaternion rotation_quaternion;
   

  GfVector loc;
  GfVector vel;
  GfVector acc;
  gf_double moment_of_inertia;
  /* I'm using a scalar for now even though I is supposed to be a tensor */

  GfBond *last_bond;
  GfBond *first_bond;
  GfMassElement *last_mass_element;
  GfMassElement *first_mass_element;
  GfExtendedObject *next;
  GfExtendedObject *prev;
  gf_int mass_element_count;
  gf_int bond_count;
  gf_string name;
  gf_int id;
  gf_double total_mass;
  gf_double bond_damping_coef;
  GfUniverse *parent_univ; /* what GfUniverse are we in */

  void compute_torque_eo();
  void bfcc_eo ();
  void compute_center_of_mass_eo();
  void iterate_bonds_eo ();
  void iterate();
  gf_double return_moment_of_inertia_eo();
  void iterate_mass_elements_eo();
  GfExtendedObject (GfUniverse &univ, gf_string name, gf_int id);
  //GfExtendedObject (gf_int a);
  //GfExtendedObject (gf_double a);

}; 

#endif
