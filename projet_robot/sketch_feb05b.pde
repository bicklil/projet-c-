#include <Wire.h>
#include <SPI.h>
#define SEUIL 150
#define SRF_ADDRESS 112
#define CMD 0x00
#define RANGEBYTE 0x02
#define LIGHTBYTE 0x01
#define CA1 2
#define CB1 10
#define CA2 3
#define CB2 11
#define MPU9150_SELF_TEST_X        0x0D   // R/W
#define MPU9150_SELF_TEST_Y        0x0E   // R/W
#define MPU9150_SELF_TEST_X        0x0F   // R/W
#define MPU9150_SELF_TEST_A        0x10   // R/W
#define MPU9150_SMPLRT_DIV         0x19   // R/W
#define MPU9150_CONFIG             0x1A   // R/W
#define MPU9150_GYRO_CONFIG        0x1B   // R/W
#define MPU9150_ACCEL_CONFIG       0x1C   // R/W
#define MPU9150_FF_THR             0x1D   // R/W
#define MPU9150_FF_DUR             0x1E   // R/W
#define MPU9150_MOT_THR            0x1F   // R/W
#define MPU9150_MOT_DUR            0x20   // R/W
#define MPU9150_ZRMOT_THR          0x21   // R/W
#define MPU9150_ZRMOT_DUR          0x22   // R/W
#define MPU9150_FIFO_EN            0x23   // R/W
#define MPU9150_I2C_MST_CTRL       0x24   // R/W
#define MPU9150_I2C_SLV0_ADDR      0x25   // R/W
#define MPU9150_I2C_SLV0_REG       0x26   // R/W
#define MPU9150_I2C_SLV0_CTRL      0x27   // R/W
#define MPU9150_I2C_SLV1_ADDR      0x28   // R/W
#define MPU9150_I2C_SLV1_REG       0x29   // R/W
#define MPU9150_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU9150_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU9150_I2C_SLV2_REG       0x2C   // R/W
#define MPU9150_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU9150_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU9150_I2C_SLV3_REG       0x2F   // R/W
#define MPU9150_I2C_SLV3_CTRL      0x30   // R/W
#define MPU9150_I2C_SLV4_ADDR      0x31   // R/W
#define MPU9150_I2C_SLV4_REG       0x32   // R/W
#define MPU9150_I2C_SLV4_DO        0x33   // R/W
#define MPU9150_I2C_SLV4_CTRL      0x34   // R/W
#define MPU9150_I2C_SLV4_DI        0x35   // R  
#define MPU9150_I2C_MST_STATUS     0x36   // R
#define MPU9150_INT_PIN_CFG        0x37   // R/W
#define MPU9150_INT_ENABLE         0x38   // R/W
#define MPU9150_INT_STATUS         0x3A   // R  
#define MPU9150_ACCEL_XOUT_H       0x3B   // R  
#define MPU9150_ACCEL_XOUT_L       0x3C   // R  
#define MPU9150_ACCEL_YOUT_H       0x3D   // R  
#define MPU9150_ACCEL_YOUT_L       0x3E   // R  
#define MPU9150_ACCEL_ZOUT_H       0x3F   // R  
#define MPU9150_ACCEL_ZOUT_L       0x40   // R  
#define MPU9150_TEMP_OUT_H         0x41   // R  
#define MPU9150_TEMP_OUT_L         0x42   // R  
#define MPU9150_GYRO_XOUT_H        0x43   // R  
#define MPU9150_GYRO_XOUT_L        0x44   // R  
#define MPU9150_GYRO_YOUT_H        0x45   // R  
#define MPU9150_GYRO_YOUT_L        0x46   // R  
#define MPU9150_GYRO_ZOUT_H        0x47   // R  
#define MPU9150_GYRO_ZOUT_L        0x48   // R  
#define MPU9150_EXT_SENS_DATA_00   0x49   // R  
#define MPU9150_EXT_SENS_DATA_01   0x4A   // R  
#define MPU9150_EXT_SENS_DATA_02   0x4B   // R  
#define MPU9150_EXT_SENS_DATA_03   0x4C   // R  
#define MPU9150_EXT_SENS_DATA_04   0x4D   // R  
#define MPU9150_EXT_SENS_DATA_05   0x4E   // R  
#define MPU9150_EXT_SENS_DATA_06   0x4F   // R  
#define MPU9150_EXT_SENS_DATA_07   0x50   // R  
#define MPU9150_EXT_SENS_DATA_08   0x51   // R  
#define MPU9150_EXT_SENS_DATA_09   0x52   // R  
#define MPU9150_EXT_SENS_DATA_10   0x53   // R  
#define MPU9150_EXT_SENS_DATA_11   0x54   // R  
#define MPU9150_EXT_SENS_DATA_12   0x55   // R  
#define MPU9150_EXT_SENS_DATA_13   0x56   // R  
#define MPU9150_EXT_SENS_DATA_14   0x57   // R  
#define MPU9150_EXT_SENS_DATA_15   0x58   // R  
#define MPU9150_EXT_SENS_DATA_16   0x59   // R  
#define MPU9150_EXT_SENS_DATA_17   0x5A   // R  
#define MPU9150_EXT_SENS_DATA_18   0x5B   // R  
#define MPU9150_EXT_SENS_DATA_19   0x5C   // R  
#define MPU9150_EXT_SENS_DATA_20   0x5D   // R  
#define MPU9150_EXT_SENS_DATA_21   0x5E   // R  
#define MPU9150_EXT_SENS_DATA_22   0x5F   // R  
#define MPU9150_EXT_SENS_DATA_23   0x60   // R  
#define MPU9150_MOT_DETECT_STATUS  0x61   // R  
#define MPU9150_I2C_SLV0_DO        0x63   // R/W
#define MPU9150_I2C_SLV1_DO        0x64   // R/W
#define MPU9150_I2C_SLV2_DO        0x65   // R/W
#define MPU9150_I2C_SLV3_DO        0x66   // R/W
#define MPU9150_I2C_MST_DELAY_CTRL 0x67   // R/W
#define MPU9150_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU9150_MOT_DETECT_CTRL    0x69   // R/W
#define MPU9150_USER_CTRL          0x6A   // R/W
#define MPU9150_PWR_MGMT_1         0x6B   // R/W
#define MPU9150_PWR_MGMT_2         0x6C   // R/W
#define MPU9150_FIFO_COUNTH        0x72   // R/W
#define MPU9150_FIFO_COUNTL        0x73   // R/W
#define MPU9150_FIFO_R_W           0x74   // R/W
#define MPU9150_WHO_AM_I           0x75   // R

