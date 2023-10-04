# COECSL_FOC_Controller
Design Files and Firmware for a BLDC FOC controller that will be used to teach lab experiments in UIUC ECE Control systems labs. (In progress, Fall 2023 Semester Project)
<br>
<p>
Firmware is in progress, Hardware development will be started mid October 2023.
</p>

Firmware Outline:
-
- CPU1:
    - Controls the PWM peripherals, all PWM rise times are synced
    - Reads the  shunt resistor ADCs, ADCs are triggered in hardware after the PWM signals rise.
    - Runs the FOC Motor control

    - CPU1's CLA (Control Law Accelerator)
        - While CPU1 is running the FOC control, it's CLA is triggeres 2us before the PWM signals rise. The CLA reads the position of the encoder and has the data ready by the time the ADCs are finished sampling

- CPU2:
    - Controls the CAN and UART peripherals
    - Receives commands and places them in shared memory for CPU1 to act on. Reads output data from CPU1 from shared memory. 

<p>
<br>
<h3>Testing out the wiring and some preliminary firmware on a testbench:</h3>
</p>
<p align="center">
  <img width="50%" src="readme-visuals/coecsl-foc-controller-testbench.gif">
</p>