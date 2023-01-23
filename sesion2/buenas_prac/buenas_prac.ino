

//float var1 = 10.15;

ulong p_time, c_time;
uint b_time_ms = 500;
const int8_t led = 2;
bool var1 = LOW;
char nombre[] = "hola mundo";
//String nombre = "hola mundo"

float funcion(int a, int b)
{
  int c = 10;
  return a + b + c;
}


void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  p_time = millis();
}

// the loop function runs over and over again forever
void loop() {
  c_time = millis();
  if ( c_time - p_time >= b_time_ms  ) {
    Serial.println(funcion(10,20));
    Serial.println(c);

    p_time = c_time;
    digitalWrite(led, var1);
    var1 = !var1;
  } 
}
