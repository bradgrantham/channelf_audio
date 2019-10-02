default: bok.wav

bok.wav: bok.u8
	sox -c 1 -r 22050 -t u8 bok.u8 bok.wav

bok.u8: volts_to_u8
	volts_to_u8 < data-20191002-1021.circuitjs.txt > bok.u8 

volts_to_u8: volts_to_u8.cpp
	c++ --std=c++17    volts_to_u8.cpp   -o volts_to_u8
