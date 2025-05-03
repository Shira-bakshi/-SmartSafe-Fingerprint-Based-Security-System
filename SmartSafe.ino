/*************** Avi Hayun 27/10/18 ***************/
#include <Servo.h>
#include <SPI.h>
#include "TFT9341Touch.h"
 tft9341touch LcdTouch(10, 9, 7, 2); //cs, dc ,tcs, tirq
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
 enum statuses { success, failed_id, failed_sum, failed_size };

int getFingerprintIDez();
// pin #2 is IN from sensor 
// pin #3 is OUT from arduino  
SoftwareSerial mySerial(A1,A0);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position
uint8_t id;// מזהה טביעת אצבע
uint8_t result;// תוצאה של פעולות טביעת אצבע
int ButtonNum;
uint8_t getFingerprintEnroll();
int cursor2=0;
int string1[8];
int pass[8] = {1,2,3,4};
int indexString=0;
void setup() {
  LcdTouch.begin();
  LcdTouch.clearButton();
  LcdTouch.setRotation(0);//0,1,2,3
  LcdTouch.setTextSize (2);
  LcdTouch.setCursor (40, 40);
  LcdTouch.set(3780, 372, 489, 3811); //Calibration
  
  screenMain();
}

void loop() 
{
  uint16_t x, y;
  String str;
    ButtonNum = 0;

  if (LcdTouch.touched())
  {
    LcdTouch.readTouch();
    x = LcdTouch.xTouch;
    y = LcdTouch.yTouch;
    ButtonNum = LcdTouch.ButtonTouch(x, y);
    // str="x=" + String(x) + " y=" + String(y) + " Bu=" + String(ButtonNum);
    // LcdTouch.print (25, 220, str, 2, BLACK, CYAN);
    // LcdTouch.fillCircle(x, y, 3, WHITE);
    if (ButtonNum == 1)
    {       
      choosKay();
           //  screenMain();
    }
     else if (ButtonNum == 2) 
    {
      Fingerprint();
      // screen1();
    } 
    else if (ButtonNum == 3 ) 
    {
      numberBoard();
      // screen1();
    }
    else if (ButtonNum>4) 
    {
      chackEnd(ButtonNum);

    }
  }
}

// x:\הנדסאים שנה ב תשפד\מערכות משובצות\חומרים לפרויקט\תכניות לרכיבים\טביעת אצבע\Adafruit-Fingerprint-Sensor-Library-master\Adafruit_Fingerprint.cpp
void screenMain() 
{
  LcdTouch.fillScreen (BLACK);
  LcdTouch.print (30 ,20, "Welcome to the", 2, WHITE);
  LcdTouch.print (10,45,"smart safe system", 2, WHITE);
  LcdTouch.drawButton(1 , 120,  100, 90, 50, 10, BLUE, WHITE, "start", 2); // NumButton, x, y, width, height, r, Color, textcolor, label, textsize);
  // digitalWrite(5, 255);
  // digitalWrite(8,255);
}
void choosKay() 
{
  LcdTouch.fillScreen (BLACK);
  LcdTouch.print(10, 20, "Choose a login option:", 2, WHITE);

  LcdTouch.drawButton(2, 20,  50, 190, 50, 10, BLUE, WHITE, "Finger print", 2); // NumButton, x, y, width, height, r, Color, textcolor, label, textsize);

  LcdTouch.drawButton(3 , 20,  120, 90, 50, 10, BLUE, WHITE, "code", 2);
    while (!LcdTouch.touched());

}


void Fingerprint() {
  LcdTouch.fillScreen (WHITE);
  LcdTouch.setTextColor(BLACK);
  
  LcdTouch.setTextSize (3);
  LcdTouch.setCursor (25, 30);
  LcdTouch.print (60 ,20, "Place your finger", 2, BLACK);
   LcdTouch.print (80,45,"on the sensor", 2, BLACK);
  LcdTouch.setTextSize (1);
  LcdTouch.begin();
 Serial.begin(9600);
 finger.begin(57600);
 LcdTouch.clearButton();
 LcdTouch.setRotation(0);//0,1,2,3
 LcdTouch.setTextSize(2);
 LcdTouch.setCursor(40, 40);
 LcdTouch.set(3780, 372, 489, 3811); //Calibration
 while (!Serial);
 delay(500);
 Serial.begin(9600);
 Serial.println("Adafruit Fingerprint sensor enrollment");
 // set the data rate for the sensor serial port
 finger.begin(57600);
 if (finger.verifyPassword())
 {
 Serial.println("Found fingerprint sensor!");
 }
 else
 {
 Serial.println("Did not find fingerprint sensor :(");
 while (1) ;
 }
//  load();
 //check();
 getFingerprintEnroll();
 screenMain();
 }

