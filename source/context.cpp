#include <context.hpp>

#include <iostream>

RenderContext::RenderContext()
  : _window(nullptr)
{}

bool RenderContext::init(uint32_t width, uint32_t height) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW\n" << std::endl;
    return false;
  }

  _aspect = static_cast<float>(width) / height;

  glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, "Window", NULL, NULL);
  if (NULL == _window) {
    std::cout << "Failed to open GLFW window" << std::endl;
    return false;
  }
	glfwMakeContextCurrent(_window);

  if(GLEW_OK != glewInit()) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return false;
  }
  
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  return true;
}

void RenderContext::deinit() {
  _shader = nullptr;
  glfwTerminate();
}

void RenderContext::beginFrame(const glm::mat4 &viewProjectionMatrix) {
  glClear(GL_COLOR_BUFFER_BIT);
  _viewProjectionMatrix = viewProjectionMatrix;
}

void RenderContext::endFrame() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void RenderContext::useShader(ShaderPtr shader) {
  _shader = shader;
  shader->setActive();
}

void RenderContext::renderGeometry(GeometryPtr geometry, const glm::mat4 &world) {
  glm::mat4 mvp = _viewProjectionMatrix * world;

  _shader->setMVP(mvp);

  glEnableVertexAttribArray(0);
  // Vertices (Position)
  glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->indexBuffer());

  // Draw Triangles
  glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_SHORT, (void*)0);

  glDisableVertexAttribArray(0);
}

bool RenderContext::exitRequest() const {
  return GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_ESCAPE ) ||
    glfwWindowShouldClose(_window);
}
