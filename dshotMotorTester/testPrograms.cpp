#include "testPrograms.h"

String choice="none";

void testProgram_dshotidle(){
  currentTime = millis()-startTime;
  if (currentTime >= 10000 && currentTime < 12000) {
    dshotUserInputValue = dshotidle;
    }
  if (currentTime >= 12000 && currentTime < 13000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }
void testProgram_dshot10(){
  currentTime = millis()-startTime;
  if (currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if (currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot10;
    }
  if (currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot30() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot30;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot50() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot50;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot75(){
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot75;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_idlerev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot10rev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot10rev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot30rev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot30rev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot50rev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot50rev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot75rev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot75rev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_dshot100rev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 20000) {
    dshotUserInputValue = dshot100rev;
    }
  if(currentTime >= 20000 && currentTime < 22000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_MQTB() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if(currentTime >= 15000 && currentTime < 17000) {
    dshotUserInputValue = dshot50;
    } 
  else if(currentTime >= 17000 && currentTime < 19000) {
    dshotUserInputValue = dshotidle;
    } 
  else if(currentTime >= 19000 && currentTime < 21000) {
    dshotUserInputValue = dshot75;
    }
  else if(currentTime >= 21000 && currentTime < 23000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 23000 && currentTime < 25000) {
    dshotUserInputValue = dshot100;
    }
  else if(currentTime >= 25000 && currentTime < 27000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 27000 && currentTime < 33000) {      
    dshotUserInputValue = dshotidle + (currentTime-27000)*(dshotmax-dshotidle)/6000.0;        
    }
  else if(currentTime >= 33000 && currentTime < 35000) {
    dshotUserInputValue = dshotidle;
    } 
  else if(currentTime >= 35000 && currentTime < 37000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_MQTBrev() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidlerev;
    }
  if(currentTime >= 15000 && currentTime < 17000) {
    dshotUserInputValue = dshot50rev;
    }
  else if(currentTime >= 17000 && currentTime < 19000) {
    dshotUserInputValue = dshotidlerev;
    }
  else if(currentTime >= 19000 && currentTime < 21000) {
    dshotUserInputValue = dshot75rev;
    }
  else if(currentTime >= 21000 && currentTime < 23000) {
    dshotUserInputValue = dshotidlerev;
    } 
  else if(currentTime >= 23000 && currentTime < 25000) {
    dshotUserInputValue = dshot100rev;
    } 
  else if(currentTime >= 25000 && currentTime < 27000) {
    dshotUserInputValue = dshotidlerev;
    } 
  else if(currentTime >= 27000 && currentTime < 33000) {      
    dshotUserInputValue = dshotidlerev + (currentTime-27000)*(dshotmaxrev-dshotidlerev)/6000.0;        
    } 
  else if(currentTime >= 33000 && currentTime < 35000) {
    dshotUserInputValue = dshotidlerev;
    } 
  else if(currentTime >= 35000 && currentTime < 37000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_fulltest() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  if(currentTime >= 15000 && currentTime < 17000) {
    dshotUserInputValue = dshot30;
    } 
  else if(currentTime >= 17000 && currentTime < 19000) {
    dshotUserInputValue = dshot40;
    } 
  else if(currentTime >= 19000 && currentTime < 21000) {
    dshotUserInputValue = dshot50;
    } 
  else if(currentTime >= 21000 && currentTime < 23000) {
    dshotUserInputValue = dshot75;
    } 
  else if(currentTime >= 23000 && currentTime < 25000) {
    dshotUserInputValue = dshot100;
    } 
  else if(currentTime >= 25000 && currentTime < 27000) {
    dshotUserInputValue = dshotidle;
    } 
  else if(currentTime >= 27000 && currentTime < 33000) {      
    dshotUserInputValue = dshotidle + (currentTime-27000)*(dshotmax-dshotidle)/6000.0;        
    }
  else if(currentTime >= 33000 && currentTime < 35000) {
    dshotUserInputValue = dshotidle;
    } 
  else if(currentTime >= 35000 && currentTime < 37000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_slowto50() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 15000 && currentTime < 25000) {      
    dshotUserInputValue = dshotidle + (currentTime-15000)*(dshot50)/10000.0;        
    } 
  else if(currentTime >= 25000 && currentTime < 27000) {
    dshotUserInputValue = dshotidle;
    }        
  else if(currentTime >= 27000 && currentTime < 29000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_slowto75() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 15000 && currentTime < 25000) {      
    dshotUserInputValue = dshotidle + (currentTime-15000)*(dshot75)/10000.0;        
    } 
  else if(currentTime >= 25000 && currentTime < 27000) {
    dshotUserInputValue = dshotidle;
    }    
  else if(currentTime >= 27000 && currentTime < 29000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_2min_50() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 15000 && currentTime < 25000) {      
    dshotUserInputValue = dshotidle + (currentTime-15000)*(dshot50)/10000.0;        
    } 
  else if(currentTime >= 25000 && currentTime < 145000) {
    dshotUserInputValue = dshot50;
    }        
  else if(currentTime >= 145000 && currentTime < 150000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }
void testProgram_30sec_50() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 15000 && currentTime < 25000) {      
    dshotUserInputValue = dshotidle + (currentTime-15000)*(dshot50)/10000.0;        
    } 
  else if(currentTime >= 25000 && currentTime < 55000) {
    dshotUserInputValue = dshot50;
    }        
  else if(currentTime >= 55000 && currentTime < 60000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }

void testProgram_2min_75() {
  currentTime = millis()-startTime;
  if(currentTime >= 10000 && currentTime < 15000) {
    dshotUserInputValue = dshotidle;
    }
  else if(currentTime >= 15000 && currentTime < 25000) {      
    dshotUserInputValue = dshotidle + (currentTime-15000)*(dshot75)/10000.0;        
    } 
  else if(currentTime >= 25000 && currentTime < 145000) {
    dshotUserInputValue = dshot75;
    }        
  else if(currentTime >= 145000 && currentTime < 150000) {
    printTelemetry = false;
    dshotUserInputValue = 0;
    }
  }
