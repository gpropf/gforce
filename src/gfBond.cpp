// $Id: gfBond.cpp 96 2008-07-05 10:17:05Z greg $

#include "gfBond.h"


GfBond::GfBond (GfExtendedObject &eo, GfMassElement &a,
		GfMassElement &b, const gf_double temp,
		const gf_double spring_constant, const gf_string name,
		const gf_int id)
{

  this->a = &a;
  this->b = &b;
  this->proper_length = (a.loc-b.loc).mag();
  this->temp = temp;
  this->spring_constant = spring_constant;
  this->name = name;
  this->id = id;
  this->next = NULL;

  eo.bond_count++;
  if (eo.last_bond) {
    this->prev = eo.last_bond;
    (this->prev)->next = this;
  }
  else {
    eo.first_bond = this;
    this->prev = NULL;
  }    
  eo.last_bond = this;
}


