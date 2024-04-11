#include <iostream>
#include <cmath>
#include <sstream> 
#include "Point.h"
#include "Circle.h"
#define PI 3.14159265358979323846

using namespace std;

//Point
int Point::instCount = 0;
Point::Point(double x, double y){
    setXY(x, y);
    cout << "Point created! Count of instances -> "<< ++instCount << endl;
}
Point::~Point(){
    cout << "Point("<< x << ", " << y << ")deleted! " 
    << "Count of instances -> "<< --instCount << endl;
}

void Point::setXY(double x, double y){
    this->x = x;
    this->y = y;
}
double Point::getX() const{
    return x;
}
void Point::setX(double x){
    this->x = x;
}
double Point::getY() const{
    return y;
}
void Point::setY(double y){
    this->y = y;
}

bool Point::operator<(const Point& p2) const{
    double res = x + y - p2.x - p2.y; 
    return res < 0 ? true : false;
}
bool Point::operator>(const Point& p2) const{
    double res = x + y - p2.x - p2.y; 
    return res > 0 ? true : false;
}
bool Point::operator<=(const Point& p2) const{
    double res = x + y - p2.x - p2.y; 
    return res <= 0 ? true : false;
}
bool Point::operator>=(const Point& p2) const{
    double res = x + y - p2.x - p2.y; 
    return res >= 0 ? true : false;
}
bool Point::operator==(const Point& p2) const{
    return (x == p2.x && y == p2.y) ? true : false;
}
bool Point::operator!=(const Point& p2) const{
    return p2 == *this ? false : true;
}
Point Point::operator+(const Point& p2) const{
    Point t(p2.x + x, p2.y + y);
    return t;
}
Point Point::operator-(const Point& p2) const{
    Point t(x - p2.x, y - p2.y);
    return t;
}
Point& Point::operator+=(const Point& p2){
    x += p2.x;
    y += p2.y;
    return *this;
}
Point& Point::operator-=(const Point& p2){
    x -= p2.x;
    y -= p2.y;
    return *this;
}
Point& Point::operator++(){
    x++;
    y++;
    return *this;
}
Point Point::operator++(int){
    Point temp(*this);
    x++;
    y++;
    return temp;
}
/*Point& Point::operator--(){
    x--;
    y--;
    return *this;
}
Point Point::operator--(int){
    Point temp(*this);
    x--;
    y--;
    return temp;
}*/
Point& operator--(Point& p){
        p.x--;
        p.y--;
        return p;
    }
Point operator--(Point& p, int){
    Point temp(p);
    p.x--;
    p.y--;
    return temp;
}
ostream& operator<<(ostream& o, const Point& p){
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}
istream& operator>>(istream& i, Point& p){
    i >> p.x;
    i.ignore(1);
    i >> p.y;
    
    return i;
}

//Circle
int Circle::instCount = 0;
Circle::Circle(double r, double x, double y) : position(new Point(x, y)){
    if(!validateR(r))
        throw invalid_argument("Received not positive value!");
    if(!validateCircle(r, x, y))
        throw invalid_argument("Circle is out of XOY!");
    
    this->r = r;
    cout << "Circle created! Count of instances -> "
        << ++instCount << endl;
}
Circle::Circle(double x, double y) : Circle(1, x, y) {}
Circle::Circle(double r) : Circle(r, 0, 0) {}
Circle::Circle(const Circle& other) : Circle(other.r, other.getPoint().getX(), other.getPoint().getY()) {}
Circle::~Circle(){
    delete position;
    cout << "Circle deleted! Count of instances -> "
    << --instCount << endl;
}

double Circle::getR() const{
    return r;
}
bool Circle::setR(const double r){
    if(!(validateR(r) && validateCircle(r, getPoint().getX(), getPoint().getY())))
        return false;
        
    this->r = r;
    return true;
}
Point& Circle::getPoint() const{
    return *position;
}
bool Circle::setPoint(const Point& p){
    return setPosition(p.getX(), p.getY());
}
bool Circle::setPosition(const double x, const double y){
    if(!validateCircle(this->r, x, y))
        return false;
        
    getPoint().setXY(x, y);
    return true;
}
string Circle::info(){               
    ostringstream os;
    
    os << "R = " << r << ", ";
    os << "(X = " << getPoint().getX() << ", ";
    os << "Y = " << getPoint().getY() << ")";
    
    return os.str();
}

