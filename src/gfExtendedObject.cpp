

#include "gfExtendedObject.h"
#include "gfMassElement.h"
#include "gfUniverse.h"



#include "gfQuaternion.h"
#include "gfVector.h"
#include "gfBond.h"


class GfUniverse;
//class GfMassElement;
//class GfBond;




void GfExtendedObject::compute_torque_eo() {
  GfMassElement *meptr = this->first_mass_element;

  GfVector t, relative_vel;
  //  GfVector total_t;
  //  gf_double x = 0;
  //  gf_double y = 0;
  //  gf_double z = 0;

  this->torque = 0;
  
  //  total_t.x = 0;
  //  total_t.y = 0;
  //  total_t.z = 0;
  
  while(meptr!=NULL) {
    //zero_GfVector(&t);
    relative_vel = (meptr->vel - this->linear_velocity);
    //t = (((meptr->loc * this->center_of_mass) - meptr->vel) * meptr->mass);
    t = ((meptr->loc - this->center_of_mass) * meptr->force);
    this->torque += t;
    GFD(printf("torque is %f\n",this->torque.mag()));
    meptr=meptr->next;
  }
  GFD(printf("Loop END\n"));
  //this->torque.x = total_t.x;
  //this->torque.y = total_t.y;
  //this->torque.z = total_t.z;
}




void GfExtendedObject::bfcc_eo () {
  GfMassElement *ma;
  GfMassElement *mb;
  ma = this->first_mass_element;
  while(ma!=NULL) {
    mb = ma->next;
    while(mb!=NULL) {
      GfVector d = (ma->loc - mb->loc);
      gf_double mag_d = d.mag();
      if (mag_d <= this->bfcc_thresh_dist ) {
	GfVector collision_force_a 
	  = d * ma->mass * this->bfcc_const / pow(mag_d,4);
	GfVector collision_force_b 
	  = d * mb->mass * this->bfcc_const / pow(mag_d,4);
	ma->force += collision_force_a;
	mb->force -= collision_force_b;
      }
      mb=mb->next;
    } 
    ma=ma->next;
  }
}









void GfExtendedObject::compute_center_of_mass_eo() {
  /* Also computes linear acceleration and total mass */

  GfMassElement *meptr = this->first_mass_element;
  GfVector weighted_loc_vector;
  GfVector linear_momentum;
  //GfVector linear_acceleration;
  
  weighted_loc_vector.x = 0;
  weighted_loc_vector.y = 0;
  weighted_loc_vector.z = 0;

  linear_momentum.x = 0;
  linear_momentum.y = 0;
  linear_momentum.z = 0;

  this->total_mass = 0;
  while(meptr!=NULL) {
    weighted_loc_vector += (meptr->loc * meptr->mass);
    linear_momentum += (meptr->vel * meptr->mass);
    this->total_mass+=meptr->mass;
    meptr=meptr->next;
  }
  this->center_of_mass = (weighted_loc_vector / this->total_mass);
  this->linear_acceleration = (linear_momentum / this->total_mass);

 
}


void GfExtendedObject::iterate_bonds_eo () {

  GfBond *bnd = this->first_bond;
  gf_double bond_current_length;
  gf_double scalar_spring_force;
  GfVector bond_vector, bond_normal, vector_spring_force;
  while(bnd!=NULL) {
    //printf ("iterating through Bond:%s\n",bnd->name);
    bond_vector = (bnd->a->loc - bnd->b->loc);
    bond_current_length = bond_vector.mag();
    bond_normal = (bond_vector / bond_current_length);
    scalar_spring_force = bnd->spring_constant * (bnd->proper_length - bond_current_length);
    vector_spring_force = (bond_normal * scalar_spring_force);
    bnd->a->force += vector_spring_force;
    bnd->b->force -= vector_spring_force;

    bnd=bnd->next;
    
  }
}

