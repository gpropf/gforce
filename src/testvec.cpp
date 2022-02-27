// $Id: testvec.cpp 82 2008-06-10 07:51:50Z greg $

#include <iostream>
#include "gfVector.h"
#include "gfQuaternion.h"
using namespace std ;




int main(int argc, char **argv) {
  GfVector fv1(1,1,1);
  //GfVector fv2(2,3,4);
  GfVector fv2;
  cout << fv2 << endl;
  cout << fv1.dot(fv2) << endl;
  cout << fv1.mag() << endl;
  GfVector fv3(5,0,0);
  GfVector axis(1,1,0);
  gf_double angle = PI/2;
  GfVector axisNorm = axis.normal();
  GfQuaternion q (axisNorm,angle);
  fv3.quatrotVector(q);
  cout << fv3 << endl;
  
  cout << fv3 * 4 << endl;

  cout << fv3.distanceFromAxis(axis.normal(),*new GfVector()) << endl;

  return 0;
}
