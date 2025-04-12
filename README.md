# FanControl
Simple script for controlling your system fans

Currently only works for nvidia gpu.

To install just clone the repo and compile the code:
<code> g++ -O3 -o fanControl main.cpp</code>

Best used with tmux and running <code> sudo ./fanControl </code>

<br>
<h2> Setting custom fan curve </h2>
To make your own custom fan curve just edit "TEMP_THRESHOLD" and "FAN_SPEED".

<b>Example:</b>
<code>  TEMP_THRESHOLD[] = {30, 50, 80}; 
FAN_SPEEd[] = {0, 30, 50, 80};            
</code>

When the GPU temperature is below 30°C, the fans will not spin (0% speed).
Once the temperature reaches 30°C or higher, the fans will spin at 30% speed.
When the temperature reaches 50°C or higher, the fan speed increases to 50%.
At 80°C or higher, the fans will spin at speed (80%).

