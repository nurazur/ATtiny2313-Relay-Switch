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
#define HEADER 'A'
#define CHANNEL '1'
#define OFF '0'
#define ON '1'
#define STATUS_REQUEST '3'
*/

//
#define HEADER (char)0xff
#define CHANNEL (char)0x01
#define OFF (char)0x00
#define ON (char)0x01
#define STATUS_REQUEST (char)0x03
//


#define REL_OUT 13

void setup() 
{
  pinMode(REL_OUT, OUTPUT);
  Serial.begin(9600);  
  delay(50);
}

char status=OFF;
char i=0;




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
                if (bt==CHANNEL) i++;
                break;
            case 2:
                if (bt==ON)
                {
                    digitalWrite(REL_OUT, HIGH);
                    status = bt;
                }
                else if (bt ==OFF)
                {
                    digitalWrite(REL_OUT, LOW);
                    status = bt;
                }
                else if (bt ==STATUS_REQUEST)
                {
                    send_status(CHANNEL);
                }
                i=0;
            default:
                break;
        }
    }
}