void numberBoard() 
{

  LcdTouch.fillScreen (BLACK);
  LcdTouch.clearButton();
  LcdTouch.drawButton(5, 30,  30, 40, 40, 2, RED, WHITE, "1", 4); // NumButton, x, y, width, height, r, Color, textcolor, label, textsize); 
  LcdTouch.drawButton(6, 75,  30, 40, 40, 2, RED, WHITE, "2", 4);
  LcdTouch.drawButton(7, 120,  30, 40, 40, 2, RED, WHITE, "3", 4);
  LcdTouch.drawButton(8, 30,  75, 40, 40, 2, RED, WHITE, "4", 4);
  LcdTouch.drawButton(9, 75,  75, 40, 40, 2, RED, WHITE, "5", 4);
  LcdTouch.drawButton(10, 120,  75, 40, 40, 2, RED, WHITE, "6", 4);
  LcdTouch.drawButton(11, 30,  120, 40, 40, 2, RED, WHITE, "7", 4);
  LcdTouch.drawButton(12, 75,  120, 40, 40, 2, RED, WHITE, "8", 4);
  LcdTouch.drawButton(13, 120,  120, 40, 40, 2, RED, WHITE, "9", 4); 
  LcdTouch.drawButton(14, 75,  165, 40, 40, 2, RED, WHITE, "0", 4);
  LcdTouch.drawButton(15, 30,  165, 40, 40, 2, RED, WHITE, "<-", 2); 
  LcdTouch.drawButton(16, 120,  165, 40, 40, 2, RED, WHITE, "ok", 2); 
  while(!LcdTouch.touched());     

}
 
void keyboard(int ButtonNum)
{
   switch(ButtonNum)
  { 
    case 5: LcdTouch.setCursor (cursor2+=15,210); 
            LcdTouch.println ("1");   
            string1[indexString++]=1;
            delay(500);
            break;
    case 6: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("2");
            string1[indexString++]=2;
            delay(500);
            break;
    case 7: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("3");
            string1[indexString++]=3;
            delay(500);
            break;
    case 8: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("4");
            string1[indexString++]=4;
            delay(500);
            break;
    case 9: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("5");
            string1[indexString++]=5;
            delay(500);
            break;
    case 10: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("6");
            string1[indexString++]=6;
            delay(500);
            break;
    case 11: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("7");
            string1[indexString++]=7;
            delay(500);
            break;
    case 12: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("8");
            string1[indexString++]=8;
            delay(500);
            // LcdTouch.setCursor (cursor2+=15,210);
            break;
    case 13: LcdTouch.setCursor (cursor2+=15,210);
            LcdTouch.println ("9");
            string1[indexString++]=9;
            delay(500);
            break;
    case 14: LcdTouch.setCursor (cursor2+=15,210); 
             LcdTouch.println ("0");
             string1[indexString++]=0;
             delay(500);
             break;
    case 15: LcdTouch.setCursor (cursor2,210);
             LcdTouch.println ("");
             cursor2-=15;
             LcdTouch.setCursor (cursor2,210);
             indexString--;
             delay(500);
             break; 
   // case 16: screen1(); 
            // break;
  }  
  while(!LcdTouch.touched());     
}

void chackEnd(int ButtonNum)
{
  int i=0,cursor1=10,x1,y1;
  while(ButtonNum!=16)
  {
    keyboard(ButtonNum);
    LcdTouch.readTouch();
    x1 = LcdTouch.xTouch;
    y1 = LcdTouch.yTouch;
    ButtonNum = LcdTouch.ButtonTouch(x1, y1);
  }
  if (ButtonNum==16){
      delay(1000);
  LcdTouch.setTextColor(WHITE,BLACK);
  LcdTouch.setCursor (cursor1,210);
  while(string1[i]!=NULL)
  {
     LcdTouch.print(String(string1[i++]));   
     cursor1+=15;
     LcdTouch.setCursor(cursor1,210);
  }
      IsSecsses(string1);
      // for (int i =0;i<=indexString;i++)
      // {
      //   string1[i]='\0';
      //   keyboard(15);

      // }
  // if(strcmp(pass,string1)==0)
  // {
  // }
  choosKay(); 
  }

}
int IsSecsses(int string1[])
 {
  int g=0;
    LcdTouch.fillScreen (BLACK);
    for (int i = 0;i<8;i++)
    {
      if(pass[i]!=string1[i])
        {
          g=1;
        break;
        }
    }
  if(g==0)
  {
    LcdTouch.println ("success");  
  }
  else{
    LcdTouch.println ("dont secess");
    delay(500);
    numberBoard();
    
  }
 for (int i =0;i<8;i++)
      LcdTouch.print(string1[i]);
  for (int i =0;i<indexString;i++)
      keyboard(15);      
  indexString=0;

    while(!LcdTouch.touched());  
          
 }
