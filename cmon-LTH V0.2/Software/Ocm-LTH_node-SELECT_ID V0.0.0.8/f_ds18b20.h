/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - f_ds18b20.h 
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

  void DS18B20_Power_On()
  {
    digitalWrite(PWR_DS18B20, DS18B20_On);
    delay(50);
  }
  
  void DS18B20_Power_Off()
  {
    digitalWrite(PWR_DS18B20, DS18B20_Off);
    delay(50);
  }

  void Initialise_DS18B20()
  {
    DS18B20_Power_On();
    
    delay(50); 
    sensors.begin();
    sensors.setWaitForConversion(false);             //disable automatic temperature conversion to reduce time spent awake, conversion will be implemented manually in sleeping http://harizanov.com/2013/07/optimizing-ds18b20-code-for-low-power-applications/ 
    numSensors=(sensors.getDeviceCount()); 
    
    byte j=0;                                        // search for one wire devices and
    byte k=-1;
                                                     // copy to device address arrays.
    while ((j < numSensors) && (oneWire.search(allAddress[j])))  j++; k++;
    if (numSensors==0)
    {
      if (Debug)
      {
        Serial.println("No DS18B20 detected");
      }
      
      DS18B20=0; 
    } 
    else 
    {
      DS18B20=1; 
      if (Debug)
      { 
        Serial.print("Detected "); Serial.print(numSensors); Serial.println(" DS18B20");
        present(CHILD_ID_DS + k, S_TEMP);
      } 
    }

    DS18B20_Power_Off();
  }
  
  void printAddress(DeviceAddress deviceAddress)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
    }
  }
  
  void Ctrl_DS18B20()
  {
    DS18B20_Power_On();
    
    if (DS18B20==1)
    {
      delay(50); 
      for(int j=0;j<numSensors;j++) sensors.setResolution(allAddress[j], TEMPERATURE_PRECISION);      // and set the a to d conversion resolution of each.
      sensors.requestTemperatures();                                        // Send the command to get temperatures
      delay(ASYNC_DELAY); //Must wait for conversion, since we use ASYNC mode
      float temp=(sensors.getTempC(allAddress[0]));
      
      if ((temp<125.0) && (temp>-40.0))
      {
        if(lastTemp != temp)
        {
          send(msgDs.set(temp, 1));
          lastTemp = temp;

          if (Debug)
          {
            Serial.print("DS18B20 : ");
            Serial.print(temp);
            Serial.println(" C");
          }
          
        }
      }
    }

    DS18B20_Power_Off();
    
  }
  
  void take_ds18b20_serial_number()
  {
    sensors.getAddress(tempDeviceAddress, 0);
    printAddress(tempDeviceAddress);
  }
