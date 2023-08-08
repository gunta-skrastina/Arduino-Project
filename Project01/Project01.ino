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

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = A0;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("PentaCode");
}

void loop()
{

  int potsValue = analogRead(potPin);
  double voltage = (potsValue / 1023.0) * 5.0;
  int brightness = map(potsValue, 0, 1023, 0, 255);

  lcd.setCursor(0, 1);
  lcd.setCursor(0, 1);
  lcd.print(voltage);

  analogWrite(9, brightness);
}
