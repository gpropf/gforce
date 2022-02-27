// $Id: gfQuaternion.cpp 79 2008-06-08 06:41:59Z greg $


#include "gfQuaternion.h"



const GfQuaternion GfQuaternion::operator*(const GfQuaternion &other) const
  // Quaternion analog of cross product.
  //quaternion mul_quaternion(quaternion a,quaternion b) 
{
  GfQuaternion q(this->s * other.x + this->x * other.s +
		    this->y * other.z - this->z * other.y,
		    this->s * other.y - this->x * other.z +
		    this->y * other.s + this->z * other.x,
		    this->s * other.z + this->x * other.y -
		    this->y * other.x + this->z * other.s,
		    this->s * other.s - this->x * other.x -
		    this->y * other.y - this->z * other.z);
  return q;
}


GfQuaternion::GfQuaternion(GfVector &v, gf_double alpha) {
  /* Treating the vector as a rotation axis, build a quaternion that
     can be used to rotate other vectors through anticlockwise angle
     alpha. WARNING: vector must be a unit vector!! */

  gf_double halfalpha = alpha/2;
  gf_double sinha = sin(halfalpha);
  gf_double cosha = cos(halfalpha);
  
  this->s = cosha;
  this->x = v.x * sinha;
  this->y = v.y * sinha;
  this->z = v.z * sinha;
}


//





