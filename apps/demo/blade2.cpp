/* $Id: blade2.cpp 93 2008-06-21 09:07:55Z greg $ */

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




#define LV_SCALE 1

#define TM_SCALE 0.01 // How much to scale down the size of the sphere for the total mass.
#define TORQUE_SCALE 1e-5

#define AM_SCALE 1e-7
// How much to scale down the size of the cone for the angular momentum

#define EO_VECTOR_CONEBASE 10

#define LVSCALE 1 // How much to scale the cone for linear velocity

#define PUSH_FORCE 80000

#define CONE_SPREAD 150

#define Y_NUM_MASSES 10
#define X_NUM_MASSES 5

#define TIMESTEP 0.5

#define AV_THRESH 0.5*TIMESTEP
#define BFCC_CONST 1e5
#define BFCC_THRESH_DIST 30

#define MASS_ELEMENT_SCALE 0.1
#define ELEMENT_MASSES 100

#define SPRING_CONST 100

#define BOND_DAMPING_COEF .9
// Use 0.9 for stable behavior, above about 0.9 the thing blows up
// before 0.5 rad/sec

vtkvis_univ *univ_v;
GfUniverse *u;
massgrid mg;

static void iterate_world(vtkObject *vtkNotUsed( caller ),
                           unsigned long vtkNotUsed(eventId), 
                           void *sr, void *)
{
  GfMassElement *meptr = u->first_extended_object->first_mass_element;
  GfBond *bptr = u->first_extended_object->first_bond;

 u->iterate();
 update_vtkvis_univ(univ_v);


  if (u->first_extended_object->angular_velocity_timestep > AV_THRESH) {
    //vector3 prec_torq = normal_vector3(sub_vector3(mg.elements[(gf_int)floor(Y_NUM_MASSES*X_NUM_MASSES-1)]->loc,mg.elements[(gf_int)floor(Y_NUM_MASSES-1)]->loc));
    //prec_torq = mul_by_scalar_vector3(prec_torq,1000000);
    //addto_vector3(&u->first_extended_object->angular_momentum,prec_torq);
    for (gf_int i=0;i<X_NUM_MASSES;i++) {
      
      mg.elements[(gf_int)floor(Y_NUM_MASSES*i)]->force += u->first_extended_object->rotation_axis * PUSH_FORCE*.01; 
    }
    
  }
  else if (u->first_extended_object->rotation_axis == 0) {
    mg.elements[(gf_int)floor(Y_NUM_MASSES*2)]->force.x += PUSH_FORCE*.000001;    
  }
  else {
    mg.elements[(gf_int)floor(Y_NUM_MASSES*2)]->force += make_tangential_force(mg.elements[(gf_int)floor(Y_NUM_MASSES*2)],u->first_extended_object, PUSH_FORCE*.05 );
  }


 
  //  update_graphics();
}





int main (int argc, char **argv)
{
  massgrid mg2;
  u = new GfUniverse();  
  //linktest();
  u->timestep = TIMESTEP;  

  u->max_allowed_acc = 10;
  u->max_allowed_timestep = TIMESTEP;
  //u->timestep_autoscaling = GF_TRUE;

  GfVector zerovec, v1, v2;
  GfMassElement *meptr;
  GfBond *bnd1,*bnd2,*bnd3;
  GfBond *bptr;
  zerovec.x = 0;
  zerovec.y = 0;
  zerovec.z = 0;
  v1.x = 100;
  v1.y = 143;
  v1.z = 435;

  v2.x = -150;
  v2.y = 143;
  v2.z = 300;

  int i;

  GfExtendedObject *eo = new GfExtendedObject(*u,"eo1",100);
  eo->bfcc_const = BFCC_CONST;
  eo->bfcc_thresh_dist = BFCC_THRESH_DIST;
  //GfExtendedObject *eo2 = new GfExtendedObject(u,"eo2",101);

  u->first_extended_object->bond_damping_coef = BOND_DAMPING_COEF;

  mg = make_massgrid(100, 200, ELEMENT_MASSES, X_NUM_MASSES,
			      Y_NUM_MASSES, SPRING_CONST, 300, 30, u->first_extended_object); 

  GfVector vel = zerovec;
  vel.x = 50;

  for (gf_int i=0;i<Y_NUM_MASSES;i++) {
    mg.elements[i]->vel = vel;
  }


  //  mg2 = make_massgrid(75, 50, 10, X_NUM_MASSES-3,
  //	     Y_NUM_MASSES-2, 10, 300, 700, u->first_extended_object->next); 
  
  //massgrid mg2 = make_massgrid(100, 300, 10, 5,10, 10, 300, 10, u->first_extended_object); 
  //for (i=0;i<50;i++) {
  //    (mg.elements[i])->vel.y=0;
  //}

  //(mg2.elements[(gf_int)floor(Y_NUM_MASSES/4)])->force.x=PUSH_FORCE/10;  
  
  //(mg.elements[(gf_int)floor(Y_NUM_MASSES/4)])->force.x=PUSH_FORCE;
  
  //  (mg.elements[Y_NUM_MASSES])->force.x=PUSH_FORCE;


  //(mg.elements[1])->vel.z=1000;
  //(mg.elements[49])->vel.x=-1000;

  //(mg.elements[49])->force.z=100;
  
  meptr = u->first_extended_object->first_mass_element;
  bptr = u->first_extended_object->first_bond;


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
  sf->mass_element_scale = MASS_ELEMENT_SCALE;
  sf->eo_vector_conebase = EO_VECTOR_CONEBASE;
  sf->cone_spread = CONE_SPREAD;
  sf->lv_scale = LV_SCALE;
  sf->tm_scale = TM_SCALE;
  //compute_center_of_mass_eo(u->first_extended_object);
  univ_v = new_vtkvis_univ(u,ren1,*sf);
  free(sf);


  
  

  renWin->SetSize(800,800);
  // render an image (lights and cameras are created automatically)
  renWin->Render();

  // begin mouse interaction
  iren->Start();

  return 0;
}
