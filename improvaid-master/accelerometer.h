void accinit(int groundpin,int powerpin) {
  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

float accmap(int pin, int xpin, int ypin, int zpin){
  int samples = 50;
  float value = 0;
  for(int i=1; i<=samples; i++){
    value = value + analogRead(pin);
  }
  value = value/samples;
  if(pin==xpin){ 
      return map(value,334,400,0,-100);
  }
  if(pin==ypin){
      return map(value,330,262,0,100);
  }
  if(pin==zpin){
      return map(value,336,272,0,-100);
  }
  
}

void accread(int xpin, int ypin, int zpin) {
  float x=accmap(xpin,xpin,ypin,zpin);
  float y=accmap(ypin,xpin,ypin,zpin);
  float z=accmap(zpin,xpin,ypin,zpin);
  float xyz=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
  Serial.print(xyz);
  Serial.println();
}

float accvalue(int xpin, int ypin, int zpin, int calibxyz){
    float x=accmap(xpin,xpin,ypin,zpin);
    float y=accmap(ypin,xpin,ypin,zpin);
    float z=accmap(zpin,xpin,ypin,zpin);
    float value = round(sqrt(pow(x,2)+pow(y,2)+pow(z,2))-calibxyz);
    value = abs(value);
  return value;
}

