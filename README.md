# PlasmaTable
Wiring schematic and code for the CIF Plasma TV Table

Files:
CIF_table_final - final running code for the table
CIF_tablesensor_values - code that reads and reports the sensor values via serial communications
Table Wiring Diagram - self explanatory

How it works:
There are 5 LED strips all wired to the Arduino PWM pins through NPN transistors, since the Arduino cannot sink enough current to run the entire 12V ~300 mA strips. 
