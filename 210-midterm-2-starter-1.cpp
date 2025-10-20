// COMSC-210 | Midterm 2 | Arkhip Finski
// IDE used: Visual Studio
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int TIME = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }
    //This method finds the name of the customer at the give position 
    string find_pos(int pos) const{
        if(!head){
            cout << "Line is empty." << endl;
        } 
        if( pos == 1){
            return head->data;
        }
        
        Node* temp = head; 

        for(int i = 1; i < pos; i++){
            if(!temp){
                cout << "Position does not exist." << endl;
                return "";
            }
            else{
                temp = temp->next;
            }
        }

        if(!temp){
            cout << "Position does not exist." << endl;
            return "";
        }

        return temp->data;

    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "    Line is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "   Line is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "   Line is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "    Line is empty." << endl;
            return;
        }
        while (current) {
            cout << "        " << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "    Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    //This method checks if the line is empty or not
    bool empty() {
        bool check = 0;
        if(head == nullptr){
            check = 1;
        } 

        return check;

    }

    //This method returns name of the customer in the front of the line 
    string get_front() const{
        if(head){
            return head->data;
        }
    }

    //This method returns the name of the customer at the back of the line
    string get_rear() const{
        if(tail){
            return tail->data;
        }
    }
};

string randomName(const vector<string>&);
bool chance(int p);



int main() {
    srand(time(0));

    DoublyLinkedList list;
    vector<string> names;
    string name;
    int count; // this integer keeps track of number of costumers in the line
    fstream input_File("names.txt");

    if(!input_File){
        cout << "Error, was not able to open the file!" << endl;

        return 1;
    }

    // this loop reads names into vector names
    while(input_File>>name){
        names.push_back(name);
    }

    input_File.close();

    cout << "Store open:" << endl;

    //This loop adds 5 costumers into the line
    for(int i = 0; i < MIN_LS; ++i){
        string n = randomName(names);
        list.push_back(n); 
        cout << "    " << n << " Joins the line" << endl;
    }
    count = 5;
    // this code prints the current line
    cout << "    Resulting line: "<< endl;

    list.print();

    //This loop simulates 20 minutes time interval
    for(int i = 2; i <= TIME; ++i){
        cout << "Time step #" << i << ":" << endl;

        //This condition statement checks if customer in the front of the line is served 
        if(chance(40) && !list.empty()){
            string s = list.get_front();
            list.pop_front();
            cout << "    " << s << " is served" << endl;
            count -= 1;

        }
        //This condition statement checks if anybody joined the line
        if(chance(60)){
            string n = randomName(names);
            list.push_back(n);
            cout << "    " << n << " Joins the line" << endl;
            count += 1;


        }
        //This condition statement checks if a customer at the end of the line left the line 
        if(chance(20) && !list.empty()){
            string last = list.get_rear();
            list.pop_back();
            cout  << "    " << last << " (at the rear) left the line" << endl;
            count -=1;

        }
        //This condition statement checks if any customer from the line left 
        if(chance(10) && !list.empty()){
            int r = rand() % count + 1;
            string find = list.find_pos(r);
            if(find != ""){
                list.delete_pos(r);
                cout << "    " << find << " left the line" << endl;
                count -=1;
            }
        }
        //This condition statement checks if any VIP customer joined the line, if so they are moved to the front of the list 
        if(chance(10)){
            string vip = randomName(names);
            vip += " - VIP";
            list.push_front(vip);
            cout << "    " << vip << " (VIP) joins the front of the line" << endl;
            count +=1;

        }

        //This code outputs the current line
        cout << "    Resulting line: "<< endl;
        list.print();


    }

    
    return 0;
}

//This function returns a random name from the vector names 
//arguments: reference to the vector of names (n)
//returns: randomly selected name 
string randomName(const vector<string>& n){
    return n.at(rand() % n.size());
}

// This function checks if event occurs based on the given percent(p)
//argument: int p (percent)
//return: true if event occurs 
bool chance(int p){
    int random = rand()% 100 + 1;
    bool check;
    if(random <= p){
        check = 1;
    }
    else{
        check = 0;
    }

    return check;
}