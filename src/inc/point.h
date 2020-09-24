#ifndef JARED_ALL_TETRIS_ENGINE_POINT_H
#define JARED_ALL_TETRIS_ENGINE_POINT_H

class Point 
{
public:

  Point( int x, int y );

  ~Point();

  void set_x( int x );

  int get_x() const;

  void set_y( int y );

  int get_y() const;

private:
  int x;
  int y;
};

#endif
