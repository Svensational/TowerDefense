#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include <set>

class GLFWWindow;

class GLFWApplication {

public:
   GLFWApplication();
   virtual ~GLFWApplication();
   void addWindow(GLFWWindow * window);
   int execute();

private:
   std::set<GLFWWindow*> windows;

   void collectGarbage();
};

#endif // GLFWAPPLICATION_H
