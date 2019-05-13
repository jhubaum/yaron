#include <app.hpp>

int main(int argc, char *argv[]) {
  yaron::App *pApp = yaron::allocateApplication();

  if (pApp->init(argv, argc)) {
    while (!pApp->exitRequest()) {
      pApp->update();
      pApp->render();
    }
  }
  pApp->deinit();
  delete pApp;
  return 0;
}
