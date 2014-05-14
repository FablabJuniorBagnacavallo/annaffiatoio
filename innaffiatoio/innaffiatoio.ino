#define NSENS 1
#define SOGLIAUMIDITA 900
#define DURATAINNAFFIO 300000
#define EVERY 3600000

//NSENS = numero sensori
//EVERY = controlla ogni EVERY ms
//SOGLIAUMIDITA = in 1024esimi
//DURATAINNAFFIO = innaffia per ...
byte pinSens[NSENS];
byte pinPump = 12;
int valUmid[NSENS];
int valOutput[NSENS];
unsigned long lastRead;

void setup(){
	pinSens[0] = A0;
	pinSens[1] = A1;	
	pinSens[2] = A2;
	pinSens[3] = A3;
	int i;
	for (i=0;i<NSENS;i++)
		pinMode(pinSens[i],INPUT);
	pinMode(pinPump,OUTPUT);
	lastRead = millis();
	innaffia();
}

void loop(){
	unsigned long currentTime = millis();
	if (abs(lastRead - currentTime) > EVERY){
		lastRead = currentTime;
		innaffia();
	}
}

void innaffia(){
	int sensOut = leggiUmidita();
	if (sensOut>=1){
		digitalWrite(pinPump,HIGH);
		delay(DURATAINNAFFIO);
		digitalWrite(pinPump,LOW);
	}
}

int leggiUmidita(){
	int i;
	int sensOut = 0;
	for (i=0;i<NSENS;i++){
		valUmid[i] = analogRead(pinSens[i]);
		if (valUmid[i]>SOGLIAUMIDITA)
			sensOut++;
	}
	return sensOut;
}