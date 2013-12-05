LedcubeRX
=========

4x4x4 LED Cube driver for Arduino and 3 Shift Registers
Physically the cube is a positive anode

This driver creates a multiplexor using a timer interrupt.  So all that needs to be done is change the values in the array named matrix[].  The interrupt automatically paints the cube.

Usage:

The data for the cube is kept in matrix[level]=<16 bits of led data>

//This would turn all the LEDs off
matrix[0]=0b0000000000000000;
matrix[1]=0b0000000000000000;
matrix[2]=0b0000000000000000;
matrix[3]=0b0000000000000000;

//This would turn one LED on in the corner on level 0
matrix[0]=0b0000000000000001;



