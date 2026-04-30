< The following README is updated. for earlier versions please go to  Fall 2024 TIME II Software owned by former TIME II lead Nohl. More updates are yet to be done.>
This is the new repository for all the Software Related to STAC's TIME II Project.
STACLOOPNANO is a version of STACLOOP1 ported over to work with a Elegoo Nano Board. I have cleaned up the code a bit too and added some new task to fullfill within. This is the MAIN SCRIPT that the nano should be running during the experiment. If you choose to use the nano for additional electrical testing, make sure to compile and build this script on the nano before launch.

STACLOOP1 uses an STM32 Nucleo F446RE Board to Read thermoresistor values, and turn on heating pads and motors according to those values.
STACMOTORCONTROL is all code related to operating our Clinostat.
STACSERVOCONTROL is test code related to tuning and testing our servos.
STACSDCONTROL is test code related to making test writes to an SD Card.
STACHEATPADCONTROL is test code related to testing the mosfet and heatpads.
diagram.png is am image of what the electrical component will look like. R_fixed is 3300k ohms

For the people onsite, both ground rails are connected together and the negative pins on all external batteries should go to ground. do NOT connect the power rails together, or put the 4.8V nano battery in either power rail. Connect that directly to the Vin rail. Wires will have tags as to what goes where. See the Google Doc I shared regarding prelaunch setup for more information regarding how/when to give power to the payload.

To edit or make this file, we recommend using VS Code's PlatformIO Extension to write code for the STM32/Elegoo Nano. For the Nano, Arduino IDE works fine as you should be able to copy-paste the main.cpp files. You may need to manually install libraries on Arduino IDE if you do so this way, so I personally recomend setting up PlatformIO and pulling the entire folders. For more information on how to install and use PlatformIO, visit this link: 
https://platformio.org/

----------------------------------------------------------------
TODO UPDATED (4/30/2026)
1. Continue reading code until all functions can be undrestood.
2. Create a README for all .cpp files for the new-comers in the future
3. figure out the library errors on my local computer

