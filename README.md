# Smart-Fire-Alarm
The Smart Fire Alarm project incorporates IOT technology to develop a fire alarm that can detect human life and alert emergency personnel. With this, the device will prioritize areas with possible signs of life and relay this information, where the authorities can better strategize a plan of attack upon arrival.

## How to upload code:
* Power wifi module thru computer
* Upload code on wifi mod
* Connect tx & rx & ground into wifi mod
* Upload code on uno
* Connect tx,rx & ground on uno
* Power uno thru external power
* Reset both uno and wifi mod
* Open serial monitor on wifi mod 

## Serial Com
_Test performed on communication between uno and wifi mod only. No sensors were involved. No ‘watchdog’ timer was involved. Watchdog timer only communicated 3 char elements and then stopped working for no apparent reason. Possible reason for this is the usage of millis() function._

Heat Sensor also uses serial communication, therefore  communication with wifi module isn’t working due to confusion on wifi modules part on which ‘line’ to read ->
**used listen with serial which directs the microcontroller to the correct pin for serial communication**


## Notes:
* Don’t use serial.print commands on the uno as it is also communicated to the wifi mod. It takes space created by the buffer and thus the important information is not communicated.
* Communication methods used above do not work when wifi mod is substituted with another arduino. Possible reason: _baud rate_
* Wifi mod might overhead, causing  malfunction on the brightness on the led and increased upload time _(not present in tests)_
* There could also be a problem with the mini white breadboard used to connect wifi mod. Large breadboard was used for the successful run. 
Possible solution for the conflicting serial communication is to create to separate class for the reading of the temperature function and that being outputted to the main uno program thru the return command.
