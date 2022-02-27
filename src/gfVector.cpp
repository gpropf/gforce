// $Id: gfVector.cpp 128 2008-07-28 06:44:44Z greg $


#include "gfVector.h"

#include "gfQuaternion.h"
#include <math.h>




#include <iostream>

using namespace std;

/*
GfVector::GfVector(gf_double inx, gf_double iny, gf_double inz) 
{
  // Default is to initialize to zero.
  x = inx;
  y = iny;
  z = inz;
}
*/

ostream& operator<<(ostream& out, const GfVector& vec) // output
{
  out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return out;
}


const GfVector GfVector::distanceFromAxis(const GfVector &a,
				    const GfVector &cm) const {
  // cm: center_of_mass, a: axis, this: the point, 
  //   WARNING: a must be unit vector!!!
  //   
  //   
  //   Returns r: the vector of displacement of this vector from axis

  gf_double t = this->dot(a) - cm.dot(a);
  
  GfVector r = *this - cm - a * t;

  return r;
  
}


const GfVector GfVector::operator*(const gf_double s) const
{
  GfVector r(this->x * s, this->y * s, this->z * s);
  return r;
}

const GfVector GfVector::operator/(const gf_double s) const
{
  GfVector r(this->x / s, this->y / s, this->z / s);
  return r;
}


void GfVector::quatrotVector(const GfQuaternion &q) {
  /* Use quaternion q to rotate this point about the axisvec.*/
  /* The math: f(v) = q * v * conj(q) This method modifies the
     vector that uses it */

  GfQuaternion conjq(- q.x,- q.y,- q.z,q.s);
  GfQuaternion qv (this->x,this->y,this->z,0);
  GfQuaternion qr = (q*qv)*conjq;
  this->x = qr.x;
  this->y = qr.y;
  this->z = qr.z;
  
}











const gf_double GfVector::mag() const {
  gf_double mag = sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
  return mag;
}

const gf_double GfVector::dot(const GfVector &other) const {
  gf_double dot = this->x * other.x + this->y * other.y + this->z * other.z;
  return dot;
}

const GfVector GfVector::normal() const
{

  gf_double mv = this->mag();
  GfVector n(this->x/mv,this->y/mv,this->z/mv);
  return n;
}

const GfVector GfVector::normalFromKnownMag(gf_double mv) const
{
  GfVector n(this->x/mv,this->y/mv,this->z/mv);
  return n;
}




GfVector & GfVector::operator=(const GfVector &rhs) {
    this->x=rhs.x;
    this->y=rhs.y;
    this->z=rhs.z;
    return *this;
}

GfVector & GfVector::operator=(const gf_double &rhs) {
    this->x=rhs;
    this->y=rhs;
    this->z=rhs;
    return *this;
}

GfVector & GfVector::operator+=(const GfVector &rhs) {
    this->x+=rhs.x;
    this->y+=rhs.y;
    this->z+=rhs.z;
    return *this;
}

GfVector & GfVector::operator-=(const GfVector &rhs){
  this->x-=rhs.x;
  this->y-=rhs.y;
  this->z-=rhs.z;
  return *this;
}

const GfVector GfVector::operator+(const GfVector &other) const
{
  GfVector result = *this; 
  result += other;            
  return result;              
}

const GfVector GfVector::operator-(const GfVector &other) const
{
  GfVector result = *this; 
  result -= other;            
  return result;              
}


const GfVector GfVector::operator*(const GfVector &other) const
{
  // Cross product

  GfVector cross(this->y * other.z - this->z * other.y,
		    this->z * other.x - this->x * other.z,
		    this->x * other.y - this->y * other.x);
  return cross;
}



bool GfVector::operator==(const GfVector &other) const
{
  if (this->x == other.x && this->y == other.y && this->z == other.z)
    return true;
  return false;
}

bool GfVector::operator==(const gf_double &other) const
{
  if (this->x == other && this->y == other && this->z == other)
    return true;
  return false;
}


bool GfVector::operator!=(const GfVector &other) const
{
  return !(*this==other);
}

bool GfVector::operator!=(const gf_double &other) const
{
  return !(*this==other);
}



