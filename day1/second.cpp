#include <iostream>
using namespace std;

// battery class
class Battery {
public:
    bool hasBattery;
    Battery(bool hasBattery) : hasBattery(hasBattery) {}
};

// gridon class
class GridOn {
public:
    bool hasGridFeature;
    GridOn(bool hasGridFeature) : hasGridFeature(hasGridFeature) {}
};

// invertor class
class Invertor {
protected:
    int powerRating;
public:
    Invertor() {}
    int calculatePowerRating(int current, int operatingVoltage) {
        return current * operatingVoltage;
    }
};

// solar invertor has Is-A relation with inverter so inheritance follow
class SolarInvertor : public Invertor {
public:
    GridOn gridOn;
    Battery battery;
    SolarInvertor(bool hasBatteryValue, bool hasGridFeatureValue) : battery(hasBatteryValue), gridOn(hasGridFeatureValue) {}
};

class PCU : public SolarInvertor {
public:
    PCU() : SolarInvertor(true, false) {}  // PCU has battery but no grid feature
};

class GTI : public SolarInvertor {
public:
    GTI() : SolarInvertor(false, true) {} // GTI has grid feature but no battery
};

class REGALIA : public SolarInvertor {
public:
    REGALIA() : SolarInvertor(true, true) {} // REGALIA has both battery and grid feature
};

// Non-solar invertor has Is-A relation with inverter so inheritance follow
class NonSolarInverter : public Invertor{   //it define non solar class (zelio, icruze)
   Battery battery;
public:
   NonSolarInverter(bool isBattery) : battery(isBattery) {}
};

class ZELIO : public NonSolarInverter {
public:
       ZELIO() : NonSolarInverter(true) {} 
   
         // ZELIO has battery by default                                     
};

class ICRUZE : public NonSolarInverter {
public:
       ICRUZE() : NonSolarInverter(true) {} 
       
         // ICRUZE has battery by default                                     
};

class Company {
private:
    Invertor* invertor;
public:
    Company(Invertor* invertor) : invertor(invertor) {}
    
   void getInfo(){
       cout<<"power rating "<< invertor->calculatePowerRating(5,24);
    }
};

int main() {
    // Create invertor objects
    // auto pcu = new PCU();
    // auto regalia = new REGALIA();
    //auto gti = new GTI();
    auto zelio = new ZELIO();
    // ICRUZE icruze;

    // Create a company with an invertor
   // auto company = new Company(gti);
    auto company = new Company(zelio);
    company->getInfo();
    
    // Company company(&pcu);
   return 0;
}
