# Sloth STM32
This is the source code for Sid the sloth that is compatible with the STM32. 

## Getting started 
Make sure you have done the following to get sid to work on your STM32!  

### Add STM32 hardware support to Arduino
Arduino's compiler can compile for the STM32 as well, make sure you add the [Arduino STM32 repo](https://github.com/rogerclarkmelbourne/Arduino_STM32) in a 'hardware' folder in the directory where the Arduino IDE was installed. On OSX this is usually located at '/Users/{Username}/Documents/Arduino' but could also be in '/usr/local/arduino' or '/usr/share/arduino'. On Windows this is usually located at 'C:\Users\{Username}\Documents\Arduino' but couls also be loacted elsewhere. You most likely have to create the 'hardware' folder yourself. This folder should be located at the same level as the 'libraries' folder. 

### Add Mozzi to libraries
In case this is 

Visual representation of the folder structure you should have after adding hardware support & Mozzi: 
```
Arduino
|
-- libraries
      |
      -- Mozzi
|
-- hardware
      |
      -- Arduino_STM32
```

## More practical STM32 info
For more information on the STM32 and how to develop with this board check out the sources mentioned in the [locosorop/stm32-test](https://github.com/locosorop/stm32-test) repo. 


TODO: add general section on how to compile samples into 'binary' arrays for sounddata.h files