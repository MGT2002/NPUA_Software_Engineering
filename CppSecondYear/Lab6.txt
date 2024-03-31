#include <iostream>

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
        cout << "Point created! Count of instances -> "
        << ++instCount << endl;
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
        this->r = r;
        cout << "Circle created! Count of instances -> "
        << ++instCount << endl;
    }
    Circle(double x, double y) : Circle(1, x, y){}
    Circle(double r) : Circle(r, 0, 0){}
    ~Circle()
    {
        cout << "Circle deleted! Count of instances -> "
        << --instCount << endl;
    }
    
    double getR() const
    {
        return r;
    }
    void setR(const double r)
    {
        this->r = r;
    }
    const Point&  getPosition() const
    {
        return position;
    }
    void setPosition(const double x, const double y)
    {
        position.setXY(x, y);
    }
    
    private:
    bool validateR(const double r)
    {
        if(r > 0)
            return true;
        return false;
    }
}; int Circle::instCount = 0;

void printCircle(const Circle& c)
{
    cout << "R = " << c.getR()<< ", ";
    cout << "(X = " << c.getPosition().getX() << ", ";
    cout << "Y = " << c.getPosition().getY() << ")" <<endl;
}
int main ()
{
    Circle c(10, 0.5, 0.8);  
    Circle c1(1, 1, 1);  
    
    printCircle(c);
    printCircle(c1);

    return 0;
}