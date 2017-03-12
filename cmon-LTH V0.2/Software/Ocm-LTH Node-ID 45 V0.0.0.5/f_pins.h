/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - f_pins.h 
  VERSION	        : V0.0.0.5
  DATE		        : 04/09/2016
  DERNIERE MAJ.	  : 03/02/2017 	
  DESCRIPTION	    :  	 
  AUTEUR	        : Kermit - Email : developers@opencontrolmonitor.be
  COPYRIGHT       : (C) 2016-2017 OpenControlMonitor
  
  REMARQUES	      : This program is free software; you can redistribute it and/or
                    modify it under the terms of the GNU General Public License
                    version 2 as published by the Free Software Foundation.
  
  DOCUMENTATION   : http://www.opencontrolmonitor.be
  SUPPORT FORUM   : http://www.opencontrolmonitor.be/ocm/forum
  GITHUB          : https://github.com/opencontrolmonitor
 
*/

  void Set_Pin_Modes()
  {
    // *** Power pin DS18B20 ***
    
    pinMode(PWR_DS18B20, OUTPUT);
    
    // *** Power Pin DHT ***
    
    pinMode(PWR_DHT_SENSOR, OUTPUT);

    // *** Battery Pin ***
    
    pinMode(BATT_ADC, INPUT);

    // *** Save Address to E2Prom ***
    
    Update_E2Prom(0, NODE_ID);
  }
