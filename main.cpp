/*
 EW202 Lab 5.3
 Proportional control of EW202 elevator
 D Evangelista, 2019
 */

#include "mbed.h"
#include "rtos.h"
#include "Motor.h"

// some defines
#define DT 20         // loop timing in ms
#define CAL_A 49.2    // inches = Ax^2+Bx+C
#define CAL_B -6.001  // calibration for instructor station
#define CAL_C 0.218
#define PROP_KP 0.1   // proportional control gain K_P

// hardware objects
Serial pc(USBTX,USBRX);
AnalogIn sensor(p20);
Motor motor(p26,p30,p29); 
DigitalOut heartbeat(LED1);

// function prototypes
float calibration(float);
float prop_control(float);





int main(void){
  int n_samples, i;
  float ref, ymeas, e, u;
  
  while(1){
    pc.scanf("%d,%f",&n_samples,&ref);

    for (i=0; i<n_samples; i++){
      ymeas = calibration(sensor.read());
      e = ref-ymeas;
      u = prop_control(e);
      motor.speed(u);

      heartbeat = !heartbeat;
      pc.printf("%d,%f,%f\n",i,ymeas,u);
      ThisThread::sleep_for(DT); 
    } // for n_samples
  } // while(1)
} // main()





/** @brief Applies calibration for GPD212 sensor
    The calibration is inches = Ay^2+By+C
    
    @param y is a float AnalogIn 0.0-1.0 
    @return height in inches as a float
*/
float calibration(float y){
  return CAL_A*y*y+CAL_B*y+CAL_C; 
}





/** @brief Implements proportional control

    @param e is the error, ref-meas in inches, float
    @return motor pwm value, a float from 0.0-1.0
*/
float prop_control(float e){
  return PROP_KP*e; 
}
