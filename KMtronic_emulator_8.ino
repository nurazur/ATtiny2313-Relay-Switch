/* KMtronic 1-Channel USB Relais Emulation Firmware               */
/* target Platform: ATtiny2313 with 3.6468 MHz external Oszillator */


// **********************************************************************************
// Copyright nurazur@gmail.com
// **********************************************************************************
// License
// **********************************************************************************
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Licence can be viewed at
// http://www.fsf.org/licenses/gpl.txt

// Please maintain this license information along with authorship
// and copyright notices in any redistribution of this code
// *********************************************************************************


/*
#define HEADER 'U'
#define CHANNEL1 '1'
#define CHANNEL2 '2'
#define CHANNEL3 '3'
#define CHANNEL4 '4'
#define CHANNEL_ALL 'A'
#define OFF '0'
#define ON '1'
#define STATUS_REQUEST '3'
*/


#define HEADER (char)0xff
#define CHANNEL1 (char)0x01
#define CHANNEL2 (char)0x02
#define CHANNEL3 (char)0x03
#define CHANNEL4 (char)0x04
#define CHANNEL5 (char)0x05
#define CHANNEL6 (char)0x06
#define CHANNEL7 (char)0x07
#define CHANNEL8 (char)0x08
#define CHANNEL_ALL (char)0x0f
#define OFF (char)0x00
#define ON (char)0x01
#define STATUS_REQUEST (char)0x03



#define REL_OUT1 13
#define REL_OUT2 12
#define REL_OUT3 11
#define REL_OUT4 10
#define REL_OUT5 9
#define REL_OUT6 8
#define REL_OUT7 7
#define REL_OUT8 6

char status=OFF;
char channel=1;
char i=0;
char ports[] = {REL_OUT1, REL_OUT2, REL_OUT3, REL_OUT4, REL_OUT5, REL_OUT6, REL_OUT7, REL_OUT8};

void setup() 
{
  pinMode(REL_OUT1, OUTPUT);
  pinMode(REL_OUT2, OUTPUT);
  pinMode(REL_OUT3, OUTPUT);
  pinMode(REL_OUT4, OUTPUT);
  pinMode(REL_OUT5, OUTPUT);
  pinMode(REL_OUT6, OUTPUT);
  pinMode(REL_OUT7, OUTPUT);
  pinMode(REL_OUT8, OUTPUT);
  
  Serial.begin(9600);  
  delay(50);
}



void send_status(char rel)
{
    Serial.print(HEADER);Serial.print(rel); Serial.print(status);
}


void loop() 
{
    while (Serial.available() > 0)
    {
        char bt = Serial.read();
        //Serial.print(bt);
        
        switch (i)
        {
            case 0:
                if (bt==HEADER) i++;
                break;
            case 1:
                switch (bt)
                {
                    case 0: // stands for request status
                    case CHANNEL1:
                    case CHANNEL2:
                    case CHANNEL3:
                    case CHANNEL4:
                    case CHANNEL_ALL:
                        channel =bt;
                        i++;  // fall through
                    default:
                        break;
                }
                break;
            case 2:
                if (channel == CHANNEL_ALL)
                {
                    // bt is a bit field with on/off bits set
                    for (uint8_t j=0; j<4; j++)
                    {
                        digitalWrite(ports[j], (bt >> j) & 0x1);
                    }
                    status = bt;
                }
                else if (bt==ON)
                {
                    unsigned char this_channel = channel-CHANNEL1;
                    digitalWrite(ports[this_channel], HIGH);
                    status |= 1<<this_channel;
                }
                else if (bt ==OFF)
                {
                    unsigned char this_channel = channel-CHANNEL1;
                    digitalWrite(ports[this_channel], LOW);
                    status &= ~(1<<this_channel);
                }
                else if (bt ==STATUS_REQUEST)
                {
                    send_status(channel);
                }
                
                i=0;
            default:
                break;
        }
    }
}
