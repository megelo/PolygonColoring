#include <iostream>
#include <math.h>
#include <QTextStream>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream> //parse simp file
using std::ifstream;
#include <string>
#include <stack>
#include "client.h"

#define PI  3.14159265358979323846  /* pi */

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS = 500;
const char* const DELIMITER = "\"    \t,()\n";

struct Client::pixel{
    int x;
    int y;
};

struct Client::Mat{
    float mat[4][4];
    Mat() {
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if(i == j) {
                    mat[i][j] = 1.0;
                }
                else {
                    mat[i][j] = 0.0;
                }
            }
        }
    };
};
typedef struct Mat Mat;

struct Client::meshPixel{
    int x;
    int y;
    int z;
};
typedef struct meshPixel meshPixel;

struct Client::vec3{
    float x;
    float y;
    float z;
};
typedef struct vec3 vec3;

struct Client::rgbvec{
    int r;
    int g;
    int b;
};
typedef struct rgbvec rgbvec;

Client::Client(Drawable *drawable, char *argv[])
{
    this->drawable = drawable;
    this->argv = argv;
}

void Client::nextPage() {

    static int pageNumber = 0;
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;

    switch(pageNumber % 8) {
    case 1:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
        drawable->updateScreen();
        SimpDrawer(argv,0xffffffff,0x00003366);
        break;
    case 2:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
        //mesh(true);
        drawable->updateScreen();
        break;
    case 3:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        SimpDrawer("page3.txt", 0xffffffff, 0x00000000);
        drawable->updateScreen();
        break;
    case 4:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        SimpDrawer("page4.txt", 0xff00CC66, 0xff008040);
        drawable->updateScreen();
        break;
    case 5:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
        drawable->updateScreen();
        break;
    case 6:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        SimpDrawer("test1.simp", 0xffffffff, 0x00000000);
        drawable->updateScreen();
        break;
    case 7:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        SimpDrawer("test2.simp", 0xffffffff, 0x00000000);
        drawable->updateScreen();
        break;
    case 8:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        SimpDrawer("test3.simp", 0xffffffff, 0x00000000);
        drawable->updateScreen();
        break;
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
        drawable->updateScreen();
    }
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}

