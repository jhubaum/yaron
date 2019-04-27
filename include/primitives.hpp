#pragma once

#include <geometry.hpp>

GeometryPtr createCircle(uint32_t vertexCount, float radius=1.0f);
GeometryPtr createSphere(uint32_t lonCount, uint32_t latCount, float radius=1.0f);
GeometryPtr createCube();
