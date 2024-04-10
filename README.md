# Flash handling library for STM32
Library to manipulate float, integer, small integer and string data in flash for STM32L4 series. Variables are converted to char and saved in flash as string with comma divider.

The best way to use this is to clone it into your STM32CubeIDE workspace folder on your computer, in projects, and import the project in your STM32CubeIDE software. 

Also, check if all the C libraries are installed. Make sure the IDE is correcty installed and, before you compile the code into your STM32 board, MAKE SURE your MCU matches the model used for this project, in this case, STM32L476RG.

In case the MCU doesn't, match, the codes can still be used, so you can use the header and source files to only get the codes you want to use, and change as you'd like.
