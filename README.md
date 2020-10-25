# C_Unix-Shell_Signaling_IO-Redirect
The program creates a Unix Shell Environment with Signal Handling for CTRL + C, CTRL + / and CTRL + Z. It also applies I/O Redirection.

I/O Redirection has bugs.

The Program creates an Unix Shell Program that accepts multiple commands as indicated in the Project Instructions, some of the built-in commands are as follows:
ls - lists all current files in the directory.
pwd - prints the full pathname of the current directory.
ps - prints information on curent running processes. 
ls +arguments - depending on the argument sent, the program will display different outputs. 
sleep - the program will wait 5 seconds before continuing with its process.
grep main +cppFileName - the program will search for a string of characters in the specified file.
exit - will end the program and display if other methods such as: CTRL+C, CTRL+Z, CTRL+\ were used and how many times. 
r n - where n is a number, will command the program to execute a previous command.
r - will command the program to execute the previous command.

The program compiles and runs efficiently with small bugs such as:
- r n commmands sometimes cause the program to crash and not complete the cycle.  
- r command sometimes causes the program to crash an not complete the cycle.  
- I/O Redirection may cause program to crash.  
   
Sources Used Included Below -  
Example codes provided by Dr. Kar were also used as reference. -  
Shell Structure:
https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html

Signal Handling:
http://www.yolinux.com/TUTORIALS/C++Signals.html
https://www.tutorialspoint.com/cplusplus/cpp_signal_handling.htm

I/O Redirect:
https://www.geeksforgeeks.org/io-redirection-c/
https://www.gnu.org/software/libc/manual/html_node/Executing-a-File.html
http://cplusplus.com/forum/general/157390/

Errors:
https://stackoverflow.com/questions/33638706/cinitializing-argument-1-of-int-agenttun-allocchar-int-fpermissive
https://stackoverflow.com/questions/24135424/strcpy-causes-invalid-conversion-from-const-char-to-char-fpermissive
https://stackoverflow.com/questions/2245193/why-does-open-create-my-file-with-the-wrong-permissions
