#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();
    struct pixel;

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void draw_line_Bres(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);
    void draw_starburst();
    void draw_blerp(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color1, unsigned int color2, unsigned int color3);
    float linelength(float x1, float y1, float x2, float y2);
    int Distance(int x1, int y1, int x2, int y2);
    void PolygonRenderer(float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3);
    bool SimpDrawer();
    void mesh(int filled);
};

#endif // CLIENT_H
