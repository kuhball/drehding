/*
  Test writing to the serial port and receiving the signal on the PC.

  On your PC,  open Tools > Serial Monitor to read the logs (this might
  cause an error, follow the permission setting instructions there). Make
  sure that the  Bauds are set to the same number as in the Serial.begin()
  method below.
 */

void setup() {
  Serial.begin(9600);
  Serial.println("This is the start.");  // might not appear in the monitor
}
 
void loop() {
  Serial.println("Hello World!");
  delay(1000);  // wait for a second (1000 ms)
}
