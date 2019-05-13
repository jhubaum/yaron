#pragma once
#include <fwd.hpp>

namespace yaron {
  namespace graphics {
    GeometryPtr createCircle(uint32_t vertexCount, float radius=1.0f);

    // Lon: vertical lines
    // Lat: horizontal lines
    GeometryPtr createSphere(uint32_t lonCount=16, uint32_t latCount=16, float radius=1.0f);
    GeometryPtr createCube();
  }
}
