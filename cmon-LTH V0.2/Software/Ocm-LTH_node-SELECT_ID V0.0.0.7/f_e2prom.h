/*

  COMPOSANT       : ATMEL AVR 8 Bits (RISC)       ATMEGA328   Quartz = 16,0 MHz
  PROGRAMME       : Ocm-LTH - f_e2prom.h 
  VERSION         : V0.0.0.7
  DATE            : 04/09/2016
  DERNIERE MAJ.   : 24/06/2017  
  DESCRIPTION     :    
  AUTEUR          : Kermit - Email : developers@opencontrolmonitor.be
  COPYRIGHT       : (C) 2016-2017 OpenControlMonitor
  
  REMARQUES       : This program is free software; you can redistribute it and/or
                    modify it under the terms of the GNU General Public License
                    version 2 as published by the Free Software Foundation.
  
  DOCUMENTATION   : http://www.opencontrolmonitor.be
  SUPPORT FORUM   : http://www.opencontrolmonitor.be/ocm/forum
  GITHUB          : https://github.com/opencontrolmonitor 
 
*/

  // **********************
  // *** Address E2Prom ***
  // **********************
  
  /*
     000 :  Default NODE_ID Address      -> 45
     001 :  
     002 :  
     003 :  
         
  */                                

  // ********************
  // *** Write E2Prom ***
  // ********************
  
  void Write_E2Prom(int Address_E2Prom, int Valeur_E2Prom)
  {
    EEPROM.write(Address_E2Prom, Valeur_E2Prom);
  }
  
  // *******************
  // *** Read E2Prom ***
  // *******************
  
  void Read_E2Prom(int Address_E2Prom)
  {
    Return_Valeur_E2Prom = EEPROM.read(Address_E2Prom);
  }
  
  // *********************
  // *** Update E2Prom ***
  // *********************
  
  void Update_E2Prom(int Address_E2Prom, int Valeur_E2Prom)
  {
    EEPROM.update(Address_E2Prom, Valeur_E2Prom);
  }
  
  // *********************
  // *** Update E2Prom ***
  // *********************
  
  void Update_E2Prom()
  {
    Update_E2Prom(0,45);                                       // Default NODE_ID
    delay(10);
    Update_E2Prom(1,0);                                        // 
    delay(10);
    Update_E2Prom(3,0);                                        // 
    delay(10);
    Update_E2Prom(4,0);                                        // 
    delay(10);
    Update_E2Prom(5,0);                                        // 
    delay(10);
    Update_E2Prom(6,0);                                        // 
    delay(10);
    Update_E2Prom(7,0);                                        // 
    delay(10);
    Update_E2Prom(8,0);                                        // 
    delay(10);
    Update_E2Prom(9,0);                                        // 
    delay(10);
  }

  // **********************
  // *** Restore E2Prom ***
  // **********************

  void Restore_E2Prom()
  {
    Write_E2Prom(0,45);                                       // Default NODE_ID
    delay(10);
    Write_E2Prom(1,0);                                        // 
    delay(10);
    Write_E2Prom(3,0);                                        // 
    delay(10);
    Write_E2Prom(4,0);                                        // 
    delay(10);
    Write_E2Prom(5,0);                                        // 
    delay(10);
    Write_E2Prom(6,0);                                        // 
    delay(10);
    Write_E2Prom(7,0);                                        // 
    delay(10);
    Write_E2Prom(8,0);                                        // 
    delay(10);
    Write_E2Prom(9,0);                                        // 
    delay(10);
  }
