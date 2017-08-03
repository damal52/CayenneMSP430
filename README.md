# CayenneMSP430
platform for coupling MSP430 Launchpad by TI and Cayenne Dashboard by MyDevices.com

Task: Add a button on ch25 that controls a digital IO on pin [2, 6, 24, 25, 26, 27, or 28].  These pins are available as of the last test.

In Energia Code:
1	Add pinMode(2,output) and digitalWrite(2,0) to setup function
2	Add a channelSubscribe(25) into subscibeAll function
3	Add “case 25” in callback case statement, if using ch24
o	Copy case 21 to handle command as a boolean
o	Use makeAgree(2) function to apply the cmd to pin 2

In Cayenne:
1	Add button and assign to ch25

Task: Add a slider on dashboard-ch24 that controls a PWM signal on pin [38,39,40,29, or 30].  These are available according to BoosterPack Checker

In Energia code:
1	Add pinMode(38,output) and analogWrite(38,0) to setup function
2	Add a channelSubscribe(24) into subscibeAll function
3	Add “case 24” in callback case statement, if using ch24
o	Copy case 22 to handle command as a float
o	Execute analogWrite(cmdValue,38) if using pin 38 in the case structure
	Make sure cmdValue will be an int in the bounds 0-254
In Cayenne:
1	Add slider and assign to ch24

Task: Change the frequency that RSSI is published to the cloud

In Energia code:
1	Change const long interval from 10,000 (for 10 seconds) to other value.