void Client::draw_line_Bres(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2){
    int dx = x2-x1;
    if(x1>x2) {
        dx = x1-x2;
    }

    int dy = y2-y1;
    if(y1>y2) {
        dy = y1-y2;
    }

    int two_dx = 2*dx;
    int two_dy = 2*dy;

    int r1,g1,b1,r2,b2,g2,rounded_r,rounded_g,rounded_b;

    r1 = (color1>>16)& 0xff;
    g1 = (color1>>8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2>>16)& 0xff;
    g2 = (color2>>8) & 0xff;
    b2 = color2 & 0xff;


    unsigned int current_Color;

    drawable->setPixel(x1,y1,color1);

    if(dx>dy){
        int err = two_dy-dx;
        int t2 = two_dy-two_dx;



        if(y2>y1){
            int y = y1;
            if(x2>x1){
                int ddx = x2 - x1;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                // Traverse along x+
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y++;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddx = x1 - x2;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                // Traverse along x-
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y++;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
        else{
            if(x2>x1){
                int ddx = x2 - x1;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                int y = y1;
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y--;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddx = x1 - x2;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                int y = y1;
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y--;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
    }
    else{
        int err = two_dx-dy;
        int t2 = two_dx-two_dy;
        if(x2>x1){
                if(y2>y1){
                    int ddy = y2 - y1;
                    float dr = r2-r1;
                    dr = dr/ddy;
                    float dg = g2-g1;
                    dg = dg/ddy;
                    float db = b2-b1;
                    db = db/ddy;

                    float temp_r = r1;
                    float temp_g = g1;
                    float temp_b = b1;

                    int x = x1;
                    // Traverse along y+
                    for(int y=y1+1; y<=y2; y++){
                        if (err>=0){
                            err = err + t2;
                            x++;
                        }
                        else{
                            err = err+two_dx;
                        }
                        temp_r = temp_r+dr;
                        temp_g = temp_g+dg;
                        temp_b = temp_b+db;
                        rounded_r = round(temp_r);
                        rounded_g = round(temp_g);
                        rounded_b = round(temp_b);

                        current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                        drawable->setPixel(x,y,current_Color);
                    }
                }
                else{
                    int ddy = y1 - y2;
                    float dr = r2-r1;
                    dr = dr/ddy;
                    float dg = g2-g1;
                    dg = dg/ddy;
                    float db = b2-b1;
                    db = db/ddy;

                    float temp_r = r1;
                    float temp_g = g1;
                    float temp_b = b1;

                    int x = x1;
                    for(int y=y1+1; y>=y2; y--){
                        if (err>=0){
                            err = err + t2;
                            x++;
                        }
                        else{
                            err = err+two_dx;
                        }
                        temp_r = temp_r+dr;
                        temp_g = temp_g+dg;
                        temp_b = temp_b+db;
                        rounded_r = round(temp_r);
                        rounded_g = round(temp_g);
                        rounded_b = round(temp_b);

                        current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                        drawable->setPixel(x,y,current_Color);
                    }
                }
        }
        else{
            if(y2>y1){
                int ddy = y2 - y1;
                float dr = r2-r1;
                dr = dr/ddy;
                float dg = g2-g1;
                dg = dg/ddy;
                float db = b2-b1;
                db = db/ddy;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;

                int x = x1;
                // Traverse along y+
                for(int y=y1+1; y<=y2; y++){
                    if (err>=0){
                        err = err + t2;
                        x--;
                    }
                    else{
                        err = err+two_dx;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddy = y1 - y2;
                float dr = r2-r1;
                dr = dr/ddy;
                float dg = g2-g1;
                dg = dg/ddy;
                float db = b2-b1;
                db = db/ddy;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;

                int x = x1;
                // Traverse along y-
                for(int y=y1+1; y>=y2; y--){
                    if (err>=0){
                        err = err + t2;
                        x--;
                    }
                    else{
                        err = err+two_dx;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;

                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
    }
}
int Client::Distance(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void Client::PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3, vec3 normalvector){
    // Create normalized normal vector for Phong
    vec3 norm_N = normalize(normalvector);
    vec3 point;
    // initialize edge case for vertical lines
    bool VertLine_p1p2 = false;
    bool VertLine_p1p3 = false;
    bool VertLine_p2p3 = false;
    float x1,y1,x2,y2,x3,y3;
    int r1,g1,b1,r2,b2,g2,r3,g3,b3,long_rounded_r,long_rounded_g,long_rounded_b,a_rounded_r,a_rounded_g,a_rounded_b,b_rounded_r,b_rounded_g,b_rounded_b;

    // Assigning parameters to p1,p2,p3
    // (x1,y1)->(x2,y2) is assigned to be the longest line
    if(Distance(xx1,yy1,xx2,yy2)>=Distance(xx1,yy1,xx3,yy3) && Distance(xx1,yy1,xx2,yy2)>=Distance(xx2,yy2,xx3,yy3)){
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        x3 = xx3;
        y3 = yy3;

        r1 = (color1>>16)& 0xff;
        g1 = (color1>>8) & 0xff;
        b1 = color1 & 0xff;
        r2 = (color2>>16)& 0xff;
        g2 = (color2>>8) & 0xff;
        b2 = color2 & 0xff;
        r3 = (color3>>16)& 0xff;
        g3 = (color3>>8) & 0xff;
        b3 = color3 & 0xff;

//        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

    }
    else if(Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx2,yy2) && Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx3,yy3)){
        x1 = xx2;
        y1 = yy2;
        x2 = xx3;
        y2 = yy3;
        x3 = xx1;
        y3 = yy1;

        r1 = (color2>>16)& 0xff;
        g1 = (color2>>8) & 0xff;
        b1 = color2 & 0xff;
        r2 = (color3>>16)& 0xff;
        g2 = (color3>>8) & 0xff;
        b2 = color3 & 0xff;
        r3 = (color1>>16)& 0xff;
        g3 = (color1>>8) & 0xff;
        b3 = color1 & 0xff;

//        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;


    }
    else{
        x1 = xx1;
        y1 = yy1;
        x2 = xx3;
        y2 = yy3;
        x3 = xx2;
        y3 = yy2;

        r1 = (color1>>16)& 0xff;
        g1 = (color1>>8) & 0xff;
        b1 = color1 & 0xff;
        r2 = (color3>>16)& 0xff;
        g2 = (color3>>8) & 0xff;
        b2 = color3 & 0xff;
        r3 = (color2>>16)& 0xff;
        g3 = (color2>>8) & 0xff;
        b3 = color2 & 0xff;
//        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;
    }

//    QTextStream(stdout)<<"(x,y)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;



    // Declaration for the longest line p1p2
    float long_dx = x2-x1;
    float long_dy = y2-y1;
    float long_m = (float)long_dy/(float)long_dx;
    float long_b = y1-long_m*x1;
    float long_y;
    float long_x;

    // Declaration for line p1p3
    float a_dx = x3-x1;
    float a_dy = y3-y1;
    float a_m = (float)a_dy/(float)a_dx;
    float a_b = y1-a_m*x1;
    float a_x;
    float a_y;

    // Declaration for line p2p3
    float b_dx = x3-x2;
    float b_dy = y3-y2;
    float b_m = (float)b_dy/(float)b_dx;
    float b_b = y2-b_m*x2;
    float b_x;
    float b_y;

    float temp_long_r = r1;
    float temp_long_g = g1;
    float temp_long_b = b1;
    float temp_a_r = r1;
    float temp_a_g = g1;
    float temp_a_b = b1;
    float temp_b_r = r3;
    float temp_b_g = g3;
    float temp_b_b = b3;

//    QTextStream(stdout)<<"r1= "<<r1<<" g1= "<<g1<<" b1= "<<b1<<endl;
//    QTextStream(stdout)<<"r2= "<<r2<<" g2= "<<g2<<" b2= "<<b2<<endl;
//    QTextStream(stdout)<<"r3= "<<r3<<" g3= "<<g3<<" b3= "<<b3<<endl;

    unsigned int current_Color1, current_Color2, current_Color3;


    drawable->setPixel(x1,y1,color1);



    //Check for vertical slope (m = infinity)
    if((x1-x2)==0){
        VertLine_p1p2 = true;
    }
    if((x1-x3)==0){
        VertLine_p1p3 = true;
    }
    if((x2-x3)==0){
        VertLine_p2p3 = true;
    }

    if(abs(long_m)<1){
        int long_ddx = abs(x2 - x1);
        float long_dr = r2-r1;
        long_dr = long_dr/long_ddx;
        float long_dg = g2-g1;
        long_dg = long_dg/long_ddx;
        float long_db = b2-b1;
        long_db = long_db/long_ddx;

        int a_ddx = abs(x3 - x1);
        float a_dr = r3-r1;
        a_dr = a_dr/a_ddx;
        float a_dg = g3-g1;
        a_dg = a_dg/a_ddx;
        float a_db = b3-b1;
        a_db = a_db/a_ddx;

        int b_ddx = abs(x2 - x3);
        float b_dr = r2-r3;
        b_dr = b_dr/b_ddx;
        float b_dg = g2-g3;
        b_dg = b_dg/b_ddx;
        float b_db = b2-b3;
        b_db = b_db/b_ddx;

        if(long_dx>0){// x1<x2
            for(float x = x1+1;x<=x2;x++){
                long_y=long_m*x+long_b;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                point.x =

                phong()

                if(x<=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    draw_line_Bres(x,long_y,x,a_y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);
                    draw_line_Bres(x,long_y,x,b_y,current_Color1,current_Color3);
                }

            }
        }
        else{
            for(float x=x1-1;x>=x2;x--){
                long_y=long_m*x+long_b;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(x>=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }
                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    draw_line_Bres(x,long_y,x,a_y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }
                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    draw_line_Bres(x,long_y,x,b_y,current_Color1,current_Color3);
                }
            }
        }
    }
    else{
        int long_ddy = abs(y2 - y1);
        float long_dr = r2-r1;
        long_dr = long_dr/long_ddy;
        float long_dg = g2-g1;
        long_dg = long_dg/long_ddy;
        float long_db = b2-b1;
        long_db = long_db/long_ddy;

        int a_ddy = abs(y3 - y1);
        float a_dr = r3-r1;
        a_dr = a_dr/a_ddy;
        float a_dg = g3-g1;
        a_dg = a_dg/a_ddy;
        float a_db = b3-b1;
        a_db = a_db/a_ddy;

        int b_ddy = abs(y2 - y3);
        float b_dr = r2-r3;
        b_dr = b_dr/b_ddy;
        float b_dg = g2-g3;
        b_dg = b_dg/b_ddy;
        float b_db = b2-b3;
        b_db = b_db/b_ddy;

        if(long_dy>0){
            for(float y=y1+1;y<=y2;y++){
                if(VertLine_p1p2){
                    long_x=x1;
                }
                else long_x=(y-long_b)/long_m;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(y<=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    draw_line_Bres(long_x,y,a_x,y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    draw_line_Bres(long_x,y,b_x,y,current_Color1,current_Color3);
                }
            }
        }
        else{
            for(float y=y1-1; y>=y2; y--){
                if(VertLine_p1p2){
                    long_x=x1;
                }
                else long_x=(y-long_b)/long_m;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(y>=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    draw_line_Bres(long_x,y,a_x,y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    draw_line_Bres(long_x,y,b_x,y,current_Color1,current_Color3);
                }
            }
        }
    }

}


float Client::linelength(float x1, float y1, float x2, float y2) {
    float a = abs(x1-x2);
    float b = abs(y1-y2);
    float c = sqrt(a*a+b*b);
    return c;
}

void Client::depthCuePolygon(int x1,int y1,int z1, int x2, int y2, int z2, int x3, int y3, int z3, unsigned int nearColor, unsigned int farColor){
    if(z1<=200 && z1>=0 && z2<=200 && z2>=0 && z3<=200 && z3>=0){
        float rNear = (nearColor>>16)& 0xff;
        float gNear = (nearColor>>8) & 0xff;
        float bNear = nearColor & 0xff;
        float rFar = (farColor>>16)& 0xff;
        float gFar = (farColor>>8) & 0xff;
        float bFar = farColor & 0xff;

        float dr = rFar-rNear;
        dr = dr/200;
        float dg = gFar-gNear;
        dg = dg/200;
        float db = bFar - bNear;
        db = db/200;

        float z1_percentage = z1/2;
        z1_percentage = z1_percentage/100;
        float z2_percentage = z2/2;
        z2_percentage = z2_percentage/100;
        float z3_percentage = z3/2;
        z3_percentage = z3_percentage/100;

        int r1 = round(rNear + dr*z1);
        int g1 = round(gNear + dg*z1);
        int b1 = round(bNear + db*z1);
        int r2 = round(rNear + dr*z2);
        int g2 = round(gNear + dg*z2);
        int b2 = round(bNear + db*z2);
        int r3 = round(rNear + dr*z3);
        int g3 = round(gNear + dg*z3);
        int b3 = round(bNear + db*z3);

        vec3 normalvector;
        normalvector.x = x2 - x1;
        normalvector.y = y2 - y1;
        normalvector.z = z2 - z1;

        unsigned int current_Color1 = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
        unsigned int current_Color2 = (0xff<<24) + ((r2 & 0xff)<<16) + ((g2 & 0xff)<<8) + (b2 & 0xff);
        unsigned int current_Color3 = (0xff<<24) + ((r3 & 0xff)<<16) + ((g3 & 0xff)<<8) + (b3 & 0xff);

        PolygonRenderer(x1,y1,x2,y2,x3,y3,current_Color1,current_Color2,current_Color3, normalvector);
    }
}


Client::rgbvec Client::phong(vec3 point, float A, float B, rgbvec I_a, rgbvec I_i, vec3 lightsource, vec3 eye, vec3 N, rgbvec kd, float ks, float alpha){
    rgbvec I_eye;
    rgbvec part1;
    vec3 L, V, R;


    part1.r = kd.r * I_a.r/255;
    part1.g = kd.g * I_a.g/255;
    part1.b = kd.b * I_a.b/255;

    //Light direction vector
    L.x = lightsource.x - point.x;
    L.y = lightsource.y - point.y;
    L.z = lightsource.z - point.z;

    //View vector
    V.x = eye.x - point.x;
    V.y = eye.y - point.y;
    V.z = eye.z - point.z;


    vec3 norm_L, norm_N, norm_V, norm_R;
    norm_L = normalize(L);
    norm_N = normalize(N);
    norm_V = normalize(V);
    float dp_NL = dotproduct(norm_L, norm_N);
    norm_R.x = 2*dp_NL*norm_N.x - norm_L.x;
    norm_R.y = 2*dp_NL*norm_N.y - norm_L.x;
    norm_R.z = 2*dp_NL*norm_N.z - norm_L.x;

    float di = veclength(lightsource, point);
    float fatt = 1/(A+B*di);

    rgbvec part2;
    part2.r = kd.r * dp_NL;
    part2.g = kd.g * dp_NL;
    part2.b = kd.b * dp_NL;
    rgbvec part3;
    part3.r = ks * kd.r * pow(dotproduct(norm_V, norm_R), alpha);
    part3.g = ks * kd.g * pow(dotproduct(norm_V, norm_R), alpha);
    part3.b = ks * kd.b * pow(dotproduct(norm_V, norm_R), alpha);

    I_eye.r = part1.r + I_i.r * fatt * (part2.r + part3.r)/255;
    I_eye.g = part1.g + I_i.g * fatt * (part2.g + part3.g)/255;
    I_eye.b = part1.b + I_i.b * fatt * (part2.b + part3.b)/255;


    return I_eye;

}

float Client::dotproduct(vec3 vec1, vec3 vec2){
    float dp;
    dp = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    return dp;
}

float Client::veclength(vec3 vec1, vec3 vec2){
    float vector_length;
    vec3 vec;
    vec.x = vec1.x - vec2.x;
    vec.y = vec1.y - vec2.y;
    vec.z = vec1.z - vec2.z;

    vector_length = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    return vector_length;
}

Client::vec3 Client::normalize(vec3 vec){
    vec3 vector_norm;
    float vector_length = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    vector_norm.x = vec.x/vector_length;
    vector_norm.y = vec.y/vector_length;
    vector_norm.z = vec.z/vector_length;

    return vector_norm;
}

//void Client::phong(float fatt, float I_a, float I_i, float N, float L, float V, float R, float kd, float ks, float alpha){

//}

bool Client::SimpDrawer(char* filename[], unsigned int nearColour, unsigned int farColour){
    ifstream fin;

    fin.open(filename[1]);// open simp file
    if(fin.fail()){// check if open successfully
        QTextStream(stdout) << "file open error.."<<endl;
        return false;
    }

    const char* tempTok[MAX_TOKENS][MAX_TOKENS] = {}; // initialize to 0
    int lineCount=0;
    const char* token[MAX_TOKENS][MAX_TOKENS] = {};

    while(!fin.eof()){
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];

        fin.getline(buf, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index

        tempTok[lineCount][n] = strtok(buf, DELIMITER); // first token

        if (tempTok[lineCount][0]) // zero if line is blank
        {
          for (n = 1; n < MAX_TOKENS; n++)
          {
            tempTok[lineCount][n] = strtok(NULL, DELIMITER); // subsequent tokens
            if (!tempTok[lineCount][n]) break; // no more tokens
          }
        }

        int i =0;
        // process (print) the tokens
        for (i; i < n; i++){
          token[lineCount][i] = strdup(tempTok[lineCount][i]);
        }
        token[lineCount][i] = "~";
        lineCount++;
    }
    fin.close();

    std::stack<Mat>mstack;
    Mat m;
    mstack.push(m);
    Mat world_m;
    world_m.mat[0][0]=3.75;
    world_m.mat[1][1]=3.75;
    world_m.mat[0][3]=375;
    world_m.mat[1][3]=375;

    Mat projection_m;

    bool fill = true;

    int x1,x2,x3,y1,y2,y3,z1,z2,z3;// temp variables for assigning polygon


    for(int j=0;j<lineCount;j++){

        int i = 0; //command iteration
        while(strcmp(token[j][i],"~")!=0){
            if(strcmp(token[j][i],"#")==0){} // do nothing if the line is a comment
            /////////////////
            // CTM Section //
            /////////////////
            // want to only do one push per scope, so need to iterate through
            else if((strcmp(token[j][i],"{"))==0){
                Mat prev_m = mstack.top();
                Mat m;
                int k=j+1;
                while((strcmp(token[k][i],"translate"))==0 || (strcmp(token[k][i],"scale"))==0 || (strcmp(token[k][i],"rotate"))==0){
                    if((strcmp(token[k][i],"translate"))==0){
                        m.mat[0][3]=m.mat[0][3]+atof(token[k][i+1]);
                        m.mat[1][3]=m.mat[1][3]+atof(token[k][i+2]);
                        m.mat[2][3]=m.mat[2][3]+atof(token[k][i+3]);
                        k++;
                    }
                    else if((strcmp(token[k][i],"scale"))==0){
                        Mat tempm;
                        Mat tempResult;
                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    tempResult.mat[ii][jj]=0;
                                }
                        }
                        tempm.mat[0][0]=atof(token[k][i+1]);
                        tempm.mat[1][1]=atof(token[k][i+2]);
                        tempm.mat[2][2]=atof(token[k][i+3]);

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    for(int kk=0;kk<4;kk++){
                                        tempResult.mat[ii][jj]+= m.mat[ii][kk]*tempm.mat[kk][jj];
                                    }
                                }
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    m.mat[ii][jj]=tempResult.mat[ii][jj];
                                }
                        }
                        k++;

                    }
                    else if((strcmp("rotate",token[k][i]))==0){
                        Mat tempm;
                        Mat tempResult;
                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    tempResult.mat[ii][jj]=0;
                                }
                        }

                        if ((strcmp(token[k][i+1],"X"))==0){
                            tempm.mat[1][1]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][2]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][1]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][2]=cos(atof(token[k][i+2])*PI/180);
                        }
                        else if((strcmp(token[k][i+1],"Y"))==0){
                            tempm.mat[0][0]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[0][2]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][0]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][2]=cos(atof(token[k][i+2])*PI/180);
                        }
                        else if((strcmp(token[k][i+1],"Z"))==0){
                            tempm.mat[0][0]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[0][1]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][0]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][1]=cos(atof(token[k][i+2])*PI/180);
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    for(int kk=0;kk<4;kk++){
                                        tempResult.mat[ii][jj]+= m.mat[ii][kk]*tempm.mat[kk][jj];
                                    }
                                }
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    m.mat[ii][jj]=tempResult.mat[ii][jj];
                                }
                        }
                        k++;
                    }
                    else{
                        break;
                    }
                }

                // multiply the current CTM by the previous CTM
                Mat tempResult;
                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            tempResult.mat[ii][jj]=m.mat[ii][jj];
                            m.mat[ii][jj] = 0;
                        }
                }
                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            for(int kk=0;kk<4;kk++){
                                m.mat[ii][jj]+= tempResult.mat[ii][kk]*prev_m.mat[kk][jj];
                            }
                        }
                }
                // always push
                mstack.push(m);
                i++;
            }
            else if((strcmp(token[j][i],"}"))==0){
                // always pop
                mstack.pop();
                i++;

            }

            ////////////////
            // wire/frame //
            ////////////////
            else if((strcmp(token[j][i],"wire"))==0){
                fill = false;
                i++;
            }
            else if((strcmp(token[j][i],"filled"))==0){
                fill = true;
                i++;
            }

            ////////////////////
            // Render Section //
            ////////////////////
            else if((strcmp(token[j][i],"polygon"))==0){
                Mat tempResult;
                Mat tempResult2;
                Mat CTM;
                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        tempResult.mat[ii][jj]=mstack.top().mat[ii][jj];
                        CTM.mat[ii][jj]=0;
                        tempResult2.mat[ii][jj]=0;
                    }
                }

                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        for(int kk=0;kk<4;kk++){
                            tempResult2.mat[ii][jj]+= world_m.mat[ii][kk]*tempResult.mat[kk][jj];
                        }
                    }
                }

                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        for(int kk=0;kk<4;kk++){
                            CTM.mat[ii][jj]+= projection_m.mat[ii][kk]*tempResult2.mat[kk][jj];
                        }
                    }
                }

