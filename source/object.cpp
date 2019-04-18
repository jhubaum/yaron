#include <object.hpp>


Object::Object()
  : _vertexArray(0), _vertexBuffer(0), _indexCount(0)
{}

Object::~Object() {
  deinit();
}

bool Object::init(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices) {
  glGenVertexArrays(1, &_vertexArray);
  glBindVertexArray(_vertexArray);

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
               &vertices[0], GL_STATIC_DRAW);

  _indexCount = vertices.size();

	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

  return true;
}

void Object::deinit() {
  glDeleteBuffers(1, &_indexBuffer);
  glDeleteBuffers(1, &_vertexBuffer);
  glDeleteVertexArrays(1, &_vertexArray);
}
