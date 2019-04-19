#include <app.hpp>

int main(char *argv[], int argc) {
  App *pApp = allocateApplication();

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
