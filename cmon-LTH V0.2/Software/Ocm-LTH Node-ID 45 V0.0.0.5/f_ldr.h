/*

  COMPOSANT       :	ATMEL AVR 8 Bits (RISC)       ATMEGA328 	Quartz = 16,0 MHz
  PROGRAMME	      : Ocm-LTH - ldr.h 
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

  void Ctrl_Ldr()
  {
    float light_level = analogRead(LIGHT_PIN);
    if (light_level != lastLight) 
    {
      lastLight = light_level;
      gw.send(msgLight.set(light_level, 1));
      if(Debug)
      {
        Serial.print("Light : ");
        Serial.println(light_level);
      }
    }
  }
