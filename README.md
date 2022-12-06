# target-LedOn
This project uses STM32CubeIDE and it's a program created to practice my C habilities during the course 'Microcontroller Embedded C Programming: Absolute Beginners' from FastBit Embedded Brain Academy.

## Section 18: Embedded C coding exercise for LED 
Hardware = NUCLEO-F401RE (differs from the used in course)

First, let's find an avaible LED to control:

![image](https://user-images.githubusercontent.com/58916022/205903747-0cd3d520-9a60-40e7-b996-7cec842a56ff.png)

Just checked the board and there is a LD2, and jumpers SB21 and SB42 are connected (by a 0R 0805 resistor). This means, that to control this LED, PA5 must be used. This means, GPIO A (port A) and pin 5.

For the firmware, we have 3 important steps: Configure to clock to control GPIOA, configure Mode for pin 5 to work as output, and finally control the signal of the output (0 or 1). 

For the clock, we need to find the clock path for the GPIOA. This information is available in the datasheet of STM32F401x. See:

![image](https://user-images.githubusercontent.com/58916022/205906338-cb787377-a7aa-4c52-9ea4-98abc0050dec.png)

Now, we need to find the register address and the bits that we need to set. For that, I used the RM0368 Reference Manual (STM32F401x). Check that the section that displays the available configurations for the RCC AHB1 register doesn't show the address: 

![image](https://user-images.githubusercontent.com/58916022/205906626-12e2b508-4aaf-482f-b9c7-0aba122b33a7.png)

To find the register address, we must sum the 'Address offset' of 0x30 to the initial register boundary addresses, given in the Memory map section of the RM0368 Reference Manual (STM32F401x). Check the ones that we will use:

![image](https://user-images.githubusercontent.com/58916022/205908640-22c4d0bb-45d5-48bb-b359-4daacd34bffe.png)

So, we are using as register address: 0x4002 3800 + 0x30 = 0x4002 3830. Basically, the lines in code that accomplish this mission are:

![image](https://user-images.githubusercontent.com/58916022/205909045-a3740fad-dcce-4038-968c-b04a4a9a35cb.png)

Now, we can go to the second step of programming the firmware. Setting the pin 5 as output in the mode register.

![image](https://user-images.githubusercontent.com/58916022/205909319-87f3f950-da3c-4081-b751-32240c649e96.png)

Let's just clear the bits from MODER5 (10 and 11) of the register GPIOA_MODER. To find the register address, I summed the Address offset to the GPIOA initial boundary address. Being 0x4000 0000 + 0x00 (offset) = 0x4000 0000.
Then, I set only the bit 10 of the register, leaving the MODER5 as 01: General purpose output mode. The lines in code that accomplishes this function are:

![image](https://user-images.githubusercontent.com/58916022/205910254-9dd361bd-2f2e-493c-a212-b69baf899854.png)

And finally the third step, setting the pin 5 of port A. The register address that control the pin's output is found by summing the Address offset of 0x14 (from GPIOx_ODR) to the inital boundary value of the memory map for GPIOA. In that case we have 0x40020000 + 0x14 = 0x40020014. 

![image](https://user-images.githubusercontent.com/58916022/205910541-a9d26f66-e7db-4636-abc3-6d4279a4bca5.png)

The code lines for this are:

![image](https://user-images.githubusercontent.com/58916022/205911081-691d7918-bdc8-4899-8749-5171d90322b2.png)

As an option, the following code was written but using the bitwise shift operator.

![image](https://user-images.githubusercontent.com/58916022/205933683-07ed8f54-03d6-4690-91e6-2f4b955891ef.png)

## Now, let's debug and test this code.

Final code:

![image](https://user-images.githubusercontent.com/58916022/205911253-215ace9e-2e98-4a34-8f39-0eb4ac614442.png)

To visualize the register addresses, we need to go in Window -> Show View -> SFRs.

![image](https://user-images.githubusercontent.com/58916022/205911423-3ef143e0-5777-4f59-9bc8-d30ff2305ff2.png)

We can reset application to garante that it is in the begin (I), then we can control and follow the instructions by going step by step (II). Just after it passes by the 21 line (and stops at line 26), it is possible to see that the the register RCC - AHB1ENR - GPIOAEN was modified. 

![image](https://user-images.githubusercontent.com/58916022/205911635-ae719b75-8b69-487e-9b6e-d1e7eee8324b.png)

Two more steps, passing througt lines 26 and 29 (stopped at line 33), we have cleared and set the register MODER - MODER5.

![image](https://user-images.githubusercontent.com/58916022/205912280-ad175fbb-7919-41dc-a25a-1a2a2c1f1eac.png)

And finally, the line that is responsible for lighting the LD2. Line 33:

![image](https://user-images.githubusercontent.com/58916022/205912503-2c22c8ec-0d36-4c0b-9d73-c84a98b6dad8.png)

## Final result

![image](https://user-images.githubusercontent.com/58916022/205913039-99bc36b7-4fa2-4432-bb78-7d6304b3fcb7.png)








