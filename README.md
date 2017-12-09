# TheHat
A bluetooth controlled hat with NeoPixel stripes and a matrix (for two arduinos)

This project runs on two arduinos:
The first one reads the data from the software serial (in this case a HC06 bluetooth module),
controls the effects and the text on the matrix
and puts data through I²C to the second arduino.

The second arduino gets the I²C data and controls the effects on the NeoPixel-strips.

Files:

TheHatFX:
The first test of effects on the neopixels. Runs only the rainbow atm. (other effects commented out)
Mostly based on the NeoPixel library demo.

TheHatSerial:
The first test on how to control the effects over serial.
Command scheme:  "effectname,waittime,r1,g1,b1,r2,g2,b2,r3,g3,b3"

TheHatBluetooth:
Like TheHatSerial, but over a software serial that is connected to a HC06 bluetooth module.

And now the important files:

TheHatTextWireSerial:
Clunky name, but describes it well.
It's the file for the first arduino.
The command scheme is in the comments.

TheHatWireColor:
The file for the second arduino.
(can be tested with TheHatManualWire)



ToDo:
- More Comments
- More effects
- a smaller SerialReader
