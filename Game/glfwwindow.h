#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include <string>
#include "vec.h"

class GLFWwindow;
class GLFWApplication;

class GLFWWindow {

public:
   GLFWWindow(Size2i size, std::string title, bool fullscreen = false);
   virtual ~GLFWWindow();
   bool isValid() const;
   void toggleFullscreen();
   void update();

protected:
   bool fullscreen;
   Size2i size;
   Size2i windowedSize;
   std::string title;
   double updatetime;
   double framerate;

   void makeContextCurrent();
   void enableVSync(bool enable = true);
   void hideCursor(bool hide = true);
   void swapBuffers();
   void destroy();
   virtual void initGL() {};
   virtual void onUpdate(double deltaTime);
   virtual void onClosed();
   virtual void onResized(Size2i const & newSize) {};
   virtual void onFocusGained() {};
   virtual void onFocusLost() {};
   virtual void onIconified() {};
   virtual void onRestored() {};
   virtual void onMouseMoved(Point2d const & newPosition) {};
   virtual void onMouseButtonPressed(int button, int modKeys) {};
   virtual void onMouseButtonReleased(int button, int modKeys) {};
   virtual void onMouseScrolled(Vec2d const & delta) {};
   virtual void onKeyPressed(int key, bool repeat, int modKeys);
   virtual void onKeyReleased(int key, int modKeys) {};
   virtual void onCharacterEntered(char32_t unicode) {};

private:
   GLFWwindow * handle;

   void init();
   static void closeCallback(GLFWwindow * handle);
   static void sizeCallback(GLFWwindow * handle, int width, int height);
   static void focusCallback(GLFWwindow * handle, int focused);
   static void iconifyCallback(GLFWwindow * handle, int iconified);
   static void cursorPositionCallback(GLFWwindow * handle, double x, double y);
   static void mouseButtonCallback(GLFWwindow * handle, int button, int action, int mods);
   static void mouseWheelCallback(GLFWwindow * handle, double deltaX, double deltaY);
   static void keyCallback(GLFWwindow * handle, int key, int scancode, int action, int mods);
   static void charCallback(GLFWwindow * handle, unsigned int codepoint);
};

#endif // GLFWWINDOW_H
