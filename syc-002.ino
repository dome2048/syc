int SYCcommand(String command);

int V1 = 7;
int ledR = A7;
int ledG = A6;
int ledB = A5;
int sirenPin = 1;

boolean watering = false;
int startCountdown = 20;
//In minutes
//40000 = 1 minute
//600000
int countdown = 0;
//PUT YOUR VARIABLES HERE

void setup()
{
	Spark.function("syccommand", SYCcommand);

	//PUT YOUR SETUP CODE HERE
	pinMode(ledR, OUTPUT);  
	pinMode(ledG, OUTPUT);  
	pinMode(ledB, OUTPUT); 
	pinMode(V1, OUTPUT); 
	pinMode(sirenPin, OUTPUT);
    
	digitalWrite(ledR, HIGH);
	digitalWrite(ledB, HIGH);
	digitalWrite(ledG, LOW);
	digitalWrite(V1, LOW);

	//tone(sirenPin, 4000);
    
	delay(10);
	RGB.control(true);
	RGB.color(0, 0, 0);
    
	delay(500);
	digitalWrite(ledG, HIGH);

	beep1();
	Spark.publish("restart");
/*	delay(1000);
	beep3();
	delay(1000);
	beep4();
	*/
	//TODO: set valve and switch to closed and off
}

void loop()
{
	//PUT YOUR LOOP CODE HERE
	if (watering == true)
	{
		countdown = countdown - 10;
    
		if (countdown <= 0)
		{
			digitalWrite(V1, LOW);
			digitalWrite(ledG, HIGH);
			watering = false;
			beep4();
		}
	}
	delay(10);
}

int SYCcommand(String command)
{
	if (command == "1") {   
		digitalWrite(V1, HIGH);
		digitalWrite(ledG, LOW);
		watering = true;
		countdown = startCountdown * 40000;
		beep3();
		beep3();
		return 1;
	} else if (command == "0") {
		digitalWrite(V1, LOW);
		digitalWrite(ledG, HIGH);
		watering = false;
		beep4();
		beep4();
		return 0;
	}
	else {
		beep2();
	}
  
}

void beep1()
{  
	tone(sirenPin, 4000);
	delay(50);
	noTone(sirenPin);
	delay(50);
	tone(sirenPin, 4000);
	delay(50);
	noTone(sirenPin);
}

void beep2()
{  
	digitalWrite(ledR, LOW);
	tone(sirenPin, 4000);
	delay(50);
	noTone(sirenPin);
	delay(50);
	tone(sirenPin, 4000);
	delay(1000);
	noTone(sirenPin);
	delay(500);
	digitalWrite(ledR, HIGH);
}

void beep3()
{  
	tone(sirenPin, 4000);
	delay(200);
	noTone(sirenPin);
	delay(50);
	tone(sirenPin, 4650);
	delay(500);
	noTone(sirenPin);
}

void beep4()
{  
	tone(sirenPin, 4125);
	delay(100);
	noTone(sirenPin);
	delay(50);
	tone(sirenPin, 4000);
	delay(500);
	noTone(sirenPin);
}
