#ifndef __MODULE_PIXEL__
#define __MODULE_PIXEL__

#include <cstdint>

////////////////////////////////////////
//
// Suppose T entier non-signé (uint8_t, size_t)
//
template <typename T>
class RGB
 {
  public:

      T r,g,b;

      ////////////////////////
      T operator[](int i) const
       {
        switch(i)
         {
          case 0: return r;
          case 1: return g;
          default:
          case 2: return b;
         }
       }
  
      ////////////////////////
      T & operator[](int i)
       {
        switch(i)
         {
          case 0: return r;
          case 1: return g;
          default:
          case 2: return b;
         }
       }

  bool operator==(const RGB & o) const { return (r==o.r) && (g==o.g) && (b==o.b); }
  bool operator!=(const RGB & o) const { return (r!=o.r) || (g!=o.g) || (b!=o.b); }

  RGB(T r_=0, T g_=0, T b_=0)
   : r(r_),g(g_),b(b_)
  {}

  ~RGB()=default;
 };

using rgb24=RGB<uint8_t>; // RGB 24 bits

extern const rgb24 white;
extern const rgb24 black;

#endif
// __MODULE_PIXEL__
