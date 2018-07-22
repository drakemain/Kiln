#pragma once

namespace KMath {
  namespace Scalar {
    template<class T>
    inline T lerp(T a, T b, float normal) {
      return T(a + (b - a) * normal);
    }

    template<class T>
    inline float norm(T a, T b, T val) {
      return ((val - a) / (b - a)).f;
    }

    template<class T>
    inline T map(T srcA, T srcB, T srcVal, T destA, T destB) {
      return T(KMath::Scalar::lerp(
        KMath::Scalar::norm(srcA, srcB, srcVal),
        destA, destB
      ));
    }

    template<class T>
    inline T clamp(T min, T max, T val) {
      if (val < min) {
        val = min;
      } else if (val > max) {
        val = max;
      }

      return val;
    }
  };
};