//MPU9150 Compass
#define MPU9150_CMPS_XOUT_L        0x4A   // R
#define MPU9150_CMPS_XOUT_H        0x4B   // R
#define MPU9150_CMPS_YOUT_L        0x4C   // R
#define MPU9150_CMPS_YOUT_H        0x4D   // R
#define MPU9150_CMPS_ZOUT_L        0x4E   // R
#define MPU9150_CMPS_ZOUT_H        0x4F   // R


// I2C address 0x69 could be 0x68 depends on your wiring. 
int MPU9150_I2C_ADDRESS = 0x68;


//Variables where our values can be stored
int cmps[3];
int accl[3];
int gyro[3];
int temp;
void obstacle();
void rotation45(int sens);


volatile int depart;
const int  cs=12; //chip select 
volatile int CPOS1=0;
volatile int CPOS2=0;

int getRange() // fonction donnant la distance

 {
   int reading=0;
   Wire.beginTransmission(SRF_ADDRESS); // transmit to device #112 (0x70)
                               // the address specified in the datasheet is 224 (0xE0)
                               // but i2c adressing uses the high 7 bits so it's 112
  Wire.send(CMD);             // sets register pointer to the command register (0x00)  
  Wire.send(0x51);             // command sensor to measure in "inches" (0x50) 
                               // use 0x51 for centimeters
                               // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(100);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(SRF_ADDRESS); // transmit to device #112
  Wire.send(RANGEBYTE);             // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(SRF_ADDRESS, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if(2 <= Wire.available()){   // if two bytes were received
  reading = Wire.receive();  // receive high byte (overwrites previous reading)
  reading = reading << 8;    // shift high byte to be high 8 bits
  reading |= Wire.receive(); // receive low byte as lower 8 bits
  //Serial.println(reading);   // print the reading
  return(reading); 
 }
 }
 
 
float getBattery()
{
 int n=analogRead(A0);
 float v=0.0179*n;
 return v;
}

int getLight()// recupere l'intensité lumineuse
{
  Wire.beginTransmission(SRF_ADDRESS);
  Wire.send(LIGHTBYTE);
  Wire.endTransmission();
  
  Wire.requestFrom(SRF_ADDRESS,1);
  while(Wire.available()<0);
  int lightRead = Wire.receive();
  return lightRead ;
}

