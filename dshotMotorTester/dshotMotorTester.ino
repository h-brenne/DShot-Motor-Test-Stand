//#include "dshot.h"
#include "testPrograms.h"

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WebSerial.h>


#include <HardwareSerial.h>


//Serial communication web server
AsyncWebServer server(80);
const char* ssid = "Taklabben"; // Your WiFi SSID
const char* password = "ascend123"; // Your WiFi Password

String webmsg = "";

void recvMsg(uint8_t *data, size_t len){
  webmsg="";
  WebSerial.println("Received Data...");
  for(int i=0; i < len; i++){
    webmsg += char(data[i]);
  }
  WebSerial.println(webmsg);
}

//String choice="none";

void setup() {

    Serial.begin(115200);
    MySerial.begin(115200, SERIAL_8N1, 16, 17);

    pinMode(34, INPUT_PULLUP);
    //attachInterrupt(35, isr, FALLING);

    loadcellInit(&loadcell, LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, LOADCELL_CALIBRATION);    
    loadcellInit(&loadcellTorque, LOADCELLTORQUE_DOUT_PIN, LOADCELLTORQUE_SCK_PIN,LOADCELLTORQUE_CALIBRATION); 
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    //WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    WebSerial.msgCallback(recvMsg);
    server.begin();
    
    mlx.begin();  
    
    if ((rmt_send = rmtInit(5, true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }

    float realTick = rmtSetTick(rmt_send, 12.5); // 12.5ns sample rate
    Serial.printf("rmt_send tick set to: %fns\n", realTick);
  
    // Empty Rx Serial of garbage telemtry
    while(MySerial.available())
        MySerial.read();
    
    requestTelemetry = true;
    

    startTelemetryTimer(); // Timer used to request tlm continually in case ESC rcv bad packet
    
    xTaskCreatePinnedToCore(secondCoreTask, "Task1", 10000, NULL, 1, &Task1, 0); 

 

WebSerial.print("Ascend Teststand. Tests available: idle: Test motor at idle speed for 3 seconds\n 10: 10% for 3 seconds \n 30: 30% for 3 seconds\n 50: 50% for 3 seconds\n 75: 75% for 3 seconds.\n");
WebSerial.print("Enter Command");
bool validcommand = false;
String commandarray[] = {"dshotidle", "dshotidlerev", "dshot10", "dshot30", "dshot50", "dshot75", "dshot100", 
                        "dshot10rev", "dshot30rev", "dshot50rev", "dshot75rev", "dshot100rev", "MQTB", "MQTBrev", 
                        "no_output", "slowto50", "slowto75", "fulltest"};
while(!validcommand){
  for(byte i =0; i<(sizeof(commandarray)/sizeof(commandarray[0]));i++){
    if(webmsg==commandarray[i]){
      choice = webmsg;
      webmsg="";
      validcommand = true;
      }
    }
    delay(500);
  };
Serial.print("Choice is: ");
Serial.println(choice);
WebSerial.print("Choice is: ");
WebSerial.println(choice);


WebSerial.println("Confirm choice? \nTesting will run 10 seconds after successfull confirmation. The motor will first run at idle speed for 5 seconds. yes to confirm");
while(webmsg!="yes"){
  delay(20);
  }
WebSerial.println("Choice confirmed. Motor spinning in 10 seconds");
  startTime = millis();
  Serial.println("Data Start");

    Serial.print("Time (ms)"); 
    Serial.print(","); 
    Serial.print("dshot"); 
    Serial.print(",");  
    Serial.print("Voltage (V)");
    Serial.print(",");   
    Serial.print("Current (A)");
    Serial.print(",");
    Serial.print("RPM");
    Serial.print(",");  
    Serial.print("Thrust (g)");
    Serial.print(","); 
    Serial.print("Torque (Nm)");
    Serial.print(","); 
    Serial.print("Ambient temp (C)");
    Serial.print(","); 
    Serial.print("Motor temp (C)");
    Serial.print(","); 
    Serial.println("ESC temp (C)");
}


void loop() {

    loopCounter++;
    
    if(loopCounter>150){
      loopCounter = 0;
      if(analogRead(34)>4000){
        dshotUserInputValue = 0;
        while(true){
        Serial.print("KILLSWITCH TRIGGERED!");
        WebSerial.print("KILLSWITCH TRIGGERED!");
        delay(2000);
      }
    }
    }
    if(loadcell.is_ready()) {
        thrust = loadcell.get_units(1);
        
    }
    if(loadcellTorque.is_ready()) {
        torque = loadcellTorque.get_units(1);
        //Serial.print("torque: ");
        //Serial.print(torque);
    }
    
    if(!requestTelemetry) {
         receiveTelemtrie();
    } 

    //Simple single output test
  if(choice=="dshotidle"){
    testProgram_dshotidle();
    }
  else if(choice=="dshot10"){
    testProgram_dshot10();
    }
  else if(choice=="dshot30"){
    testProgram_dshot30();
    }
  else if(choice=="dshot50"){
    testProgram_dshot50();
    }
  else if(choice=="dshot75"){
    testProgram_dshot75();
    }    
  else if(choice=="dshotidlerev"){
    testProgram_idlerev();
    }    
  else if(choice=="dshot10rev"){
    testProgram_dshot10rev();
    }    
  else if(choice=="dshot30rev"){
    testProgram_dshot30rev();
    }    
  else if(choice=="dshot50rev"){
    testProgram_dshot50rev();
    }
  else if(choice=="dshot75rev"){
    testProgram_dshot75rev();
    }
  else if(choice=="dshot100rev"){
    testProgram_dshot100rev();
    }
  else if(choice=="MQTB"){
    testProgram_MQTB();
    }
  else if(choice=="MQTBrev"){
    testProgram_MQTBrev();
    }

  else if(choice=="fulltest"){
    testProgram_fulltest();
    }

  else if(choice=="slowto50"){
    testProgram_slowto50();
    }

  else if(choice=="slowto75"){
    testProgram_slowto75();
    }
            
  else if(choice=="no_output"){
        dshotUserInputValue = 0;
    }
  else {
    Serial.print("Error, unexpected command: ");
    Serial.println(choice);
    WebSerial.print("Error, unexpected command: ");
    WebSerial.println(choice);
    Serial.print("Restarting ESP...");
    WebSerial.print("Restarting ESP...");
    delay(1000);
    ESP.restart();
    }
}
