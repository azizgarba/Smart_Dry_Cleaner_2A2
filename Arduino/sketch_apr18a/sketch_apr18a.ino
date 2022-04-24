const int buttonPin = 2; // broche du capteur PIR
const int ledPin = 13; // la LED du Arduino
int buttonState = 0; // etat de la sortie du capteur
int nb;

void setup()
{
  pinMode(ledPin, OUTPUT); //la broche de la LED est mise en sortie
  pinMode(buttonPin, INPUT); //la broche du capteur est mise en entree
  Serial.begin(9600);

}

void loop()
{
 buttonState = digitalRead(buttonPin);//lecture du capteur
  if (buttonState == HIGH) //si quelquechose est detecte
  {
    nb++;
    Serial.write("1");
    Serial.print("1");
    digitalWrite(ledPin, HIGH); //on allume la LED
    //buttonState = LOW;
  }
  else //sinon
  {
    Serial.print("0");
    Serial.write('0');
    digitalWrite(ledPin, LOW); //on eteint la LED
  }
}
