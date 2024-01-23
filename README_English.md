Recently, physical environmental monitoring has become essential for studying various environmental problems. The status and growth of forests is considered important for monitoring the global heat and water cycle, especially in terms of CO2 reduction through tree photosynthesis. Monitoring tree growth conditions, such as the rate of radial tree growth, could solve some environmental pollution and deforestation problems in order to prevent forest decline. The scope of this work is to implement a NB-IoT node with a sensor for measuring the diameter of trees (tree diameter) and to implement it in such a way to ensure the long-term operation of the device.  The main problem we face is the lack of information on the rate of forest growth in different geomorphological regions.By implementing a NB-IoT node we can provide the appropriate information to experts with the measurements sent by the tree meter to examine the respective areas where the tree meters have been placed. Knowing that, in an area A, the trees grow faster while in an area B the trees grow at a slower rate than in area A, we conclude that the conditions in area A are clearly better. Thus, knowing that the 'main conditions for forest growth' prevail in area A, we provide the relevant authorities with the information that area A is considered important to consider for the conditions prevailing there.





The provided Arduino code utilizes an Arduino microcontroller with an encoder sensor and a GSM/GPRS/NB-IoT module (DFRobot_SIM7000) to communicate with an MQTT broker over a mobile network. Here is a brief explanation of the code:

Encoder Interrupts:
The attachInterrupt() function is used to declare an interrupt when the state of ENCODER_PIN1 changes.
The handleEncoderChange() function is called when the encoder state changes.

Encoder Variables:
The variables counter and encoder_direction are used to track changes in the encoder's position.
SIM7000 Activation and Configuration:

In the if (encoderChanged) section, it checks if there is a change in the encoder.
If yes, the NB-IoT module (SIM7000) is activated, and the connection to the network is configured.

MQTT Broker Communication:
Subsequently, AT commands are executed to configure the MQTT broker and send data.



![image](https://github.com/eee-Andrew/Dendrometer_NB-IoT/assets/98215048/093ad6c0-08b4-4314-9bda-c4887b94e014)
![Uploading image.png…]()
![Uploading image.png…]()
![Uploading image.png…]()
![Uploading image.png…]()
![Uploading image.png…]()
![Uploading image.png…]()
![Uploading image.png…]()












Logging and Sleep:
The direction and current value of the encoder are logged.
Afterward, a command is executed to terminate the network connection, and the microcontroller is put into a low-power state using the LowPower library.
