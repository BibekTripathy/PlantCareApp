#ifndef PLANT_H
#define PLANT_H

#include <string>
#include<vector>
#include<ctime>

using namespace std;

class plant{
    private:
        string name;string species;string description;string healthStatus;

        vector<string> careTips;
        int wateringFrequencyDays;
        time_t lastWateredDate;
    public:
    plant(
        const string& name,const string& species,const string& description,int waterFreq 
    );
    
    string

}        











#endif