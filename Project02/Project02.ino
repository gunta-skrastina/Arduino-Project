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

#include <Servo.h>

Servo myservo; 
int currentPos;

int analogPins[] = {A0, A1, A2};
int servoPositions[] = {0, 90, 180};

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {

  int maxAnalogValue = 0;
  for (int i = 0; i < 3; i++)
  {
    int analogValue = analogRead(analogPins[i]);
    if (analogValue > maxAnalogValue)
    {
      maxAnalogValue = analogValue;
      currentPos = servoPositions[i];
    }
    Serial.print("Analog reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(analogValue);
  }
  myservo.write(currentPos);
  delay(500);
}
