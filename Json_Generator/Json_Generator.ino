#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
int num,sum;
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) continue;

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
}

void loop() {
  StaticJsonDocument<200> doc_1;
  StaticJsonDocument<200> doc_2;

  JsonArray data_1 = doc_1.createNestedArray("Soil");
  JsonArray data_2 = doc_1.createNestedArray("Humidity");
  JsonArray data_3 = doc_1.createNestedArray("Temperature");
  JsonArray data_4 = doc_1.createNestedArray("Light");
  data_1.add(analogRead(A0));
  data_2.add(analogRead(A1));
  data_3.add(analogRead(A2));
  data_4.add(analogRead(A3));

  serializeJson(doc_1, Serial); 
  Serial.println();
  sum = 0;
  num = Serial.read();
  //temp ==> 116 /soil ==> 115 / humidity ==> 104 / light ==> 108
  if(num > -1)
  {
    if (num == 116)
      mySerial.print("Temperature = ");
    else if(num == 115)
      mySerial.print("Soil = ");
    else if(num == 104)
      mySerial.print("Humidity = ");
    else if(num == 108)
      mySerial.print("Light = ");
    num = Serial.read();
  }
  while(num > -1)
  {
    sum = sum*10 + (num - 48);
    num = Serial.read();
  }
  //
  if(sum)
    mySerial.println(sum);
  // }
}