void GfExtendedObject::iterate() {
  GfMassElement *meptr = this->first_mass_element;
  GfBond *bptr = this->first_bond;
  gf_double ap_by_twopi;
  this->compute_center_of_mass_eo();
  gf_double angular_velocity_mag;

  /* Also computes linear acceleration and total mass */

  


  this->compute_torque_eo(); 

  // KEY: torque_timestep (set = to this->torque is way too big)
  //GfVector torque_timestep = this->torque;
  GfVector torque_timestep = (this->torque * this->parent_univ->timestep);

  //&this->angular_momentum += this->torque;     
  this->angular_momentum += torque_timestep;     
  
  if (this->angular_momentum == 0) {
    this->moment_of_inertia = 0;   
    this->angular_velocity = 0;
  }
  else {
    this->moment_of_inertia = this->return_moment_of_inertia_eo();
    // CONV: this used to call compute_moment_of_inertia_eo
    this->angular_velocity = (this->angular_momentum / this->moment_of_inertia);



    angular_velocity_mag = this->angular_velocity.mag();
    //&this->angular_position += this->angular_velocity; 
    

    //this->angular_position_mag = this->angular_position.mag();
    //ap_by_twopi = this->angular_velocity_timestep/TWOPI;
    //this->angular_velocity_timestep = ap_by_twopi - floor(ap_by_twopi);
    /* above keeps it in the interval [0,TWOPI] */
    

    //KEY: angular_velocity_timestep (important effect, makes diff between correct and backwards rotation if transfer_lv is turned on)
    //this->angular_velocity_timestep = angular_velocity_mag;
    this->angular_velocity_timestep = angular_velocity_mag * this->parent_univ->timestep;
    GFD(printf("AV timestep %f\n",this->angular_velocity_timestep));

    this->rotation_axis = (this->angular_velocity /  angular_velocity_mag);


    this->rotation_quaternion = GfQuaternion(this->rotation_axis, this->angular_velocity_timestep);

  }


  this->linear_velocity += this->linear_acceleration;
  
  this->iterate_mass_elements_eo();
  // We now transfer the linear velocity so we need the NEW LV before this.

  this->iterate_bonds_eo();
  this->bfcc_eo();

}





gf_double GfExtendedObject::return_moment_of_inertia_eo() {
  /* Making the assumption that the current angular_momentum vector
     and the vector of rotation have the same direction */


  GfVector r;
  char *str;
  gf_double mag_r;
  gf_double mi = 0;
  GfMassElement *meptr = this->first_mass_element;
  //this->moment_of_inertia = 0;


  /* The stuff below this causes a crash if AM is zero and the concept
     of moment of inertia is meaningless without an axis anyway so
     this function should never be called in the abscence of spin!!!*/
  if (this->angular_momentum == 0) {
    // CONV: used to use the is_zero_vector function
    printf( "AM IS ZERO!");
    return 0;
  }

  GfVector a = this->angular_momentum.normal();

  while(meptr!=NULL) {
    r =  meptr->loc.distanceFromAxis(a, this->center_of_mass);
    mag_r = r.mag();
    mi += pow(mag_r,2)*meptr->mass;
    /* I = mr^2 */
    meptr=meptr->next;
  }

  GFD(printf("Moment of inertia: %f\n",this->moment_of_inertia));
  return mi;
}




