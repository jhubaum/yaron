#include <context.hpp>
#include <shader.hpp>

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
  Object obj;

  if (!obj.init({
                 {-0.5f, -h, 0.0f},
                 {0.5f, -h, 0.0f},
                 {0.0f,  h, 0.0f},
      }, {0, 1, 2}))
    return 1;

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
