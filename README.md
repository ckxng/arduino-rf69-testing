# RF69 Testing

These are experiments with RF69 modules which will eventually collect data for (and automate) terrarium and greenhouse
climate control.

## 434Mhz Ham Radio (USA)

These examples use the 434 MHz RF69 module, which in the United States requires a Ham Radio license and includes various
restrictions (on power and no encryption). However, if a 915MHz module is used instead (or if the user is in Europe),
this requirement does not exist.

## hello-sender

Send data on a periodic schedule including the onboard RF69 temperature and current battery level.

## hello-receiver

Receive and acknowledge the packet from a hello-sender, and reply with RSSI, RF69 temperature, and battery level of its
own. 

## Author

Cameron King  
<http://cameronking.me>

## Copying

See LICENSE for details.