float getLed(int pinLed)// recupere l'analogue de la led en parametre
{
  float L=analogRead(pinLed);
  return L ;
}


void ISR1()
{
  if (digitalRead(CA1)==digitalRead(CB1)) CPOS1--;
  else CPOS1++;
}

void ISR2()
{
  if (digitalRead(CA2)==digitalRead(CB2)) CPOS2++;
  else CPOS2--; 
}

void mot1(int s,int vit){
  if (s == 1){
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    analogWrite(6,vit);
  }
  if (s == 2){
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    analogWrite(6,vit);
  }
  if (s == 0){
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    analogWrite(6,0);
  }
}
void mot2(int s,int vit){
  if (s == 2){
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
    analogWrite(5,vit);
  }
  if (s == 1){
    digitalWrite(7,LOW);
    digitalWrite(4,HIGH);
    analogWrite(5,vit);
  }
  if (s == 0){
    digitalWrite(7,LOW);
    digitalWrite(4,HIGH);
    analogWrite(5,0);
  }
}

//=====================================
int RTC_init(){ 
	  pinMode(cs,OUTPUT); // chip select
	  // start the SPI library:
	  SPI.begin();
	  SPI.setBitOrder(MSBFIRST); 
	  SPI.setDataMode(SPI_MODE1); // both mode 1 & 3 should work 
	  //set control register 
	  digitalWrite(cs, LOW);  
	  SPI.transfer(0x8E);
	  SPI.transfer(0x60); //60= disable Osciallator and Battery SQ wave @1hz, temp compensation, Alarms disabled
	  digitalWrite(cs, HIGH);
	  delay(10);
}
//=====================================
int SetTimeDate(int d, int mo, int y, int h, int mi, int s){ 
	int TimeDate [7]={s,mi,h,0,d,mo,y};
	for(int i=0; i<=6;i++){
		if(i==3)
			i++;
		int b= TimeDate[i]/10;
		int a= TimeDate[i]-b*10;
		if(i==2){
			if (b==2)
				b=B00000010;
			else if (b==1)
				b=B00000001;
		}	
		TimeDate[i]= a+(b<<4);
		  
		digitalWrite(cs, LOW);
		SPI.transfer(i+0x80); 
		SPI.transfer(TimeDate[i]);        
		digitalWrite(cs, HIGH);
  }
}
//=====================================
String ReadTimeDate(){
	String temp;
	int TimeDate [7]; //second,minute,hour,null,day,month,year		
	for(int i=0; i<=6;i++){
		if(i==3)
			i++;
		digitalWrite(cs, LOW);
		SPI.transfer(i+0x00); 
		unsigned int n = SPI.transfer(0x00);        
		digitalWrite(cs, HIGH);
		int a=n & B00001111;    
		if(i==2){	
			int b=(n & B00110000)>>4; //24 hour mode
			if(b==B00000010)
				b=20;        
			else if(b==B00000001)
				b=10;
			TimeDate[i]=a+b;
		}
		else if(i==4){
			int b=(n & B00110000)>>4;
			TimeDate[i]=a+b*10;
		}
		else if(i==5){
			int b=(n & B00010000)>>4;
			TimeDate[i]=a+b*10;
		}
		else if(i==6){
			int b=(n & B11110000)>>4;
			TimeDate[i]=a+b*10;
		}
		else{	
			int b=(n & B01110000)>>4;
			TimeDate[i]=a+b*10;	
			}
	}
	temp.concat(TimeDate[4]);
	temp.concat("/") ;
	temp.concat(TimeDate[5]);
	temp.concat("/") ;
	temp.concat(TimeDate[6]);
	temp.concat(" ,") ;
	temp.concat(TimeDate[2]);
	temp.concat(":") ;
	temp.concat(TimeDate[1]);
	temp.concat(":") ;
	temp.concat(TimeDate[0]);
  return(temp);
}
void MPU9150_setupCompass(){
  MPU9150_I2C_ADDRESS = 0x0C;      //change Adress to Compass

  MPU9150_sendSensor(0x0A, 0x00); //PowerDownMode
  MPU9150_sendSensor(0x0A, 0x0F); //SelfTest
  MPU9150_sendSensor(0x0A, 0x00); //PowerDownMode

  MPU9150_I2C_ADDRESS = 0x68;      //change Adress to MPU

  MPU9150_sendSensor(0x24, 0x40); //Wait for Data at Slave0
  MPU9150_sendSensor(0x25, 0x8C); //Set i2c address at slave0 at 0x0C
  MPU9150_sendSensor(0x26, 0x02); //Set where receiveing at slave 0 starts
  MPU9150_sendSensor(0x27, 0x88); //set offset at start receiveing and enable
  MPU9150_sendSensor(0x28, 0x0C); //set i2c address at slv1 at 0x0C
  MPU9150_sendSensor(0x29, 0x0A); //Set where receiveing at slave 1 starts
  MPU9150_sendSensor(0x2A, 0x81); //Enable at set length to 1
  MPU9150_sendSensor(0x64, 0x01); //overvride register
  MPU9150_sendSensor(0x67, 0x03); //set delay rate
  MPU9150_sendSensor(0x01, 0x80);

  MPU9150_sendSensor(0x34, 0x04); //set i2c slv4 delay
  MPU9150_sendSensor(0x64, 0x00); //override register
  MPU9150_sendSensor(0x6A, 0x00); //clear usr setting
  MPU9150_sendSensor(0x64, 0x01); //override register
  MPU9150_sendSensor(0x6A, 0x20); //enable master i2c mode
  MPU9150_sendSensor(0x34, 0x13); //disable slv4
}

