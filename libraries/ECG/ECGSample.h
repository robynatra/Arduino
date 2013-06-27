#ifndef ECGSample_H
#define ECGSample_H

class ECGSample {
public:
	ECGSample();
	~ECGSample();
	void setValue(int sensor, float value);
	float getValue(int sensor);
};

#endif