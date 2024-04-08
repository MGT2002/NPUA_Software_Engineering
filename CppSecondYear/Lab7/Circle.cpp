#include <iostream>
#include <sstream> 
#include "Point.cpp"

using namespace std;

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
    const Point&  getPoint() const
    {
        return position;
    }
    bool setPoint(const Point& p)
    {
        return setPosition(p.getX(), p.getY());
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
    
    Circle& setRadius(double r)
    {
        setR(r);
        return *this;
    }
    Circle& setX(double x)
    {
        setPosition(x, position.getY());
        return *this;
    }
    Circle& setY(double y)
    {
        setPosition(position.getX(), y);
        return *this;
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
    
    friend double getLength(Circle& c);
};
