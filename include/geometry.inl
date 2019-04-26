#pragma once

template<typename TVertex>
GeometryPtr Geometry<TVertex>::create(const std::vector<TVertex> &vertices, const std::vector<unsigned short> &indices) {

  GeometryIn data;
  data.vertices = &vertices[0];
  data.indices = &indices[0];
  data.vertexSize = sizeof(TVertex);
  data.vertexCount = vertices.size();
  data.indexCount = indices.size();
  GeometryOut o = createGeometry(data);

  Geometry_B *res = new Geometry<TVertex>(o.vertexArrayObject,
                                          o.vertexBuffer,
                                          o.indexBuffer,
                                          data.indexCount);

  return GeometryPtr(res);
}

template<typename TVertex>
Geometry<TVertex>::Geometry(GLuint vao, GLuint vb, GLuint ib, uint32_t ic) : Geometry_B(vao, vb, ib, ic)
{}

template<typename TVertex>
void Geometry<TVertex>::vEnableVertexAttributes() {
  enableVertexAttributes<TVertex>(vertexBuffer(), indexBuffer());
}

template<typename TVertex>
void Geometry<TVertex>::vDisableVertexAttributes() {
  disableVertexAttributes<TVertex>();
}
