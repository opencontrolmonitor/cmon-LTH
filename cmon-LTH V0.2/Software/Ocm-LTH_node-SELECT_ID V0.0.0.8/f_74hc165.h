/*

  COMPOSANT       : ATMEL AVR 8 Bits (RISC)       ATMEGA328   Quartz = 16,0 MHz
  PROGRAMME       : Ocm-LTH - f_74hc165.h 
  VERSION         : V0.0.0.8
  DATE            : 04/09/2016
  DERNIERE MAJ.   : 25/06/2017  
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

  void Init_Select_ID()
  {
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, INPUT);

    digitalWrite(CLOCK,LOW);
    digitalWrite(LATCH,LOW);
  }

  byte shiftInFixed(byte dataPin, byte clockPin) 
  {
    byte value = 0;
  
    for (byte i = 0; i < 8; ++i) 
    {
      value = value |  (digitalRead(dataPin) << i);
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
    }
    return value;
  }

  void Read_ID()
  {
    digitalWrite(LATCH,HIGH);

    byte a_temp = shiftInFixed(DATA,CLOCK);

    digitalWrite(LATCH,LOW);

    // Envoie la valeur lue si elle change
    if ( a_temp != a ) 
    {
      a = a_temp;
      if (Debug)
      {
        Serial.print("Address Node : ");
        Serial.println(a, DEC);
      }
      
      switch(a)
      {
        case 240 : // Addr = 0
          MY_NODE_ID = myNodeId;
          break;

        case 112 : // Addr = 1
          MY_NODE_ID = (myNodeId + 1);
          break;

        case 176 : // Addr = 2
          MY_NODE_ID = (myNodeId + 2);
          break;

        case 48 : // Addr = 3
          MY_NODE_ID = (myNodeId + 3);
          break;

        case 208 : // Addr = 4
          MY_NODE_ID = (myNodeId + 4);
          break;

        case 80 : // Addr = 5
          MY_NODE_ID = (myNodeId + 5);
          break;

        case 144 : // addr = 6
          MY_NODE_ID = (myNodeId + 6);
          break;

        case 16 : // addr = 7
          MY_NODE_ID = (myNodeId + 7);
          break;

        case 224 : // Addr = 8
          MY_NODE_ID = (myNodeId + 8);
          break;
          
        case 96 : // Addr = 9
          MY_NODE_ID = (myNodeId + 9);
          break;

        case 160 : // Addr = 10
          MY_NODE_ID = (myNodeId + 10);
          break;

        case 32 : // Addr = 11
          MY_NODE_ID = (myNodeId + 11);
          break;

        case 192 : // Addr = 12
          MY_NODE_ID = (myNodeId + 12);
          break;

        case 64 : // Addr = 13
          MY_NODE_ID = (myNodeId + 13);
          break;

        case 128 : // Addr = 14
          MY_NODE_ID = (myNodeId + 14);
          break;

        case 0 : // Addr = 15
          MY_NODE_ID = (myNodeId + 15);
          break;

        default :
          MY_NODE_ID = myNodeId;
          break;
       
      }
      
    }
  }


