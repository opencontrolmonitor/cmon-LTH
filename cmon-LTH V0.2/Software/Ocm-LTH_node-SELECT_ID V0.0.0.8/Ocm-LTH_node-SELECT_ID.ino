/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH 
  VERSION	        : V0.0.0.8
  DATE		        : 04/09/2016
  DERNIERE MAJ.	  : 25/06/2017 	
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

//#define MY_DEBUG                                // Enable debug prints to serial monitor

#define MY_RADIO_NRF24                            // Enable and select radio type attached

#include <SPI.h>
#include <DHT.h>    
#include <DallasTemperature.h>
#include <OneWire.h>
#include <EEPROM.h>

#include "configuration.h"
#include "f_74hc165.h"
#include "f_battery.h"
#include "f_dht.h"
#include "f_e2prom.h"
#include "f_ds18b20.h"
#include "f_ldr.h"
#include "f_pins.h"

void before()
{
  Init_Select_ID();                             // Init 74HC165
  myNodeId = 45;                                // Default Node ID  
  Read_ID();                                    // Select Address
}

void presentation()
{
  sendSketchInfo(MARQUE, VERSION);

  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
  present(CHILD_ID_LIGHT, S_LIGHT_LEVEL);
  present(CHILD_ID_BATT, S_POWER);

  metric = getControllerConfig().isMetric;
}

void setup()  
{ 
  Update_E2Prom();
  
  Debug = Serial ? 1 : 0;

  // *** PIN MODES ***

  Set_Pin_Modes();

  // *** POWER DEVICES ***

  DS18B20_Power_On();
  DHT_Power_On();
  
  delay(500);

  // *********** //
  // *** DHT *** //
  // *********** //

  // *** Initialisation DHT sensor ***
  
  dht.setup(HUMIDITY_DHT_DIGITAL_PIN);
  
  // *************** //
  // *** DS18B20 *** //
  // *************** //

  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  if (Debug)
  {
    Serial.print(MARQUE);
    Serial.print(" - ");
    Serial.println(VERSION);
    Serial.println(COPYRIGHT);

    Serial.print("Node ID : ");
    Serial.println(myNodeId);
  }
  
  /*********************************************************/

  // *** Present all sensors to controller ***

  Initialise_DS18B20();
 
}

void loop()      
{
  // *** Control DHT ***
  
  Ctrl_Dht();

  // *** Control LDR ***
  
  Ctrl_Ldr();
  
  // *** Control Battery ***
  
  Ctrl_Voltage_Battery();
  
  // *** DS18B20 ***
  
  Ctrl_DS18B20();
  
  /* */
  
  sleep(SLEEP_TIME); //sleep a bit
}