uint8_t getFingerprintEnroll() 
{
    int p = -1;
    Serial.print("Waiting for valid finger to enroll as #");
 
    // Loop until a valid fingerprint image is obtained
    while (p != FINGERPRINT_OK) {
        p = finger.getImage(); // Attempt to capture fingerprint image

        switch (p) {
            case FINGERPRINT_OK:
                Serial.println("Image taken");
                // Display instructions on an LCD (assuming LcdTouch object is defined)
                LcdTouch.print(5, 20, "Remove finger and then", 2.6, WHITE);
                LcdTouch.print(5, 40, "Place same finger again", 2.6, WHITE);
                break;
            case FINGERPRINT_NOFINGER:
                Serial.println(".");
                // Optionally display a dot or message on LCD
                break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println("Communication error");
                LcdTouch.print(50, 160, "Communication error", 3, GREEN);
                break;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println("Imaging error");
                LcdTouch.print(50, 160, "Imaging error", 3, GREEN);
                break;
            default:
                Serial.println("Unknown error");
                LcdTouch.print(50, 160, "Unknown error", 3, GREEN);
                break;
        }
    }

    // Once a fingerprint image is obtained, convert it
    p = finger.image2Tz(1);
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image converted");
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println("Image too messy");
            LcdTouch.print(25, 160, "Image too messy", 3, GREEN);
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            LcdTouch.print(1, 160, "Could not find fingerprint features", 3, GREEN);
            return p;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            return p;
        default:
            Serial.println("Unknown error");
            return p;
    }

    Serial.println("Remove finger");
    delay(2000);

    // Wait until the finger is removed
    p = 0;
    while (p != FINGERPRINT_NOFINGER) {
        p = finger.getImage();
    }

    // Serial.print("ID "); Serial.println(id);
    LcdTouch.print(15, 100, "Found ID", 2.5, BLUE);
    // LcdTouch.print(15, 120, String(id), 2.5, BLUE);
    LcdTouch.print(15, 140, String(finger.fingerID), 2.5, BLUE);

    Serial.println("Place same finger again");

    // Loop until a valid fingerprint image is obtained again
    while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        switch (p) {
            case FINGERPRINT_OK:
                Serial.println("Image taken");
                break;
            case FINGERPRINT_NOFINGER:
                Serial.print(".");
                break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println("Communication error");
                break;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println("Imaging error");
                break;
            default:
                Serial.println("Unknown error");
                break;
        }
    }

    // Convert the second fingerprint image
    p = finger.image2Tz(2);
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image converted");
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println("Image too messy");
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            return p;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            return p;
        default:
            Serial.println("Unknown error");
            return p;
    }

    // Create a fingerprint model
    // Serial.print("Creating model for #"); Serial.println(id);
    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
        Serial.println("Prints matched!");
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FINGERPRINT_ENROLLMISMATCH) {
        Serial.println("Fingerprints did not match");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }

    // Store the fingerprint model
    // Serial.print("ID "); Serial.println(id);
    // p = finger.storeModel(id);
    if (p == FINGERPRINT_OK) {
        Serial.println("Stored!");
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FINGERPRINT_BADLOCATION) {
        Serial.println("Could not store in that location");
        return p;
    } else if (p == FINGERPRINT_FLASHERR) {
        Serial.println("Error writing to flash");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }

    // Wait until touch input is detected to continue
    while (!LcdTouch.touched());

    // End of function
}
//פוננקציה ראשונית לקליטת קוד
int getCode()
{

}
int openSafe()
{

}
uint8_t getFingerPrint() {
  
}


  

 


