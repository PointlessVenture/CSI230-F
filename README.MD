# CSI230 Final Project
# Aiden Tracy
This program is a D&D Enemy manager, for use as a Dungeon Master (DM) for a game.
As a DM, managing a large number of enemies is required while the other players are fighting them, so this program will automate much of the process.
 
A file which contains a list of files containing stat data to read must be provided as an argument to run the program. 
The program will take the stat data from the files, parse it into usable data using a custom library, and then provide the user 
with an interface in which they can interact with the enemies they have created, making them roll dice as needed by the game, 
modifying their health, giving them names, et cetera.

The library that I created to parse the data, 
allowing the program to turn a rip of a D&D stat block into a machine readable format. 

An example of a stat block is shown in assets/acolyte.txt. 

To Use the file run the "make" command in the location of the makefile.
You can also run "make install" to make it available anywhere. (Requires root access.)

To run the file, execute dnddriver (which will be placed in /bin if you ran "make", or available anywhere if you ran "make install".)

usage: dnddriver -i (encounter file)
(for an example of an encounter file, see assets/encounter.txt)

to uninstall, run "make clean" and/or "sudo make remove" in the makefile directory.

# Demo Video
https://youtu.be/Pz0GfZihBLs
