# Li-Fi-Project
Li-Fi or Light fidelity is a wireless Communication Technology that uses the light to transmit data and information among different devices.

This is a group project for embedded systems course high-lighting the use of light-communication technology and practical applications of embedded systems.

This project is an implementation of a home protection system, where a smoke sensor detecting smoke form a fire , a magnetic sensor detecting an opened door, an ultrasonic sensor detecting movement (intrusion) and a blurtooth module are set-up and connected to a Tiva-C board.

If any signal is detected it is sent to a receiver arduino board via light communication where the information of sensors is encoded into flashes of light sent from the Tiva-C board and decodeded by the receiver Arduino board via an LDR.

A message is then displayed on an LCD connected to the Arduino board stating the type of signal (FIRE, INTROUSION, OPEN DOOR) or a combination of them, also the message is displayed on the user phone via bluetooth using a bluetooth module connected to the Tiva-C board via UART. 

