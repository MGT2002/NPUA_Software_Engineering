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
    void setX(double x)
    {
        this->x = x;
    }
    double getY() const
    {
        return y;
    }
    void setY(double y)
    {
        this->y = y;
    }
    
    bool operator<(const Point& p2) const
    {
        double res = x + y - p2.x - p2.y; 
        return res < 0 ? true : false;
    }
    friend ostream& operator<<(ostream& o, const Point& p)
    {
        o << "(" << p.x << ", " << p.y << ")";
        return o;
    }
    friend istream& operator>>(istream& i, const Point& p)
    {
        i >> setw(10) >> p.x;
        i.ignore(1);
        i >> setw(10) >> p.y;
        
        return i;
    }
};