void GfExtendedObject::iterate_mass_elements_eo () {
  GfMassElement *meptr = this->first_mass_element;

  GfVector transfer_lv, omega,
    r, centrifugal_force, omega_centrifugal;
  char *str;
  gf_double mag_r, transfer_lv_mag, mag_omega, centrifugal_force_mul;
  GfVector a = this->angular_momentum.normal();

  

  if (this->moment_of_inertia == 0) {


    while(meptr!=NULL) {
      
      
      //printf ("iterating through ME:%s\n",meptr->name);
      
      
      meptr->acc = (meptr->force / meptr->mass);


      //KEY: acc_timestep (this is for MI == 0)
      //GfVector acc_timestep = meptr->acc;
      GfVector acc_timestep = (meptr->acc *  this->parent_univ->timestep);

      printf ("acc_timestep: %f\n", acc_timestep.mag());

      meptr->vel += acc_timestep;
      meptr->vel = (meptr->vel * this->bond_damping_coef);
      GFD(printf("Linear vel: %f\n", this->linear_velocity.y));
      
      //KEY: important in collision demo
      meptr->vel -= this->linear_acceleration;
      /* This transfers the linear velocity for the mass elements to
	 the the eo as a whole in effect since the eo has already added the
	 net linear velocity to itself for. */
      

      //meptr->loc = rotated_loc;
      

      //KEY (special, was turned on in previous version too): vel_timestep
      GfVector vel_timestep = (meptr->vel * this->parent_univ->timestep);
      //GfVector vel_timestep = meptr->vel;
      meptr->loc += vel_timestep;

      meptr->force=0;
      //zero_GfVector(&(meptr->acc));
      meptr=meptr->next;
    
    }
  }
  else {



    while(meptr!=NULL) {
      
      /* Begin transfer of angular momentum from individual masses to
	 extended object as a whole, also add in centrifugal pseudo
	 force to cause "spin out" of extended structures, also set up
	 distanceFromAxis member of mass_element class */

      meptr->distanceFromAxis =  meptr->loc.distanceFromAxis(a, this->center_of_mass);
      //r = (meptr->loc - this->center_of_mass);


      //KEY: transfer_lv
      GfVector torque_timestep = (this->torque * this->parent_univ->timestep);
      //GfVector torque_timestep = this->torque;
      omega = (torque_timestep / this->moment_of_inertia);
      mag_omega = omega.mag();
      transfer_lv_mag = (meptr->distanceFromAxis * mag_omega).mag();
      GFD(printf("transfer_lv_mag is %f\n",transfer_lv_mag));
      //      str = print_GfVector(meptr->distanceFromAxis);

      GFD(cout << "r is " << meptr->distanceFromAxis << endl);
      //      free(str);

      //str = print_GfVector(this->center_of_mass);
      GFD(cout << "cm is " << this->center_of_mass << endl);
    //free(str);
    //str = print_GfVector(meptr->loc);
    //GFD(printf("p is %s\n",str));
    //free(str);
      transfer_lv = (a * meptr->distanceFromAxis).normal();
      transfer_lv = (transfer_lv * transfer_lv_mag);
      meptr->vel -= transfer_lv;




      mag_r = meptr->distanceFromAxis.mag();
      centrifugal_force_mul = pow(this->angular_velocity_timestep,2);

      //KEY: Check this print statement!! Use the timestep scaled one!!
      //printf("Angular vel (rad/sec):%f\n",this->angular_velocity_timestep/this->parent_univ->timestep);
      //printf("Angular vel (rad/sec):%f\n",this->angular_velocity_timestep);


      centrifugal_force = (meptr->distanceFromAxis * centrifugal_force_mul*meptr->mass);
      meptr->force += centrifugal_force;

      /* End transfer of angular momentum code */

      GFD(printf ("iterating through ME:%s\n",meptr->name));
      
      GFD(printf ("Force is %f\n",meptr->force.mag()));


      meptr->acc = (meptr->force / meptr->mass);

      //KEY: acc_timestep (seems to have no effect)
      GfVector acc_timestep = (meptr->acc *  this->parent_univ->timestep);
      //GfVector acc_timestep = meptr->acc;

      //printf ("acc_timestep: %f, meptr->vel: %f\n", acc_timestep.mag(),(meptr->vel + this->linear_velocity)).mag();

      meptr->vel += acc_timestep;



      meptr->vel = (meptr->vel * this->bond_damping_coef);
      GFD(printf("Linear vel: %f\n", this->linear_velocity.y));


      //printf("Linear vel for me:%f\n",meptr->vel).mag();

      //KEY: important in collision demo
      meptr->vel -= this->linear_acceleration;
      /* This transfers the linear velocity for the mass elements to
	 the the eo as a whole in effect since the eo has already added the
	 net linear velocity to itself for. */

      
      meptr->loc += (meptr->vel * this->parent_univ->timestep);
      meptr->force=0;

      /* Now that we know it's relative location let's find out where
	 it really is taking spin and movement of the parent object
	 into account */

      /* Do the spin using the quaternion stuff */
      
      meptr->relativeLoc = (meptr->loc - this->center_of_mass);
      meptr->relativeLoc.quatrotVector(this->rotation_quaternion);
      meptr->loc = (meptr->relativeLoc + this->center_of_mass);

      




      //zero_GfVector(&(meptr->acc));
      meptr=meptr->next;
    
    }
  }
  //printf("eo Linear acc %f\n",this->linear_acceleration).mag();
  //printf("this->angular_momentum:%f\n",this->angular_momentum.mag());
  gf_double post_rot_mi = return_moment_of_inertia_eo();
  gf_double pre_post_ratio = this->moment_of_inertia/post_rot_mi;
  //printf("Ratio of pre to post rotation MI:%f\n",pre_post_ratio);
}




GfExtendedObject::GfExtendedObject (GfUniverse &univ,
				     gf_string name, gf_int id) 
{
  this->bfcc_const = 0;

  this->name = name;
  this->id = id;
  this->last_mass_element = NULL;
  this->first_mass_element = NULL;
  this->last_bond = NULL;
  this->first_bond = NULL;

  this->moment_of_inertia = 0;
  this->angular_velocity_timestep = 0;
  //this->angular_position_mag = 0;

  this->mass_element_count = 0;
  this->bond_count = 0;
  this->bond_damping_coef = 1;
  this->next = NULL;
 
  
 if (univ.last_extended_object) {
    this->prev = univ.last_extended_object;
    this->prev->next = this;
  }
 else {
   this->prev = NULL;
   univ.first_extended_object = this;
 }
 univ.last_extended_object = this;
 univ.extended_object_count++;
 this->parent_univ = &univ;
}
