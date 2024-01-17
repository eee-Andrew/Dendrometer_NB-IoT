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

Logging and Sleep:
The direction and current value of the encoder are logged.
Afterward, a command is executed to terminate the network connection, and the microcontroller is put into a low-power state using the LowPower library.
