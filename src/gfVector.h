// $Id: gfVector.h 92 2008-06-21 06:35:38Z greg $




#ifndef gfVector_h
#define gfVector_h

#include "gftypes.h"

#include <ostream>

using namespace std;

class GfQuaternion;

class GfVector
{
public:
  gf_double x;
  gf_double y;
  gf_double z;
  GfVector & operator+=(const GfVector &rhs);
  GfVector & operator-=(const GfVector &rhs);
  GfVector & operator=(const GfVector &rhs);
  GfVector & operator=(const gf_double &rhs);
  const GfVector operator+(const GfVector &other) const;
  const GfVector operator-(const GfVector &other) const;
  const GfVector operator*(const GfVector &other) const;
  const GfVector operator*(const gf_double s) const;
  const GfVector operator/(const gf_double s) const;

  friend ostream& operator<<(ostream& out, const GfVector& vec);
  bool operator==(const GfVector &other) const;
  bool operator==(const gf_double &other) const;
  bool operator!=(const GfVector &other) const;
  bool operator!=(const gf_double &other) const;

  GfVector(gf_double inx = 0, gf_double iny = 0, gf_double inz = 0): x(inx), y(iny), z(inz) {};
  //GfVector(gf_double = 0, gf_double = 0, gf_double = 0);
  const gf_double mag() const;
  const GfVector normal() const;
  const GfVector normalFromKnownMag(gf_double mv) const;
  const gf_double dot(const GfVector &other) const;
  void quatrotVector(const GfQuaternion &q);
  const GfVector distanceFromAxis(const GfVector &a, const GfVector &cm) const;
};



#endif