//                for(int ii=0;ii<4;ii++){
//                    for(int jj=0;jj<4;jj++){
//                        for(int kk=0;kk<4;kk++){
//                            CTM.mat[ii][jj]+= world_m.mat[ii][kk]*tempResult.mat[kk][jj];
//                        }
//                    }
//                }

                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        QTextStream(stdout) << CTM.mat[ii][jj] << " ";
                    }
                    QTextStream(stdout) << " " << endl;
                }
                QTextStream(stdout) << " " << endl;

                float temp_x1 = atof(token[j][i+1]);
                float temp_y1 = atof(token[j][i+2]);
                float temp_z1 = atof(token[j][i+3]);
                float temp_x2 = atof(token[j][i+4]);
                float temp_y2 = atof(token[j][i+5]);
                float temp_z2 = atof(token[j][i+6]);
                float temp_x3 = atof(token[j][i+7]);
                float temp_y3 = atof(token[j][i+8]);
                float temp_z3 = atof(token[j][i+9]);

                x1 = temp_x1*CTM.mat[0][0]+temp_y1*CTM.mat[0][1]+temp_z1*CTM.mat[0][2]+CTM.mat[0][3];
                y1 = temp_x1*CTM.mat[1][0]+temp_y1*CTM.mat[1][1]+temp_z1*CTM.mat[1][2]+CTM.mat[1][3];
                z1 = temp_x1*CTM.mat[2][0]+temp_y1*CTM.mat[2][1]+temp_z1*CTM.mat[2][2]+CTM.mat[2][3];
                x2 = temp_x2*CTM.mat[0][0]+temp_y2*CTM.mat[0][1]+temp_z2*CTM.mat[0][2]+CTM.mat[0][3];
                y2 = temp_x2*CTM.mat[1][0]+temp_y2*CTM.mat[1][1]+temp_z2*CTM.mat[1][2]+CTM.mat[1][3];
                z2 = temp_x2*CTM.mat[2][0]+temp_y2*CTM.mat[2][1]+temp_z2*CTM.mat[2][2]+CTM.mat[2][3];
                x3 = temp_x3*CTM.mat[0][0]+temp_y3*CTM.mat[0][1]+temp_z3*CTM.mat[0][2]+CTM.mat[0][3];
                y3 = temp_x3*CTM.mat[1][0]+temp_y3*CTM.mat[1][1]+temp_z3*CTM.mat[1][2]+CTM.mat[1][3];
                z3 = temp_x3*CTM.mat[2][0]+temp_y3*CTM.mat[2][1]+temp_z3*CTM.mat[2][2]+CTM.mat[2][3];

                if(fill==true){
                    depthCuePolygon(x1,y1,z1,x2,y2,z2,x3,y3,z3,nearColour,farColour);
                }
                else{
                    draw_line_Bres(x1,y1,x2,y2,0xffffffff,0xffffffff);
                    draw_line_Bres(x1,y1,x3,y3,0xffffffff,0xffffffff);
                    draw_line_Bres(x2,y2,x3,y3,0xffffffff,0xffffffff);
                }

                i++;
            }
            else if((strcmp(token[j][i],"mesh"))==0){
                Mat tempResult;
                Mat CTM;
                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        tempResult.mat[ii][jj]=mstack.top().mat[ii][jj];
                        CTM.mat[ii][jj]=0;
                    }
                }

                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            for(int kk=0;kk<4;kk++){
                                CTM.mat[ii][jj]+= world_m.mat[ii][kk]*tempResult.mat[kk][jj];
                            }
                        }
                }

                meshDrawer(token[j][i+1], CTM,nearColour,farColour);
                i++;
            }
            else if((strcmp(token[j][i],"camera"))==0){
                float xlo, ylo, hither, xhi, yhi, yon;
                xlo = atof(token[j][i+1]);
                QTextStream(stdout) << "xlo " << xlo << endl;
                ylo = atof(token[j][i+2]);
                QTextStream(stdout) << "ylo " << ylo << endl;
                xhi = atof(token[j][i+3]);
                QTextStream(stdout) << "xhi " << xhi << endl;
                yhi = atof(token[j][i+4]);
                QTextStream(stdout) << "yhi " << yhi << endl;
                hither = atof(token[j][i+5]);
                QTextStream(stdout) << "hither " << hither << endl;
                yon = atof(token[j][i+6]);
                QTextStream(stdout) << "yon " << yon << endl;

//                projection_m = projection(xlo, ylo, hither, xhi, yhi, yon);

                projection_m.mat[0][0] = (2*hither)/(xhi-xlo);
                projection_m.mat[0][2] = (xhi+xlo)/(xhi-xlo);
                projection_m.mat[1][1] = (2*hither)/(yhi-ylo);
                projection_m.mat[1][2] = (yhi+ylo)/(yhi-ylo);
                projection_m.mat[2][2] = (yon + hither)/(yon-hither);
                projection_m.mat[2][3] = (2*yon*hither)/(yon-hither);
                projection_m.mat[3][2] = 1;
                projection_m.mat[3][3] = 0;

                j++;
            }
            else if((strcmp(token[j][i],"ambient"))==0){
                float amb_r, amb_g, amb_b;
                amb_r = atof(token[j][i+1]);
                amb_g = atof(token[j][i+2]);
                amb_b = atof(token[j][i+3]);

                j++;
            }
            else if((strcmp(token[j][i],"surface"))==0){
                float s_r, s_g, s_b;
                s_r = atof(token[j][i+1]);
                s_g = atof(token[j][i+2]);
                s_b = atof(token[j][i+3]);

                float ks; //Specular coefficient - Defaults to 0.3
                ks = atof(token[j][i+4]);

                float alpha; //Specular exponent - Defaults to 8
                alpha = atof(token[j][i+5]);

                j++;
            }
            else break;

        }
    }

    return true;
}

