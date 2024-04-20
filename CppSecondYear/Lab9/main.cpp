#include <iostream>
#include <string>

using namespace std;

enum class EngineType 
{
    Disel, Petrol, Gas, Electric,
};
ostream& operator<<(std::ostream& os, const EngineType& et) {
    switch (et) {
        case EngineType::Disel:
            os << "Disel";
            break;
        case EngineType::Petrol:
            os << "Petrol";
            break;
        case EngineType::Gas:
            os << "Gas";
            break;
        default:
            os << "Electric";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, EngineType& et) {
    std::string input;
    is >> input;

    if (input == "Disel") {
        et = EngineType::Disel;
    } else if (input == "Petrol") {
        et = EngineType::Petrol;
    } else if (input == "Gas") {
        et = EngineType::Gas;
    } else if(input == "Electric"){
        et = EngineType::Electric;
    } else{
         cout << "Wrong input! The default type 'Disel' has been set!"<< endl;
         et = EngineType::Disel;
    }

    return is;
}

class Engine
{
    private:
    static int instCount;
    
    string model;
    string date;
    string power;
    EngineType type;
    
    public:
    
    Engine(string model, string date, string power, EngineType type) : model(model), date(date), power(power), type(type)
    {
        instCount++;
        cout << "Engine created, count of instances " << instCount << endl;
    }
    Engine() : Engine("", "", "", EngineType::Disel) {}
    ~Engine()
    {
        instCount--;
        cout << "Engine deleted, count of instances " << instCount << endl;
    }
    
    string getModel() const
    {
        return model;
    }
    void setModel(string model)
    {
        this->model = model;
    }
    string getDate() const
    {
        return date;
    }
    void setDate(string date)
    {
        this->date = date;
    }
    string getPower() const
    {
        return power;
    }
    void setPower(string power)
    {
        this->power = power;
    }
    EngineType getEngineType() const
    {
        return type;
    }
    
    friend ostream& operator<<(ostream& os, const Engine& e)
    {
        os << "Engine {model: " << e.getModel() << ", Date: "
            << e.getDate() << ", Power: " << e.getPower() << 
            ", EngineType: " << e.getEngineType() << "}";
        return os;
    }

    friend istream& operator>>(istream& is, Engine& e)
    {
        string input;
        cout << "Enter model: ";
        is >> input;
        e.setModel(input);
    
        cout << "Enter date: ";
        is >> input;
        e.setDate(input);
        
        cout << "Enter power: ";
        is >> input;
        e.setPower(input);
        
        cout << "Enter engine type(Disel, Petrol, Gas, Electric): ";
        is >> e.type;
    
        return is;
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
    Vehicle() : Vehicle(*new Engine(), "", "", 0, 0, 0, "") {}
    ~Vehicle()
    {
        delete &engine;
        instCount--;
        cout << "Vehicle deleted, count of instances " << instCount << endl;
    }
    
    const Engine& getEngine() const
    {
        return engine;
    }
    string getProducer() const
    {
        return producer;
    }
    void setProducer(string producer)
    {
        this->producer = producer;
    }
    double getPrice() const
    {
        return price;
    }
    void setPrice(double price)
    {
        this->price = price;
    }
    double getWeight() const
    {
        return weight;
    }
    void setWeight(double weight)
    {
        this->weight = weight;
    }
    double getMaxSpeed() const
    {
        return weight;
    }
    void setMaxSpeed(double maxSpeed)
    {
        this->maxSpeed = maxSpeed;
    }
    string getDate() const
    {
        return date;
    }
    void setDate(string date)
    {
        this->date = date;
    }
    
    friend ostream& operator<<(ostream& os, const Vehicle& v)
    {
        os << "Vehicle {producer: " << v.getProducer() << ", price: "
            << v.getPrice() << ", weight: " << v.getWeight() << 
            ", MaxSpeed: " << v.getMaxSpeed() <<
            ", date: " << v.getDate() << ",\n Engine: " 
            << v.engine << "\n}";
        return os;
    }

    friend istream& operator>>(istream& is, Vehicle& v)
    {
        string inputS;
        cout << "Enter producer: ";
        is >> inputS;
        v.setProducer(inputS);
    
        cout << "Enter date: ";
        is >> inputS;
        v.setDate(inputS);
        
        double input;
        cout << "Enter price: ";
        is >> input;
        v.setPrice(input);
        
        cout << "Enter weight: ";
        is >> input;
        v.setWeight(input);
        
        cout << "Enter MaxSpeed: ";
        is >> input;
        v.setMaxSpeed(input);
        
        cout << "Enter engine -> ";
        is >> v.engine;
    
        return is;
    }
}; int Vehicle::instCount = 0;

class Car : public Vehicle
{
    private:
    static int instCount;
    
    int seats;
    
    public:
    Car(Engine& engine, string producer, string model, double price, double weight, double maxSpeed, string date, double maxLoad, int seats)
    : Vehicle(engine, producer, model, price, weight, maxSpeed, date)
    {
        instCount++;
        cout << "Truck created, count of instances " << instCount << endl;
        this->seats = seats;
    }
    ~Car()
    {
        instCount--;
        cout << "Car deleted, count of instances " << instCount << endl;
    }
    
    int getSeats()
    {
        return seats;
    }
    void setSeats(int seats)
    {
        this->seats = seats;
    }
}; int Car::instCount = 0;

class Truck : public Vehicle
{
    private:
    static int instCount;
    
    double maxLoad;
    
    public:
    
    Truck(Engine& engine, string producer, string model, double price, double weight, double maxSpeed, string date, double maxLoad)
    : Vehicle(engine, producer, model, price, weight, maxSpeed, date)
    {
        instCount++;
        cout << "Truck created, count of instances " << instCount << endl;
        this->maxLoad = maxLoad;
    }
    ~Truck()
    {
        instCount--;
        cout << "Truck deleted, count of instances " << instCount << endl;
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

Engine& createAndInputEngine()
{
    Engine& e = *new Engine();
    cout << "e = {";
    cin >> e;
    cout << "}" << endl;
    return e;
}
Vehicle& createAndInputVehicle()
{
    Vehicle& v = *new Vehicle();
    cout << "v = {";
    cin >> v;
    cout << "}" << endl;
    return v;
}
int main()
{
    
    
    return 0;
}