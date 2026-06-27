

#ifndef gfQuaternion_h
#define gfQuaternion_h

//class GfVector;

#include <math.h>
#include "gfVector.h"

//class GfVector;

class GfQuaternion
{
public:
  gf_double x;
  gf_double y;
  gf_double z;
  gf_double s;
  //GfQuaternion & operator+=(const GfQuaternion &rhs);
  //GfQuaternion & operator-=(const GfQuaternion &rhs);
  //GfQuaternion & operator=(const GfQuaternion &rhs);
  //const GfQuaternion operator+(const GfQuaternion &other) const;
  //const GfQuaternion operator-(const GfQuaternion &other) const;
  const GfQuaternion operator*(const GfQuaternion &other) const;
  //bool operator==(const GfQuaternion &other) const;
  //bool operator!=(const GfQuaternion &other) const;

  GfQuaternion(gf_double inx = 0, gf_double iny = 0, gf_double inz = 0, gf_double ins = 0): x(inx), y(iny), z(inz), s(ins) {};
  GfQuaternion(GfVector &v, gf_double alpha);
  //GfQuaternion(gf_double = 0, gf_double = 0, gf_double = 0);
  //const gf_double mag() const;
  //const GfQuaternion normal() const;
  //const GfQuaternion normalFromKnownMag(gf_double mv) const;
  //const gf_double dot(const GfQuaternion &other) const;
};

#endif
