#include <vertex.hpp>

template<>
void enableVertexAttributes<VertexP>(GLuint vertexBuffer, GLuint indexBuffer) {
  glEnableVertexAttribArray(0);

  // Position
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

template<>
void disableVertexAttributes<VertexP>() {
  glDisableVertexAttribArray(0);
}
