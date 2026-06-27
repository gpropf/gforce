/* $Id: collision2.cpp 93 2008-06-21 09:07:55Z greg $ */

// // #include "vtkProperty.h"
// #include "vtkSphereSource.h"
// #include "vtkConeSource.h"
// #include "vtkPolyDataMapper.h"
// #include "vtkActor.h"
// #include "vtkRenderWindow.h"
// #include "vtkRenderer.h"
// #include "vtkRenderWindowInteractor.h"
// #include "vtkCallbackCommand.h"

// #include "gfvtk2.h"
#include "gftypes.h"
#include "gforce.h"
#include "util2.h"

#include "gfMassElement.h"
#include "gfExtendedObject.h"
#include "gfUniverse.h"
#include "gfBond.h"



#define TMSCALE 0.05 // How much to scale down the size of the sphere for the total mass.
#define TORQUE_SCALE 1e-2

#define AM_SCALE 1e-2
// How much to scale down the size of the cone for the angular momentum


#define LVSCALE 10 // How much to scale the cone for linear velocity

#define DISPLAY_VECTORS GF_FALSE

#define RING_SEPARATION 3
#define RING_WIDTH 0.25

#define CONE_SPREAD 0.5

#define RING_SECTIONS 25
#define OUTER_RING_RADIUS 1
#define INNER_RING_RADIUS 0.8

#define ATTR_STRENGTH  -0.001
#define BFCC_CONST 1e-1 // 1e0 works with MAX_ALLOWED_ACC = 0.1
#define BFCC_THRESH_DIST 0.2


#define TIMESTEP 0.15
#define MAX_ALLOWED_ACC 0.1 // 0.1 produces very high quality results.

#define X_NUM_MASSES 10
#define Y_NUM_MASSES 10


#define RING_MASS 4
#define SPRING_CONST 10

#define PUSH_FORCE (9.81*RING_MASS/(2*RING_SECTIONS))


#define MASS_ELEMENT_SCALE 0.5
#define AV_THRESH 30*TIMESTEP


vtkvis_univ *univ_v;
GfUniverse *u;
massgrid mg;
ring r1,r2,r3;


GfVector attractor_loc;





static void iterate_world(vtkObject *vtkNotUsed( caller ),
                           unsigned long vtkNotUsed(eventId), 
                           void *sr, void *)
{
  GfMassElement *meptr = u->first_extended_object->first_mass_element;
  GfBond *bptr = u->first_extended_object->first_bond;

  //r2.outer_masses[RING_SECTIONS-1]->force.x=-PUSH_FORCE*0.1;
  //r2.outer_masses[RING_SECTIONS-1]->force.z=PUSH_FORCE*0.1;
  //r2.outer_masses[(gf_int)floor(RING_SECTIONS/2)]->force.z=-PUSH_FORCE*0.1;
  if (u->time < 2) {
  for (gf_int i=0;i<RING_SECTIONS;i++) {
    r2.outer_masses[i]->force.x=-PUSH_FORCE;
    r2.inner_masses[i]->force.x=-PUSH_FORCE;
     
  }
  }
  printf("Ring acc: %f\n",r2.outer_masses[0]->acc.mag());
  printf("Ring vel: %f\n",r2.outer_masses[0]->vel.mag());
  u->iterate();
  update_vtkvis_univ(univ_v);
 
  //  update_graphics();
}





