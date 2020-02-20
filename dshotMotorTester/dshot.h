/*
 * DSHOT implementation from JyeSmith.  
 * https://github.com/JyeSmith/dshot-esc-tester
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp32-hal.h"
#include "sensors.h"

#define MOTOR_POLES 14

extern TaskHandle_t Task1;
extern rmt_data_t dshotPacket[16];
extern rmt_obj_t* rmt_send;
extern hw_timer_t * timer;
extern uint8_t receivedBytes;
extern volatile bool requestTelemetry;
extern bool printTelemetry;
extern HardwareSerial MySerial;
extern int16_t ESC_telemetrie[5]; // Temperature, Voltage, Current, used mAh, eRpM
extern uint32_t currentTime;
extern uint32_t startTime;
extern uint16_t dshotUserInputValue;

extern uint16_t dshotmin;
extern uint16_t dshotmid;
extern uint16_t dshotmax;
extern uint16_t dshotmaxrev;
extern uint16_t dshotidle; // 3.5%
extern uint16_t dshot10; // 10%
extern uint16_t dshot30; // 30%
extern uint16_t dshot40; // 40%
extern uint16_t dshot50; // 50%
extern uint16_t dshot75; // 75%
extern uint16_t dshot100; //100% 
extern uint16_t dshotidlerev; // 3.5%
extern uint16_t dshot10rev; // 10%
extern uint16_t dshot30rev; // 30%
extern uint16_t dshot40rev; // 40%
extern uint16_t dshot50rev; // 50%
extern uint16_t dshot75rev; // 75%
extern uint16_t dshot100rev; //100
extern uint16_t loopCounter;

void getTelemetry();
uint8_t update_crc8(uint8_t crc, uint8_t crc_seed);
uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen);
void startTelemetryTimer();
void receiveTelemtrie();
void dshotOutput(uint16_t value, bool telemetry);
void secondCoreTask( void * pvParameters );
