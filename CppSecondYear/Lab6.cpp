#include <iostream>
#include <sstream> 
#include <cmath>
#define PI 3.14159265358979323846

using namespace std;

class Point 
{
    private:
    static int instCount;
    double x;
    double y;
    
    public:
        
    Point(double x, double y)
    {
        setXY(x, y);
        cout << "Point created! Count of instances -> "<< ++instCount << endl;
    }
    ~Point()
    {
        cout << "Point("<< x << ", " << y << ")deleted! " 
        << "Count of instances -> "<< --instCount << endl;
    }
    
    void setXY(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double getX() const
    {
        return x;
    }
    double getY() const
    {
        return y;
    }
}; int Point::instCount = 0;

class Circle{
    private:
    static int instCount;
    
    double r;
    Point position;
    
    public:
    
    Circle(double r, double x, double y) : position(Point(x, y)){
        if(!validateR(r))
            throw invalid_argument("Received not positive value!");
        if(!validateCircle(r, x, y))
            throw invalid_argument("Circle is out of XOY!");
        
        this->r = r;
        cout << "Circle created! Count of instances -> "
        << ++instCount << endl;
    }
    Circle(double x, double y) : Circle(1, x, y) {}
    Circle(double r) : Circle(r, 0, 0) {}
    ~Circle()
    {
        cout << "Circle deleted! Count of instances -> "
        << --instCount << endl;
    }
    
    double getR() const
    {
        return r;
    }
    bool setR(const double r)
    {
        if(!(validateR(r) && validateCircle(r, position.getX(), position.getY())))
            return false;
            
        this->r = r;
        return true;
    }
    const Point&  getPosition() const
    {
        return position;
    }
    bool setPosition(const double x, const double y)
    {
        if(!validateCircle(this->r, x, y))
            return false;
            
        position.setXY(x, y);
        return true;
    }
    string info()
    {               
        ostringstream os;
        
        os << "R = " << r << ", ";
        os << "(X = " << position.getX() << ", ";
        os << "Y = " << position.getY() << ")";
        
        return os.str();
    }
    
    private:
    bool validateR(const double r)
    {
        if(r > 0)
            return true;
        return false;
    }
    bool validateCircle(const double r, const double x, const double y)
    {
        if(x - r >= 0 && y - r >= 0)
            return true;
        return false;
    }
}; int Circle::instCount = 0;

void printCircle(Circle& c)
{
    cout << c.info() << endl;
}
bool isInCircle(Circle& c, Point& p)
{
    if(pow(p.getX() - c.getPosition().getX(), 2) + pow(p.getY() - c.getPosition().getY(), 2) <= 
        pow(c.getR(), 2))
        return true;
    return false;
}
double distanceBetweenCircles(Circle& c1, Circle& c2)
{
    return sqrt(pow(c1.getPosition().getX() - c2.getPosition().getX(), 2)
    + pow(c1.getPosition().getY() - c2.getPosition().getY(), 2));
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
    return 2*c.getR()*PI;
}
double getArea(Circle& c)
{
    return c.getR()*c.getR()*PI;
}
bool moveX(Circle& c, double x)
{
    return c.setPosition(c.getPosition().getX() + x, c.getPosition().getY());
}
bool moveY(Circle& c, double y)
{
    return c.setPosition(c.getPosition().getX(), c.getPosition().getY() + y);
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
    cout << "point is in circle -> " << isInCircle(c, p) << endl;
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
    
    return 0;
}