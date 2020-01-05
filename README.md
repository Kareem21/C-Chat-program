# C-Chat-program
A TCP chat program that was written in C.

# Build instructions

Usage instructions for the TCP chat program written in C.

1 - Open up a terminal window and navigate to the folder containing the 2 .c files (client.c and server.c)

2 - Run the makefile by typing "make" 

3 - Run the server by typing ./server

4 - In another terminal window  type ./client -p {PORTNUMBERHERE} -s {valid IP here}. You can also enter the IP address first in this manner: ./client -s {valid IP here} -p {PORTNUMBERHERE}




**How to view the help message**

- In a terminal window type ./client -h

**How to quit**

Use the Ctrl C escape sequence while running server, then do the same for client.
**Note:** If you quit the server, make sure you also quit the client as it will keep running it the background if you don't. 

If you quit and run the program again, make sure to use a different port (you could also wait till it's clear) . 

**Potential problems**

Use with -p first then -s preferably, it may or may not work when you do -s and THEN -p


Line 63 in chat.c tells the server which address it's waiting on
Port is hardcoded to 3007 on line 64 in chat.c

**Guidance for this programming assignment:**

- Beej's networking guide
- Stackoverflow (the function I used for validating IP to make sure it's valid IPV4 was from a stackoverflow question)
