# DShot-Motor-Test-Stand
![Stand](/img/stand1.jpg)

Motor test stand made for Ascend NTNU. 

# Features
* Capable of measuring thrust, torque, voltage, current, rpm, motor temperature, ESC temperature and ambient temperature. 
* Using [WebSerial](https://github.com/ayushsharma82/WebSerial) for remote commands to start the different tests.
* Physical kill switch

# Components
* ESP32. I'm eusing the ESP32 devkit v1.
* BLHELI_32 ESC. Other ESC's won't have the telemetry.
* HX711 amplifier and three load cells. You can use one HX711 for the two load cells measuring torque. There's also a pad that can be bridged to up the refresh rate to 80Hz. 
* [MLX9061](https://www.banggood.com/CJMCU-906-MLX90614ESF-IR-Infrared-Body-Temperature-Sensor-Non-contact-Temperature-Module-p-1079036.html?rmmds=myorder&cur_warehouse=CN) optical temp sensor for motor and ambient temperature. 
* Safety switch as kill switch

DShot implementation from JyeSmith.  
https://github.com/JyeSmith/dshot-esc-tester

CAD by Adrian Stokdal Opheim

![plot](/Plots/XING4214_fulltest.png)
