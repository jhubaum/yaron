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

  float h = sqrt(0.75f);
  Object obj = createCircle(8);

  while (!context.exitRequest()) {
    context.beginFrame();
    context.useShader(shader);
    context.renderObject(obj);
    context.endFrame();
  }

  obj.deinit();
  glDeleteProgram(shader);
  context.deinit();

	return 0;
}
