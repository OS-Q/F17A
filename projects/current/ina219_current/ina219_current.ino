#include <math.h>
#include "TM1637.h"
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#define CLK 10//pins definitions for TM1637 and can be changed to other ports
#define DIO 9
TM1637 tm1637(CLK, DIO);
unsigned char ClockPoint = 1;
int sensorValue = 0;

unsigned char hour = 0;
unsigned char minute = 0;
int8_t TimeDisp[] = { 0x00, 0x00, 0x00, 0x00 };
//float shuntvoltage = 0;
//  float busvoltage = 0;
float current_mA = 0;
//  float loadvoltage = 0;
 // float power_mW = 0;


void TimeUpdate(void) { int sensorValuesa=current_mA*10;
	//int sensorValuesa = cbrt(sensorValue) * 100; //ȡ������
	//int sensorValue1 = constrain(sensorValue - 0.5 * 4096 / 2.56, 850, 2500);

//	int sensorValuesa = log10(sensorValue1) * 1000; //��10Ϊ�׵Ķ���

//	int voltage = sensorValue * (2.560 / 4096.0) * 1000;
	//int BRIGHTS = constrain(sensorValuesa, 2800, 3200);
//	int BRIGHT = map(BRIGHTS, 2800, 3200, 0, 7);

	//int BRIGHTS = constrain(sensorValuesa, 1000, 1320);
	//int BRIGHT = map(BRIGHTS, 1000, 1320, 0, 7);

	if (ClockPoint) {
		//tm1637.point(POINT_ON);
	//	Serial.println(sensorValuesa / 1);
	//	delay(100);
	//	tm1637.set(BRIGHT);
		TimeDisp[0] = sensorValuesa / 100 / 10;
		TimeDisp[1] = sensorValuesa / 100 % 10;
		TimeDisp[2] = sensorValuesa % 100 / 10;
		TimeDisp[3] = sensorValuesa % 100 % 10;
	}

	/*else {
		tm1637.point(POINT_OFF);
		Serial.println(voltage / 1);
		delay(100);
		tm1637.set(BRIGHT);
		TimeDisp[0] = 0;
		TimeDisp[1] = 0;
		TimeDisp[2] = 0;
		TimeDisp[3] = BRIGHT;
		}
		*/

	//Serial.println(sensorValuesa);
	//delay(100);
	//ClockPoint = !ClockPoint;
	//int sensorValuesa = cbrt(sensorValue) * 100;
	//TimeDisp[0,1,2,3] = sensorValuesa /  1;

}

void setup() {
	// initialize serial communication at 9600 bits per second:
	//Serial.begin(9600);

	uint32_t currentFrequency;

	// Initialize the INA219.
	// By default the initialization will use the largest range (32V, 2A).  However
	// you can call a setCalibration function to change this range (see comments).
	ina219.begin();
	// To use a slightly lower 32V, 1A range (higher precision on amps):
	//ina219.setCalibration_32V_1A();
	// Or to use a lower 16V, 400mA range (higher precision on volts and amps):
	ina219.setCalibration_16V_400mA();


	tm1637.init();
	tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
	tm1637.point(POINT_OFF);
	analogReference(INTERNAL2V56); //use internal 1.1v as Avref
	//analogReference(EXTERNAL); //ʹ���ⲿ��׼

//analogReference(type)
//����
//��������ģ������Ļ�׼��ѹ�������뷶Χ�����ֵ����ѡ����:
//DEFAULT��Ĭ��5V��Ocrobot���ư�Ϊ5V����3.3���أ�Ocrobot���ư�Ϊ3.3V��Ϊ��׼��ѹ��
//INTERNAL����ATmega168��ATmega328����1.1VΪ��׼��ѹ���Լ���ATmega8����2.56VΪ��׼��ѹ��Ocrobot Mega�޴�ѡ�
////INTERNAL1V1����1.1VΪ��׼��ѹ����ѡ������Ocrobot Mega��
//INTERNAL2V56����2.56VΪ��׼��ѹ����ѡ������Ocrobot Mega��
//EXTERNAL����AREF���ţ�0��5V���ĵ�ѹ��Ϊ��׼��ѹ��
//����
//type��ʹ�����ֲο����ͣ�DEFAULT, INTERNAL, INTERNAL1V1, INTERNAL2V56, INTERNAL4V096 ���� EXTERNAL����
//����
//��

	uint32_t guid = (GUID3 << 24) | (GUID2 << 16) | (GUID1 << 8) | GUID0; // ��guid��ֵΨһID
	//Serial.println(guid); // �������ΨһID
	delay(2000);
}

// the loop routine runs over and over again forever:
void loop() {
	// read the input on analog pin 0:
	sensorValue = analogRead(A0);



	//  shuntvoltage = ina219.getShuntVoltage_mV();
	//  busvoltage = ina219.getBusVoltage_V();
	  current_mA = ina219.getCurrent_mA();
	//  power_mW = ina219.getPower_mW();
	//  loadvoltage = busvoltage + (shuntvoltage / 1000);

	//  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
	//  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
	//  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
	//  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
	  //Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
	//  Serial.println("");

	  delay(200);



	// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
	//float voltage = sensorValue * (2.56 / 4096.0);
	// print out the value you read:
	//Serial.print(sensorValue);
	//Serial.print(' ');
	//Serial.print(cbrt(sensorValue));
	//Serial.print(' ');
	//Serial.println(voltage);

	//delay(1000);
	TimeUpdate();
	tm1637.display(TimeDisp);
}
