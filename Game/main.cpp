#include "glfwapplication.h"
#include "glfwwindow.h"

int main(int argc, char * argv[]) {
   GLFWApplication app;

   app.addWindow(new GLFWWindow(Size2i(800, 600), std::string("Testwindow")));

   return app.execute();
}
