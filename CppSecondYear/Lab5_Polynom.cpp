#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Polynom {
public:
    const int size = 6;

    Polynom()  
    {
        Polynom::instanceCount++;
        coefficients.assign(size, 0);
        degrees.assign(size, 0);
        symbol = 'X';
    }
    Polynom(vector<double> coeff) : Polynom()
    {
        degrees.assign(size, 1);
        for(int i = 0; i < size; i++)
            coefficients[i] = coeff[i];
    }
    Polynom(vector<int> degs) : Polynom()
    {
        coefficients.assign(size, 1);
        for(int i = 0; i < size; i++)
            degrees[i] = degs[i];
    }
    Polynom(vector<double> coeff, vector<int> degs, char symb) : Polynom()
    {
        symbol = symb;
        for(int i = 0; i < size; i++)
            degrees[i] = degs[i];
        for(int i = 0; i < size; i++)
            coefficients[i] = coeff[i];
    }
    ~Polynom()
    {
        Polynom::instanceCount--;
    }
    
    vector<double> getCoefficients()
    {
        return coefficients;
    }
    void setCoefficients(const vector<double>& newCoeff)
    {
        coefficients = newCoeff;
    }
    vector<int> getDegrees()
    {
        return degrees;
    }
    void setDegrees(const vector<int>& newDegs)
    {
        degrees = newDegs;
    }
    char getSymbol()
    {
        return symbol;
    }
    void setSymbol(char newSymbol)
    {
        symbol = newSymbol;
    }
    static int getInstanceCount()
    {
        return instanceCount;
    }
    
    void print()
    {
        bool polynomPrinted = false;
        int c = 0;
        for(int i = 0; i < size; i++)
        {
            if(coefficients[i] == 0)
                continue;
                
            if(degrees[i] == 0)
            {
                c += coefficients[i];
                continue;
            }

            if(polynomPrinted)
            cout << " + ";
        
            if(coefficients[i] > 1)
                cout << coefficients[i];
            
            cout << symbol;
            if(degrees[i] != 1)
                cout << "^" << degrees[i];
            
            polynomPrinted = true;
        }
        if(c == 0)
            return;
        
        if(polynomPrinted)
            cout << " + ";
        cout << c << endl;
    }
    
    template<typename T>
    void printVector(vector<T> v)
    { 
        for(int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ", ";
        }
        cout << endl;
    }
    void printAll()
    {
        cout << "Size = " << size << endl;
        cout << "Count coefficients = " << coefficients.size() << endl;
        printVector(coefficients);
        cout << "Count degrees = " << degrees.size() << endl;
        printVector(degrees);
        cout << "Symbol = " << symbol << endl;
        cout << "Instance Count = " << Polynom::instanceCount << endl;
        cout << "Polynom -> "; print(); cout << endl;
        cout << "____________" << endl;
    }
    
private:
    static int instanceCount; 
    
    vector<double> coefficients;
    vector<int> degrees;
    char symbol;
};
int Polynom::instanceCount = 0;

Polynom getDerivative(Polynom& pol, int degree)
{
    vector<double> coeff = pol.getCoefficients();
    vector<int> degs = pol.getDegrees();
    
    for(int i = 0; i < degree; i++)
    {
        for(int j = 0; j < coeff.size(); j++)
        {
            if(degs[j] == 0)
            {
                coeff[j] = 0;
                continue;
            }
                
            coeff[j] *= degs[j];
            degs[j]--;
        }
    }
    
    Polynom np(coeff, degs, pol.getSymbol());
    return np;
}
    
double calcPolynomAt(Polynom& pol, double x)
{
    vector<double> coeff = pol.getCoefficients();
    vector<int> degs = pol.getDegrees();
    
    double res = 0;
    for(int i = 0; i < coeff.size(); i++)
        res += (pow(x, degs[i]) * coeff[i]);
    
    return res;
}
    
int main()
{
    vector<double> coeff;
    coeff.assign(6, 1);
    Polynom p(coeff);
    p.printAll();
    
    coeff = p.getCoefficients();
    coeff[0] = 4;
    coeff[4] = 2;
    coeff[3] = 0;
    coeff[1] = 5;
    p.setCoefficients(coeff);
    vector<int> degs = p.getDegrees();
    degs[3] = 12;
    degs[2] = 2;
    degs[5] = 6;
    degs[1] = 0;
    p.setDegrees(degs);
    
    p.printAll();
    
    double x = 2;
    cout << "calc at x = " << x << " : " << calcPolynomAt(p, x) << endl;
    
    Polynom p2 = getDerivative(p, 1);
    p2.printAll();
    cout << "calc at x = " << x << " : " << calcPolynomAt(p2, x) << endl;
    Polynom p3 = getDerivative(p, 2);
    p3.printAll();
    cout << "calc at x = " << x << " : " << calcPolynomAt(p3, x) << endl;
    Polynom p4 = getDerivative(p, 20);
    p4.printAll();
    cout << "calc at x = " << x << " : " << calcPolynomAt(p4, x) << endl;
    
    return 1;
}