#include <iostream>
#include <ctime>
#include "client.h"
#include <math.h>
#include <QTextStream>
#define PI  3.14159265358979323846

#include <fstream> //parse simp file
using std::ifstream;
#include <string>
#include <stack>
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS = 500;
const char* const DELIMITER = "\" ,()\n";

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
//        PolygonRenderer(700, 700, 600, 350, 100, 150, 0x00ff0000, 0x000000ff, 0x0000ff00);
        mesh(1);
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

int Client::Distance(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void Client::PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3){
    // initialize edge case for vertical lines
    bool VertLine_p1p2 = false;
    bool VertLine_p1p3 = false;
    bool VertLine_p2p3 = false;
    float x1,y1,x2,y2,x3,y3;

    // Assigning parameters to p1,p2,p3
    // (x1,y1)->(x2,y2) is assigned to be the longest line
    if(linelength(xx1,yy1,xx2,yy2)>=linelength(xx1,yy1,xx3,yy3) && linelength(xx1,yy1,xx2,yy2)>=linelength(xx2,yy2,xx3,yy3)){
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        x3 = xx3;
        y3 = yy3;
        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

    }
    else if(linelength(xx2,yy2,xx3,yy3)>=linelength(xx1,yy1,xx2,yy2) && linelength(xx2,yy2,xx3,yy3)>=linelength(xx1,yy1,xx3,yy3)){
        x1 = xx2;
        y1 = yy2;
        x2 = xx3;
        y2 = yy3;
        x3 = xx1;
        y3 = yy1;
        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;
    }
    else{
        x1 = xx1;
        y1 = yy1;
        x2 = xx3;
        y2 = yy3;
        x3 = xx2;
        y3 = yy2;
        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;
    }

    QTextStream(stdout)<<"(x,y)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;



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

    int r1,g1,b1,r2,b2,g2,r3,g3,b3,long_rounded_r,long_rounded_g,long_rounded_b,a_rounded_r,a_rounded_g,a_rounded_b,b_rounded_r,b_rounded_g,b_rounded_b;

    r1 = (color1>>16)& 0xff;
    g1 = (color1>>8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2>>16)& 0xff;
    g2 = (color2>>8) & 0xff;
    b2 = color2 & 0xff;
    r3 = (color3>>16)& 0xff;
    g3 = (color3>>8) & 0xff;
    b3 = color3 & 0xff;

    float temp_long_r = r1;
    float temp_long_g = g1;
    float temp_long_b = b1;
    float temp_a_r = r1;
    float temp_a_g = g1;
    float temp_a_b = b1;
    float temp_b_r = r3;
    float temp_b_g = g3;
    float temp_b_b = b3;

    QTextStream(stdout)<<"r1= "<<r1<<" g1= "<<g1<<" b1= "<<b1<<endl;
    QTextStream(stdout)<<"r2= "<<r2<<" g2= "<<g2<<" b2= "<<b2<<endl;
    QTextStream(stdout)<<"r3= "<<r3<<" g3= "<<g3<<" b3= "<<b3<<endl;

    unsigned int current_Color1, current_Color2, current_Color3;

    drawable->setPixel(x1,y1,color1);



    //Check for vertical slope (m = infinity)
    if((x1-x2)==0){
        VertLine_p1p2 = true;
        QTextStream(stdout)<<"p1p2 inf slope"<<endl;
    }
    if((x1-x3)==0){
        VertLine_p1p3 = true;
        QTextStream(stdout)<<"p1p3 inf slope"<<endl;
    }
    if((x2-x3)==0){
        VertLine_p2p3 = true;
        QTextStream(stdout)<<"p2p3 inf slope"<<endl;
    }

    //QTextStream(stdout)<<"(y,x)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;
    //QTextStream(stdout)<<"Slope= "<<long_m<<" || x1,y1="<<x1<<","<<y1<<"|| x2,y2="<<x2<<","<<y2<<"|| x3,y3="<<x3<<","<<y3<<endl;

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
            //QTextStream(stdout)<<"long_ddx, a_ddx, b_ddx= "<<long_ddx<<", "<<a_ddx<<", "<<b_ddx<<endl;
            //QTextStream(stdout)<<"a_dr, a_dg, a_db= "<<a_dr<<", "<<a_dg<<", "<<a_db<<endl;

            for(float x = x1+1;x<=x2;x++){
                long_y=long_m*x+long_b;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

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
                    //QTextStream(stdout)<<"a_rounded_r= "<<a_rounded_r<<" a_rounded_g= "<<a_rounded_g<<" a_rounded_b= "<<a_rounded_b<<endl;


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
                    //QTextStream(stdout)<<"a_rounded_r= "<<a_rounded_r<<" a_rounded_g= "<<a_rounded_g<<" a_rounded_b= "<<a_rounded_b<<endl;


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
                long_x=(y-long_b)/long_m;

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
                    //QTextStream(stdout)<<"a_rounded_r= "<<a_rounded_r<<" a_rounded_g= "<<a_rounded_g<<" a_rounded_b= "<<a_rounded_b<<endl;


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
                long_x=(y-long_b)/long_m;

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
                    //QTextStream(stdout)<<"a_rounded_r= "<<a_rounded_r<<" a_rounded_g= "<<a_rounded_g<<" a_rounded_b= "<<a_rounded_b<<endl;


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

struct Client::pixel{
    int x;
    int y;
};

void Client::mesh(int filled) {
    if(filled == 0) {
        qsrand(time(NULL)); // random seeding
        struct pixel grid[10][10];
        int shift_x;
        int shift_y;
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                grid[i][j].x = 100+60*j;
                grid[i][j].y = 100+60*i;

                shift_x = qrand() % 20;
                shift_y = qrand() % 20;
                grid[i][j].x += shift_x;
                grid[i][j].y += shift_y;
                drawable->setPixel(grid[i][j].x,grid[i][j].y,0xffffffff);
            }
        }
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                int r1 = qrand() % 256;
                int g1 = qrand() % 256;
                int b1 = qrand() % 256;
                int r2 = qrand() % 256;
                int g2 = qrand() % 256;
                int b2 = qrand() % 256;
                unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);
                unsigned int colour2 = (0xff<<24)+((r2&0xff)<<16)+((g2&0xff)<<8)+(b2&0xff);

                if(j<9){
                    draw_line_Bres(grid[i][j].x,grid[i][j].y,grid[i][j+1].x,grid[i][j+1].y,colour1,colour2);
                }
                if(i<9){
                    draw_line_Bres(grid[i][j].x,grid[i][j].y,grid[i+1][j].x,grid[i+1][j].y,colour1,colour2);
                }
                if(i!=0 && i<9 && j<9){
                    draw_line_Bres(grid[i][j].x,grid[i][j].y,grid[i-1][j+1].x,grid[i-1][j+1].y,colour1,colour2);
                }
            }
        }
    }
    else { //filled = 1
        qsrand(time(NULL)); // random seeding
        struct pixel grid[10][10];
        unsigned int colorgrid[10][10];
        int shift_x;
        int shift_y;
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                grid[i][j].x = 100+60*j;
                grid[i][j].y = 100+60*i;

                shift_x = qrand() % 20;
                shift_y = qrand() % 20;
                grid[i][j].x += shift_x;
                grid[i][j].y += shift_y;

                int r = qrand() % 256;
                int g = qrand() % 256;
                int b = qrand() % 256;
                unsigned int color = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
                colorgrid[i][j] = color;
                drawable->setPixel(grid[i][j].x,grid[i][j].y,0xffffffff);
            }
        }
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                if(j<9 && i<9) {
                    PolygonRenderer(grid[i][j].x, grid[i][j].y, grid[i][j+1].x, grid[i][j+1].y, grid[i+1][j].x, grid[i+1][j].y, colorgrid[i][j], colorgrid[i][j+1], colorgrid[i+1][j]);
                    PolygonRenderer(grid[i+1][j+1].x, grid[i+1][j+1].y, grid[i][j+1].x, grid[i][j+1].y, grid[i+1][j].x, grid[i+1][j].y, colorgrid[i][j], colorgrid[i][j+1], colorgrid[i+1][j]);
                }
            }
        }
    }
}

