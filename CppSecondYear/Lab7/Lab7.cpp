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
    
    //cout << c.setPosition(0.4, 0.5) << endl;
    //cout << c.setPosition(0.5, 0.5) << endl;
    printCircle(c);
    printCircle(c2);
    
    Point p  = *new Point(0.5,0.5);
    cout << "point(" << p.getX() << "," << p.getY() <<") is in circle -> " << isInCircle(c, p) << endl;
    cout << "intersect count -> " << circleIntersectionCount(c, c2) << endl;
    cout << "Length of c -> " << getLength(c) << endl;
    cout << "Area of c -> " << getArea(c) << endl;
    cout << "Distance between c and c2 -> " << distanceBetweenCircles(c, c2) << endl;
    double mx = 3;
    cout << "move c by " << mx << ", moveX validation passed -> " << moveX(c, mx) << endl; 
    printCircle(c);
    double my = -3;
    cout << "move c by " << my << ", moveY validation passed -> " << moveY(c, my) << endl; 
    printCircle(c);
    double k = 0.3;
    cout << "multiply r of c by *" << k << ", multiplyR validation passed -> " << multiplyR(c, k) << endl; 
    printCircle(c);
    c.setX(10).setY(20).setRadius(3);
    printCircle(c);
    
    return 0;
}