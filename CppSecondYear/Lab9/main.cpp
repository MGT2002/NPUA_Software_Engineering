#include <iostream>
#include <string>

using namespace std;

enum class EngineType 
{
    Disel,
    Petrol,
    Gas,
    Electric
};

class Engine
{
    private:
    static int instCount;
    
    string model;
    string date;
    string power;
    EngineType type;
    
    public:
    
    Engine()
    {
        instCount++;
        cout << "Engine created, count of instances " << instCount << endl;
    }
    ~Engine()
    {
        instCount--;
        cout << "Engine deleted, count of instances " << instCount << endl;
    }
    
};int Engine::instCount = 0;

class Vehicle
{
    private:
    static int instCount;
    
    Engine& engine;
    string producer;
    string model;
    double price;
    double weight;
    double maxSpeed;
    string date;
    
    public:
    
    Vehicle(Engine& engine, string producer, string model, double price, double weight, double maxSpeed, string date)
    : engine(engine), producer(producer), model(model), price(price), weight(weight), maxSpeed(maxSpeed), date(date)
    {
        instCount++;
        cout << "Vehicle created, count of instances " << instCount << endl;
    }
    ~Vehicle()
    {
        instCount--;
        cout << "Vehicle deleted, count of instances " << instCount << endl;
    }
}; int Vehicle::instCount = 0;

class Car : public Vehicle
{
    private:
    int seats;
};

class Truck : public Vehicle
{
    private:
    static int instCount;
    
    double maxLoad;
    
    public:
    
    Truck(Engine& engine, string producer, string model, double price, double weight, double maxSpeed, string date)
    : Vehicle(engine, producer, model, price, weight, maxSpeed, date)
    {
        instCount++;
        cout << "Truck created, count of instances " << instCount << endl;
    }
    
    double getMaxLoad()
    {
        return maxLoad;
    }
    void setMaxLoad(double maxLoad)
    {
        this->maxLoad = maxLoad;
    }
};int Truck::instCount = 0;

int main()
{
    Engine e;
    Truck t(e, "prd", "model", 100, 200, 50, "12/12/2002");
    t.setMaxLoad(12.5);
    cout << t.getMaxLoad() << endl;
    return 0;
}



