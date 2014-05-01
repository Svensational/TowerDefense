#include "glfwwindow.h"
#include "gl_core_4_4.h"
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(Size2i size, std::string title, bool fullscreen) :
   fullscreen(fullscreen), size(size), windowedSize(fullscreen?Size2i(800, 600):size), title(title),
   handle(glfwCreateWindow(size.width(), size.height(), title.c_str(), fullscreen?glfwGetPrimaryMonitor():nullptr, nullptr))
{
   init();
}

GLFWWindow::~GLFWWindow() {
   destroy();
}

void GLFWWindow::charCallback(GLFWwindow * handle, unsigned int codepoint) {
   static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onCharacterEntered(codepoint);
}

void GLFWWindow::closeCallback(GLFWwindow * handle) {
   static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onClosed();
}

void GLFWWindow::cursorPositionCallback(GLFWwindow * handle, double x, double y) {
   int width, height;
   glfwGetWindowSize(handle, &width, &height);
   static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onMouseMoved(Point2d(x/double(width-1), 1.0-y/double(height-1)));
}

void GLFWWindow::destroy() {
   if (handle) {
      glfwDestroyWindow(handle);
      handle = nullptr;
   }
}

void GLFWWindow::enableVSync(bool enable) {
   glfwSwapInterval(enable?1:0);
}

void GLFWWindow::focusCallback(GLFWwindow * handle, int focused) {
   if (focused) {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onFocusGained();
   }
   else {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onFocusLost();
   }
}

void GLFWWindow::hideCursor(bool hide) {
   glfwSetInputMode(handle, GLFW_CURSOR, hide?GLFW_CURSOR_HIDDEN:GLFW_CURSOR_NORMAL);
}

void GLFWWindow::iconifyCallback(GLFWwindow * handle, int iconified) {
   if (iconified) {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onIconified();
   }
   else {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onRestored();
   }
}

void GLFWWindow::init() {
   if (handle) {
      glfwSetWindowUserPointer(handle, this);
      // register callbacks
      glfwSetWindowCloseCallback(handle, closeCallback);
      glfwSetWindowSizeCallback(handle, sizeCallback);
      glfwSetWindowFocusCallback(handle, focusCallback);
      glfwSetWindowIconifyCallback(handle, iconifyCallback);
      glfwSetCursorPosCallback(handle, cursorPositionCallback);
      glfwSetMouseButtonCallback(handle, mouseButtonCallback);
      glfwSetScrollCallback(handle, mouseWheelCallback);
      glfwSetKeyCallback(handle, keyCallback);
      glfwSetCharCallback(handle, charCallback);

      glfwMakeContextCurrent(handle);
      ogl_LoadFunctions();
      initGL();
   }
}

bool GLFWWindow::isValid() const {
   return handle;
}

void GLFWWindow::keyCallback(GLFWwindow * handle, int key, int scancode, int action, int mods) {
   if (action == GLFW_RELEASE) {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onKeyReleased(key, mods);
   }
   else {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onKeyPressed(key, action==GLFW_REPEAT, mods);
   }
}

void GLFWWindow::makeContextCurrent() {
   glfwMakeContextCurrent(handle);
}

void GLFWWindow::mouseButtonCallback(GLFWwindow * handle, int button, int action, int mods) {
   if (action == GLFW_PRESS) {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onMouseButtonPressed(button, mods);
   }
   else {
      static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onMouseButtonReleased(button, mods);
   }
}

void GLFWWindow::mouseWheelCallback(GLFWwindow * handle, double deltaX, double deltaY) {
   static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle))->onMouseScrolled(Vec2d(deltaX, deltaY));
}

void GLFWWindow::onClosed() {
   destroy();
}

void GLFWWindow::onKeyPressed(int key, bool repeat, int modKeys) {
   if (key == GLFW_KEY_ENTER && modKeys&GLFW_MOD_ALT) {
      toggleFullscreen();
   }
}

void GLFWWindow::sizeCallback(GLFWwindow * handle, int width, int height) {
   GLFWWindow * window = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(handle));
   window->size = Size2i(width, height);
   if (!window->fullscreen) {
      window->windowedSize = window->size;
   }
   window->onResized(window->size);
}

void GLFWWindow::swapBuffers() {
   glfwSwapBuffers(handle);
}

void GLFWWindow::toggleFullscreen() {
   fullscreen = !fullscreen;
   glfwDestroyWindow(handle);
   if (fullscreen) {
      GLFWvidmode const * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      handle = glfwCreateWindow(vidMode->width, vidMode->height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
   }
   else {
      handle = glfwCreateWindow(windowedSize.width(), windowedSize.height(), title.c_str(), nullptr, nullptr);
   }
   init();
}

void GLFWWindow::update(double deltaTime) {
   makeContextCurrent();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   swapBuffers();
}
