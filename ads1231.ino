//CONNECTIONS
#define POWERDOWN 10    //POWERDOWN -LOW TO POWER DOWN
#define SPEED 11    //Chip selection pin
#define DATAPIN 12    //Data pin
#define CLOCK 6  //ADS 7817 clock
#define ZEROSWITCH 7 // FOR ZERO ERROR
 unsigned long  adcvalue;
 short int i;
 float c,y;
void setup() 
{                
  initspi();
  Serial.begin(9600);  //Initialize serial for debugging
  pinMode(ZEROSWITCH, INPUT_PULLUP);
caliberate();
}
void loop() 
{
displaydata();
//delay(200);
if(!digitalRead(ZEROSWITCH))
{
caliberate();
//float c=y;
}
}

void readADS1231(void) 
{
adcvalue=0;  
//digitalWrite(POWERDOWN, HIGH); //POWER ON
while(digitalRead(DATAPIN));//WAIT UNTIL DATA IS READY
//24-->21
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X800000;} //24
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X400000;}//23
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X200000;}//22
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X100000;}//21
//20-->17
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X80000;} //20
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X40000;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X20000;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X10000;}//17
//16-->13
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X8000;} //16
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X4000;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X2000;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X1000;}//13
//12-->9
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X800;} //12
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X400;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X200;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X100;}//9
//8-->5
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X80;} //8
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X40;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X20;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X10;}//5
//4-->1
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X8;} //4
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X4;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X2;}//
clock ();
if(digitalRead(DATAPIN)){adcvalue=adcvalue+0X1;}//1
clock ();//TO PULL DATA READY TO HIGH STATE --PAGE No.14 ON ADS1231 DATASHEET
//
digitalWrite(CLOCK, LOW);   
//digitalWrite(POWERDOWN, LOW);
}
void caliberate(void)
{
  readADS1231();
 c=(adcvalue/100000.0);
  Serial.print("caliber=");Serial.println(c);    
}

void displaydata(void)
{
  readADS1231();
 y=(adcvalue/100000.0);
 y=y-c;
  Serial.print("adcvalue=");Serial.println(y);  
}
void clock (void)
{
digitalWrite(CLOCK, LOW);   
digitalWrite(CLOCK, HIGH);
delayMicroseconds(10);

}
void initspi(void)
{
pinMode(POWERDOWN, OUTPUT);  
pinMode(DATAPIN, INPUT);
pinMode(CLOCK, OUTPUT);
pinMode(SPEED, OUTPUT);
digitalWrite(POWERDOWN, HIGH);  //0-->  POWERDOWN(SLEEPING -NO CONVERSION) ,1-->WORKING MODE
digitalWrite(SPEED, 0);//0-->  10SPS ,1-->80SPS
digitalWrite(CLOCK, LOW);
}
