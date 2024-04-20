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
    double power;
    EngineType type;
    
    public:
    
    Engine(string model, string date, double power, EngineType type) : model(model), date(date), power(power), type(type)
    {
        instCount++;
        cout << "Engine created, count of instances " << instCount << endl;
    }
    Engine(double power) : Engine("", "", power, EngineType::Disel) {}
    Engine() : Engine("", "", 0, EngineType::Disel) {}
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
    double getPower() const
    {
        return power;
    }
    void setPower(double power)
    {
        this->power = power;
    }
    EngineType getEngineType() const
    {
        return type;
    }
    
    friend ostream& operator<<(ostream& os, const Engine& e)
    {
        os << "model: " << e.getModel() << ", Date: "
            << e.getDate() << ", Power: " << e.getPower() << 
            ", EngineType: " << e.getEngineType();
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
        
        double inputD;
        cout << "Enter power: ";
        is >> inputD;
        e.setPower(inputD);
        
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
        os << "producer: " << v.getProducer() << ", price: "
            << v.getPrice() << ", weight: " << v.getWeight() << 
            ", MaxSpeed: " << v.getMaxSpeed() <<
            ", date: " << v.getDate() << ",\n Engine: { " 
            << v.engine << "}";
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
        cout << "Car created, count of instances " << instCount << endl;
        this->seats = seats;
    }
    Car(double power, int seats) : Car(*new Engine(power), "", "", 0, 0, 0, "", 0, seats) {}
    Car() : Car(*new Engine(), "", "", 0, 0, 0, "", 0, 0) {}
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
    
    friend ostream& operator<<(ostream& os, Car& c) 
    {
        os << "seats: " << c.getSeats() << ", ";
        os << static_cast<Vehicle&>(c);
        return os;
    }
    friend istream& operator>>(istream& is, Car& c) 
    {
        int input;
        cout << "Enter seats: ";
        is >> input;
        c.setSeats(input);
        
        is >> static_cast<Vehicle&>(c);
        
        return is;
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
    Truck() : Truck(*new Engine(), "", "", 0, 0, 0, "", 0) {}
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
    
    friend ostream& operator<<(ostream& os, Truck& t) 
    {
        os << "max load: " << t.getMaxLoad() << ", ";
        os << static_cast<Vehicle&>(t);
        return os;
    }
    friend istream& operator>>(istream& is, Truck& t) 
    {
        double input;
        cout << "Enter max load: ";
        is >> input;
        t.setMaxLoad(input);
        
        is >> static_cast<Vehicle&>(t);
        
        return is;
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
Car& createAndInputCar()
{
    Car& c = *new Car();
    cout << "c = {";
    cin >> c;
    cout << "}" << endl;
    return c;
}
Truck& createAndInputTruck()
{
    Truck& t = *new Truck();
    cout << "t = {";
    cin >> t;
    cout << "}" << endl;
    return t;
}
void SortByPowerDescending(Car* arr[], int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size - i; j++) {
            if (arr[j]->getEngine().getPower() > arr[j - 1]->getEngine().getPower()) {
                Car* temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}
int main()
{
    int n = 5;
    Car* arr[n];
    arr[0] = new Car(10, 4);
    arr[1] = new Car(8, 8);
    arr[2] = new Car(14, 3);
    arr[3] = new Car(5, 2);
    arr[4] = new Car(90, 5);
    
    SortByPowerDescending(arr, n);
    for(Car* c : arr)
        if(c->getSeats() <= 5)
            cout << *c << endl;
    
    for(Car* c : arr)
        delete c;
    return 0;
}