Circle& Circle::setRadius(double r){
    setR(r);
    return *this;
}
Circle& Circle::setX(double x){
    setPosition(x, getPoint().getY());
    return *this;
}
Circle& Circle::setY(double y){
    setPosition(getPoint().getX(), y);
    return *this;
}
bool Circle::validateR(const double r){
    if(r > 0)
        return true;
    return false;
}
bool Circle::validateCircle(const double r, const double x, const double y){
    if(x - r >= 0 && y - r >= 0)
        return true;
    return false;
}
ostream& operator<<(ostream& o, Circle& c){
    o << "R = " << c.getR() << ", " << c.getPoint();
    return o;
}
istream& operator>>(istream& i, Circle& c){
    i >> c.r;
    i.ignore(1);
    i >> c.getPoint();
    
    return i;
}

//global functions
void printCircle(Circle& c){
    cout << c.info() << endl;
}
bool isInCircle(Circle& c, Point& p){
    if(pow(p.getX() - c.getPoint().getX(), 2) + pow(p.getY() - c.getPoint().getY(), 2) <= 
        pow(c.getR(), 2))
        return true;
    return false;
}
double distanceBetweenCircles(Circle& c1, Circle& c2){
    return sqrt(pow(c1.getPoint().getX() - c2.getPoint().getX(), 2)
    + pow(c1.getPoint().getY() - c2.getPoint().getY(), 2));
}
int circleIntersectionCount(Circle& c1, Circle& c2){
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
double getLength(Circle& c){
    return 2* c.r *PI;
}
double getArea(Circle& c){
    return c.getR()*c.getR()*PI;
}
bool moveX(Circle& c, double x){
    return c.setPosition(c.getPoint().getX() + x, c.getPoint().getY());
}
bool moveY(Circle& c, double y){
    return c.setPosition(c.getPoint().getX(), c.getPoint().getY() + y);
}
bool multiplyR(Circle& c, double k){
    return c.setR(c.getR() * k);
}
int main ()
{
    Point p1  = *new Point(0.5,0.5);
    Point p2  = *new Point(0.4,0.5);
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    
    cout << "p1 < p2 -> " << ((p1 < p2) ? "true" : "false") << endl;
    cout << "p1 > p2 -> " << ((p1 > p2) ? "true" : "false") << endl;
    cout << "p1 <= p2 -> " << ((p1 <= p2) ? "true" : "false") << endl;
    cout << "p1 >= p2 -> " << ((p1 >= p2) ? "true" : "false") << endl;
    cout << "p1 == p2 -> " << ((p1 == p2) ? "true" : "false") << endl;
    cout << "p1 != p2 -> " << ((p1 != p2) ? "true" : "false") << endl<<endl;
    
    cout << "p1 + p2 -> " << p1 + p2 << endl;
    cout << "p1 - p2 -> " << p1 - p2 << endl;
    cout << "p1 += p2 -> " << (p1 += p2) << endl;
    cout << "p1 -= p2 -> " << (p1 -= p2) << endl<<endl;
    
    cout << "++p1 -> " << ++p1 << endl;
    cout << "p1++ -> " << p1++ << endl;
    cout << "--p1 -> " << --p1 << endl;
    cout << "p1-- -> " << p1-- << endl;
    cout << "p1 -> " << p1 << endl<<endl;
    
    Circle c(5, 5, 5);  
    Circle c2(5, 7, 5);  
    printCircle(c);
    printCircle(c2);
    
    cout << "p1(x y) = ";
    cin >> p1;
    cout << p1 << endl;
    cout << "c(r x y) = ";
    cin >> c;
    cout << c << endl;
    
    cout << "\n\n";
    
    return 0;
}