# Drug Drone

## Project Members
Asher Shertok,
Daniel Dimitrov,
Jason Jensen,
Elliot Zimpfer

## Project Description
This is a project to have a drone carry life saving drugs to 
emergency situations. The project uses a custom built drone with 
pre-loaded GPS navigation through INAV configurator. INAV configurator 
allows to set waypoints on missions which is set to the desired drop location, 
then upon arrival a channel is triggered on the flight controller to release a
package of life saving medication. The medication is dropped in flight with a 
parachute. 

The drone also allows for manual flight through RF communication via two Arduinos.
The Arduinos are connected using 2x NRF24L01+ modules. One module is connected to a laptop via serial
communication. Input is detected by keyboard movement through a python script run locally. This data is then interpreted
and sent in radio waves to the drone. The drone Arduino receives the data and is directly connected to the drone's flight
controller to navigate the drone.