//bool Client::SimpDrawer(){
//    ifstream fin;

//    fin.open("newtest.txt");// open simp file
//    if(fin.fail()){// check if open successfully
//        QTextStream(stdout) << "file open error.."<<endl;
//        return false;
//    }
//    const char* token[MAX_TOKENS][MAX_TOKENS] = {}; // initialize to 0
//    const char* realtoken[MAX_TOKENS][MAX_TOKENS] = {};
//    int tokencount[MAX_TOKENS] = {};
//    int lineCount=0;
//    //char buf[MAX_CHARS_PER_LINE];

//    char buf[MAX_CHARS_PER_LINE];
//    while(!fin.eof()){
//        // read an entire line into memory

//        char buf[MAX_CHARS_PER_LINE];
//        fin.getline(buf, MAX_CHARS_PER_LINE);

//        // parse the line into blank-delimited tokens
//        int n = 0; // a for-loop index

//        // array to store memory addresses of the tokens in buf

//        // parse the line
//        token[lineCount][n] = strtok(buf, DELIMITER); // first token
//        if (token[lineCount][0]) // zero if line is blank
//        {
//          for (n = 1; n < MAX_TOKENS; n++)
//          {
//            token[lineCount][n] = strtok(0, DELIMITER); // subsequent tokens

//            if (!token[lineCount][n]) break; // no more tokens
//          }
//        }
//        tokencount[lineCount] = n;

