#include "sensors.h"
//Optical temp sensor MLX. 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
long ambient = 0;
long mottemp = 0;

HX711 loadcell;
HX711 loadcellTorque;

long thrust = 0;
long torque = 0;

void loadcellInit(HX711 *loadcell, int DOUT, int SCK, int loadcellCalibration){
  loadcell->begin(DOUT, SCK);
  loadcell->set_scale(loadcellCalibration);
  loadcell->tare();
  }


  
