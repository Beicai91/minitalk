# Minitalk
Minitalk is a small client-server communication project where two programs (a client and a server) exchange messages using only UNIX signals (`SIGUSR1` and `SIGUSR2`).

## Dev features
- Signal-based communication
- Bit-level encoding
- Ascychronous signal handling (No active polling)
- Transmission pacing using small delays

## Technical notes
- The server does not poll or actively check for incoming data. Instead, it simply pauses and relies on UNIX signal mechanics: the operating system monitors events and interrupts the program whenever a signal arrives, triggering the signal handler automatically. This avoids busy loops, uses minimal CPU and lets the server process bits asynchronously as they come in.
