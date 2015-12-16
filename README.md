# Improvaid modules
Software for the wrist, master and slave modules developed during the Living Technology Project Semester at Saxion. 

## Master
Master module is build to receive info from a remote module. The remote (wrist) module is an analogue device that doesn't use software scripts. The master module controls a motor on one of the output pins and sends messages to the slave. Input from an accelerometer is used to look if user is moving or not. 
## Slave
Slave gets input from master module and powers another motor. 

## Additional info
Tested on Arduino Uno and Nano. Uses 433MHz receiver and transmitter pair (http://www.hackerstore.nl/Artikel/99). Most of the functions used are imported from the VirtualWire library (https://www.pjrc.com/teensy/td_libs_VirtualWire.html). 

RF transmissions are based of the arduino-RFchat program (https://github.com/steefmin/arduino-RFchat).
