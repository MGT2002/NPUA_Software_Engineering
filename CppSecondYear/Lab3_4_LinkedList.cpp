#include <iostream>
using namespace std;

class ListNode{
    public:
    ListNode(const double data, ListNode* next = nullptr){
        this->_data = data;
        this->_nextPtr = next;
    }
    
    double _data;
    ListNode* _nextPtr;
};

class List{
    public:
    
        List(){
            _firstPtr = nullptr;
            _lastPtr = nullptr; 
            _count = 0;
        };
        ~List(){
            cout << "Destructor start!" << endl;
            double data;
            while(removeFromFront(data))
            {
                cout << data << endl;
                print();
            }
            cout << "Distructor End!" << endl;
        };
        
        void insertAtFront(const double data){
            ListNode* newPtr = createNode(data);
            newPtr->_nextPtr = _firstPtr;
            if(this->isEmpty()) _lastPtr = newPtr;
            _firstPtr = newPtr;
            _count++;
        };
        void insertAtBack(const double data){
            ListNode* newPtr = createNode(data);
            if(this->isEmpty())
                _lastPtr = _firstPtr = newPtr;
            else{
            _lastPtr->_nextPtr = newPtr;
            _lastPtr = newPtr;
            }
            _count++;
        };
       bool insertAfterIndex(const int index, const double data){
            if(_count == 0 || index >= _count || index < 0)
                return false;
            
            if(index == _count - 1)
                insertAtBack(data);
            else{
                    ListNode* newPtr = createNode(data);
                    
                    ListNode* current = _firstPtr;
                    for(int i = 0; i < index; i++)
                        current = current->_nextPtr;
                    newPtr->_nextPtr = current->_nextPtr;
                    current->_nextPtr = newPtr;
                }
            
            _count++;
            
            return true;
        };
        bool removeFromFront(double& data){
            if(this->isEmpty())
                return false;
            
            ListNode* next = _firstPtr->_nextPtr;
            data = _firstPtr->_data;
            delete _firstPtr;
            if(next == nullptr) _lastPtr = nullptr;
            _firstPtr = next;
            _count--;
            
            return true;
        };
        bool removeFromBack(double& data){
            if(this->isEmpty())
                return false;
            
            data = _lastPtr->_data;    
            
            if(_lastPtr == _firstPtr)
            {
                delete _lastPtr;
                _lastPtr = _firstPtr = nullptr;
                return true;
            }
            
            ListNode* current = _firstPtr;
            while(current->_nextPtr != _lastPtr)
                current = current->_nextPtr;
            delete _lastPtr;
            current->_nextPtr = nullptr;
            _lastPtr = current;
            _count--;
            
            return true;
        };
        int getElementCount(){
            return _count;
        };
        bool isEmpty() const {
            return _firstPtr == nullptr;
        };
        void print() const {
            cout << "List { ";
            ListNode* current = _firstPtr;
            while(current != nullptr)
            {
                cout << current->_data;
                cout << endl;
                
                current = current->_nextPtr;
            }
            cout << "}" << endl;
        };
    
    private:
    
        ListNode* createNode(const double data) const {
            return new ListNode(data);
        };
    public:
        int _count;
    
    private:
        
        ListNode* _firstPtr;
        ListNode* _lastPtr;
};

void instructions()
{
    cout << "Enter one of the following:" << endl;
    cout << "1 to insert at begining of list" << endl;
    cout << "2 to insert at end of list" << endl;
    cout << "3 to delete from begining of list" << endl;
    cout << "4 to delete from end of list" << endl;
    cout << "5 to see element count" << endl;
    cout << "6 to insert after index " << endl;
    cout << "7 to end list processing" << endl;
}

int main()
{
    List* l = new List;
    int index;
    while(true)
    {
        instructions();
        int input; cin >> input;
        if(input == 1){
            cout << "data = ";
            cin >> input;
            l->insertAtFront(input);
            l->print();
        }
        else if(input == 2){
            cout << "data = ";
            cin >> input;
            l->insertAtBack(input);
            l->print();
        }
        else if(input == 3){
            double data;
            if(l->removeFromFront(data))
                cout << data << endl;
            l->print();
        }
        else if(input == 4){
            double data;
            if(l->removeFromBack(data))
                cout << data << endl;
            l->print();
        }
        else if(input == 5){
            cout << "count = " << l->getElementCount() << endl;
        }
        else if(input == 6){
            cout << "index = ";
            cin >> index;
            cout << "data = ";
            cin >> input;
            if(!l->insertAfterIndex(index, input))
                cout << "Wrong Input!" << endl;
            l->print();
        }
        else if(input == 7){
            delete l;
            break;
        }
        else
        {
            cout << "Wrong input!";
        }
    }
    
    return 0;
}