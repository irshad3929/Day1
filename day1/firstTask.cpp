#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declarations for use in the future
class Constituency;
class Vehicle;

class Person {
protected:
    string name;
public:
    Person(const string& name) : name(name) {}

    virtual Constituency* getConstituency() const = 0;
    virtual string getDriver() const {
        return "Car Driver"; 
     }
    virtual bool exceedsSpendingLimit() const = 0;
    string getName() const { 
        return name; 
    } // Public member function to access name
};

class MP : public Person {
protected:
    Constituency* constituency;
public:
    int spendingCost;      // Moved spendingCost here

    MP(const string& name, Constituency* constituency) : Person(name), constituency(constituency), spendingCost(0) {}

    Constituency* getConstituency() const override {
        return constituency;
    }

    bool exceedsSpendingLimit() const override {
        return spendingCost > 100000;     // 1 lakh spending limit for MP
    }
};

class Minister : public MP {
public:
    Minister(const string& name, Constituency* constituency) : MP(name, constituency) {}

    bool exceedsSpendingLimit() const override {
        return spendingCost > 1000000;       // 10 lakhs spending limit for Minister
    }
};

class PrimeMinister : public Minister {
public:
    PrimeMinister(const string& name, Constituency* constituency) : Minister(name, constituency) {}

    string getDriver() const override 
    { 
        return "Car Driver and Aircraft Pilot"; 
    }

    bool exceedsSpendingLimit() const override {
        return spendingCost > 10000000;     // 1 crore spending limit for Prime Minister
    }

    bool givePermissionToArrest(const Minister* minister) {
        // Prime Minister can give permission to arrest a Minister if the Minister crosses the spending limit
        return (minister->exceedsSpendingLimit());
    }
};

class Commissioner {
public:
    void canArrest(const vector<Person*>& persons) const {
        for (const auto& person : persons) {
            if (person->exceedsSpendingLimit())
                cout << person->getName() << " can be arrested" << endl; // Access name here using public member function
            else
                cout << person->getName() << " is within the spending limit" << endl; // Access name using public member function
        }
    }
};

class Constituency {
    string name;
public:
    Constituency(const string& name) : name(name) {}

    string getName() const {
        return name;
    }
};

class Vehicle {
    string driverName;
    string type;
public:
    Vehicle(const string& driverName, const string& type) : driverName(driverName), type(type) {}

    string getDriver() const {
        return driverName;
    }
};

int main() {
    // Creating constituencies
    Constituency* constituency1 = new Constituency("Constituency 1");
    Constituency* constituency2 = new Constituency("Constituency 2");

    // Creating persons
    MP mp1("MP1", constituency1);
    Minister minister1("Minister1", constituency1);
    PrimeMinister pm("Prime Minister", constituency2);

    // Additional cases
    MP mp2("MP2", constituency2);
    Minister minister2("Minister2", constituency2);

    // Setting spending costs
    mp1.spendingCost = 90000;  // under limit
    minister1.spendingCost = 1100000;  // above limit
    pm.spendingCost = 8500000;  // under limit

    mp2.spendingCost = 12000000;  // above limit
    minister2.spendingCost = 900000;  // under limit

    //vector of persons(MP,Minister, PM)
    vector<Person*> persons = {&mp1, &minister1, &pm, &mp2, &minister2};

    // Creating a commissioner and check who can be arrested
    Commissioner commissioner;
    commissioner.canArrest(persons);

    // Prime Minister can give permission to arrest
    cout << "Does Prime Minister give permission to arrest Minister1 ? ";
    if (pm.givePermissionToArrest(&minister1))
        cout << "Yes, Prime Minister gives permission." << endl;
    else
        cout << "No, Prime Minister should give permission to arrest." << endl;

    cout << "Does Prime Minister give permission to arrest Minister2 ? ";
    if (pm.givePermissionToArrest(&minister2))
        cout << "Yes, Prime Minister gives permission." << endl;
    else
        cout << "No, Prime Minister should give permission." << endl;

    

    return 0;
}
