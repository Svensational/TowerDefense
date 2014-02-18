#ifndef SIZE2I_H
#define SIZE2I_H
#include <array>

class Size2i {

public:
   Size2i(int width = 0, int height = 0);
   int width() const;
   int & width();
   int height() const;
   int & height();
   float aspectRatio() const;
   int area() const;
   int min() const;
   int max() const;

private:
   std::array<int, 2> size;
};

#endif // SIZE2I_H
