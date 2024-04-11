#ifndef CIRCLE_H
#define CIRCLE_H

class Circle{
    private:
    static int instCount;
    
    double r;
    Point* position;
    
    public:
    
    Circle(double r, double x, double y);
    Circle(double x, double y);
    Circle(double r);
    explicit Circle(const Circle& other);
    ~Circle();
    
    double getR() const;
    bool setR(const double r);
    Point&  getPoint() const;
    bool setPoint(const Point& p);
    bool setPosition(const double x, const double y);
    string info();
    Circle& setRadius(double r);
    Circle& setX(double x);
    Circle& setY(double y);
    
    private:
    bool validateR(const double r);
    bool validateCircle(const double r, const double x, const double y);
    
    friend double getLength(Circle& c);
    
    friend ostream& operator<<(ostream& o, Circle& c);
    friend istream& operator>>(istream& i, Circle& c);
};

#endif