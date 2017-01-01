# Take-an-Action
“Take an Action” Game

• Design an alarm in the Lost, using MPU6050, HMC 5883L, speaker, RGB LED:
– Show the counting down in the serial monitor
– The cycle is 5 sec. Divide the cycle into two parts:
a) Safe (3 sec), and b) Alarm (2 sec).
– Use RGB LED to show Green and Red for the a)
Safe, and b) Alarm, respectively.
– Use the speaker to remind (without delay() see Chapter 3)
• Safe: no sound
• Alarm: two beeps per second

• Theplayerisgivenanactiontaskineachcycle.The tasks are selected randomly. Please use Serial Monitor to remind the player the selected task in each cycle. Possible tasks:
– Shaking (MPU 6050)
– Heading to North (HMC 5883L)
– Rotate more than 20 degrees of HMC 5883L – Turn the bottom of MPU 6050 up
• Iftheplayersuccessfullyfinishesatask,hecan proceed to the next cycle. Otherwise, the game ends and the speaker beeps continuously.
