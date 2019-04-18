#include <context.hpp>
#include <shader.hpp>

#include <primitives.hpp>

#include <glm/glm.hpp>

int main()
{
  RenderContext context;
  if (!context.init(1024, 768)) {
    context.deinit();
    return 0;
  }

  GLuint shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();

  PerspectiveCamera camera(glm::radians(45.0f), context.aspectRatio());
  camera.position({0.0f, 0.0f, -5.0f});

  Object obj = createCircle(8);

  while (!context.exitRequest()) {
    context.beginFrame(camera.calculateViewProjectionMatrix());
    context.useShader(shader);
    context.renderObject(obj);
    context.endFrame();
  }

  obj.deinit();
  glDeleteProgram(shader);
  context.deinit();

	return 0;
}
