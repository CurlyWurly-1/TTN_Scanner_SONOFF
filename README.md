# TTN_Scanner_SONOFF
Arduino code for SONOFF S20 mains switch (ESP8266) - to automatically switch on TTN gateway if WiFi is present

To complete this hack, you need
- standard SONOFF S20 Mains switch
- Soldering Iron, solder and header pins (4 off)
- USB to Serial TTL adapter (Get a switchable 3.3v/5v one)
- A 3.3v linear regulator (N.B. The standard USB to Serial adaptor cannot supply enough power for the LEDs)
- Some dupont connectors
- PC with Arduino / ESP8266 software installed

You also need to know how to break into the case as described here
https://www.youtube.com/watch?v=GbaMF6zfQZU

N.B. MAINS VOLTAGE CAN KILL!!!
     DO NOT CONNECT THE SONOFF TO THE MAINS SUPPLY UNLESS FULLY RE_ASSEMBLED
     WHEN YOU ARE RE-PROGRAMMING, ONLY SUPPLY POWER VIA THE 3.3V LINEAR REGULATOR 
