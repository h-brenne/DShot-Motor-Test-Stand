#include "dshot.h"

TaskHandle_t Task1;
rmt_data_t dshotPacket[16];
rmt_obj_t* rmt_send = NULL;
hw_timer_t * timer = NULL;
uint8_t receivedBytes = 0;
volatile bool requestTelemetry = false;
bool printTelemetry = true;
int16_t ESC_telemetrie[5]; // Temperature, Voltage, Current, used mAh, eRpM
uint16_t dshotUserInputValue = 0;

HardwareSerial MySerial(1);

uint32_t currentTime;
uint32_t startTime;

uint8_t temperature = 0;
uint8_t temperatureMax = 0;
float voltage = 0;
float voltageMin = 99;
uint32_t current = 0;
uint32_t currentMax = 0;
uint32_t erpm = 0;
uint32_t erpmMax = 0;
uint32_t rpm = 0;
uint32_t rpmMAX = 0;
uint32_t kv = 0;
uint32_t kvMax = 0;

uint16_t dshotmin = 48;
uint16_t dshotmid = 1048;
uint16_t dshotmax = 1047;
uint16_t dshotmaxrev = 2047;
uint16_t dshotidle = dshotmin + round(3.5*(dshotmaxrev-dshotmid)/100); // 3.5%
uint16_t dshot10 =   dshotmin + round(10*(dshotmaxrev-dshotmid)/100); // 10%
uint16_t dshot30 =   dshotmin + round(30*(dshotmaxrev-dshotmid)/100); // 30%
uint16_t dshot40 =   dshotmin + round(40*(dshotmaxrev-dshotmid)/100); // 40%
uint16_t dshot50 =   dshotmin + round(50*(dshotmaxrev-dshotmid)/100); // 50%
uint16_t dshot75 =   dshotmin + round(75*(dshotmaxrev-dshotmid)/100); // 75%
uint16_t dshot100 =   dshotmax; //100% 
uint16_t dshotidlerev = dshotmid + round(3.5*(dshotmaxrev-dshotmid)/100); // 3.5%
uint16_t dshot10rev =   dshotmid + round(10*(dshotmaxrev-dshotmid)/100); // 10%
uint16_t dshot30rev =   dshotmid + round(30*(dshotmaxrev-dshotmid)/100); // 30%
uint16_t dshot40rev =   dshotmid + round(40*(dshotmaxrev-dshotmid)/100); // 40%
uint16_t dshot50rev =   dshotmid + round(50*(dshotmaxrev-dshotmid)/100); // 50%
uint16_t dshot75rev =   dshotmid + round(75*(dshotmaxrev-dshotmid)/100); // 75%
uint16_t dshot100rev = dshotmaxrev; //100% pls fix
uint16_t loopCounter = 0;

void IRAM_ATTR getTelemetry(){
  requestTelemetry = true;        
}

uint8_t update_crc8(uint8_t crc, uint8_t crc_seed){
  uint8_t crc_u, i;
  crc_u = crc;
  crc_u ^= crc_seed;
  for ( i=0; i<8; i++) crc_u = ( crc_u & 0x80 ) ? 0x7 ^ ( crc_u << 1 ) : ( crc_u << 1 );
  return (crc_u);
}

uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen){
  uint8_t crc = 0, i;
  for( i=0; i<BufLen; i++) crc = update_crc8(Buf[i], crc);
  return (crc);
}

void startTelemetryTimer() {
  timer = timerBegin(0, 80, true); // timer_id = 0; divider=80; countUp = true;
  timerAttachInterrupt(timer, &getTelemetry, true); // edge = true
  timerAlarmWrite(timer, 20000, true);  //1000 = 1 ms
  timerAlarmEnable(timer);
}


