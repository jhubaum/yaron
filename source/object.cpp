#include <object.hpp>

Geometry::Geometry() {

}

Geometry::~Geometry() {
  glDeleteBuffers(1, &_indexBuffer);
  glDeleteBuffers(1, &_vertexBuffer);
  glDeleteVertexArrays(1, &_vertexArray);
}


GeometryPtr Geometry::create(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices) {
  struct SharedEnabler : public Geometry { };

  GeometryPtr res = std::make_shared<SharedEnabler>();
  if (!res->init(vertices, indices))
    return nullptr;
  return res;
}

bool Geometry::init(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices) {
  glGenVertexArrays(1, &_vertexArray);
  glBindVertexArray(_vertexArray);

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
               &vertices[0], GL_STATIC_DRAW);

  _indexCount = indices.size();

	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

  return true;
}
