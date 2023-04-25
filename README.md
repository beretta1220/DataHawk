# DataHawk
Arduino Data Logger for UND Flying Team


Format: Latitude, Longitude, Time (UTC), Sound (Analog), Altitude (MSL)

1. Plug in 9V battery
2. GPS will begin blinking blue LED, indicating power and searching for signal
3. MicroSD card initializes

    a. On-board LED blinks 3 times
4. GPS will blink red LED indicating acquired position, will start reading at this point

    a. On-board LED blinks every second indicating every time data is written to the MicroSD card
    
    b. GPS should take <30s to acquire position in clear view of the sky
5. To turn off, simply unplug the 9V

    a. Power down device before removing MicroSD
    
    b. When reading card on PC, remember to always select to "eject" MicroSD before physically removing from computer
