# Calculator
### It is based on microcontroller namely, ATmega328p, which is 8-bit microcontroller.

Here we tried to make a calculator which is able to perform various actions and it also support decimal numbers. We designed both hardware and software of the calculator, as both the things should be accurate and fast to provide accurate results in efficient time. It has OLED screen to show the numbers we type and to show the result. It can be implemented physically on a 10 cm by 4.2 cm, which is small comparatively to present calculators, which make it handy and easy to carry. It has total 24 buttons, out of which 10
denotes numbers “0, 1, 2, 3, 4 … 9” and one button for decimal point “.” and other for several other use, as stated.

### It has total 7 operands, which can be performed, which are –

* \+ add
* \- subtract
* X multiply
* / divide
* ^ power function
* % modulus/remainder
* = equal to

### It also has other features –

* e
  * Euler’s number, constant
  * value = 2.71828...
* π
  * Pi, constant
  * value = 3.14…
* ANS
  * previous answer
* Backspace
  * used to erase one digit/symbol
* Clear
  * used to erase full screen
* Prime check
  * used to check if a number is prime or not, if composite, smallest
    factor is returned

To supply the power, we can use battery or a power source, it can run on 7-25V DC supply and 5V DC supply (both got different pin input). It also a LED indicator to indicate that calculator started perfectly and the screen is responding, if the screen doesn’t respond the LED will not glow even if the power is supplied.
