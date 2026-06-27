// $Id: gfBond.h 93 2008-06-21 09:07:55Z greg $

#ifndef GFBOND_H
#define GFBOND_H

#include <iostream>
#include "gftypes.h"

#include "gfMassElement.h"
#include "gfExtendedObject.h"

using namespace std;

class GfBond 
{
 public:
    GfMassElement *a;
    GfMassElement *b;
    gf_double proper_length;
    gf_double temp;
    gf_double spring_constant;
    gf_string name;
    gf_int id;
    GfBond *next;
    GfBond *prev;


    GfBond (GfExtendedObject &eo, GfMassElement &a,
	    GfMassElement &b, const gf_double temp,
	    const gf_double spring_constant, const gf_string name,
	    const gf_int id);


  };

#endif
