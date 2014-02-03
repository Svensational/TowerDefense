#include "glfwapplication.h"
#include <chrono>
#include <thread>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "glfwwindow.h"

GLFWApplication::GLFWApplication() {
   glfwInit();
}

GLFWApplication::~GLFWApplication() {
   glfwTerminate();
}

void GLFWApplication::addWindow(GLFWWindow * window) {
   if (window) {
      windows.insert(window);
   }
}

void GLFWApplication::collectGarbage() {
   auto it = windows.begin();
   while (it!=windows.end()) {
      if ((*it)->isValid()) {
         ++it;
      }
      else {
         delete *it;
         it = windows.erase(it);
      }
   }
}

int GLFWApplication::execute() {
   double time = glfwGetTime();
   double deltaTime = 0.015;

   while (!windows.empty()) {
      for (auto it=windows.cbegin(); it!=windows.cend(); ++it) {
         (*it)->update(deltaTime);
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(std::max(int((0.015-glfwGetTime()+time)*1000.0), 0)));
      deltaTime = glfwGetTime()-time;
      time = glfwGetTime();

      glfwPollEvents();
      collectGarbage();
   }
   return 0;
}