void receiveTelemtrie(){
  static uint8_t SerialBuf[10];
  if(MySerial.available()){
    SerialBuf[receivedBytes] = MySerial.read();
    receivedBytes++;
    }
    if(receivedBytes > 9){ // transmission complete
      uint8_t crc8 = get_crc8(SerialBuf, 9); // get the 8 bit CRC 
      if(crc8 != SerialBuf[9]) {
        // Empty Rx Serial of garbage telemtry
        while(MySerial.available())
        MySerial.read();     
        requestTelemetry = true; 
        return; // transmission failure 
        }
          
      // compute the received values
      ESC_telemetrie[0] = SerialBuf[0]; // temperature
      ESC_telemetrie[1] = (SerialBuf[1]<<8)|SerialBuf[2]; // voltage
      ESC_telemetrie[2] = (SerialBuf[3]<<8)|SerialBuf[4]; // Current
      ESC_telemetrie[3] = (SerialBuf[5]<<8)|SerialBuf[6]; // used mA/h
      ESC_telemetrie[4] = (SerialBuf[7]<<8)|SerialBuf[8]; // eRpM *100
            
      requestTelemetry = true;

      if(printTelemetry) {
        Serial.print(currentTime); 
        Serial.print(","); 
        Serial.print(dshotUserInputValue); 
        Serial.print(",");  
        Serial.print(0.968*ESC_telemetrie[1] / 100.0); 
        Serial.print(",");   
        Serial.print(ESC_telemetrie[2] / 100.0); 
        Serial.print(","); 
        Serial.print(ESC_telemetrie[4] * 100 / (MOTOR_POLES / 2)); 
        Serial.print(",");  
        Serial.print(thrust);
        Serial.print(","); 
        Serial.print(torque);
        Serial.print(","); 
        Serial.print(mlx.readAmbientTempC());
        Serial.print(","); 
        Serial.print(mlx.readObjectTempC());
        Serial.print(","); 
        Serial.println(ESC_telemetrie[0]);
        }
          
      temperature = 0.9*temperature + 0.1*ESC_telemetrie[0];
      if (temperature > temperatureMax) {
        temperatureMax = temperature;
        }
            
      voltage = 0.9*voltage + 0.1*(ESC_telemetrie[1] / 100.0);
      if (voltage < voltageMin) {
        voltageMin = voltage;
        }
            
      current = 0.9*current + 0.1*(ESC_telemetrie[2] * 100);
      if (current > currentMax) {
        currentMax = current;
        }
            
      erpm = 0.9*erpm + 0.1*(ESC_telemetrie[4] * 100);
      if (erpm > erpmMax) {
        erpmMax = erpm;
        }
            
      rpm = erpm / (MOTOR_POLES / 2);
      if (rpm > rpmMAX) {
        rpmMAX = rpm;
        }
            
      if (rpm) {                  // Stops weird numbers :|
        kv = rpm / voltage / ( (float(dshotUserInputValue) - dshotmin) / (dshotmax - dshotmin) );
        } 
      else {
        kv = 0;
        }
      if (kv > kvMax) {
        kvMax = kv;
        }
    }
  return;
}

void dshotOutput(uint16_t value, bool telemetry) {
    
  uint16_t packet;
    
  // telemetry bit    
  if (telemetry) {
    packet = (value << 1) | 1;
    } 
  else {
    packet = (value << 1) | 0;
    }

  // https://github.com/betaflight/betaflight/blob/09b52975fbd8f6fcccb22228745d1548b8c3daab/src/main/drivers/pwm_output.c#L523
  int csum = 0;
  int csum_data = packet;
  for (int i = 0; i < 3; i++) {
    csum ^=  csum_data;
    csum_data >>= 4;
    }
  csum &= 0xf;
  packet = (packet << 4) | csum;

  // durations are for dshot600
  // https://blck.mn/2016/11/dshot-the-new-kid-on-the-block/
  // Bit length (total timing period) is 1.67 microseconds (T0H + T0L or T1H + T1L).
  // For a bit to be 1, the pulse width is 1250 nanoseconds (T1H – time the pulse is high for a bit value of ONE)
  // For a bit to be 0, the pulse width is 625 nanoseconds (T0H – time the pulse is high for a bit value of ZERO)
  for (int i = 0; i < 16; i++) {
    if (packet & 0x8000) {
      dshotPacket[i].level0 = 1;
      dshotPacket[i].duration0 = 100;
      dshotPacket[i].level1 = 0;
      dshotPacket[i].duration1 = 34;
      }
    else {
      dshotPacket[i].level0 = 1;
      dshotPacket[i].duration0 = 50;
      dshotPacket[i].level1 = 0;
      dshotPacket[i].duration1 = 84;
      }
    packet <<= 1;
    }
    
  rmtWrite(rmt_send, dshotPacket, 16);
  return;
}




// Second core used to handle dshot packets
void secondCoreTask( void * pvParameters ){
  while(1){
    dshotOutput(dshotUserInputValue, requestTelemetry);
    if (requestTelemetry) {                
      requestTelemetry = false;
      receivedBytes = 0;
      }
    delay(1);     
    } 
}
