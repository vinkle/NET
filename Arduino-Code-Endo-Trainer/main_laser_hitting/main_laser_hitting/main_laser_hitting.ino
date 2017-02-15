#include <Keypad_MC17.h>
#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>


/***********
* write cheat sheat here
* if receive D on the serial port print the debugging information
*/
#define I2CADDR 0x20
#define LCD_E 2            // pin 2 of arduino
#define LCD_RS 3           // pin 3 of arduino
#define LCD_D4 4           // pin 4 of arduino
#define LCD_D5 5           // pin 5 of arduino
#define LCD_D6 6           // pin 6 of arduino
#define LCD_D7 7           // pin 7 of arduino
#define SERVO_SIG 8        // pin 8 of arduino

#define LASER_C0_i2c 8     // pin 8(B0) of MCP20017  using library Keypad_MC17
#define LASER_C1_i2c 9     // pin 9(B1) of MCP20017  using library Keypad_MC17
#define LASER_C2_i2c 10    // pin 10(B2) of MCP20017 using library Keypad_MC17
#define LASER_C3_i2c 11    // pin 11(B3) of MCP20017 using library Keypad_MC17

#define Keypad_row0 0       //pin 0(A0) of MCP20017  using library Keypad_MC17
#define Keypad_row1 1       //pin 1(A1) of MCP20017  using library Keypad_MC17
#define Keypad_row2 2       //pin 2(A2) of MCP20017  using library Keypad_MC17
#define Keypad_row3 3       //pin 3(A3) of MCP20017  using library Keypad_MC17
#define Keypad_col0 4       //pin 4(A4) of MCP20017  using library Keypad_MC17
#define Keypad_col1 5       //pin 5(A5) of MCP20017  using library Keypad_MC17
#define Keypad_col2 6       //pin 6(A6) of MCP20017  using library Keypad_MC17
#define Keypad_col3 7       //pin 7(A7) of MCP20017  using library Keypad_MC17
#define FORCE_THRESHOLD 300

LiquidCrystal lcd(LCD_E, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const int channel_laser[4] = { LASER_C0_i2c, LASER_C1_i2c, LASER_C2_i2c, LASER_C3_i2c };
int muxChannel[16][4] =
{
  { 0, 0, 0, 0 }, //channel 0
  { 1, 0, 0, 0 }, //channel 1
  { 0, 1, 0, 0 }, //channel 2
  { 1, 1, 0, 0 }, //channel 3
  { 0, 0, 1, 0 }, //channel 4 
  { 1, 0, 1, 0 }, //channel 5
  { 0, 1, 1, 0 }, //channel 6
  { 1, 1, 1, 0 }, //channel 7
  { 0, 0, 0, 1 }, //channel 8
  { 1, 0, 0, 1 }, //channel 9
  { 0, 1, 0, 1 }, //channel 10
  { 1, 1, 0, 1 }, //channel 11
  { 0, 0, 1, 1 }, //channel 12
  { 1, 0, 1, 1 }, //channel 13
  { 0, 1, 1, 1 }, //channel 14
  { 1, 1, 1, 1 }  //channel 15
};

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys_keypad[ROWS][COLS] = {
  { 'S', '3', '2', '1' },
  { 'R', '6', '5', '4' },
  { '>', '9', '8', '7' },
  { '<', 'A', '0', '-' }
};
byte rowPins[ROWS] = { Keypad_row0, Keypad_row1, Keypad_row2, Keypad_row3 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { Keypad_col0, Keypad_col1, Keypad_col2, Keypad_col3 }; //connect to the column pinouts of the keypad

// create the keypad object
Keypad_MC17 keypad(makeKeymap(keys_keypad), rowPins, colPins, ROWS, COLS, I2CADDR);

// ******************* Servo ***************************************************************
Servo myservo;  // create servo object to control a servo a maximum of eight servo objects can be created
const int servoMotorPin = SERVO_SIG;
int servo_pos = 84;    // variable to store the servo position
// **********************************************************************************

// keypad
boolean  keyGet = false;
char key1 = '_';
char key2 = '_';
char key3 = '_';
char key4 = '_';
char keys[3] = { '*', '*', '*' };
int numofKeyPressed = 0;
bool start = false;


// Force Sensor
const int forceSensor = A0;

int forceSensorRead = 0;  

String angle = "Angle-> ";
String deg   = " deg";

// serialComm variables
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean enterCalib = false;
boolean firstSerialData = false;
boolean secondSerialData = false;
boolean enterStart = false;

void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
    else
    {
      inputString += inChar;
    }
  }
}

void setup()
{
  randomSeed(0);
  Serial.begin(9600);
  keypad.begin();
  keypad.setDebounceTime(50);
  lcd.begin(16, 2);

  keypad.pin_mode(LASER_C0_i2c, OUTPUT);
  keypad.pin_mode(LASER_C1_i2c, OUTPUT);
  keypad.pin_mode(LASER_C2_i2c, OUTPUT);
  keypad.pin_mode(LASER_C3_i2c, OUTPUT);
  keypad.pin_write(LASER_C0_i2c, LOW);
  keypad.pin_write(LASER_C1_i2c, LOW);
  keypad.pin_write(LASER_C2_i2c, LOW);
  keypad.pin_write(LASER_C3_i2c, LOW);


  myservo.attach(servoMotorPin);
  myservo.write(servo_pos);

  // Print a message to the LCD.
  lcd.print("NeuroEndoTrainer");
  lcd.setCursor(0, 1);
  lcd.print(" NETS-AIIMS-IITD");

  delay(1000);
  inputString.reserve(200);
  randomSeed(analogRead(4));
}


