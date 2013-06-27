#include "ECGSample.h" //include the declaration for this class

#define sensorCount 3	// Different ECGs have different numbers of sensors 

float values[sensorCount];

//<<constructor>> 
ECGSample::ECGSample(){
}

//<<destructor>>
ECGSample::~ECGSample(){/*nothing to destruct*/}

//set a value
void ECGSample::setValue(int sensor, float value){
	values[sensor] = value;
}

//return a value
float ECGSample::getValue(int sensor){
	return values[sensor];
}
