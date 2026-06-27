/* $Id: gfvtk.h 60 2008-05-23 07:00:03Z greg $ */
#ifndef __gfvtk_h
#define __gfvtk_h

#include "gfvtktypes.h"




#ifdef __cplusplus
extern "C" {
#endif

  void linktest(void);

  vtkvis_eo *new_vtkvis_eo(extended_object *eo,vtkRenderer *ren1,
			   vtkvis_univ *vtkvis_univ, vtkvis_scaling_factors sf);
  vtkvis_univ *new_vtkvis_univ(universe *univ, vtkRenderer *ren1, vtkvis_scaling_factors sf);

  void setup_info_display(vtkRenderer *ren,
			  vtkvis_univ * univ_v);

  void update_vtkvis_eo(vtkvis_eo *eov);
  void update_vtkvis_univ (vtkvis_univ *univ_v);


  vtkvis_scaling_factors *new_vtkvis_scaling_factors(void);
    

  void set_scaling_factors_vtkvis_univ(vtkvis_univ *univ_v, gf_double tm_scale,
				       gf_double am_scale, gf_double lv_scale,
				       gf_double torque_scale,
				       gf_double cone_spread,
				       gf_double mass_element_scale);


  void set_scaling_factors_eo(vtkvis_eo *eov, gf_double tm_scale,
			      gf_double am_scale, gf_double lv_scale,
			      gf_double torque_scale, gf_double cone_spread,
			      gf_double mass_element_scale);
       



  
#ifdef __cplusplus
}
#endif 

#endif
