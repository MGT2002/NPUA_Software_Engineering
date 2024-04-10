#include <iostream>
#include <cmath>
#include "Circle.cpp"
#define PI 3.14159265358979323846

using namespace std;

int Circle::instCount = 0;
int Point::instCount = 0;

void printCircle(Circle& c)
{
    cout << c.info() << endl;
}
bool isInCircle(Circle& c, Point& p)
{
    if(pow(p.getX() - c.getPoint().getX(), 2) + pow(p.getY() - c.getPoint().getY(), 2) <= 
        pow(c.getR(), 2))
        return true;
    return false;
}
double distanceBetweenCircles(Circle& c1, Circle& c2)
{
    return sqrt(pow(c1.getPoint().getX() - c2.getPoint().getX(), 2)
    + pow(c1.getPoint().getY() - c2.getPoint().getY(), 2));
}
int circleIntersectionCount(Circle& c1, Circle& c2)
{
    double dist = distanceBetweenCircles(c1, c2);
    double k = c1.getR() + c2.getR();
    
    if (dist > k)
        return 0;
    if (dist == k)
        return 1;
    if(dist > abs(c1.getR() - c2.getR()))
        return 2;
    if(dist == abs(c1.getR() - c2.getR()))
    {
        if(dist == 0) //c1 = c2
            return -1;
        return 1;
    }
    //dist < abs(r1 - r2)
    return 0;
}
double getLength(Circle& c)
{
    return 2* c.r *PI;
}
double getArea(Circle& c)
{
    return c.getR()*c.getR()*PI;
}
bool moveX(Circle& c, double x)
{
    return c.setPosition(c.getPoint().getX() + x, c.getPoint().getY());
}
bool moveY(Circle& c, double y)
{
    return c.setPosition(c.getPoint().getX(), c.getPoint().getY() + y);
}
bool multiplyR(Circle& c, double k)
{
    return c.setR(c.getR() * k);
}
int main ()
{
    Circle c(5, 5, 5);  
    Circle c2(5, 7, 5);  
    printCircle(c);
    printCircle(c2);
    
    Point p1  = *new Point(0.5,0.5);
    Point p2  = *new Point(0.9,0.3);
    cout << "\n\n";
    
    cout << "p1 < p2 -> " << ((p1 < p2) ? "true" : "false") << endl;
    cout << "p1 > p2 -> " << ((p1 < p2) ? "true" : "false") << endl;
    
    cout << p1 << endl;
    cout << p2 << endl;
    
    cout << "\n\n";
    
    return 0;
}