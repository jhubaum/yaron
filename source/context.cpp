#include <context.hpp>

#include <iostream>

RenderSettings::RenderSettings()
  : width(1366), height(768), windowName("Empty Window Name"),
    clearColor(Color::white)
{}

RenderContext::RenderContext()
{}

RenderContextPtr RenderContext::create(const RenderSettings &settings) {
  struct SharedEnabler : public RenderContext { };

  RenderContextPtr ptr = std::make_shared<SharedEnabler>();

  if (ptr->init(settings))
    return ptr;
  return nullptr;
}

RenderContext::~RenderContext() {
  glfwTerminate();
}

bool RenderContext::init(const RenderSettings &settings) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW\n" << std::endl;
    return false;
  }

  _aspect = static_cast<float>(settings.width) / settings.height;

  glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(settings.width, settings.height,
                             settings.windowName.c_str(), NULL, NULL);
  if (nullptr == _window) {
    std::cout << "Failed to open GLFW window" << std::endl;
    return false;
  }
	glfwMakeContextCurrent(_window);

  if(GLEW_OK != glewInit()) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return false;
  }

  clearColor(settings.clearColor);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

  return true;
}

void RenderContext::beginFrame(std::weak_ptr<Camera> camera) {
  _camera = camera;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderContext::endFrame() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void RenderContext::useShader(std::weak_ptr<Shader> shader) {
  _shader = shader;
  _shader.lock()->setActive();
}

void RenderContext::renderGeometry(GeometryPtr geometry, const Transform &transform) {
  renderGeometry(geometry, transform.calculateWorld());
}

void RenderContext::renderGeometry(GeometryPtr geometry, const glm::mat4 &world) {
  if (_camera.expired())
    std::cout << "RenderContext: Camera is expired" << std::endl;
  if (_shader.expired())
    std::cout << "RenderContext: Shader is expired" << std::endl;

  auto shader = _shader.lock();
  shader->setMVP(_camera.lock()->viewProjectionMatrix() * world);

  glEnableVertexAttribArray(0);
  // Vertices (Position)
  glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->indexBuffer());

  // Draw Triangles
  glDrawElements(static_cast<GLenum>(shader->drawMode()), geometry->indexCount(), GL_UNSIGNED_SHORT, (void*)0);

  glDisableVertexAttribArray(0);
}

bool RenderContext::exitRequest() const {
  return GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_ESCAPE ) ||
    glfwWindowShouldClose(_window);
}

void RenderContext::clearColor(const Color &c) {
	glClearColor(c.r, c.g, c.b, c.a);
}