////////////////////////////////////////////////////////////
///////// I2C functions to get easier all values ///////////
////////////////////////////////////////////////////////////

int16_t MPU9150_receiveSensor(int addrL, int addrH){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.send(addrL);
  Wire.endTransmission();

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1);
  byte L = Wire.receive();

  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.send(addrH);
  Wire.endTransmission();

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1);
  byte H = Wire.receive();

  return (int16_t)((H<<8)+L);
}

int16_t MPU9150_receiveSensor(int addr){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.send(addr);
  Wire.endTransmission();

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1);
  return Wire.receive();
}

int MPU9150_sendSensor(int addr,int data){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.send(addr);
  Wire.send(data);
  Wire.endTransmission();

  return 1;
}

String lecture_str(){
  String str;
  if (Serial.available()>0)
    {str=Serial.readStringUntil(',');
      return str;
    }
      
}

int moteur_manuel(){
   String donnee[4];
   int i;
   if ((donnee[0]=lecture_str())=="M")
   {for(i=1;i<4;i++)
   {
       donnee[i]=lecture_str();
   }}
   if (donnee[1]=="2")
   {
     mot2(donnee[2].toInt(),donnee[3].toInt());
     return 1;
   }
   if (donnee[1]=="1")
   {
     mot1(donnee[2].toInt(),donnee[3].toInt());
    return 1; 
   }
}

void suivre_ligne(){

  if ( (depart == 1))
  {
    mot1(0,150);
    mot2(0,150);
  }
  if ((analogRead(A8)>SEUIL)  &&(analogRead(A7)>SEUIL)  &&(analogRead(A6)>SEUIL)  &&(analogRead(A5)>SEUIL)  &&(analogRead(A4)>SEUIL)  &&(analogRead(A3)>SEUIL)  &&(analogRead(A2)>SEUIL)  && (analogRead(A1)>SEUIL)&&(depart == 0))
  {
    depart = 1;
    mot1(0,150);
    mot2(0,150);
  }
  else
  {
 if ((analogRead(A4)>SEUIL) && (analogRead(A5)>SEUIL)&&(depart == 0))
  {
      mot1(1,150);
      mot2(1,150);
  }
 else
   {if ((analogRead(A4)<SEUIL) && (analogRead(A5)>SEUIL)&&(depart == 0))
   {
        mot1(1,100);
        mot2(1,50);
   }
     else {
       if ((analogRead(A3) > SEUIL)|| (analogRead(A2) > SEUIL) || (analogRead(A1) > SEUIL)&&(depart == 0))
       {
            mot2(1,100);
            mot1(1,50);
            while((analogRead(A4)>SEUIL) && (analogRead(A5)>SEUIL)){}
       }
       else 
       {
       mot2(1,50);
       mot1(1,100);
       while ((analogRead(A4)>SEUIL) && (analogRead(A5)>SEUIL)){}
 }  }}
}}
void rotation45(int sens)
{
  if (sens == 1)
  {
    mot1(1,100);
    mot2(2,100);
    delay(350);  // delai pour faire un angle de 45 degre avec 100 comme vitesse (A REVOIR)
    mot1(0,0);
    mot2(0,0);
  }
  if (sens == 0)
  {
    mot1(2,100);
    mot2(1,100);
    delay(350);  // delai pour faire un angle de 45 degre avec 100 comme vitesse (A REVOIR)
    mot1(0,0);
    mot2(0,0);
  }
}
void obstacle()
{
  int distance1 = getRange();
  int distance2 = 0;
  if (distance1 < 50)
  {
    rotation45(1);
    distance2 = getRange();
    if (distance2 < distance1)
    {
      rotation45(0);
    }
  }
}

