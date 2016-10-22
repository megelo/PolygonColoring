#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void draw_line_Bres(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);
    void draw_starburst();
};

#endif // CLIENT_H
