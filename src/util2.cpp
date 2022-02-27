/* $Id: util2.cpp 93 2008-06-21 09:07:55Z greg $ */

#include "gftypes.h"
#include "util2.h"
#include "gforce.h"

#ifdef __cplusplus
extern "C" {
#endif


GfVector make_tangential_force(GfMassElement *me, GfExtendedObject *eo, gf_double mag) {
  /* Given a mass_element and an eo and a magnitude, create a force
vector that is always tangential to the current rotation.  If mag is
negative the force will oppose the rotation, if positive, it will
amplify it */
  GfVector unit_force = (eo->rotation_axis * me->relativeLoc).normal();
  return unit_force * mag;
}
 
ring make_cylinder(gf_int num_sections, gf_double rad, gf_double width, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo) {
  /* Makes a short cylinder */
  ring r;
  gf_double arc = TWOPI/num_sections;
  gf_double me_mass = mass/(num_sections*2);
  gf_double angle = 0;
  GfVector loco,loci,zv;
  GfMassElement **outer_masses = (GfMassElement **)malloc(sizeof(GfMassElement *)*num_sections);
  GfMassElement **inner_masses = (GfMassElement **)malloc(sizeof(GfMassElement *)*num_sections);
  gf_int i,j;
  zv.x = 0;
  zv.y = 0;
  zv.z = 0;
  r.outer_masses = outer_masses;
  r.inner_masses = inner_masses;

  j = 0;
  for (i=0;i<num_sections;i++) {
    loco.x = rad * cos(angle);
    loco.y = rad * sin(angle);
    loco.z = zplane;
    angle+=arc;
    outer_masses[j++] = new GfMassElement(*eo,loco,zv,zv,me_mass,temp,"RING_OUTER",0);
  }
  j = 0;
  angle = 0;
  for (i=0;i<num_sections;i++) {
    loci.x = rad * cos(angle);
    loci.y = rad * sin(angle);
    loci.z = zplane+width;
    angle+=arc;
    inner_masses[j++] = new GfMassElement(*eo,loci,zv,zv,me_mass,temp,"RING_INNER",0);
  }

  for (i=0;i<num_sections-1;i++) {
    new GfBond(*eo,*outer_masses[i] ,*outer_masses[i+1] ,temp, spring_constant, "BOND_OUTER",0);
    new GfBond(*eo,*inner_masses[i] ,*inner_masses[i+1] ,temp, spring_constant, "BOND_INNER",0);
    new GfBond(*eo,*outer_masses[i] ,*inner_masses[i] ,temp, spring_constant, "SPOKE",0);
    new GfBond(*eo,*outer_masses[i] ,*inner_masses[i+1] ,temp, spring_constant, "DIAG",0);
    new GfBond(*eo,*inner_masses[i] ,*outer_masses[i+1] ,temp, spring_constant, "DIAG",0);
  }

  new GfBond(*eo,*outer_masses[num_sections-1],*outer_masses[0] ,temp, spring_constant, "BOND_OUTER",0);
  new GfBond(*eo,*inner_masses[num_sections-1],*inner_masses[0] ,temp, spring_constant, "BOND_INNER",0);
  new GfBond(*eo,*outer_masses[num_sections-1] ,*inner_masses[0] ,temp, spring_constant, "BOND_OUTER",0);
  new GfBond(*eo,*inner_masses[num_sections-1] ,*outer_masses[0] ,temp, spring_constant, "BOND_INNER",0);
  new GfBond(*eo,*outer_masses[num_sections-1] ,*inner_masses[num_sections-1] ,temp, spring_constant, "SPOKE",0);
  return r;

}



ring make_ring(gf_int num_sections, gf_double outer_r, gf_double inner_r, gf_double mass, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo) {
  /* Makes a ring with two rings of interconnected masses */
  ring r;
  gf_double arc = TWOPI/num_sections;
  gf_double me_mass = mass/(num_sections*2);
  gf_double angle = 0;
  GfVector loco,loci,zv;
  GfMassElement **outer_masses = (GfMassElement **)malloc(sizeof(GfMassElement *)*num_sections);
  GfMassElement **inner_masses = (GfMassElement **)malloc(sizeof(GfMassElement *)*num_sections);
  gf_int i,j;
  zv.x = 0;
  zv.y = 0;
  zv.z = 0;
  r.outer_masses = outer_masses;
  r.inner_masses = inner_masses;

  j = 0;
  for (i=0;i<num_sections;i++) {
    loco.x = outer_r * cos(angle);
    loco.y = outer_r * sin(angle);
    loco.z = zplane;
    angle+=arc;
    outer_masses[j++] = new GfMassElement(*eo,loco,zv,zv,me_mass,temp,"RING_OUTER",0);
  }
  j = 0;
  angle = 0;
  for (i=0;i<num_sections;i++) {
    loci.x = inner_r * cos(angle);
    loci.y = inner_r * sin(angle);
    loci.z = zplane;
    angle+=arc;
    inner_masses[j++] = new GfMassElement(*eo,loci,zv,zv,me_mass,temp,"RING_INNER",0);
  }

  for (i=0;i<num_sections-1;i++) {
    new GfBond(*eo,*outer_masses[i] ,*outer_masses[i+1] ,temp, spring_constant, "BOND_OUTER",0);
    new GfBond(*eo,*inner_masses[i] ,*inner_masses[i+1] ,temp, spring_constant, "BOND_INNER",0);
    new GfBond(*eo,*outer_masses[i] ,*inner_masses[i] ,temp, spring_constant, "SPOKE",0);
    new GfBond(*eo,*outer_masses[i] ,*inner_masses[i+1] ,temp, spring_constant, "DIAG",0);
    new GfBond(*eo,*inner_masses[i] ,*outer_masses[i+1] ,temp, spring_constant, "DIAG",0);
  }

  new GfBond(*eo,*outer_masses[num_sections-1],*outer_masses[0] ,temp, spring_constant, "BOND_OUTER",0);
  new GfBond(*eo,*inner_masses[num_sections-1],*inner_masses[0] ,temp, spring_constant, "BOND_INNER",0);
  new GfBond(*eo,*outer_masses[num_sections-1] ,*inner_masses[0] ,temp, spring_constant, "BOND_OUTER",0);
  new GfBond(*eo,*inner_masses[num_sections-1] ,*outer_masses[0] ,temp, spring_constant, "BOND_INNER",0);
  new GfBond(*eo,*outer_masses[num_sections-1] ,*inner_masses[num_sections-1] ,temp, spring_constant, "SPOKE",0);
  return r;

}

massgrid make_massgrid(gf_double xspacing, gf_double yspacing, gf_double mass, gf_int x_num_masses, gf_int y_num_masses, gf_double spring_constant, gf_double temp, gf_double zplane, GfExtendedObject *eo) {
  gf_int x,y,num_bonds;
  massgrid mg;
  GfMassElement *meptr;
  GfBond *bptr;
  GfVector zv;
  GfVector loc;
  gf_double xpos, ypos;
  gf_int i = 0;
  zv.x = 0;
  zv.y = 0;
  zv.z = 0;
  loc.x = 0;
  loc.z = zplane;
  num_bonds = (x_num_masses-1)*y_num_masses+(y_num_masses-1)*x_num_masses
    + 2*(x_num_masses-1)*(y_num_masses-1);
  mg.elements = (GfMassElement **)malloc(sizeof(GfMassElement *)*x_num_masses*y_num_masses);
  mg.bonds = (GfBond **)malloc(sizeof(GfBond *)*num_bonds);
  for (x=0;x<x_num_masses;x++) {
    loc.y = 0;
    
    for (y=0;y<y_num_masses;y++) {
      mg.elements[i++] = new GfMassElement(*eo,loc,zv,zv,mass,temp,"FIXME",0);
      loc.y+=yspacing;
    }
    loc.x+=xspacing;
  }
  i=0;
  for (x=1;x<x_num_masses;x++) {
    for (y=0;y<y_num_masses;y++) {
      mg.bonds[i++] = new GfBond(*eo, *mg.elements[(x-1)*y_num_masses+y], *mg.elements[x*y_num_masses+y],temp, spring_constant, "FIXME",0);
    }

  }

  for (x=0;x<x_num_masses;x++) {
    for (y=1;y<y_num_masses;y++) {
      mg.bonds[i++] = new GfBond(*eo,* mg.elements[x*y_num_masses+y-1],* mg.elements[x*y_num_masses+y],temp, spring_constant, "FIXME",0);
    }

  }
  for (x=0;x<x_num_masses-1;x++) {
    for (y=1;y<y_num_masses;y++) {
      mg.bonds[i++] = new GfBond(*eo,* mg.elements[x*y_num_masses+y],* mg.elements[(x+1)*y_num_masses+y-1],temp, spring_constant, "FIXME",0);
    }

  }
  for (x=0;x<x_num_masses-1;x++) {
    for (y=0;y<y_num_masses-1;y++) {
      mg.bonds[i++] = new GfBond(*eo,* mg.elements[x*y_num_masses+y],* mg.elements[(x+1)*y_num_masses+y+1],temp, spring_constant, "FIXME",0);
    }

  }
  return mg;
}
  
#ifdef __cplusplus
}
#endif