int main (int argc, char **argv)
{
  
  attractor_loc.x = 0;
  attractor_loc.y = OUTER_RING_RADIUS;
  attractor_loc.z = 0.5;
  
  /*
  attractor_loc.x = 0;
  attractor_loc.y = 0;
  attractor_loc.z = 0;
  */
  massgrid mg2;
  u = new GfUniverse();  
 
  u->timestep = TIMESTEP;  

  u->max_allowed_acc = MAX_ALLOWED_ACC;
  u->max_allowed_timestep = TIMESTEP;
  u->timestep_autoscaling = GF_TRUE;


  GfVector zerovec;
  GfMassElement *meptr;
  GfBond *bnd1,*bnd2,*bnd3;
  GfBond *bptr;
  zerovec.x = 0;
  zerovec.y = 0;
  zerovec.z = 0;


  int i;

  GfExtendedObject *eo = new GfExtendedObject(*u,"eo1",100);

  eo->bfcc_const = BFCC_CONST;
  eo->bfcc_thresh_dist = BFCC_THRESH_DIST;

  //GfExtendedObject *eo2 = new_extended_object(u,"eo2",101);

  //GfExtendedObject *eo3 = new_extended_object(u,"billiards",102);

  u->first_extended_object->bond_damping_coef = .9;


 

  //r3 = make_ring(RING_SECTIONS, OUTER_RING_RADIUS, INNER_RING_RADIUS, RING_MASS, SPRING_CONST, 300, RING_SEPARATION-0.1, eo);


  r1 = make_cylinder(RING_SECTIONS, OUTER_RING_RADIUS, RING_WIDTH, RING_MASS, SPRING_CONST, 300, RING_SEPARATION, eo);

  
  for (gf_int i=0;i<RING_SECTIONS;i++) {
    r1.outer_masses[i]->loc.x-=RING_SEPARATION;
    r1.inner_masses[i]->loc.x-=RING_SEPARATION;
    r1.outer_masses[i]->loc.z-=RING_WIDTH/2;
    r1.inner_masses[i]->loc.z-=RING_WIDTH/2;
    r1.outer_masses[i]->vel.x=1;
    r1.inner_masses[i]->vel.x=1;
    r1.outer_masses[i]->vel.z=1.4;
    r1.inner_masses[i]->vel.z=1.4;
  }
  
  /*
  gf_int half_ring_sec = (gf_int)floor(RING_SECTIONS/2);
  for (gf_int i=0;i<half_ring_sec;i++) {

    new_bond(eo, r1.outer_masses[i],r1.outer_masses[i+half_ring_sec],300, SPRING_CONST, "FIXME",0);
    new_bond(eo, r1.inner_masses[i],r1.outer_masses[i+half_ring_sec],300, SPRING_CONST, "FIXME",0);

  }
  */
  r2 = make_cylinder(RING_SECTIONS, OUTER_RING_RADIUS, RING_WIDTH, RING_MASS, SPRING_CONST, 300, RING_SEPARATION, eo);


  //mg = make_massgrid(0.2, 0.2, RING_MASS/(X_NUM_MASSES*Y_NUM_MASSES),
  //		     X_NUM_MASSES,
  //		     Y_NUM_MASSES, SPRING_CONST, 300, 4, eo); 


   
  //massgrid mg2 = make_massgrid(100, 300, 10, 5,10, 10, 300, 10, u->first_extended_object); 
 
  //r.outer_masses[20]->force.x=PUSH_FORCE*0.001;
  r2.outer_masses[RING_SECTIONS-1]->force.x=-PUSH_FORCE;


  r2.outer_masses[(gf_int)floor(RING_SECTIONS/2)]->force.x=PUSH_FORCE;
  meptr = u->first_extended_object->first_mass_element;
  bptr = u->first_extended_object->first_bond;

  GfVector xv,b1loc,b2loc,b1acc,b2acc;


  b2loc = zerovec;

  b2loc.z = 10;
  b2loc.x = 1;
  b1loc = b2loc;
  b1loc.x = -1;
  b2acc.x = -1;
  b1acc.x = 1;

 //  GfMassElement *b1 =  new_mass_element(eo, b1loc,zerovec,
// 				       b1acc, 0.5,300, "Stationary Ball", 0);


//   GfMassElement *b2 =  new_mass_element(eo, b2loc,zerovec,
// 				       zerovec, 0.3,300, "Moving Ball", 0);


//   b1->force.x = 1;
//   b2->force.x = -1;



  while (meptr) {
    //print_mass_element(meptr);
    meptr = meptr->next;
  }


  while (bptr) {
    //print_bond(bptr);
    bptr = bptr->next;
  }
  
  
  //  print_bond(bnd1);


  // a renderer and render window
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);

  // an interactor
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  ren1->SetBackground(0.3,0.3,0.3); // Background color white

  vtkCallbackCommand *cbc = vtkCallbackCommand::New();
  cbc->SetCallback(iterate_world);
//cbc->SetClientData((void *)source1);
  iren->AddObserver(vtkCommand::KeyPressEvent,cbc);
  cbc->Delete();

  //  init_graphics(ren1);

  vtkvis_scaling_factors *sf = new_vtkvis_scaling_factors();
  sf->am_scale = AM_SCALE;
  sf->torque_scale = TORQUE_SCALE;
  //compute_center_of_mass_eo(u->first_extended_object);
  univ_v = new_vtkvis_univ(u,ren1,*sf);
  free(sf);
  
  if (DISPLAY_VECTORS == GF_FALSE) {
    univ_v->first_vtkvis_eo->show_cm_sphere = GF_FALSE;
    univ_v->first_vtkvis_eo->show_lv_cone = GF_FALSE;
    univ_v->first_vtkvis_eo->show_am_cone = GF_FALSE;
    univ_v->first_vtkvis_eo->show_torque_cone = GF_FALSE;
  }
  
  
  

  













 

  renWin->SetSize(800,800);
  // render an image (lights and cameras are created automatically)
  renWin->Render();

  // begin mouse interaction
  iren->Start();

  return 0;
}
