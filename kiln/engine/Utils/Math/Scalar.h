#pragma once

namespace KMath {
  namespace Scalar {
    template<class T>
    T lerp(T a, T b, float normal) {
      return T(a + (b - a) * normal);
    }
  };
};