void setup()
{
  //Wire.begin();                // join i2c bus (address optional for master)capte
  //Serial.begin(9600);          // start serial communication at 9600bps
  //pinMode(CA1,INPUT);pinMode(CA2,INPUT);pinMode(CB1,INPUT);pinMode(CB2,INPUT); //init de cpt
  //attachInterrupt(1,ISR1,FALLING);attachInterrupt(0,ISR2,FALLING); //init de cpt
  pinMode(13,OUTPUT);digitalWrite(13,1); //allume led capteur
  pinMode(4,OUTPUT);pinMode(5,OUTPUT);pinMode(6,OUTPUT);pinMode(7,OUTPUT);pinMode(8,OUTPUT);pinMode(9,OUTPUT); // init de moteur
  
    //CapteurLigne//
//  pinMode(A1,INPUT);
//  pinMode(A2,INPUT);
//  pinMode(A3,INPUT);
//  pinMode(A4,INPUT);
//  pinMode(A5,INPUT);
//  pinMode(A6,INPUT);
//  pinMode(A7,INPUT);
//  pinMode(A8,INPUT); 
  //RTC_init();
  //day(1-31), month(1-12), year(0-99), hour(0-23), minute(0-59), second(0-59)
  //SetTimeDate(9,04,15,15,20,0);
  // Clear the 'sleep' bit to start the sensor.
  //MPU9150_sendSensor(MPU9150_PWR_MGMT_1, 0);
  //MPU9150_setupCompass();
    mot1(1,150);
    mot2(1,150);
    depart = 0;
    delay(500);

}

void loop(){
  suivre_ligne();
  //obstacle();
      //mot1(1,100);
      //mot2(1,100);
  //delay(1);
//    moteur_manuel();
//    delay(5000);
//  Serial.print("RTCC,");      //print la premiere ligne (date / heure)
//  Serial.println(ReadTimeDate());
//  Serial.print("DIST,"); // print de la deuxieme ligne (distance)
//  Serial.print(getRange(), DEC);
//  Serial.println("cm");
//  Serial.print("L="); // print la troisieme (lumiere)
//  Serial.println(getLight(),DEC);
//  Serial.print("TEMP");
//  double dT = ( (double) MPU9150_receiveSensor(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H) + 12412.0) / 340.0;
//  Serial.println(dT);
//  Serial.print("MAG,MX=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_CMPS_XOUT_L,MPU9150_CMPS_XOUT_H));
//  Serial.print(",MY=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_CMPS_YOUT_L,MPU9150_CMPS_YOUT_H));
//  Serial.print(",MZ=");
//  Serial.println(MPU9150_receiveSensor(MPU9150_CMPS_ZOUT_L,MPU9150_CMPS_ZOUT_H));
//  Serial.print("GYR,GX=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_GYRO_XOUT_L,MPU9150_GYRO_XOUT_H));
//  Serial.print(",GY=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_GYRO_YOUT_L,MPU9150_GYRO_YOUT_H));
//  Serial.print(",GZ=");
//  Serial.println(MPU9150_receiveSensor(MPU9150_GYRO_ZOUT_L,MPU9150_GYRO_ZOUT_H));
//  Serial.print("ACCEL,AX=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H));
//  Serial.print(",AY=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H));
//  Serial.print(",AZ=");
//  Serial.print(MPU9150_receiveSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H));
//  Serial.println();
//  Serial.print("COD,");
//  Serial.print(CPOS1,DEC);
//  Serial.print(",");
//  Serial.println(CPOS2,DEC);
//  Serial.print("LINE,");
//  Serial.print(analogRead(A1));
//  Serial.print(",");
//  Serial.print(analogRead(A2));
//  Serial.print(",");
//  Serial.print(analogRead(A3));
//  Serial.print(",");
//  Serial.print(analogRead(A4));
//  Serial.print(",");
//  Serial.print(analogRead(A5));
//  Serial.println(",");
//  Serial.print(analogRead(A6));
//  Serial.print(",");
//  Serial.print(analogRead(A7));
//  Serial.print(",");
//  Serial.println(analogRead(A8));
//  Serial.print("VOLT,");
//  Serial.print(getBattery());
//  Serial.println("V,");
//  Serial.println();

}
