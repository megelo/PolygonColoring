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
        draw_starburst();
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

    QTextStream(stdout)<<"r1: "<<r1<<" "<<"g1: "<<g1<<" "<<"b1: "<<b1<<endl;
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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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

                    QTextStream(stdout)<<"r: "<<roundr<<" "<<"g: "<<roundg<<" "<<"be: "<<roundb<<endl;

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
