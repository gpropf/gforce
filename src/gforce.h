/* $Id: gforce.h 60 2008-05-23 07:00:03Z greg $ */

#ifndef __gforce_h
#define __gforce_h

#ifdef __cplusplus
extern "C" {
#endif



  void bfcc_eo (extended_object *eo);

  void compute_center_of_mass_eo(extended_object *eo);

  void compute_torque_eo(extended_object *eo);

  mass_element *new_mass_element(extended_object *eo, vector3 loc,
				 vector3 vel, vector3 acc, gf_double mass,
				 gf_double temp, gf_string name, gf_int id);

  extended_object *new_extended_object(universe *univ, gf_string name, gf_int id);
  universe *new_universe ();

  bond *new_bond(extended_object *eo, mass_element *a, mass_element *b,
		 gf_double temp,gf_double spring_constant,
		 gf_string name, gf_int id);

  vector3 sub_vector3(vector3 a, vector3 b);

  vector3 distance_from_axis(vector3 a, vector3 p,vector3 cm);

  vector3 *moment_of_inertia_vectors(vector3 a, vector3 p,
				     vector3 cm, vector3 *v);

  void compute_moment_of_inertia_eo(extended_object *eo);

  gf_double return_moment_of_inertia_eo(extended_object *eo);

  void compute_timestep_univ(universe *univ);
  

  gf_double mag_vector3(vector3 v);


  char *print_vector3 (vector3 v);


  void print_mass_element (mass_element *me);


  void print_bond(bond *bnd);
 
  void iterate_universe(universe *u);


  void iterate_mass_elements_eo (extended_object *eo);
  void iterate_bonds_eo (extended_object *eo);


  void addto_vector3(vector3 *a, vector3 b);
  void subfrom_vector3(vector3 *a, vector3 b);

  vector3 normal_from_know_mag_vector3(vector3 v, gf_double mag);
  vector3 normal_vector3(vector3 v);

  gf_bool is_zero_vector(vector3 v);

  vector3 mul_by_scalar_vector3(vector3 v, gf_double m);
  vector3 div_by_scalar_vector3(vector3 v, gf_double m);

  void zero_vector3(vector3 *v);

  vector3 cross_vector3(vector3 a, vector3 b);
  vector3 add_vector3(vector3 a, vector3 b);

  quaternion mul_quaternion(quaternion a,quaternion b);

  quaternion make_rotation_quaternion(vector3 v, gf_double alpha);

  vector3 quatrot_vector3(vector3 v,quaternion q);


#ifdef __cplusplus
}
#endif 

#endif
