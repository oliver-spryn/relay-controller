                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 = nowMilliseconds;
  }

  // check for return character
}

//*****************************************************************************
void SmartThings::handleLine(void)
{
  if(_nBufRX > 0)
  {
    if(isRxLine(_pBufRX))
    {
      debugPrintBuffer("->| ", _pBufRX, _nBufRX);
      {
        char messageBuf[255]; // TODO: Figure this out
        uint_fast8_t messageBufLength = translatePayload(_pBufRX, _nBufRX, messageBuf);

        if(messageBufLength > 0)
        {
          debugPrintBuffer("->| payload :: ",(uint8_t *)messageBuf, messageBufLength);

          _calloutFunction(messageBuf);  // call out to main application
          // that.handleSmartThingMessage(message);
        }
        else
        {
          debugPrintBuffer("->| no payload from :: ", _pBufRX, _nBufRX);
        }
      }
    }
    else 
    { //XXX Totally slapped together since this is temp-- will go away with command set change 
      uint_fast8_t i=0;
      bool found = false;
      if (_nBufRX >= 32) //netinfo:0022A3000000B675,E30E,02 
      {
        while (i < _nBufRX)
        {
          if (
              (_pBufRX[i  ] == 'n') && 
              (_pBufRX[i+1] == 'e') && 
              (_pBufRX[i+2] == 't') && 
              (_pBufRX[i+3] == 'i') && 
              (_pBufRX[i+4] == 'n') && 
              (_pBufRX[i+5] == 'f') && 
              (_pBufRX[i+6] == 'o') && 
              (_pBufRX[i+7] == ':') &&
              (_pBufRX[i+24] == ',') &&
              (_pBufRX[i+29] == ',') 
             )
          { 
            // parse off EUI 
            if(
                isAsciiHex(_pBufRX[i+8]) && 
                isAsciiHex(_pBufRX[i+9]) && 
                isAsciiHex(_pBufRX[i+10]) && 
                isAsciiHex(_pBufRX[i+11]) && 
                isAsciiHex(_pBufRX[i+12]) && 
                isAsciiHex(_pBufRX[i+13]) && 
                isAsciiHex(_pBufRX[i+14]) && 
                isAsciiHex(_pBufRX[i+15]) && 
                isAsciiHex(_pBufRX[i+16]) && 
                isAsciiHex(_pBufRX[i+17]) && 
                isAsciiHex(_pBufRX[i+18]) && 
                isAsciiHex(_pBufRX[i+19]) && 
                isAsciiHex(_pBufRX[i+20]) && 
                isAsciiHex(_pBufRX[i+21]) && 
                isAsciiHex(_pBufRX[i+22]) && 
                isAsciiHex(_pBufRX[i+23]) &&

                isAsciiHex(_pBufRX[i+25]) && 
                isAsciiHex(_pBufRX[i+26]) && 
                isAsciiHex(_pBufRX[i+27]) && 
                isAsciiHex(_pBufRX[i+28]) &&

                isAsciiHex(_pBufRX[i+30]) && 
                isAsciiHex(_pBufRX[i+31]) 
                )
                {
                  uint8_t tempNetStat = asciiToHexU8(&(_pBufRX[i+30]));
                  if (tempNetStat <= STATE_LEAVING) // make sure it maps to the enum
                  {
                    _networkState = (SmartThingsNetworkState_t)tempNetStat;

                    _nodeID = asciiToHexU8(&(_pBufRX[i+25]));
                    _nodeID <<= 8; 
                    _nodeID |= asciiToHexU8(&(_pBufRX[i+27]));

                    _eui64[7] = asciiToHexU8(&(_pBufRX[i+8 ]));
                    _eui64[6] = asciiToHexU8(&(_pBufRX[i+10]));
                    _eui64[5] = asciiToHexU8(&(_pBufRX[i+12]));
                    _eui64[4] = asciiToHexU8(&(_pBufRX[i+14]));
                    _eui64[3] = asciiToHexU8(&(_pBufRX[i+16]));
                    _eui64[2] = asciiToHexU8(&(_pBufRX[i+18]));
                    _eui64[1] = asciiToHexU8(&(_pBufRX[i+20]));
                    _eui64[0] = asciiToHexU8(&(_pBufRX[i+22]));

                    debugPrintBuffer("  |~> ", &(_pBufRX[i]), 32);
                    found = true;
                  }
                }
          }
          i++;
        }
      }
      if (found == false)
        debugPrintBuffer("->| IGNORING :: ", _pBufRX, _nBufRX);
    }
    _nBufRX = 0;  
  }
}
  //*****************************************************************************
  void SmartThings::_shieldGetNetworkInfo(void)
  {
    print("custom netinfo");
    print('\n');

    if(_isDebugEnabled)
    {
      Serial.print("  |<~ ");
      Serial.print("custom netinfo");
      Serial.print('\n');
    }
  }


  //*****************************************************************************
  // Thing API  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //            V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
  //*****************************************************************************
  SmartThings::SmartThings(uint8_t pinRX, uint8_t pinTX, SmartThingsCallout_t *callout, String shieldType, bool enableDebug) :
    SoftwareSerial(pinRX, pinTX),  
    _calloutFunction(callout), 
    _isDebugEnabled(enableDebug), 
    _nBufRX(0), 
    _lastPingMS(0xFFFFFF00),
    _lastShieldMS(0xFFFFFF00),
    _networkState(STATE_UNKNOWN)
  {
    uint_fast8_t i;

    i = shieldType.length();
    if (i > 32) 
      i = 32;
    _shieldTypeLen = i;

    while (i--)
    {
      _shieldTypeBuf[i] = (uint8_t)shieldType[i];
    } 

    begin(2400);
  }

  //*****************************************************************************
  //SmartThings::~SmartThings() : ~SoftwareSerial()
  SmartThings::~SmartThings() 
  {
  }

  //*****************************************************************************
  void SmartThings::run(void)
  { 
    while((_nBufRX < SMARTTHINGS_RX_BUFFER_SIZE) && available())
    {
#if 0 
      _pBufRX[_nBufRX++] = read();
#else
      uint8_t readByte = read();
      if((readByte == 0x0D) || (readByte == 0x0A))
      { // handle data from SmartThing line-by-line 
        handleLine();
      }
      else
      { 
        // keep track of everything that comes in until we reach a newline
        // TODO(cwvh): validate bufferlength 1988-10-19
        //if (_nBufRX > 200)
        //  panic("too many characters!"); 
        _pBufRX[_nBufRX++] = readByte;
      }
#endif 
    }
    _process();
  }

  //*****************************************************************************
  void SmartThings::send(String message)
  {
    // e.g. thing.print("raw 0x0 {00 00 0A 0A 62 75 74 74 6f 6e 20 64 6f 77 6e }");
    print("raw 0x0 { 00 00 0A 0A ");
    if(_isDebugEnabled)
    {
      Serial.print("<-| ");
      Serial.print("raw 0x0 { 00 00 0A 0A ");
    }

    for(int i = 0; i < message.length(); i++)
    {
      char c = message[i];

      print(c, HEX);
      print(' ');

      if(_isDebugEnabled)
      {
        Serial.print(c, HEX);
        Serial.print(' ');
      }
    }

    print('}');
    print('\n');
    if(_isDebugEnabled)
    {
      Serial.print('}');
      Serial.print('\n');
    }

    print("send 0x0 1 1");
    print('\n');
  }

  //*****************************************************************************
  void SmartThings::shieldSetLED(uint8_t red, uint8_t green, uint8_t blue)
  {
    if (red > 9)    red = 9;
    if (green > 9)  green = 9;
    if (blue > 9)   blue = 9;

    print("custom rgb ");
    write( (red+'0') );
    print(' ');
    write( (green+'0') );
    print(' ');
    write( (blue+'0') );
    print(' ');
    print('\n');

    if(_isDebugEnabled)
    {
      Serial.print("  |<~ ");
      Serial.print("custom rgb ");
      Serial.write(red+'0');
      Serial.print(' ');
      Serial.write(green+'0');
      Serial.print(' ');
      Serial.write(blue+'0');
      Serial.print(' ');
      Serial.print('\n');
    }
  }


  //*****************************************************************************
  SmartThingsNetworkState_t SmartThings::shieldGetLastNetworkState(void)
  {
    return _networkState;
  }

  //*****************************************************************************
  SmartThingsNetworkState_t SmartThings::shieldGetNetworkState(void)
  {
    _shieldGetNetworkInfo();
    return _networkState;
  }

  //*****************************************************************************
  uint16_t SmartThings::shieldGetNodeID(void)
  { 
    _shieldGetNetworkInfo();
    return _nodeID;
  }

  //*****************************************************************************
  void SmartThings::shieldGetEUI64(uint8_t eui[8])
  {
    _shieldGetNetworkInfo();
    {
      uint_fast8_t i = 7;
      do 
      {
        eui[i] = _eui64[i];
      }
      while (i--);
    }
  }

  //*****************************************************************************
  void SmartThings::shieldFindNetwork(void)
  {
    print("custom find");
    print('\n');

    if(_isDebugEnabled)
    {
      Serial.print("  |<~ ");
      Serial.print("custom find");
      Serial.print('\n');
    }
  }

  //*****************************************************************************
  void SmartThings::shieldLeaveNetwork(void)
  {
    print("custom leave");
    print('\n');

    if(_isDebugEnabled)
    {
      Serial.print("  |<~ ");
      Serial.print("custom leave");
      Serial.print('\n');
    }
  }
