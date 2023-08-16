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


int analogPins[] = {A0, A1, A2};
int servoPositions[] = {0, 90, 180};

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {

  int servoId = 0;
  static int currentPos = 90;
  static int goToPos = 90; 
  int unused;  

  int firstMax = findMaxExept(-1, &servoId);
  int secondMax = findMaxExept(servoId, &unused);

  if (firstMax - 6 > secondMax)
  {
    goToPos = servoPositions[servoId];
  }

  if (goToPos != currentPos)
    currentPos = (int)naive_lerp(currentPos, goToPos, 0.2);

  myservo.write(currentPos);
  delay(20);
}

int findMaxExept(int exept, int* servoId)
{
  int maxAnalogValue = 0;
  
  for (int i = 0; i < 3; i++)
  {
    int analogValue = analogRead(analogPins[i]);
    Serial.print(analogValue);
    Serial.print(" ");
    if (analogValue > maxAnalogValue && exept != i)
    {
      maxAnalogValue = analogValue;
      *servoId = i;
    }
  }
  Serial.println();
  return maxAnalogValue;
}

float naive_lerp(float a, float b, float t)
{
    return a + t * (b - a);
}


