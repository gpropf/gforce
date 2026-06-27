/* $Id: gfvtktypes.h 60 2008-05-23 07:00:03Z greg $ */

#ifndef __gfvtktypes_h
#define __gfvtktypes_h




#include "config.h"
#include "gftypes.h"

// #include "vtkTextActor.h"
// #include "vtkTextProperty.h"
// // #include "vtkProperty.h"
// #include "vtkSphereSource.h"
// #include "vtkConeSource.h"
// #include "vtkPolyDataMapper.h"
// #include "vtkActor.h"
// #include "vtkRenderWindow.h"
// #include "vtkRenderer.h"
// #include "vtkRenderWindowInteractor.h"
// #include "vtkCallbackCommand.h"


struct vtkvis_scaling_factors {
  gf_double tm_scale;
  gf_double am_scale;
  gf_double lv_scale;
  gf_double torque_scale;
  gf_double cone_spread;
  gf_double mass_element_scale;
  gf_double eo_vector_conebase;
};

typedef vtkvis_scaling_factors vtkvis_scaling_factors;






struct vtkvis_eo {
  


  vtkSphereSource **spheres;
  vtkConeSource **cones;
  vtkConeSource *torque_cone; // Special cone for the torque
  vtkConeSource *am_cone; // Special cone for the angular_momentum
  vtkConeSource *lv_cone; // Special cone for the linear velocity;
  vtkSphereSource *cm_sphere; // Special sphere for center of mass
  gf_double torque_scale;
  gf_double cone_spread;
  gf_double am_scale;
  gf_double lv_scale;
  gf_double tm_scale;
  gf_double mass_element_scale;
  gf_double eo_vector_conebase;

  gf_bool show_cm_sphere;
  gf_bool show_torque_cone;
  gf_bool show_lv_cone;
  gf_bool show_am_cone;

  
  struct vtkvis_eo *next;
  struct vtkvis_eo *prev;
  struct vtkvis_univ *parent_vtkvis_univ;
  extended_object *eo;
};



typedef struct vtkvis_eo vtkvis_eo;

struct vtkvis_univ {
  universe *univ;
  vtkTextActor *clock; // The clock readout
  gf_double mass_element_scale;
  vtkvis_eo *first_vtkvis_eo;
  vtkvis_eo *last_vtkvis_eo;
};

typedef struct vtkvis_univ vtkvis_univ;







  


#endif
