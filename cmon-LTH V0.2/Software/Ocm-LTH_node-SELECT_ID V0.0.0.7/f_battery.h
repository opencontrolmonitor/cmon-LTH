/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - f_battery.h 
  VERSION	        : V0.0.0.7
  DATE		        : 04/09/2016
  DERNIERE MAJ.	  : 24/06/2017 	
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
    sensorValue = analogRead(BATT_ADC);                                             // get the battery Voltage
  
    // 1M, 470K divider across battery and using internal ADC ref of 1.1V
    // Sense point is bypassed with 0.1 uF cap to reduce noise at that point
    // ((1e6+470e3)/470e3)*1.1 = Vmax = 3.44 Volts
    // 3.44/1023 = Volts per bit = 0.003363075
  
    batteryPcnt = sensorValue / 10;
    batteryV  = sensorValue * 0.003363075;

    if(oldbatteryV != batteryV)
    {
      oldbatteryV = batteryV;
      send(msgBatt.set(batteryV, 1));

      if (Debug)
      {
        Serial.print("Sensor Value : ");
        Serial.println(sensorValue);   
        Serial.print("Battery Voltage : ");
        Serial.print(batteryV);
        Serial.println(" V");
      }
    }
      
    if (oldBatteryPcnt != batteryPcnt) 
    {
      oldBatteryPcnt = batteryPcnt;
  
      if (Debug)
      {
        Serial.print("Battery percent : ");
        Serial.print(batteryPcnt);
        Serial.println(" %");
      }
    }
  }

  void Ctrl_Chg_Battery()
  {
    batteryChg = digitalRead(BATT_ADC);
  
    if (oldbatteryChg != batteryChg)
    {
      oldbatteryChg = batteryChg;
  
      if (Debug)
      {
        if (batteryChg == 0)
        {
          Serial.print("Status Battery : ");
          Serial.println("Charging");
        }
      }
    }
  }
