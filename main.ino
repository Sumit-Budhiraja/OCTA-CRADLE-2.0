#include <LiquidCrystal.h>
#include<DHT.h>

#define DHTPIN 6

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal lcd(0,1,8,9,10,11);


int ledPin=13;

int soundPin=22;

boolean val =0;

int moisturePin = A0;
int count=0;
 int count2=0;
 int count3=0;
int sensorValue; 

int limit = 800;

int mledpin=23;

int PIR = 24;             

int state = LOW;            

int pval = 0;                

int obstaclePin = 26;  // This is our input pin

int hasObstacle = HIGH;  // HIGH MEANS NO OBSTACLE

int trigPin = 28;    // Trigger

int echoPin = 30;    // Echo

long duration, cm, inches;

float hum;

float temp;
int enA = 10;

int in1 = 9;

int in2 = 8;

// motor two

int enB = 5;

int in3 = 7;

int in4 = 6;

int buz=32;
int buz1=34; 
int alg;
int algo;
void setup(){

  pinMode(buz,OUTPUT);
  pinMode(buz1,OUTPUT);
  
  pinMode(ledPin, OUTPUT);

  pinMode(soundPin, INPUT);

  Serial.begin (9600);

  pinMode(mledpin, OUTPUT);

  pinMode(PIR, INPUT);   

  Serial.begin(9600);

  pinMode(obstaclePin, INPUT);

  Serial.begin(9600);

  //Serial.begin (9600);

  //Define inputs and outputs

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  dht.begin();

 pinMode(enA, OUTPUT);

  pinMode(enB, OUTPUT);

  pinMode(in1, OUTPUT);

  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);

  pinMode(in4, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Octa Cradle 2.0");
}

void demoOne()

{

  // this function will run the motors in both directions at a fixed speed

  // turn on motor A

  digitalWrite(in1, HIGH);

  digitalWrite(in2, LOW);

  // set speed to 200 out of possible range 0~255

  analogWrite(enA, 230);

  // turn on motor B

  digitalWrite(in3, HIGH);

  digitalWrite(in4, LOW);

  // set speed to 200 out of possible range 0~255

  analogWrite(enB, 230);

  delay(1000);

  // now change motor directions

  digitalWrite(in1, LOW);

  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);

  digitalWrite(in4, HIGH);

  delay(1000);

  // now turn off motors

  digitalWrite(in1, LOW);

  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);

  digitalWrite(in4, LOW);

}

void demoTwo()

{

  digitalWrite(in1, LOW);

  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);

  digitalWrite(in4, HIGH);

 

 for (int i = 0; i < 230; i++) {

analogWrite(enA, i);

analogWrite(enB, i);

delay(20);

}

for (int i = 230; i > 0; --i)

  {

    analogWrite(enA, i);

    analogWrite(enB, i);

    delay(20);

  }

  

  // now turn off motors

  digitalWrite(in1, LOW);

  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);

  digitalWrite(in4, LOW);

}

 

void loop (){

  val =digitalRead(soundPin);

  //Serial.println (val);

  if (val==HIGH) {

     digitalWrite(buz, HIGH);

      Serial.println("Baby is crying");
      count=1;
      
  lcd.setCursor(0, 1);
  lcd.print("   CRY ALERT!!!");

    algo=1234;
  }

  else {

    digitalWrite(buz, LOW);

    Serial.println("Baby is quiet");
   
  }

  delay(10);

sensorValue = analogRead(moisturePin);

// Serial.println("Analog Value : ");

//Serial.println(sensorValue);

 if (sensorValue<limit) {

digitalWrite(23, HIGH);
count2=2;
 Serial.println("Baby has urinated");
  digitalWrite(buz, HIGH);
  alg=123;
  lcd.setCursor(0, 1);
  lcd.print("Change DIAPER!!!");
//  //count++;
   
}
//if(count==2)
//{
//  lcd.setCursor(0, 1);
//  lcd.print("NEED WATER!!!");
//
//}

else {

digitalWrite(23, LOW);
Serial.println("Baby is dry");
digitalWrite(buz, LOW);

}

delay(100);

  pval = digitalRead(PIR);  

  if (pval == HIGH) {

    Serial.println("Motion detected!");

        count=3;         

    delay(100);                

    

    if (state == LOW) {

      state = HIGH;

//Serial.println("No Motion around!");

   

      delay(100);

}

  } 

  hasObstacle = digitalRead(obstaclePin); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino

  if (hasObstacle == LOW) //LOW means something is ahead, so illuminates the 13th Port connected LED

  {

    Serial.println("NO Insects Around");
    

   

    //digitalWrite(LED, HIGH);//Illuminates the 13th Port LED

  }

  else

  {

    Serial.println("Insect Protection Alert!!");

    count3=4;
//    digitalWrite(LED, LOW);
//  lcd.setCursor(0, 0);
//  lcd.print("Insect Alert!!!");
  lcd.setCursor(0, 1);
  lcd.print("ACTIVATE SHIELD!!!");

  }

  delay(200);

  digitalWrite(trigPin, LOW);
    delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);

  duration = pulseIn(echoPin, HIGH);

  cm = (duration*0.0343);     // Divide by 29.1 or multiply by 0.0343

  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

 

  //Serial.print(inches);

  //Serial.print("in, ");

  ///Serial.print(cm);

  ///Serial.print("cm");

  ///Serial.println();

 

  if(cm<7||cm>17)

  Serial.println("Be Careful Child may get hurt");

  //else

  //Serial.println(".....");

  delay(250);

 

  delay(200);

  hum=dht.readHumidity();

  temp=dht.readTemperature();

  Serial.print("Humidity :--");

  Serial.print(hum);

  Serial.print(" %, Temp: ");

  Serial.print(temp);

  Serial.println(" Celsius");

  delay(100); //Delay 2 sec.

 

  demoOne();

  delay(1000);

  demoTwo();

  delay(1000);

   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  
//  lcd.setCursor(0, 0);
//  lcd.print("Babu ro rha hai");
if(count==1)
{
  lcd.setCursor(0, 1);
  lcd.print("CRY ALERT!!!");
}
if(count==2)
{
  lcd.setCursor(0, 1);
  lcd.print("CHANGE DIAPER!!!");
}
//if(count==3)
//{
//  lcd.setCursor(0, 1);
//  lcd.print("EXCC MOTION!!!");
//}
if(count==4)
{
  lcd.setCursor(0, 0);
  lcd.print("Insect Alert!!!");
  lcd.setCursor(0, 1);
  lcd.print("ACTIVATE SHIELD!!!");

}
lcd.setCursor(0, 1);
lcd.print("EXCC MOTION!!!");

}
