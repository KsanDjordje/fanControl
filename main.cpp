#include <iostream>
#include <sstream>
#include <unistd.h>

const int MIN_TEMP = 30;
const int MAX_TEMP = 80;
const int TEMP_THRESHOLD[] ={30, 40, 55, 60, 70, 80, 85};
const int FAN_SPEED[] =	{ 0, 30, 40, 50, 60, 65, 80, 100};

int getTemperature(){
	std::string command = "nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits";

	FILE* fp = popen(command.c_str(), "r");
	if(fp == NULL){
		std::cerr << "Failed to run command to get GPU temperature." << std::endl; 
		return -1;
	}
	char buffer[128];
	std::string result = "";
	while(fgets(buffer, sizeof(buffer), fp) != NULL){
		result += buffer;
	}

	pclose(fp);

	int temp;
	std::stringstream(result) >> temp;

	return temp;

}

void setGpuFanSpeed(int speed){
	if(speed < 0 || speed > 100){
		std::cerr << "Invalid fan speed:" << speed << ", speed must be between 0 and 100." << std::endl;
		return;
	}

	std::string command = "nvidia-settings --assign 'GPUTargetFanSpeed=" + std::to_string(speed) + "'";
	
	if(system(command.c_str()) == 0){
		std::cout << "Fan speed set to " << speed << "%" << std::endl;
	}else{
		std::cerr << "Failed to change fan speed." << std::endl;
	}
}
int getFanSpeedFromTemperature(int temperature){
	for(size_t i = 0; i < std::size(TEMP_THRESHOLD); i++){
		if(temperature < TEMP_THRESHOLD[i]) return FAN_SPEED[i];
		
	}
	return FAN_SPEED[std::size(FAN_SPEED) - 1];	// max speed

}
int main(int argc, char *argv[]){

	while(true){
		int temperature = getTemperature();

		if(temperature == -1){
			return 1;
		}

		std::cout << "GPU temperature: " << temperature << "°C" << std::endl;
		setGpuFanSpeed(getFanSpeedFromTemperature(temperature));
		sleep(5);

	}
}
