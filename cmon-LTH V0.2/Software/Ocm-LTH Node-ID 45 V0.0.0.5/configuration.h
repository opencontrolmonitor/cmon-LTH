/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - configuration.h 
  VERSION	        : V0.0.0.5
  DATE		        : 04/09/2016
  DERNIERE MAJ.	  : 03/02/2017 	
  DESCRIPTION	    :  	 
  AUTEUR	        : Kermit - Email : developers@opencontrolmonitor.be
  COPYRIGHT       : (C) 2016-2017 OpenControlMonitor
  
  REMARQUES       : This program is free software; you can redistribute it and/or
                    modify it under the terms of the GNU General Public License
                    version 2 as published by the Free Software Foundation.
  
  DOCUMENTATION   : http://www.opencontrolmonitor.be
  SUPPORT FORUM   : http://www.opencontrolmonitor.be/ocm/forum
  GITHUB          : https://github.com/opencontrolmonitor	
 
*/

// ****************
// *** Child ID ***
// ****************

/*

  Recommended node ID allocation
  ------------------------------
  
  0         : *** Un-assigned ***
  1 - 4     : Base station & Control node   (Ocm-PI)
  5 - 14    : Environmental security        (Ocm-KEY)
  15 - 29   : Environmental security        (Ocm-PIR)
  30 - 44   : Environmental security        (Ocm-CTC)
  45 - 59   : Environmental sensing         (Ocm-LTH)
  60 - 74   : Environmental sensing         (Ocm-PLANT)
  75 - 89   : Environmental security        (Ocm-FLOOD)
  90 - 104  : Environmental security        (Ocm-NODE)
  105 - 119 : Environmental sensing         (Ocm-AQUA) 
  120 - 254 : *** Un-assigned *** 
 
*/

#define MARQUE                          "Ocm LTH"
#define VERSION                         "V0.0.0.5"
#define COPYRIGHT                       "(c) Ocm 02/2017"

int NODE_ID                           = 45;

#define CHILD_ID_HUM                    0     // DHT11 or DHT22
#define CHILD_ID_TEMP                   1     // DHT11 or DHT22
#define CHILD_ID_LIGHT                  2
#define CHILD_ID_BATT                   3
#define CHILD_ID_DS                     4

// **********************************
// *** Ocm-LTH Pin's Allocations ***
// **********************************

#define PWR_DHT_SENSOR                  4
#define HUMIDITY_DHT_DIGITAL_PIN        19

#define ONE_WIRE_BUS                    17
#define PWR_DS18B20                     16

#define LIGHT_PIN                       18

#define DIGITAL_OUTPUT_LED              8

#define BATT_ADC                        14

// *****************************
//  *** Variables Definition ***
// *****************************

#define DS18B20_On                      HIGH
#define DS18B20_Off                     LOW

#define DHT_On                          HIGH
#define DHT_Off                         LOW

float lastDHTTemp;
float lastDHTHum;

// ********************************
// *** Monitoring Configuration ***
// ********************************

unsigned long SLEEP_TIME = 180000;                                           // 3 minutes - Sleep time between reads (in milliseconds)

// ****************************
// *** Variables Definition ***
// ****************************

MySensor gw;
DHT dht;

// ***************
// *** DS18B20 ***
// ***************

OneWire oneWire(ONE_WIRE_BUS);                                              // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);                                        // Pass the oneWire reference to Dallas Temperature.
DeviceAddress tempDeviceAddress;

// *** addresses of sensors, MAX 4!!   *** //

byte allAddress [4][8];                                // 8 bytes per address
boolean DS18B20; 
int numSensors;
float lastTemp;
      
const int ASYNC_DELAY           = 375; // Default 375 - Delay for onewire sensors to respond - 750
const int TEMPERATURE_PRECISION = 11;  // Default 12  - Onewire temperature sensor precisionn. Details found below.

boolean receivedConfig = false;
boolean metric = true; 

/*
  NOTE: - There is a trade off between power consumption and sensor resolution.
    - A higher resolution will keep the processor awake longer - Approximate values found below.
                                         
    - DS18B20 temperature precision:
        9bit: 0.5C,  10bit: 0.25C,  11bit: 0.1125C, 12bit: 0.0625C
    - Required delay when reading DS18B20
        9bit: 95ms,  10bit: 187ms,  11bit: 375ms,   12bit: 750ms
         
    More info can be found here: http://harizanov.com/2013/07/optimizing-ds18b20-code-for-low-power-applications/   
*/

// ***********
// *** LDR ***
// ***********

float lastLight;

// ***************
// *** Battery ***
// ***************

float lastBatt;
int BatteryValue = 0;                                                       // value read from the VBAT pin
int SendBatteryValue = 0;
float outputValue = 0;                                                      // variable for voltage calculation

// **************
// *** E2Prom ***
// **************

char Return_Valeur_E2Prom;
int Address_E2Prom;

// ******************
// *** Debug Soft ***
// ******************

boolean Debug;                                                              // variable to store is debug is avalable or not.

MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
MyMessage msgLight(CHILD_ID_LIGHT, V_LIGHT_LEVEL);
MyMessage msgBatt(CHILD_ID_BATT, V_VOLTAGE);
MyMessage msgDs(CHILD_ID_DS,V_TEMP);

