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
int accmap(int pin, int zpin){
  if(pin==zpin){
      return map(analogRead(pin),0,600,-1000,1000);
  }else{
      return map(analogRead(pin),0,720,-1000,1000);
  }
}
  

void accread(int xpin, int ypin, int zpin, int calibx, int caliby, int calibz) {
  // print the sensor values:
  Serial.print(accmap(xpin,zpin)-calibx);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(accmap(ypin,zpin)-caliby);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(accmap(zpin,zpin)-calibz);
  Serial.println();
  // delay before next reading:
}
int accvalue(int xpin, int ypin, int zpin, int calibx, int caliby, int calibz){
  int x=accmap(xpin,zpin)-calibx;
  int y=accmap(ypin,zpin)-caliby;
  int z=accmap(zpin,zpin)-calibz;
  int value = round(sqrt(x^2+y^2+z^2));

  return value;
}

