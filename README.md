# PlasmaTable
Wiring schematic and code for the CIF Plasma TV Table

Files:

CIF_table_final - final running code for the table

CIF_tablesensor_values - code that reads and reports the sensor values via serial communications

Table Wiring Diagram - self explanatory

How it works:

There are 5 LED strips all wired to the Arduino PWM pins through NPN transistors, since the Arduino cannot sink enough current to run the entire 12V ~300 mA strips. 

The Arduino reads 4 photoressitors wired to the analog in pins and if it detects a drop in voltage beyond the threshold value (coresponsding to a drop in light) on one of the photoresistors, it will flash on the nearest LED strip and gradually dim it. 

One problem with using light sensors to trigger the lights is that if the overhead lights turn off completely, the sensors would give the same readings as if someone waved their hand over the sensor. To fix this, the table will turn off all lights if one of the sensors is covered for too long (in this case it's about 5 seconds). The table will resume regular operations once light is restored.
