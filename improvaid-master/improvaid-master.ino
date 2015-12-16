#include <VirtualWire.h> // Download at https://www.pjrc.com/teensy/td_libs_VirtualWire.html

//left-right oscillation functionality
double part=0.5;
int interval=500;
const int interval0=300;
const int interval1=500;
const int interval2=600;
const int interval3=650;
const double part0=0.7;
const double part1=0.3;
const double part2=0.1;
int power = 0;

double testtime=part*interval;
unsigned long previousMillis = 0;
int counter=0;

//chat functionality
const int transmit_pin = 12;                           // connect to transmitter
const int receive_pin = 8;                             // connect to receiver
const int transmit_en_pin = 2;                         // don't know if needed, but works
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
int incomingByte = 0;

//LED functions
const int led_pin1=3;
const int led_pin2=4;
const int led_pin3=5;
const int led_pin4=6;
const int led_pin5=7;

void setup(){
    //enable chat
        Serial.begin(9600);                             // Start serial monitor connection
        Serial.println(".__                                         .__    .___\n|__| _____ _____________  _______  _______  |__| __| _/\n|  |/     \\\\____ \\_  __ \\/  _ \\  \\/ /\\__  \\ |  |/ __ | \n|  |  Y Y  \\  |_> >  | \\(  <_> )   /  / __ \\|  / /_/ | \n|__|__|_|  /   __/|__|   \\____/ \\_/  (____  /__\\____ | \n         \\/|__|                           \\/        \\/ \n\n  _____ _____    _______/  |_  ___________\n /     \\\\__  \\  /  ___/\\   __\\/ __ \\_  __ \\\n|  Y Y  \\/ __ \\_\\___ \\  |  | \\  ___/|  | \\/\n|__|_|  (____  /____  > |__|  \\___  >__|   \n      \\/     \\/     \\/            \\/       \n                   .___    .__          \n  _____   ____   __| _/_ __|  |   ____  \n /     \\ /  _ \\ / __ |  |  \\  | _/ __ \\ \n|  Y Y  (  <_> ) /_/ |  |  /  |_\\  ___/ \n|__|_|  /\\____/\\____ |____/|____/\\___  >\n      \\/            \\/               \\/ ");
        Serial.println("Initializing...");
        vw_set_tx_pin(transmit_pin);
        vw_set_rx_pin(receive_pin);
        vw_set_ptt_pin(transmit_en_pin);
        vw_set_ptt_inverted(true);                      // Required for DR3100
        vw_setup(2000);                                 // Bits per sec
        vw_rx_start();                                  // Start receiver
        
    //enable LED's
        Serial.println("Resetting outputs...");
        pinMode(led_pin1,OUTPUT);
        pinMode(led_pin2,OUTPUT);
        pinMode(led_pin3,OUTPUT);
        pinMode(led_pin4,OUTPUT);
        pinMode(led_pin5,OUTPUT);
        reset();
        Serial.println("Ready");
}
void reset() {
    for (int thisPin = led_pin1; thisPin <= led_pin5; thisPin++) {
        digitalWrite(thisPin, LOW);
    }
    sendchar('+');
    part = part0;
    interval = interval0;
}
void setled(char a){
    switch(a){                                    //controls for changing LED status from remote
        case '1':
            digitalWrite(led_pin1,HIGH);
        break;
        case '2':
            digitalWrite(led_pin2,HIGH);
        break;
        case '3':
            digitalWrite(led_pin3,HIGH);
        break;
        case '4':
            digitalWrite(led_pin4,HIGH);
        break;
        case '5':
            digitalWrite(led_pin5,HIGH);
        break;
        case 'p': //cycle through values for part
            if(part == part0){
              part = part1;
            }else if(part == part1){
              part = part2;
            }else if(part == part2){
              part = part0;
            }else{
              part = part0;
            }
        break;
        case 'i': //cycle through values for interval
            if(interval == interval0){
              interval = interval1;
            }else if(interval == interval1){
              interval = interval2;
            }else if(interval ==interval2){
              interval = interval3;
            }else if(interval == interval3){
              interval = interval0;
            }else{
              interval = interval0;
            }
        break;
        case '.':
            power=1;
        break;
        case ',':
            power=0;
        case '`':
            reset();
        break;
        case '+':
            sendchar('+');
        break;
        case 'c':
            sendchar('c');
        break;
    }
}

int updatetime(double part, int interval, int counter){  //sets the time until next blink event
    if(counter%2==0){
        testtime = part*interval;
    }else if(counter%2==1){
        testtime = (1-part)*interval;
    }else{
        testtime=interval;
    }
    return testtime;
}

int ledblink(int counter){                                //blink events
    if(counter==0){
        digitalWrite(led_pin1, HIGH);
        counter++;
    }else if(counter==1){
        digitalWrite(led_pin1, LOW);
        counter++;
    }else if(counter==2){
        digitalWrite(led_pin5, HIGH);
        counter++;
        sendchar('c');
    }else if(counter==3){
        digitalWrite(led_pin5, LOW);
        counter = 0;
        sendchar('+');
    }else{
        counter = 0;
        digitalWrite(led_pin1,LOW);
        digitalWrite(led_pin5,LOW);
    }
    return counter;
}
void sendchar(char message){                                //sends a character 
    char msg[1]={message};
    vw_send((uint8_t *)msg,1);
    vw_wait_tx();
    Serial.print("Send: ");
    Serial.print(message);
    Serial.println("");
}
void recvchar(char message){                                //receives a character from serial monitor or RFreceiver
    Serial.print("Rec : ");
    Serial.write(message);
    Serial.println("");
    setled(message);
}
char msg[1] = {};
void loop() {
    // Send the serial input
    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        if(incomingByte != '\n' && incomingByte != 13){
            recvchar(incomingByte);
        }
    }
    // Read the received data
    vw_wait_rx_max(100); //delay needed, otherwise to little time to receive 
    if (vw_get_message(buf, &buflen)){
        recvchar(buf[0]);
    }
    // change output when time is exceeded
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= testtime && power==1){
        previousMillis = currentMillis;
        testtime=updatetime(part,interval,counter);
        counter = ledblink(counter);
    }
}

