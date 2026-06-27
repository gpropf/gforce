/* $Id: gfvtk2.cpp 97 2008-07-08 10:19:39Z greg $ */


#include "gfvtktypes2.h"
#include "gforce.h"
// #include "gfvtk2.h"

void Foo::testvtk(vtkRenderer *ren1)
{
  printf ("testvtk works!\n");
}



#ifdef __cplusplus
extern "C" {
#endif

  void swigtestPtr(GfUniverse *u) {
    printf ("SWIG universe pointer!\n");
  }

  void swigtestValue(GfUniverse u) {
    printf ("SWIG universe value!\n");
  }

  void swigtestRef(GfUniverse &u) {
    printf ("SWIG universe reference!\n");
  }

  void linktest(void) {
    printf("I am linktest, I do nothing!\n");
  }


  vtkvis_scaling_factors *new_vtkvis_scaling_factors(void) {
    vtkvis_scaling_factors *sf = (vtkvis_scaling_factors *)malloc(sizeof(vtkvis_scaling_factors));

    /* A bunch of "sane" scaling factors mostly taken from the ring demo, should work for objects of human scale (a few meters) and total masses of a few kilograms. */

    sf->tm_scale = 0.05;
    sf->am_scale = 0.5;
    sf->lv_scale = 10;
    sf->torque_scale = 10;
    sf->cone_spread = 0.5;
    sf->mass_element_scale = 0.5;
    sf->eo_vector_conebase = 0.1;
    return sf;
  }




  void position_cone(vtkConeSource *c, GfBond *bptr) {
    GfVector direction = bptr->b->loc - bptr->a->loc;
    GfVector center = (bptr->a->loc + (direction / 2));

    c->SetHeight(direction.mag());
    c->SetResolution(10);
    c->SetCenter(center.x, center.y, center.z);
    c->SetDirection(direction.x, direction.y, direction.z);
  }


  void setup_info_display(vtkRenderer *ren,
			  vtkvis_univ * univ_v) {

    /* Create a scaled text actor. 
       Set the text, font, justification, and properties (bold, italics,
       etc.).*/

    univ_v->clock = vtkTextActor::New();
    //univ_v->clock->ScaledTextOn();
    univ_v->clock->SetDisplayPosition(10, 10);
    char *timestr = (char *)malloc(sizeof(char)*100);
    snprintf(timestr,100,"Time:%f",univ_v->univ->time);
    univ_v->clock->SetInput(timestr);
    free(timestr);

    /* Set coordinates to match the old vtkScaledTextActor default value */
    univ_v->clock->GetPosition2Coordinate()->SetCoordinateSystemToNormalizedViewport();
    univ_v->clock->GetPosition2Coordinate()->SetValue(0.6, 0.1);

    vtkTextProperty *tprop = univ_v->clock->GetTextProperty();
    tprop->SetFontSize(24);
    tprop->SetFontFamilyToArial();
    //tprop->SetJustificationToCentered();
    //tprop->BoldOn();
    tprop->ItalicOn();
    tprop->ShadowOn();
    tprop->SetColor(1, 1, 1);
    ren->AddActor2D(univ_v->clock);
  }

  void set_scaling_factors_eo(vtkvis_eo *eov, gf_double tm_scale,
			      gf_double am_scale, gf_double lv_scale,
			      gf_double torque_scale, gf_double cone_spread,
			      gf_double mass_element_scale) {
    eov->tm_scale = tm_scale;
    eov->am_scale = am_scale;
    eov->lv_scale = lv_scale;
    eov->torque_scale = torque_scale;
    eov->cone_spread = cone_spread;
    eov->mass_element_scale = mass_element_scale;
  }

  void set_scaling_factors_vtkvis_univ(vtkvis_univ *univ_v, gf_double tm_scale,
				       gf_double am_scale, gf_double lv_scale,
				       gf_double torque_scale,
				       gf_double cone_spread, gf_double mass_element_scale) {
    vtkvis_eo *eovptr = univ_v->first_vtkvis_eo;
    univ_v->mass_element_scale = mass_element_scale;
    while(eovptr!=NULL) {
      set_scaling_factors_eo(eovptr,tm_scale,am_scale,lv_scale,torque_scale,cone_spread,mass_element_scale);
      eovptr = eovptr->next;
    }
  }

  vtkvis_eo *new_vtkvis_eo(GfExtendedObject *eo,vtkRenderer *ren1,
			   vtkvis_univ *univ_v, vtkvis_scaling_factors sf) {

    vtkvis_eo *eov = (vtkvis_eo *)malloc(sizeof(vtkvis_eo));
    //eov->tm_scale = 0.05;
    eov->eo = eo;
    eov->parent_vtkvis_univ = univ_v;
    eov->spheres = (vtkSphereSource **)malloc(sizeof(vtkSphereSource *)*eo->mass_element_count);
    GfMassElement *meptr = eo->first_mass_element;
    int i=0;


    eov->tm_scale = sf.tm_scale;
    eov->am_scale = sf.am_scale;
    eov->lv_scale = sf.lv_scale;
    eov->torque_scale = sf.torque_scale;
    eov->cone_spread = sf.cone_spread;
    eov->mass_element_scale = sf.mass_element_scale;
    eov->eo_vector_conebase = sf.eo_vector_conebase;

    eov->show_cm_sphere = GF_TRUE;
    eov->show_torque_cone = GF_TRUE;
    eov->show_lv_cone = GF_TRUE;
    eov->show_am_cone = GF_TRUE;



    // BEGIN: Center of Mass sphere crap

    eov->cm_sphere = vtkSphereSource::New();
    //eov->cm_sphere->SetRadius(0);
    eov->cm_sphere->SetRadius(eo->total_mass*eov->tm_scale);
    eov->cm_sphere->SetCenter(eo->center_of_mass.x,
			      eo->center_of_mass.y,
			      eo->center_of_mass.z);

    eov->cm_sphere->SetThetaResolution(18);
    eov->cm_sphere->SetPhiResolution(18);

    // map to graphics library
    vtkPolyDataMapper *cm_map = vtkPolyDataMapper::New();
    cm_map->SetInput(eov->cm_sphere->GetOutput());
  
    // actor coordinates geometry, properties, transformation
    vtkActor *acm_sphere = vtkActor::New();
    acm_sphere->SetMapper(cm_map);
    acm_sphere->GetProperty()->SetColor(1,0,0); // sphere color red

    // add the actor to the scene
    ren1->AddActor(acm_sphere);

    // END: Center of Mass sphere crap

    while (meptr) {

      // create sphere geometry
      vtkSphereSource *sphere = vtkSphereSource::New();
      sphere->SetRadius(meptr->mass * eov->mass_element_scale);
      sphere->SetCenter(meptr->loc.x,meptr->loc.y,meptr->loc.z);
    
      sphere->SetThetaResolution(18);
      sphere->SetPhiResolution(18);

      // map to graphics library
      vtkPolyDataMapper *map = vtkPolyDataMapper::New();
      map->SetInput(sphere->GetOutput());

      // actor coordinates geometry, properties, transformation
      vtkActor *aSphere = vtkActor::New();
      aSphere->SetMapper(map);
      aSphere->GetProperty()->SetColor(0,0,1); // sphere color blue



      // add the actor to the scene
      ren1->AddActor(aSphere);
      eov->spheres[i] = sphere;
      i++;
      meptr = meptr->next;

    }


    eov->torque_cone = vtkConeSource::New();
    eov->torque_cone->SetRadius(eov->eo_vector_conebase);
    vtkPolyDataMapper *torque_mapper = vtkPolyDataMapper::New();
    torque_mapper->SetInputConnection( eov->torque_cone->GetOutputPort() );

    vtkActor *torque_actor = vtkActor::New();
    torque_actor->GetProperty()->SetColor(0,1,0);
    torque_actor->SetMapper( torque_mapper );


    ren1->AddActor( torque_actor );


    eov->am_cone = vtkConeSource::New();
    eov->am_cone->SetRadius(eov->eo_vector_conebase);
    vtkPolyDataMapper *am_mapper = vtkPolyDataMapper::New();
    am_mapper->SetInputConnection( eov->am_cone->GetOutputPort() );

    vtkActor *am_actor = vtkActor::New();
    am_actor->GetProperty()->SetColor(1,1,0);
    am_actor->SetMapper( am_mapper );


    ren1->AddActor( am_actor );

    eov->lv_cone = vtkConeSource::New();
    eov->lv_cone->SetRadius(eov->eo_vector_conebase);
    vtkPolyDataMapper *lv_mapper = vtkPolyDataMapper::New();
    lv_mapper->SetInputConnection( eov->lv_cone->GetOutputPort() );

    vtkActor *lv_actor = vtkActor::New();
    lv_actor->GetProperty()->SetColor(1,0,1);
    lv_actor->SetMapper( lv_mapper );
    
    ren1->AddActor( lv_actor );




    eov->cones = (vtkConeSource **)malloc(sizeof(vtkConeSource *)*eo->bond_count);
    GfBond *bptr = eo->first_bond;
    i=0;
    while(bptr) {
      GFD(printf("Adding a cone\n"));
      vtkConeSource *c = vtkConeSource::New();
      position_cone(c,bptr);

      vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
      coneMapper->SetInputConnection( c->GetOutputPort() );

      vtkActor *coneActor = vtkActor::New();
      coneActor->GetProperty()->SetColor(1,1,0);
      coneActor->SetMapper( coneMapper );


      ren1->AddActor( coneActor );
      eov->cones[i] = c;
      
      gf_double avg_mass = eov->eo->total_mass/eov->eo->mass_element_count;
      eov->cones[i]->SetRadius(avg_mass * eov->mass_element_scale);
      
      i++;
      bptr=bptr->next;

    }
    return eov;
  }
  
  
  void update_vtkvis_eo(vtkvis_eo *eov) {
    GfExtendedObject *eo = eov->eo;
    GfMassElement *meptr = eo->first_mass_element;
    GfBond *bptr = eo->first_bond;
    int i=0;
    static gf_int step = 0;


    eov->cm_sphere->SetRadius(eo->total_mass*eov->tm_scale);
    eov->cm_sphere->SetCenter(eo->center_of_mass.x,
			      eo->center_of_mass.y,
			      eo->center_of_mass.z);


    if (eov->show_cm_sphere == GF_FALSE) {
      eov->cm_sphere->SetRadius(0);
    }



    GfVector torque_center = (eo->center_of_mass + (eo->torque * eov->torque_scale/2));
    eov->torque_cone->SetRadius(eov->eo_vector_conebase);
    eov->torque_cone->SetHeight(eo->torque.mag()*eov->torque_scale);
    eov->torque_cone->SetResolution(10);
    eov->torque_cone->SetCenter(torque_center.x-eov->cone_spread, torque_center.y, torque_center.z);
    eov->torque_cone->SetDirection(eo->torque.x,eo->torque.y,eo->torque.z);

    GfVector am_center = (eo->center_of_mass + (eo->angular_momentum * eov->am_scale/2));
    eov->am_cone->SetRadius(eov->eo_vector_conebase);
    eov->am_cone->SetHeight(eo->angular_momentum.mag()*eov->am_scale);
    eov->am_cone->SetResolution(10);
    eov->am_cone->SetCenter(am_center.x+eov->cone_spread, am_center.y, am_center.z);
    eov->am_cone->SetDirection(eo->angular_momentum.x,eo->angular_momentum.y,eo->angular_momentum.z);




    GfVector lv_center = (eo->center_of_mass + (eo->linear_velocity * eov->lv_scale/2));
    eov->lv_cone->SetRadius(eov->eo_vector_conebase);
    eov->lv_cone->SetHeight(eo->linear_velocity.mag()*eov->lv_scale);
    eov->lv_cone->SetResolution(10);
    eov->lv_cone->SetCenter(lv_center.x, lv_center.y, lv_center.z);
    eov->lv_cone->SetDirection(eo->linear_velocity.x,eo->linear_velocity.y,eo->linear_velocity.z);

    if (eov->show_torque_cone == GF_FALSE) {
      eov->torque_cone->SetRadius(0);
    }
    if (eov->show_lv_cone == GF_FALSE) {
      eov->lv_cone->SetRadius(0);
    }
    if (eov->show_am_cone == GF_FALSE) {
      eov->am_cone->SetRadius(0);
    }




    while (meptr) {

      //    sphere->SetRadius(meptr->mass);
      eov->spheres[i]->SetRadius(meptr->mass * eov->mass_element_scale);
      eov->spheres[i]->SetCenter(meptr->loc.x,meptr->loc.y,meptr->loc.z);
      i++;
      meptr=meptr->next;
    }
    i=0;
    while (bptr) {
      gf_double avg_mass = eov->eo->total_mass/eov->eo->mass_element_count;
      eov->cones[i]->SetRadius(avg_mass * eov->mass_element_scale);
      position_cone(eov->cones[i],bptr);
      i++;
      bptr=bptr->next;
    }
  }


  
  

  vtkvis_univ *new_vtkvis_univ(GfUniverse *univ, vtkRenderer *ren1, vtkvis_scaling_factors sf) {
    vtkvis_univ *univ_v = (vtkvis_univ *)malloc(sizeof(vtkvis_univ));
    GfExtendedObject *eoptr = univ->first_extended_object;
    //vtkvis_eo *eov;

    univ_v->univ = univ;
    univ_v->first_vtkvis_eo = NULL;
    univ_v->last_vtkvis_eo = NULL;
    //univ_v->mass_element_scale = 1;

    setup_info_display(ren1,univ_v);

    while(eoptr!=NULL) {

      eoptr->compute_center_of_mass_eo();

      /* Center of mass is not set up initially, it gets created
	 during the first iteration so to show the objects before that
	 you must force the creation of CM which also computes total
	 mass */

      vtkvis_eo *eov = new_vtkvis_eo(eoptr,ren1,univ_v,sf);
      if (univ_v->last_vtkvis_eo) {
	eov->prev = univ_v->last_vtkvis_eo;
	eov->prev->next = eov;
      }
      else {
	eov->prev = NULL;
	univ_v->first_vtkvis_eo = eov;
      }
      univ_v->last_vtkvis_eo = eov;
      eoptr = eoptr->next;
    }
    return univ_v;

  }

  vtkvis_univ *wnew_vtkvis_univ(GfUniverse *univ, vtkOpenGLRenderer *ren1, vtkvis_scaling_factors sf) {
    return new_vtkvis_univ(univ, ren1, sf);
  }



  void update_vtkvis_univ (vtkvis_univ *univ_v) {

    char *timestr = (char *)malloc(sizeof(char)*100);
    snprintf(timestr,100,"Time:%f",univ_v->univ->time);
    univ_v->clock->SetInput(timestr);
    free(timestr);
    vtkvis_eo *eovptr = univ_v->first_vtkvis_eo;
    while(eovptr!=NULL) {
      update_vtkvis_eo(eovptr);
      eovptr = eovptr->next;
    }

  }




#ifdef __cplusplus
}
#endif 


