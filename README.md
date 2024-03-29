# COECSL_FOC_Controller
Design Files and Firmware for a BLDC FOC controller that will be used to teach lab experiments in UIUC ECE Control systems labs. (In progress, Fall 2023 Semester Project)
<br>
<br>
This project uses a dual-core Ti C2000 f28379D processor that runs at 200MHz and has two Control Law Accelerators (CLAs) which equates to having the computational power of 4 CPUs total. The processor interfaces with a DRV8353RS to commutate the motor, amplify shunt voltages, and provide fault protection.
<p>
Firmware for this project is in progress, Hardware development will be started in mid October 2023.
</p>

Firmware Outline:
-
- CPU1:
    - Controls the PWM peripherals, all PWM rise times are synced
    - Reads the  shunt resistor ADCs, ADCs are triggered in hardware after the PWM signals rise.
    - Runs the FOC Motor control

    - CPU1's CLA (Control Law Accelerator)
        - While CPU1 is running the FOC control, it's CLA is triggered 2us before the PWM signals rise. The CLA reads the position of the encoder and has the data ready by the time the ADCs are finished sampling

- CPU2:
    - Controls the CAN and UART peripherals
    - Receives commands and places them in shared memory for CPU1 to act on. Reads output data from CPU1 from shared memory. 

<p>
<br>
<h3>Testing out the wiring and some preliminary firmware on a testbench:</h3>
</p>
(If you don't see the gif here it may have been too big to load, you can find it by navigating to to readme-visuals/coecsl-foc-controller-testbench.gif)
<p align="center">
  <img width="50%" src="readme-visuals/coecsl-foc-controller-testbench.gif">
</p>
