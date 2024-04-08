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
};