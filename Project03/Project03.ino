
//             _____            .___    .__                           
//            /  _  \_______  __| _/_ __|__| ____   ____              
//           /  /_\  \_  __ \/ __ |  |  \  |/    \ /  _ \             
//          /    |    \  | \/ /_/ |  |  /  |   |  (  <_> )            
//          \____|__  /__|  \____ |____/|__|___|  /\____/             
//                  \/           \/             \/                    
// __________               __         _________            .___      
// \______   \ ____   _____/  |______  \_   ___ \  ____   __| _/____  
//  |     ___// __ \ /    \   __\__  \ /    \  \/ /  _ \ / __ |/ __ \ 
//  |    |   \  ___/|   |  \  |  / __ \\     \___(  <_> ) /_/ \  ___/ 
//  |____|    \___  >___|  /__| (____  /\______  /\____/\____ |\___  >
// 

#include <ESP8266WiFi.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <FastLED.h>
#define LED_PIN D1
#define NUM_LEDS 64

CRGB leds[NUM_LEDS];
String mode = "manual";
bool ledMatrix[NUM_LEDS];

const char* ssid = "PentaCode";
const char* pass = "Root1234";

WiFiServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("!Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New client :D");
    currentTime = millis();
    previousTime = currentTime;

    connection(client);
  }

  if (mode == "manual")
    manual();
  else
    pattern();
  delay(20);
}

void connection(WiFiClient client)
{
  String buffer = "";

  while(client.connected())
  {
    currentTime = millis();
    if (client.available())
    {
      char c = client.read();
      Serial.write(c);
      header += c;
      if (c == '\n')
      {
        if (buffer.length() == 0)
        {
          createHTML(client);
           break;
        }
        else
          buffer = "";
      }
      else if(c != '\r')
        buffer += c;
    } 
  }
    header = "";
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
}

void createHTML(WiFiClient client)
{
  switchMode();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println("");
  client.println("<!DOCTYPE html> <html>");
  client.println("<head> <meta name=\"viewport\" content=\"device-width, initial-scale=1\">");

  readCSS(client);

  client.println("</head>");
  client.println("<body><h1> PentaCode </h1>");
  client.println("LED mode: " + mode + "<br>");
  
  createButtons(client);
  client.println("<br><br><a href=\"/r\"><button>Reset</button>");
  client.println("<br><br><a href=\"/x\"><button>PentaCode</button>");

  client.println("</body></html>");
  client.println();
}

void readCSS(WiFiClient client)
{
  client.println("<style>");
  client.println("body{background-color: aquamarine;});");
  client.println("</style>");
}

void switchMode()
{
  if (header.indexOf("GET /p") >= 0)
  {
    readLEDs();
    mode = "manual";
  }
  if (header.indexOf("GET /x") >= 0 || header.indexOf("GET /r") >= 0)
  {
    for(int j = 0; j < NUM_LEDS; j++)
    {
      ledMatrix[j] = false;
      leds[j] = CHSV(95, 255, 0);
    }
    if(header.indexOf("GET /x") >= 0)
      mode = "pattern";
  }
}

void readLEDs()
{
  int pos = header.indexOf("GET /p") + 6;
  int pin = header.substring(pos, pos + 2).toInt();
  ledMatrix[pin] = !ledMatrix[pin];
}

void createButtons(WiFiClient client)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (ledMatrix[i])
    {
       client.println("<a href=\"/p" + String(i) + "\"><button style=\"background-color:red;\">1</button>");
    }
    else
    {
       client.println("<a href=\"/p" + String(i) + "\"><button>0</button>");
    }
    if((i + 1) % 8 == 0)
      client.println("<br>");
  } 
}

void manual()
{
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);


    for(int j = 0; j < NUM_LEDS; j++)
    {
      if (ledMatrix[j])
        leds[j] = CHSV((sensorValue * 8) % 255, 255, 255);
      else
        leds[j] = CHSV(0, 255, 0);
    }
    FastLED.show();
    delay(10);
}


void pattern()
{
    static int offset = 95, x = 15;

    if (offset > 255)
      x = -15;
    if (offset < 0)
      x = 15;
      
    offset += x;
    int patt[46] = { 3, 4, 10, 11, 12, 13, 17, 18, 19, 20, 21, 22,
                24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                49, 50, 51, 52, 53, 54, 58, 59, 60, 61 };

    for(size_t i = 0; i < 46; i++)
    {
      leds[patt[i]] = CHSV(offset, 255, 255);
      delay(10);
      FastLED.show();
    }
}
