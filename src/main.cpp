/*

Demonstrates simple RX and TX operation.
Any of the Basic_TX examples can be used as a transmitter.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9                      PURPLE
CSN   -> 10 (Hardware SPI SS)   BLUE
MOSI  -> 11 (Hardware SPI MOSI) YELLOW
MISO  -> 12 (Hardware SPI MISO) GREEN
SCK   -> 13 (Hardware SPI SCK)  ORANGE
IRQ   -> No connection
VCC   -> No more than 3.6 volts RED
GND   -> GND                    BLACK

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0; // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
/*
struct RadioPacket // Any packet up to 32 bytes can be sent.
{
    uint8_t FromRadioId;
    uint8_t anotherByte=1;
    uint8_t anotherByte2=2;
    uint8_t anotherByte3=3;
    uint8_t anotherByte4=4;
    uint8_t anotherByte5=5;   
    uint8_t anotherByte6=6;
    uint8_t anotherByte7=7;
    uint8_t anotherByte8=8;

    uint8_t anotherByte9=9;
    uint8_t anotherByte10=10;
    uint8_t anotherByte11=11;
    uint8_t anotherByte12=12;
    uint8_t anotherByte13=13;
    uint8_t anotherByte14=14;
    uint8_t anotherByte15=15;    
    uint8_t anotherByte16=16;  
};
*/

struct RadioPacket2 // Any packet up to 32 bytes can be sent.
{
  uint8_t aByte;
  uint8_t aByte2;
  uint8_t aByte3;
  uint8_t aByte4;
  uint8_t aByte5;
  uint32_t aLong;
};


NRFLite _radio;
RadioPacket2 _radioData;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  // By default, 'init' configures the radio to use a 2MBPS bitrate on channel 100 (channels 0-125 are valid).
  // Both the RX and TX radios must have the same bitrate and channel to communicate with each other.
  // You can run the 'ChannelScanner' example to help select the best channel for your environment.
  // You can assign a different bitrate and channel as shown below.
  //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100) // THE DEFAULT
  //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE1MBPS, 75)
  //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 0)

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100))
  {
    Serial.println("Cannot communicate with radio");
    while (1)
      ; // Wait here forever.
  }
  else
  {
    Serial.println("Works great!");
  }
}
uint8_t anArray[32];
void loop()
{
  while (_radio.hasData())
  {
    _radio.readData(anArray); // Note how '&' must be placed in front of the variable name.

    String msg = "Radio ";

    msg += anArray[0];        
    msg += ", ";
    
   for(int i =0; i< 32; i++)
   {
    msg += anArray[i];        
    msg += ", ";
   }

    /*
        msg += _radioData.FromRadioId;
        msg += ", ";
        msg += _radioData.anotherByte;        
        msg += ", ";
        msg += _radioData.anotherByte2;        
        msg += ", ";
        msg += _radioData.anotherByte3;        
        msg += ", ";
        msg += _radioData.anotherByte4;        
        msg += ", ";
        msg += _radioData.anotherByte5;        
        msg += ", ";
        msg += _radioData.anotherByte6;        
        msg += ", ";
        msg += _radioData.anotherByte7;        
        msg += ", ";
        msg += _radioData.anotherByte8;        
        msg += ", ";


        msg += _radioData.anotherByte9;        
        msg += ", ";
        msg += _radioData.anotherByte10;        
        msg += ", ";
        msg += _radioData.anotherByte11;        
        msg += ", ";
        msg += _radioData.anotherByte12;        
        msg += ", ";
        msg += _radioData.anotherByte13;        
        msg += ", ";
        msg += _radioData.anotherByte14;        
        msg += ", ";
        msg += _radioData.anotherByte15;        
        msg += ", ";
        msg += _radioData.anotherByte16;        
        msg += ", ";
*/

    Serial.println(msg);
  }
}