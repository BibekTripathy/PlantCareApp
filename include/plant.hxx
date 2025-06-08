#ifndef PLANT_HXX
#define PLANT_HXX

#include <string>
#include<vector>
#include<ctime> /* Migrate to <chrono> later */

class plant {
private:
	std::string name, species, description, healthStatus;
	std::vector<string> careTips;
	int wateringFrequencyDays;
	std::time_t lastWateredDate;
public:
	plant(
		const string& name, const string& species, const string& description, int wateringFrequencyDays
	);
};

#endif
