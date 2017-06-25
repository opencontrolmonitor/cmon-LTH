/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - f_dht.h 
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

  void DHT_Power_On()
  {
    digitalWrite(PWR_DHT_SENSOR, DHT_On);
    delay(500);
  }
  
  void DHT_Power_Off()
  {
    digitalWrite(PWR_DHT_SENSOR, DHT_Off);
    delay(500);
  }
  
  void Ctrl_Dht()
  {
    DHT_Power_On();
    delay(2000);
    
    delay(dht.getMinimumSamplingPeriod());
    
    float temperature = dht.getTemperature();
    if (isnan(temperature)) 
    {
      if(Debug)
      {
        Serial.println("Failed reading temperature from DHT");
      }
    } 
    else 
    if (temperature != lastDHTTemp) 
    {
      lastDHTTemp = temperature;
      if (!metric) 
      {
        temperature = dht.toFahrenheit(temperature);
      }
      send(msgTemp.set(temperature, 1));
      if(Debug)
      {
        Serial.print("Temp : ");
        Serial.print(temperature);
        Serial.println(" C");
      }
    }
  
    float humidity = dht.getHumidity();
    if (isnan(humidity)) 
    {
      Serial.println("Failed reading humidity from DHT");
    } 
    else 
    if (humidity != lastDHTHum) 
    {
      lastDHTHum = humidity;
      send(msgHum.set(humidity, 1));
      if(Debug)
      {
        Serial.print("Hum : ");
        Serial.print(humidity);
        Serial.println(" %");
      }
    }
    DHT_Power_Off();
  }

