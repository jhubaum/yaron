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


template<>
void enableVertexAttributes<VertexPN>(GLuint vertexBuffer, GLuint indexBuffer) {
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPN), (void*)0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPN), (void*)3);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

template<>
void disableVertexAttributes<VertexPN>() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
