# GSE-MVP

The purpose of this firmware is to provide an interface between TCP packets and the activation of various components responsible for the combustion system of the rocket.

The ESP32-PoE-ISO is used, with an onboard Ethernet port. The Ethernet port allows communication through the WiFi bridge using TCP. The WiFi bridge receives packets from Ground Control.

Based on the packets received the program will activate/deactivate various pins/ports.

# Connected pins:
* N2O Fill:
    This activates the solenoid that releases N2O into the combustion chamber.

* Purge:
    This activates the solenoids that empty the entire combustion system.

* O2 Fill:
    This activates the solenoid that releases O2 into the combustion chamber.

* Fire:
    This activates the igniter, where activating this pin allows 12V to flow through toward the igniter.

* Fire PWM:
    The PWM signal is to activate the sparker.

# States
The possible states of the control pendant are:
## System Standby Mode
### Pin States:
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                LOW Pin      (Solenoid Open)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Fill Mode
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                LOW Pin      (Solenoid Open)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Fill->N2O
* N2O Fill             HIGH Pin     (Solenoid Open)
* Purge                HIGH Pin     (Solenoid Closed)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Fill->Purge
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                LOW Pin      (Solenoid Open)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Launch Mode
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                HIGH Pin     (Solenoid Closed)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Launch->O2
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                HIGH Pin     (Solenoid Closed)
* O2 Fill              HIGH Pin     (Solenoid Open)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

## Launch->O2->Fire
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                HIGH Pin     (Solenoid Closed)
* O2 Fill              HIGH Pin     (Solenoid OPEN)
* Fire                 HIGH Pin     (Ignition 12V Power On)
* Fire PWM             HIGH Pin     (Ignition Sparker On)

## Estop
* N2O Fill             LOW Pin      (Solenoid Closed)
* Purge                LOW Pin      (Solenoid Open)
* O2 Fill              LOW Pin      (Solenoid Closed)
* Fire                 LOW Pin      (Ignition 12V Power Off)
* Fire PWM             LOW Pin      (Ignition Sparker Off)

# Additions for future:
* Shift bits from incoming packets from GCS, this allows upgradability. Currently not done given state machine has all possible states accounted for. If individual bits are shifted then state machine can be more modular.s
