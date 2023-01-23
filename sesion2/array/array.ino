int void_array[5];
int full_array[] ={ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
 
void setup() {
    Serial.begin(115200);
}
 
void loop() {

   Serial.print("First element of void array: ");
    Serial.println(void_array[0]);
    Serial.print("First element of full array: ");
    Serial.println(full_array[0]);
    Serial.print("11th element of full array: ");
    Serial.println(full_array[10]);
    full_array[10]=110;
    Serial.print("11th element of full array with value: ");
    Serial.println(full_array[10]);
  
    void_array[7]=123456;
    Serial.print("8th element of void array with value: ");
    Serial.println(void_array[7]);
    delay(10000);
   
}