/*
  Repeating Web client

  This sketch connects to a a web server and makes a request
  using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
  the Adafruit Ethernet shield, either one will work, as long as it's got
  a Wiznet Ethernet module on board.

  This example uses DNS, by assigning the Ethernet client with a MAC address,
  IP address, and DNS address.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 19 Apr 2012
  by Tom Igoe
  modified 21 Jan 2014
  by Federico Vanzati

  http://www.arduino.cc/en/Tutorial/WebClientRepeating
  This code is in the public domain.

*/

#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>                      // 서보모터 라이브러리

Servo servo;                            // 서보모터 사용을 위한 객체 생성

int motor = 2;                          // 서보모터의 핀
int angle = 90;

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(172, 20, 10, 1);
IPAddress myDns(192, 168, 0, 1);

// initialize the library instance:
EthernetClient client;

char server[] = "msm4585.dothome.co.kr";  // also change the Host line in httpRequest()
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 3 * 1000; // delay between updates, in milliseconds

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  servo.attach(motor);
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  String data = "";
  bool getted = false;
  while (client.available()) {
    char c = client.read();
    data += String(c);
    Serial.write(c);
    getted = true;
  }
  if (getted) {
    int isZero = data.indexOf("\"flag\":\"0\"");
    int flag;
    flag = (data.indexOf("\"flag\":\"0\"") == -1);


    if (flag)      //flag 의 값으 1일때 .            
    {
      open_door();
    }
    else           
    {
      close_door();
    }




  }


  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /lockStatus.php HTTP/1.1");
    client.println("Host: msm4585.dothome.co.kr");
    //client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}



void open_door(){

 Serial.println("angle" + String(angle));
   servo.write(50);
}

void close_door(){


  Serial.println("angle" + String(angle));
   servo.write(180);
  
}
