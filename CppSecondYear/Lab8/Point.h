#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <iomanip>

using namespace std;

class Point 
{
    private:
    static int instCount;
    double x;
    double y;
    
    public:
        
    Point(double x, double y);
    Point(const Point& other);
    ~Point();
    
    void setXY(double x, double y);
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    
    bool operator<(const Point& p2) const;
    bool operator>(const Point& p2) const;
    bool operator<=(const Point& p2) const;
    bool operator>=(const Point& p2) const;
    bool operator==(const Point& p2) const;
    bool operator!=(const Point& p2) const;
    Point operator+(const Point& p2) const;
    Point operator-(const Point& p2) const;
    Point& operator+=(const Point& p2);
    Point& operator-=(const Point& p2);
    Point& operator++();
    Point operator++(int);
    /*Point& operator--();
    Point operator--(int);*/
    friend Point& operator--(Point& p);
    friend Point operator--(Point& p, int);
    friend ostream& operator<<(ostream& o, const Point& p);
    friend istream& operator>>(istream& i, Point& p);
};

#endif