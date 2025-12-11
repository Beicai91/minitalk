# Minitalk
Minitalk is a small client-server communication project where two programs (a client and a server) exchange messages using only UNIX signals (`SIGUSR1` and `SIGUSR2`).

## Dev features
- Signal-based communication
- Bit-level encoding and decoding
- Ascychronous signal handling (No active polling)
- Transmission pacing using small delays

## Technical notes
- The server does not poll or actively check for incoming data. Instead, it simply pauses and relies on UNIX signal mechanics: the operating system monitors events and notifys the program whenever a signal arrives, waking it up just long enough to run the signal handler. This avoids busy loops, uses minimal CPU and lets the server process bits asynchronously as they come in.
 
- Bit-level encoding and decoding <br>
The client encodes each character of a message into its 8-bit ASCII representation using bitwise operation.<br>
For example <br>
 ```
 char c = 'A'; //01000001
 (c >> 6) & 1;
 ```
 1. right-shift by 6 moves discards the lower bits until the target bit (6th bit) become LSB (least significant bit). Result: 00000001<br>
 2. mask the result with 1 to extract the LSB. If it's 0, send SIGUSR1. If it's 1, send SIGUSR2 <br>

 The server reconstructs each character bit by bit as signals arrive. It keeps a static counter that starts at 7 (the most significant bit) and decreases to 0 (the least  significant bit). Each incoming signal represents one bit of the character:<br>
 1. `SIGUSR1` → bit = 0   Nothing is added to the character.<br>
 2. `SIGUSR2` → bit = 1 The server sets the correct bit in the current character.<br>
 To set a bit 1, the server uses the expression:<br>
```
c = c | (1 << counter);
```
 This operation turns on the bit at position `counter`.<br>

 Example when SIGUSR2 arrives for MSB:<br>
```
char c = 00000000; //base from which we add up
counter = 7; //meaning that signal(SIGUSR2) arrives for MSB

1 << 7 = 10000000 //left-shift 11111111 to get 10000000
c = c | 10000000 //sets MSB of c
```
 Once all 8 bits (from bit 7 down to bit 0) have been received, the server has a complete ASCII character. It prints the character, resets the accumulator, and prepares for the next one.<br>
```
//bitwise & operator
 00000001
&11111111
----------
 00000001

//bitwise | operator
  00000000
| 10000000
----------
  10000000
```

- Bonus2 (over-engineering) VS Bonus1 (semplified)
Minitalk's English subject requires "support of Unicode characters" for bonus part, which caused over-engineering by implementing message buffer, linked list and even partial UTF-8 decoding logic.(see Bonus2)
But UTF-8 characters are composed of one or four independant bytes. **The shell, terminal emulator and system locale are already responsible for interpreting these byte sequences and rendering the corresponding characters on the screen**. So the bonus part just need to ensure **reliable byte transmission**. The client sends onebyte, wait for acknowledgement the server sends back with a signal and repeat. (See Bonus1)
