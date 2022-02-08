// <- this is a comment "line" in c
/* <- comment block in c
 *  
 */
// Every line in C needs to have a semicolon after (;). Only functions, conditionals, and loops do not need semicolons.

//Anything within the curly braces are ran only once.
void setup() {
  // Begins communication on the Serial port with 9600 Bits/sec
  Serial.begin(9600);
}

// This creates memory space for variables.
// The size of the memory space is determined by the type
// int are integers, floats are decimal numbers
// We will be using mostly ints and floats, but if you want to know about more of c data types follow this link:https://en.wikipedia.org/wiki/C_data_types
int integer;
float decimal;
int i;
void loop() {

  // Conditionals in C start with if (condition)
  // Comparison between any two numbers (ints, or floats) can be done with =, >, <, etc,.
  // Any conditonal needs curly brackets around what code is supposed to run during that condition.
  if (integer == 1){
    Serial.println("Integer is 1");
    integer = 10;
  } else if (integer == 10){
    Serial.println("Integer is 10");
    integer = 0;
  }
  else {
    Serial.println("Integer is neither 10 or 1");
    integer = 1;
  }
  int i;

  //For loops in C start with this statement (starting value; continue condition, increment)
  for(i=0; 0<5; i++){
    func1(i);
  }

  // Delay stops any code from running for a certain amount of time
  // measured in milliseconds
  delay(1000);
}

// functions are defined by a return type
// With this function nothing is returned so it is a void type
// Any input values also need a specified data type
void func1(int j){
  int i;
  for (i=j; i<10; i++){
    if (i == 1){
      // continue passes over the current loop and starts on the next loop iteration.
      continue;
    }
    if (i == 5){
      // Break exits the loop.
      break;
    }
    Serial.println(i);
  } 
}