//        // process (print) the tokens
//        for (int i = 0; i < n+1; i++){ // n = #of tokens
//          if (i < n) {
//            realtoken[lineCount][i] = strdup(token[lineCount][i]);
//          }
//          else {
//              realtoken[lineCount][i] = "endofline";
//          }
//          QTextStream(stdout) << "RealToken[" << lineCount << "]["<<i<<"] = " << realtoken[lineCount][i] << endl;
//        }
//        lineCount++;
//    }

//    fin.close();

//    using namespace std;

//    stack<const char*> tokenstack;
//    stack<int> xstack;
//    stack<int> ystack;
//    stack<int> zstack;


//    int o = 0;
//    int n = 0;
//    int x1, y1, z1, x2, y2, z2, x3, y3, z3;

//    xstack.push(0); //X
//    ystack.push(0); //Y
//    zstack.push(0); //Z

//    while(o<lineCount) {
//        while(n<tokencount[lineCount]) {
//            n++;
//            if(o == 0 && n == 0 && (strcmp(realtoken[o][n], "{") == 1)) {
//                if(strcmp(realtoken[o][n], "{") == 1) {
//                    tokenstack.push(realtoken[o][n]);
//                }
//                else if(strcmp(realtoken[o][n], "translate") == 1) {
//                    tokenstack.push(realtoken[o][n]);
//                    xstack.push(xstack.top() + atoi(realtoken[o][n+1]));
//                    ystack.push(ystack.top() + atoi(realtoken[o][n+2]));
//                    zstack.push(zstack.top() + atoi(realtoken[o][n+3]));
//                    n+=3;

//                }
//                else if(strcmp(realtoken[o][n], "polygon") == 1) {
//                    x1 = atoi(realtoken[o][n+1]);
//                    y1 = atoi(realtoken[o][n+2]);
//                    z1 = atoi(realtoken[o][n+3]);
//                    n+=3;

//                    x2 = atoi(realtoken[o][n+1]);
//                    y2 = atoi(realtoken[o][n+2]);
//                    z2 = atoi(realtoken[o][n+3]);
//                    n+=3;

//                    x3 = atoi(realtoken[o][n+1]);
//                    y3 = atoi(realtoken[o][n+2]);
//                    z3 = atoi(realtoken[o][n+3]);
//                    n+=3;
//                    PolygonRenderer(x1, y1, x2, y2, x3, y3, 0x00ffffff, 0x00ffffff, 0x00ffffff);
//                }
////                else if(strcmp(realtoken[o][n], "}") == 1) {
////                    bool islatesttransform;
////                    while(strcmp(tokenstack.top(), "{") != 1){
////                        if(islatesttransform){

////                        }
////                        tokenstack.pop();
////                    }
////                }
//            }
//            else {
//                return 1;
//            }
//        }
//        o++;
//    }
//}

