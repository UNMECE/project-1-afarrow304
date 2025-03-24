#include "capacitor.h"
#include <iostream>

void solveConstantVoltage(Capacitor &cap, double I, double delta_t,
int numTimeSteps) {
	cap.voltage[0]=0; //inital voltage is zero
	
	for (int t =1; t < numTimeSteps; t++){
	 cap.voltage[t]=cap.voltage[t-1]+I* delta_t*(1/cap.C);
		if(t% 200==0){
		 	std::cout <<"Time step "<<t<<": Voltage is "<<cap.voltage[t]<<"\n";
		}
	}
}
void solveConstantCurrent(Capacitor &cap, double R, double Vo,
double delta_t, int numTimeSteps) {
	cap.current[0]=Vo/R; //current at time zero
	for (int t =1; t < numTimeSteps; t++){
		double IOfTMinusOne=cap.current[t-1];
		cap.current[t]=IOfTMinusOne-(IOfTMinusOne / (R * cap.C)) * delta_t;
		if(t% 200==0){
			std::cout <<"Time step "<<t<<": Current is "<<cap.current[t]<<"\n";
		}
	}
}

//function:Create a program that will solve for voltage and current 
//across a capacitor as a function of time.
int main(){
	const double delta_t =1e-10;          //change in time
	const double finalTime = 5e-6;
	const int numTimeSteps = 50000;  //finalTime/dt
	const double R =1000.0;          //1k omega resistance
	const double C = 100e-12;        //Capacitance
	const double I = 1e-2;        //constant current supply
	const double Vo = 10.0;          //constant voltage supply

	Capacitor cap;
	cap.time = new double[numTimeSteps];
	cap.voltage = new double[numTimeSteps];
	cap.current= new double[numTimeSteps];
	cap.C=C;
	for (int t =0; t<numTimeSteps; t++){
		cap.time[t] =t*delta_t;
	}
	solveConstantVoltage(cap,I,delta_t,numTimeSteps);
	solveConstantCurrent(cap, R, Vo, delta_t, numTimeSteps);

	//memory cleanup
	delete[] cap.time;
	delete[] cap.voltage;
	delete[] cap.current;

	return 0;
}
