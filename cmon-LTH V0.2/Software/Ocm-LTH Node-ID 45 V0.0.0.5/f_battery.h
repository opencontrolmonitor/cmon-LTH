/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - f_battery.h 
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

  void Ctrl_Voltage_Battery()
  {
    // *** Read the analog in value ***
    
    BatteryValue = analogRead(BATT_ADC);
    
    // *** Calculate the battery voltage value ***
    
    outputValue = (float(BatteryValue)*5)/1023*2;
  
    if (outputValue != lastBatt) 
    {
      lastBatt = outputValue;
      gw.send(msgBatt.set(outputValue, 1));
      
      if (Debug)
      {
        Serial.print("Battery : ");
        Serial.print(outputValue);
        Serial.println(" V");
      }
    }
  }
