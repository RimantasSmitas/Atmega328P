int val;
int tempPin = 1;

void setup()
{
	
}
void loop()
{
	val = in(tempPin);
	float mv = ( val/1024.0)*5000;
	float cel = mv/10;
	float farh = (cel*9)/5 + 32;

	
	/* uncomment this to get temperature in farenhite
	Serial.print("TEMPRATURE = ");
	Serial.print(farh);
	Serial.print("*F");
	Serial.println();


	*/
}