void loop()
{
  // keypad operation
  char key = keypad.getKey();
  keypadOperations(key);
  
  if (stringComplete || enterStart) 
  {
    //Serial.print("Serial-Data = ");
    //Serial.println(inputString);
    if(inputString[0] == 'z')
    {
      enterStart = false;
      press_reset();
    }
    else if(inputString[0] == 's' || enterStart)
    {
      if(inputString[0] == 's')
      {
        enterStart = true;
        lcd.clear();
        lcd.print(" Follow Red Dot");
      }
      press_start();
    }
    inputString = "";
    stringComplete = false;
  }
}

void press_start()
{
    int forceVal = analogRead(forceSensor);
    if(forceVal > FORCE_THRESHOLD)
    {
      String forceString = String(forceVal, DEC); 
      Serial.print("Ht,");
      Serial.println(forceString); 
    }
    if(inputString[0] == 'a')
    {
       muxWrite(0);
    }
    else if(inputString[0] == 'b')
    {
       muxWrite(1);
    }
    else if(inputString[0] == 'c')
    {
       muxWrite(2);
    }
    else if(inputString[0] == 'd')
    {
       muxWrite(3);
    }
    else if(inputString[0] == 'e')
    {
       muxWrite(4);
    }
    else if(inputString[0] == 'f')
    {
       muxWrite(5);
    }
    else if(inputString[0] == 'g')
    {
       muxWrite(6);
    }
    else if(inputString[0] == 'h')
    {
       muxWrite(7);
    }
    else if(inputString[0] == 'i')
    {
       muxWrite(8);
    }
    else if(inputString[0] == 'j')
    {
       muxWrite(9);
    }
    else if(inputString[0] == 'k')
    {
       muxWrite(10);
    }
    else if(inputString[0] == 'l')
    {
       muxWrite(11);
    }
    else if(inputString[0] == '1')
    {
      servo_pos = servo_pos + 2;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '2')
    {
      servo_pos = servo_pos - 2;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '3')
    {
      servo_pos = 84;
      servo_pos = servo_pos + 15;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '4')
    {
      servo_pos = 84;
      servo_pos = servo_pos - 15;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '5')
    {
      servo_pos = 84;
      servo_pos = servo_pos + 20;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '6')
    {
      servo_pos = 84;
      servo_pos = servo_pos - 20;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '7')
    {
      servo_pos = 84;
      servo_pos = servo_pos + 30;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '8')
    {
      servo_pos = 84;
      servo_pos = servo_pos - 30;
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '0')
    {
      servo_pos = 84;
      servo_pos = servo_pos + random(0, 20);
      myservo.write(servo_pos);
    }
    else if(inputString[0] == '9')
    {
      servo_pos = 84;
      servo_pos = servo_pos - random(0, 20);
      myservo.write(servo_pos);
    }
}


void muxWrite(int p)
{
    for (int i = 0; i < 4; i++)
    {
      keypad.pin_write(channel_laser[i], muxChannel[p][i]);
    }
}

void press_reset()
{
  lcd.clear();
  lcd.print("NeuroEndoTrainer");
  lcd.setCursor(0, 1);
  lcd.print(" NETS-AIIMS-IITD");
  servo_pos = 84;
  start = false;
  myservo.write(servo_pos);
  keyGet = false;
  keys[0] = '*'; keys[1] = '*'; keys[2] = '*';
  numofKeyPressed = 0;
}

void error_keypress()
{
  lcd.clear();
  lcd.print("**Wrong--Angle**");
  lcd.setCursor(0, 1);
  lcd.print("**Press--Reset**");
  servo_pos = 84;
  start = false;
  myservo.write(servo_pos);
  keyGet = false;
  keys[0] = '*'; keys[1] = '*'; keys[2] = '*';
  numofKeyPressed = 0;
}

void press_forward()
{
  // code for the next level

}

void press_backward()
{
  // code for the previous level
}


void keypadOperations(char key)
{
  if (key)
  {
    if (key == 'A')
    {
      press_reset();
    }
    else if (key == '>')
    {
      press_forward();
    }
    else if (key == '<')
    {
      press_backward();
    }
    else if (key == 'R')
    {
      press_start();
    }
    else if (key == 'S')
    {
      press_reset();
      lcd.clear();
      lcd.print("SET bw -70 to 70");
      keyGet = true;
    }
    else if (key == '-')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = key;
          numofKeyPressed++;
        }
        else
        {
          keys[0] = '0';
        }
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
      }
    }

    else if (key == '0')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '1')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '2')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '3')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '4')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '5')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '6')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '7')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '8')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
    else if (key == '9')
    {
      if (keyGet && numofKeyPressed < 3)
      {
        if (numofKeyPressed == 0)
        {
          keys[0] = '0';
          numofKeyPressed = numofKeyPressed + 1;
        }
        keys[numofKeyPressed++] = key;
        lcd.setCursor(0, 1);
        lcd.print(angle);
        lcd.print(keys);
        lcd.print(deg);
        if (numofKeyPressed == 3)
        {
          int angle_new = atoi(keys);
          if (angle_new <= 70 && angle_new >= -70)
          {
            servo_pos = angle_new + 90;
            myservo.write(servo_pos);
          }
          else
          {
            error_keypress();
          }
        }
      }
    }
  }
}










