/* $Id: gfvtk2.h 97 2008-07-08 10:19:39Z greg $ */
#ifndef __gfvtk2_h
#define __gfvtk2_h

#include "gfvtktypes2.h"

class Foo {
public:
  void testvtk(vtkRenderer *ren1);
};

#ifdef __cplusplus
extern "C" {
#endif

  void linktest(void);

  void swigtestPtr(GfUniverse *u);

  void swigtestValue(GfUniverse u);


  void swigtestRef(GfUniverse &u);


  vtkvis_eo *new_vtkvis_eo(GfExtendedObject *eo,vtkRenderer *ren1,
			   vtkvis_univ *vtkvis_univ, vtkvis_scaling_factors sf);
  vtkvis_univ *new_vtkvis_univ(GfUniverse *univ, vtkRenderer *ren1, vtkvis_scaling_factors sf);

  vtkvis_univ *wnew_vtkvis_univ(GfUniverse *univ, vtkOpenGLRenderer *ren1, vtkvis_scaling_factors sf);

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
