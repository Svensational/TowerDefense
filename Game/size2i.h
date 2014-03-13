#ifndef SIZE2I_H
#define SIZE2I_H

struct Size2i {
   int width;
   int height;

   Size2i();
   Size2i(int width, int height);
   float aspectRatio() const;
   int area() const;
   int min() const;
   int max() const;
};



struct Point2i {
   int x;
   int y;

   Point2i();
   Point2i(int x, int y);
   int min() const;
   int max() const;
};



class Rect2i {

public:
   Rect2i();
   Rect2i(int left, int bottom, int width, int height);
   Rect2i(Point2i const & pos, Size2i const & size);
   Rect2i(Point2i const & a, Point2i const & b);
   int width() const;
   int height() const;
   Size2i const & size() const;
   int left() const;
   int right() const;
   int top() const;
   int bottom() const;
   Point2i lowerLeft() const;
   Point2i lowerRight() const;
   Point2i upperLeft() const;
   Point2i upperRight() const;

private:
   Point2i pos;
   Size2i _size;
};

#endif // SIZE2I_H
