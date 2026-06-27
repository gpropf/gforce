/* $Id: ring2.cpp 93 2008-06-21 09:07:55Z greg $ */

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
#define TORQUE_SCALE 1e-1

#define AM_SCALE 1e-1
// How much to scale down the size of the cone for the angular momentum


#define LVSCALE 10 // How much to scale the cone for linear velocity

#define PUSH_FORCE 0.1

#define CONE_SPREAD 0.5

#define RING_SECTIONS 25
#define OUTER_RING_RADIUS 1
#define INNER_RING_RADIUS 0.8

#define ATTR_STRENGTH  -0.3
#define BFCC_CONST 0 //1e-4


#define TIMESTEP 0.005

#define X_NUM_MASSES 10
#define Y_NUM_MASSES 10


#define RING_MASS 4
#define SPRING_CONST 10

#define MASS_ELEMENT_SCALE 0.5
#define AV_THRESH 10*TIMESTEP


vtkvis_univ *univ_v;
GfUniverse *u;
massgrid mg;
ring r;


GfVector attractor_loc;





static void iterate_world(vtkObject *vtkNotUsed( caller ),
                           unsigned long vtkNotUsed(eventId), 
                           void *sr, void *)
{
  GfMassElement *meptr = u->first_extended_object->first_mass_element;
  GfBond *bptr = u->first_extended_object->first_bond;


  if (u->first_extended_object->angular_velocity_timestep > AV_THRESH) {
    for (gf_int i=0;i<RING_SECTIONS;i++) {

      GfVector distance_to_attractor = attractor_loc - r.outer_masses[i]->loc;
      gf_double distance_to_attractor_mag = distance_to_attractor.mag();
      gf_double attraction_force_mag = ATTR_STRENGTH / pow(distance_to_attractor_mag,3);
      GfVector attraction_force = distance_to_attractor * attraction_force_mag;
      r.outer_masses[i]->force += attraction_force; 
      r.inner_masses[i]->force += attraction_force; 
    }

    /*
    GfBond *bptr = u->first_extended_object->first_bond;
    while (bptr!=NULL) {
      bptr->proper_length = bptr->proper_length *.9;
      bptr = bptr->next;
    }
    */

  }
    
  
  else if (u->first_extended_object->rotation_axis == 0) {
   
  }
  else {
    for (gf_int i=0;i<RING_SECTIONS;i++) {
      r.outer_masses[i]->force += make_tangential_force(r.outer_masses[i],u->first_extended_object, PUSH_FORCE );
      r.inner_masses[i]->force += make_tangential_force(r.inner_masses[i],u->first_extended_object, PUSH_FORCE );
    }

    //vector3 f = make_tangential_force(r.inner_masses[0],u->first_extended_object, PUSH_FORCE*.015 );

    //printf("Force is %f\n",mag_vector3(f));

  }

 u->iterate();
 update_vtkvis_univ(univ_v);
 
  //  update_graphics();
}





int main (int argc, char **argv)
{
  
  attractor_loc.x = 0;
  attractor_loc.y = OUTER_RING_RADIUS;
  attractor_loc.z = 0.3;
  
  /*
  attractor_loc.x = 0;
  attractor_loc.y = 0;
  attractor_loc.z = 0;
  */
  massgrid mg2;
  u = new GfUniverse();  
 
  u->timestep = TIMESTEP;  

  u->max_allowed_acc = 0.001;
  u->max_allowed_timestep = TIMESTEP;
  //  u->timestep_autoscaling = GF_TRUE;

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

  //GfExtendedObject *eo2 = new GfExtendedObject(*u,"eo2",101);

  u->first_extended_object->bond_damping_coef = .9;


  r = make_ring(RING_SECTIONS, OUTER_RING_RADIUS, INNER_RING_RADIUS, RING_MASS, SPRING_CONST, 300, 0, eo);


   
  //massgrid mg2 = make_massgrid(100, 300, 10, 5,10, 10, 300, 10, u->first_extended_object); 
 
  r.outer_masses[20]->force.x=PUSH_FORCE*0.001;
  
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
  //compute_center_of_mass_eo(u->first_extended_object);
  univ_v = new_vtkvis_univ(u,ren1,*sf);
  free(sf);

 // BEGIN: Attractor sphere
  vtkSphereSource *attractor_sphere;
  attractor_sphere = vtkSphereSource::New();
  //attractor_sphere->SetRadius(fabs(log(ATTR_STRENGTH)*3));
  attractor_sphere->SetRadius(log(ceil(fabs(ATTR_STRENGTH))*2)/10);
  attractor_sphere->SetThetaResolution(18);
  attractor_sphere->SetPhiResolution(18);
  attractor_sphere->SetCenter(attractor_loc.x,attractor_loc.y,attractor_loc.z);
  // map to graphics library
  vtkPolyDataMapper *attr_map = vtkPolyDataMapper::New();
  attr_map->SetInput(attractor_sphere->GetOutput());
  
  // actor coordinates geometry, properties, transformation
  vtkActor *attr_actor = vtkActor::New();
  attr_actor->SetMapper(attr_map);
  if (ATTR_STRENGTH >0) {
    attr_actor->GetProperty()->SetColor(1,1,0); 
  }
  else {
    attr_actor->GetProperty()->SetColor(0,1,1); 
  }

  // add the actor to the scene
  
  

  ren1->AddActor(attr_actor);

  // END: Attractor sphere














 

  renWin->SetSize(800,800);
  // render an image (lights and cameras are created automatically)
  renWin->Render();

  // begin mouse interaction
  iren->Start();

  return 0;
}
