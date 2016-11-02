#include <iostream>
#include "client.h"
#include <math.h>
#include <QTextStream>
#define PI  3.14159265358979323846

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}


void Client::nextPage() {
    static int pageNumber = 0;
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;

    switch(pageNumber % 4) {
    case 1:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(50, 50, 700, 700, 0x00000000);
//        draw_line_Bres(600, 600, 100, 200, 0x11111111, 0x5678abcd);
//        draw_starburst();
        draw_blerp(100, 450, 200, 350, 650, 150, 0x00ff0000, 0x0000ffff, 0x0000ff00);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        // fall through...
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

void Client::draw_line_Bres(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2) {

    int dx = x2-x1;
    if(x1>x2) {
        dx = x1-x2;
    }

    int dy = y2-y1;
    if(y1>y2) {
        dy = y1-y2;
    }
    int twodx = 2*dx;
    int twody = 2*dy;

    int x = x1;
    int y = y1;

    float r, g ,b, dr, dg, db, drdx, dgdx, dbdx, drdy, dgdy, dbdy;
    int newcolor;
    int r1, g1, b1, r2, g2, b2, roundr, roundg, roundb;
    r1 = (color1>>16)& 0xff;
    g1 = (color1>>8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2>>16)& 0xff;
    g2 = (color2>>8) & 0xff;
    b2 = color2 & 0xff;

    r = r1;
    g = g1;
    b = b1;

    dr = r2 - r1;
    dg = g2 - g1;
    db = b2 - b1;

//    QTextStream(stdout)<<"r1: "<<r1<<" "<<"g1: "<<g1<<" "<<"b1: "<<b1<<endl;
//    QTextStream(stdout)<<"dr1: "<<dr1<<" "<<"dg1: "<<dg1<<" "<<"db1: "<<db1<<endl;
    drawable->setPixel(x1, y1, color1);

    if(dx > dy) {
        int t = twody - twodx;
        int err = twody - dx;

        if(y1 > y2) {
            if(x1 > x2) {
                for(x=x1-1; x>x2; x--) {

                    if(err>=0) {
                        err = err + t;
                        y--;
                    }
                    else {
                        err = err + twody;
                    }

                    drdx = dr/dx;
                    dgdx = dg/dx;
                    dbdx = db/dx;

                    r += drdx;
                    g += dgdx;
                    b += dbdx;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
            else {
                for(x=x1+1; x<x2; x++) {

                    if(err>=0) {
                        err = err + t;
                        y--;
                    }
                    else {
                        err = err + twody;
                    }

                    drdx = dr/dx;
                    dgdx = dg/dx;
                    dbdx = db/dx;

                    r += drdx;
                    g += dgdx;
                    b += dbdx;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
        }
        else {
            if(x1 > x2) {
                for(x=x1-1; x>x2; x--) {

                    if(err>=0) {
                        err = err + t;
                        y++;
                    }
                    else {
                        err = err + twody;
                    }
                    drdx = dr/dx;
                    dgdx = dg/dx;
                    dbdx = db/dx;

                    r += drdx;
                    g += dgdx;
                    b += dbdx;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
            else {
                for(x=x1+1; x<x2; x++) {

                    if(err>=0) {
                        err = err + t;
                        y++;
                    }
                    else {
                        err = err + twody;
                    }
                    drdx = dr/dx;
                    dgdx = dg/dx;
                    dbdx = db/dx;

                    r += drdx;
                    g += dgdx;
                    b += dbdx;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
        }
    }
    else {
        int t = twodx - twody;
        int err = twodx - dy;

        if(x1>x2){
            if(y1>y2){
                for(y=y1-1; y>y2; y--) {
                    if(err>=0) {
                        err = err + t;
                        x--;
                    }
                    else {
                        err = err + twodx;
                    }
                    drdy = dr/dy;
                    dgdy = dg/dy;
                    dbdy = db/dy;

                    r += drdy;
                    g += dgdy;
                    b += dbdy;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
            else{
                for(y=y1+1; y<y2; y++) {
                    if(err>=0) {
                        err = err + t;
                        x--;
                    }
                    else {
                        err = err + twodx;
                    }
                    drdy = dr/dy;
                    dgdy = dg/dy;
                    dbdy = db/dy;

                    r += drdy;
                    g += dgdy;
                    b += dbdy;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
        }
        else {
            if(y1>y2){
                for(y=y1+1; y>y2; y--) {
                    if(err>=0) {
                        err = err + t;
                        x++;
                    }
                    else {
                        err = err + twodx;
                    }
                    drdy = dr/dy;
                    dgdy = dg/dy;
                    dbdy = db/dy;

                    r += drdy;
                    g += dgdy;
                    b += dbdy;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
            else{
                for(y=y1+1; y<y2; y++) {
                    if(err>=0) {
                        err = err + t;
                        x++;
                    }
                    else {
                        err = err + twodx;
                    }
                    drdy = dr/dy;
                    dgdy = dg/dy;
                    dbdy = db/dy;

                    r += drdy;
                    g += dgdy;
                    b += dbdy;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

//                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

                    newcolor = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
                    drawable->setPixel(x, y, newcolor);
                }
            }
        }
    }
}

void Client::draw_starburst() {
    float x1,x2,y1,y2 = 0;
    float space = 2*PI/90;

    for (float theta=0; theta<2*PI; theta+=space){
        x1 = 200;
        y1 = 200;
        x2 = 200 + 75*cos(theta);
        y2 = 200 + 75*sin(theta);
        QTextStream(stdout)<<"(x2,y2)= ("<<x2<<","<<y2<<")"<<endl;
        draw_line_Bres(x1,y1,x2,y2,0xabcd1234, 0xefab7890);
    }
}

void Client::draw_blerp(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color1, unsigned int color2, unsigned int color3) {
    float lengthfrom1to2 = linelength(x1, y1, x2, y2);
    float lengthfrom1to3 = linelength(x1, y1, x3, y3);
    float lengthfrom2to3 = linelength(x2, y2, x3, y3);

    float maxline = std::max({lengthfrom1to2, lengthfrom1to3, lengthfrom2to3});
    float leftx, lefty;
    float rightx, righty;
    float otherx, othery;
    int leftcolor, rightcolor, othercolor;

    if(maxline == lengthfrom1to2) {
        if(x1 < x2) {
            leftx = float(x1);
            lefty = float(y1);
            leftcolor = float(color1);
            rightx = float(x2);
            righty = float(y2);
            rightcolor = float(color2);
        }
        else {
            leftx = float(x2);
            lefty = float(y2);
            leftcolor = float(color2);
            rightx = float(x1);
            righty = float(y1);
            rightcolor = float(color1);
        }
        otherx = float(x3);
        othery = float(y3);
        othercolor = float(color3);
    }
    else if(maxline == lengthfrom1to3) {
        if(x1 < x3) {
            leftx = float(x1);
            lefty = float(y1);
            leftcolor = float(color1);
            rightx = float(x3);
            righty = float(y3);
            rightcolor = float(color3);
        }
        else {
            leftx = float(x3);
            lefty = float(y3);
            leftcolor = float(color3);
            rightx = float(x1);
            righty = float(y1);
            rightcolor = float(color1);
        }
        otherx = float(x2);
        othery = float(y2);
        othercolor = color2;
    }
    else { //maxline == lengthfrom2to3
        if(x2 < x3) {
            leftx = float(x2);
            lefty = float(y2);
            leftcolor = float(color2);
            rightx = float(x3);
            righty = float(y3);
            rightcolor = float(color3);
        }
        else {
            leftx = float(x3);
            lefty = float(y3);
            leftcolor = float(color3);
            rightx = float(x2);
            righty = float(y2);
            rightcolor = float(color2);
        }
        otherx = float(x1);
        othery = float(y1);
        othercolor = float(color1);
    }

    float longdx = rightx - leftx;
    float longdy = righty - lefty;

    float m = float(longdy)/float(longdx);
    float constb = lefty - m * leftx;

    float x, xx1, xx2;
    float y, yy1, yy2;

    float m1 = float(othery-lefty)/float(otherx-leftx);
    float b1 = lefty - m1 * leftx;

    float m2 = float(righty-othery)/float(rightx-otherx);
    float b2 = othery - m2 * otherx;

    float leftr, leftg, leftb;
    float otherside_r, otherside_g, otherside_b;
    float r, g, b;
    float dr, dg, db;
    float drdx, dgdx, dbdx;
    float drdy, dgdy, dbdy;

    float temp_r, temp_g, temp_b;
    float temp_color, temp_color1;

    int roundr, roundg, roundb;
    float dx, dy;

    leftr = (leftcolor>>16)& 0xff;
    leftg = (leftcolor>>8) & 0xff;
    leftb = leftcolor & 0xff;

    rightr = (rightcolor>>16)& 0xff;
    rightg = (rightcolor>>8) & 0xff;
    rightb = rightcolor & 0xff;

    otherr = (othercolor>>16)& 0xff;
    otherg = (othercolor>>8) & 0xff;
    otherb = othercolor & 0xff;

    QTextStream(stdout)<<leftr<<leftg<<leftb<<endl;

    r = leftr;
    g = leftg;
    b = leftb;

    if(abs(longdx) > abs(longdy)){
        if(longdx>=0){
            for(x=leftx; x<rightx; x++){
                y = m*x + constb;
                if(x<otherx) {

                    dr = leftr - otherside_r;
                    dg = leftg - otherside_g;
                    db = leftb - otherside_b;
                    QTextStream(stdout)<<r<<" "<<g<<" "<<b<<endl;

                    yy1 = m1*x + b1;

                    drdx = dr/longdx;
                    dgdx = dg/longdx;
                    dbdx = db/longdx;

                    r += drdx;
                    g += dgdx;
                    b += dbdx;

                    roundr = round(r);
                    roundg = round(g);
                    roundb = round(b);

                    temp_color = (0xff << 24) + ((roundr & 0xff) << 16) + ((roundg & 0xff) << 8) + (roundb & 0xff);
//                    QTextStream(stdout)<<"r: "<<r<<" "<<"g: "<<g<<" "<<"b: "<<b<<endl;
                    draw_line_Bres(x, y, x, yy1, leftcolor, temp_color);
                }
//                else {
//                    otherside_r = (othercolor>>16)& 0xff;
//                    otherside_g = (othercolor>>8) & 0xff;
//                    otherside_b = othercolor & 0xff;

//                    yy2 = m2*x + b2;
//                    draw_line_Bres(x, y, x, yy2, color);
//                }
            }
        }
    }
//    else{
//        if(longdy>0){

//            for(y=lefty; y<righty; y++){
//                x = (y-b)/m;

//                if(y>=othery){
//                    xx2 = (y-b2)/m2;
//                    draw_line_Bres(x, y, xx2, y, color);
//                }
//                else{
//                    xx1 = (y-b1)/m1;
//                    draw_line_Bres(x, y, xx1, y, color);
//                }
//                drawable->setPixel(x, y, color);

//            }
//        }
//        else {
//            for(y=lefty; y>righty; y--){
//                x = (y-b)/m;

//                if(y<othery){
//                    xx2 = (y-b2)/m2;
//                    draw_line_Bres(x, y, xx2, y, color);
//                }
//                else {
//                    xx1 = (y-b1)/m1;
//                    draw_line_Bres(x, y ,xx1, y ,color);
//                }
//                drawable->setPixel(x, y, color);

//            }
//        }
//    }
}

float Client::linelength(float x1, float y1, float x2, float y2) {
    float a = abs(x1-x2);
    float b = abs(y1-y2);
    float c = sqrt(a*a+b*b);
    return c;
}
