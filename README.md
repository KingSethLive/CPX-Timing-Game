# CPX-Timing-Game
Description/Rules:
There are 2 green pixles lit up, and 1 red pixel spinning around the circle. If you push either button and stop the red pixle inbetween the green pixels, you pass on to the next level.
Levels will progressivly get faster. If you pass a level the lights will flash green, then continue to the next level. If you lose then the lights will flash red and a tone will play, then start over at the beginning.
There will also be two modes for the user, using the switch. If the switch is in the first position. Then the sound will be on, else the sound will be off.
Inputs:
Button pin 4 and 5 have a 0-1 integer range, they will be used to stop the red pixel in its tracks by triggering an ISR.
Switch has a 0-1 integer range, it will be used to toggle the sound by triggering an ISR.