struct Client::MeshCoord{
    int x;
    int y;
    int z;
};
typedef struct MeshCoord MeshCoord;

//Mat Client::projection(int xlo, int ylo, int hither, int xhi, int yhi, int yon){
////    float xc, yc, zc, wc;
////    float xp, yp;
////    float xn, yn, zn;
////    float n = hither;

////    xp = (n*xe)/ze;
////    yp = (n*ye)/ze;

////    xn = (2*xp)/(xhi-xlo);
////    yn = (2*yp)/(yhi-ylo);


//    Mat projection_m;
//    projection_m.mat[0][0] = (2*hither)/(xhi-xlo);
//    projection_m.mat[0][2] = (xhi+xlo)/(xhi-xlo);
//    projection_m.mat[1][1] = (2*hither)/(yhi-ylo);
//    projection_m.mat[1][2] = (yhi+ylo)/(yhi-ylo);
//    projection_m.mat[2][2] = (yon + hither)/(yon-hither);
//    projection_m.mat[2][3] = (2*yon*hither)/(yon-hither);
//    projection_m.mat[3][2] = -1;
//    projection_m.mat[3][3] = 0;

//    return projection_m;
//}

bool Client::meshDrawer(const char* filename, Mat m, unsigned int nearColor, unsigned int farColor) {
    ifstream fin;

    fin.open(filename);// open simp file
    if(fin.fail()){// check if open successfully
        QTextStream(stdout) << "file open error.."<<endl;
        return false;
    }
    const char* token[MAX_TOKENS][MAX_TOKENS] = {}; // initialize to 0
    const char* realtoken[MAX_TOKENS][MAX_TOKENS] = {};
    int tokencount[MAX_TOKENS] = {};
    int linecount=0;
    //char buf[MAX_CHARS_PER_LINE];

    char buf[MAX_CHARS_PER_LINE];
    while(!fin.eof()){
        // read an entire line into memory

        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);

        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index

        // array to store memory addresses of the tokens in buf

        // parse the line
        token[linecount][n] = strtok(buf, DELIMITER); // first token
        if (token[linecount][0]) // zero if line is blank
        {
          for (n = 1; n < MAX_TOKENS; n++)
          {
            token[linecount][n] = strtok(0, DELIMITER); // subsequent tokens

            if (!token[linecount][n]) break; // no more tokens
          }
        }
        tokencount[linecount] = n;

        // process (print) the tokens
        for (int i = 0; i < n+1; i++){ // n = #of tokens
          if(i<n) {
              realtoken[linecount][i] = strdup(token[linecount][i]);
          }
          else {
              realtoken[linecount][i] = "endofline";
          }
//          QTextStream(stdout) << "RealToken[" << linecount << "]["<<i<<"] = " << realtoken[linecount][i] << endl;
        }
        linecount++;
    }

    fin.close();

    int row = atoi(realtoken[0][0]);
    int col = atoi(realtoken[1][0]);


    meshPixel grid_points[row][col];
    int colCounter=2;

    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            grid_points[i][j].x = atoi(realtoken[colCounter][0]);
            grid_points[i][j].y = atoi(realtoken[colCounter][1]);
            grid_points[i][j].z = atoi(realtoken[colCounter][2]);
            colCounter++;

        }
//        QTextStream(stdout)<<" "<<endl;
    }

     //transform the grid points by CTM
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            float temp_x1 = grid_points[i][j].x;
            float temp_y1 = grid_points[i][j].y;
            float temp_z1 = grid_points[i][j].z;

            grid_points[i][j].x = temp_x1*m.mat[0][0]+temp_y1*m.mat[0][1]+temp_z1*m.mat[0][2]+m.mat[0][3];
            grid_points[i][j].y = temp_x1*m.mat[1][0]+temp_y1*m.mat[1][1]+temp_z1*m.mat[1][2]+m.mat[1][3];
            grid_points[i][j].z = temp_x1*m.mat[2][0]+temp_y1*m.mat[2][1]+temp_z1*m.mat[2][2]+m.mat[2][3];

        }
    }
    for(int i=0; i<row;i++){
        for (int j=0;j<col-1;j++){
            if(j<col && i<row-1){
                depthCuePolygon(grid_points[i][j].x,grid_points[i][j].y,grid_points[i][j].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,nearColor,farColor);
                depthCuePolygon(grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,grid_points[i+1][j+1].x,grid_points[i+1][j+1].y,grid_points[i+1][j+1].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,nearColor,farColor);
            }
        }
    }
    return true;
}

