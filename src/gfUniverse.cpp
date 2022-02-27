#include "gftypes.h"



#include "gfMassElement.h"
#include "gfExtendedObject.h"
#include "gfUniverse.h"



void GfUniverse::iterate() {
  gf_double ap_by_twopi;

  this->time+=this->timestep; /* tick-tock */

  GfExtendedObject *eoptr = this->first_extended_object;
  while(eoptr!=NULL) {
    //printf("Timestep:%f, max_acc: %f\n",this->timestep,this->max_acc);
    eoptr->iterate();
    if (this->timestep_autoscaling)
      this->compute_timestep_univ();
    eoptr = eoptr->next;
  }
}

void GfUniverse::compute_timestep_univ() {

  GfMassElement *meptr;
  GfExtendedObject *eoptr = this->first_extended_object;
  GfVector mag_force;
  gf_double mag_acc;

  this->max_acc = 0;

  while (eoptr!=NULL) {
    meptr = eoptr->first_mass_element;
    while(meptr!=NULL) {
      mag_acc = meptr->acc.mag();
	if (mag_acc > this->max_acc) {
	  this->max_acc = mag_acc;
	}
	meptr = meptr->next;
    }
    eoptr = eoptr->next;

  }
	
  if (this->max_acc != 0) {
    this->timestep = this->max_allowed_acc/this->max_acc;
    if (this->timestep > this->max_allowed_timestep) {
      this->timestep = this->max_allowed_timestep;
    }
  }
}




using namespace std;

GfUniverse::GfUniverse() 
{
  this->extended_object_count = 0;
  this->first_extended_object = NULL;
  this->last_extended_object = NULL;
  this->G = G_CONST;
  this->timestep = 1;
  this->max_allowed_timestep = 1;
  this->timestep_autoscaling = GF_FALSE;
  this->max_acc = 0;
  this->max_allowed_acc = 10; // 10m/s^2 about 1g, hopefully this will be set.

}
