

#include "gfExtendedObject.h"
#include "gfMassElement.h"

GfMassElement::GfMassElement(GfExtendedObject &eo, GfVector loc,
		   GfVector vel, GfVector acc, gf_double mass,
		   gf_double temp, gf_string name, gf_int id)
{
  this->loc = loc;
  this->vel = vel;
  this->acc = acc;
  this->mass = mass;
  this->temp = temp;
  this->name = name;
  this->id = id;
  this->next = NULL;

  eo.mass_element_count++;
  if (eo.last_mass_element) {
    this->prev = eo.last_mass_element;
    (this->prev)->next = this;
  }
  else {
    eo.first_mass_element = this;
    this->prev = NULL;
  }    
  eo.last_mass_element = this;
}
