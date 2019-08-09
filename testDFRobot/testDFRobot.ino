#include <SoftwareSerial.h>

// Configure software serial port
SoftwareSerial SIM900(7, 8); 
String incoming_char="";

void setup() {
      Serial.begin(115200);

  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(20000);   
  
  // Send the SMS
  sendSMS();
}


void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  readOutput(100);
  
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+940779713087\""); 
  delay(100);
  readOutput(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Message example from Arduino Uno."); 
  delay(100);
  readOutput(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  readOutput(100);
  
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
  readOutput(100);
}


void loop() {
  // Display any text that the GSM shield sends out on the serial monitor

}

void readOutput(unsigned int timeout){

    unsigned long timerStart, prevChar;
    timerStart = millis();
    
    while(1){

      while(SIM900.available() >0) {
        //Get the character from the cellular serial port
        incoming_char=SIM900.readString(); 
        //Print the incoming character to the terminal
        Serial.println(incoming_char); 
        break;
        }
      if(timeout){
          if((unsigned long) (millis() - timerStart) > timeout*1000){
              break;
          }
      }
      
      }

  
}
