/*

Demonstrates simple RX and TX operation.
Any of the Basic_RX examples can be used as a receiver.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 199;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
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
NRFLite _radio;
//RadioPacket _radioData;

uint8_t anArray[32];
void setup()
{
    Serial.begin(115200);
    
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
        while (1); // Wait here forever.
    }
    

   for(int i =0; i< 32; i++)
   {
    anArray[i]=i;
   }
   for(int i =0; i< 32; i++)
   {
    anArray[i]=anArray[i]+1;
   }

}

void loop()
{
    //_radioData.OnTimeMillis = millis();

    Serial.print("Sending ");
    //Serial.print(_radioData.OnTimeMillis);
    Serial.print(" ms");

    // By default, 'send' transmits data and waits for an acknowledgement.  If no acknowledgement is received,
    // it will try again up to 16 times.  This retry logic is built into the radio hardware itself, so it is very fast.
    // You can also perform a NO_ACK send that does not request an acknowledgement.  In this situation, the data packet
    // will only be transmitted a single time and there is no verification of delivery.  So NO_ACK sends are suited for
    // situations where performance is more important than reliability.
    //   _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::REQUIRE_ACK) // THE DEFAULT
    //   _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::NO_ACK)
    
    if (_radio.send(DESTINATION_RADIO_ID, anArray, sizeof(anArray))) // Note how '&' must be placed in front of the variable name.
    {
        Serial.println("...Success");
        
   for(int i =0; i< 32; i++)
   {
    anArray[i]=anArray[i]+1;
   }

        /*
        _radioData.FromRadioId++;
        _radioData.anotherByte++;
        _radioData.anotherByte2++;
        _radioData.anotherByte3++;
        _radioData.anotherByte4++;
        _radioData.anotherByte5++;
        _radioData.anotherByte6++;
        _radioData.anotherByte7++;
        _radioData.anotherByte8++;

        _radioData.anotherByte9++;
        _radioData.anotherByte10++;
        _radioData.anotherByte11++;
        _radioData.anotherByte12++;
        _radioData.anotherByte13++;
        _radioData.anotherByte14++;
        _radioData.anotherByte15++;
        _radioData.anotherByte16++;
*/

        
    }
    else
    {
        Serial.println("...Failed");
        //_radioData.FailedTxCount++;
    }

    delay(1000);
}
