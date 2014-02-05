#include "glfwapplication.h"
#include "window.h"

int main(int argc, char * argv[]) {
   GLFWApplication app;

   app.addWindow(new Window());

   return app.execute();
}
