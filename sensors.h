#include "HX711.h"
#include <Adafruit_MLX90614.h>

// HX711
#define LOADCELL_DOUT_PIN     32
#define LOADCELL_SCK_PIN      33
#define LOADCELLTORQUE_DOUT_PIN     25
#define LOADCELLTORQUE_SCK_PIN      26
#define LOADCELL_CALIBRATION  -215
#define LOADCELLTORQUE_CALIBRATION  -1100

extern HX711 loadcell;
extern HX711 loadcellTorque;
extern long thrust;
extern long torque;

void loadcellInit(HX711 *loadcell, int DOUT, int SCK, int loadcellCalibration);

extern Adafruit_MLX90614 mlx;
extern long ambient;
extern long mottemp;
