

//int var1 = 2147483610; //int =  minimum value of -2^31 and a maximum value of (2^31) - 1) 

//int8_t var1 = 100; //int8_t = minimum value of -2^7 and a maximum value of (2^7) - 1) -128 a 127
//int8_t var1 = 0b01100100;
//int8_t var1 = 0x64;

//uint8_t var1 = 0b01100100
//uint8_t var1 = 240; //int8_t =  maximum value of (2^8) 

//byte var1 = 240; //  2^8  


//int16_t var1 = 32760; //minimum value of -2^15 and a maximum value of (2^15) - 1) -128 a 127
//uint16_t var1 = 65530; // 2^16

//int32_t var1 = 32760; //minimum value of -2^15 and a maximum value of (2^15) - 1) -128 a 127
uint32_t var1 = 65530; // 2^16


bool flag = 1;

//char nombre[] = "andres";
String nombre = "andres"; 


int void_array[5];
int full_array[] ={ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

void setup() {

    Serial.begin(115200);
}


void loop() {

  Serial.print("var1: ");
  Serial.print(var1);
  Serial.print(" var2: ");
  Serial.print(flag);
  Serial.print(" char: ");
  Serial.print(nombre);

  int div = 10/3;

  Serial.print(" div: ");
  Serial.println(div);

  var1 = var1 + 1;

  delay(500);

  flag = !flag;


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

    int a = 10;
    int b = 20;
    int var3 = 10;
    Serial.print("funciones ");
    Serial.print(funcion(a,b));
    Serial.print("  ");
    Serial.print(funcion(10,20));
    Serial.print("  ");
    Serial.println(var2);


    delay(1000);
  


}

int funcion(int n, int m) { 
  int var2 = m+n+var3;
  n = n + 2; 
  m = m - 5; 
  return n+m; 
}
 


