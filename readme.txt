1. 

(a) Name: Debashish Sarkar Durjoy
    ID: 19902470

(b) cc main.c -o main && ./main afile-21.txt afile-21.txt

(c) main(): creates 3 child process using the fork() system call.
	    Pseudo Code:
	    if (current process is child_1 process) then execute calM() function.
	    if (current process is child_2 process) then execute wc() and pass command 		    					    line argument 1.
	    if (current process is child_3 process) then execute fileUpdate() function.
						    and pass command line argument 2.
	    if (current process is parent process) then wait for the child processes to
						    finish execution.

    calM(): This function takes in 8 input from the keyboard and calculates the highest 	    and average marks. This is the slowest process as it requires user input. 
	    Pseudo Code:
	    initialise total as 0 and highest as 0
		
	    loop 8 times:
	      get user input
	      calculate total by adding previous total with new input 
	      (total = total + input)
	      if (input is larger than highest) then assign input into highest 
		(highest = input)
	    endloop

	    calculate average (average = total / 8)
	    print the average and highest

    wc(): This function counts the number of words in a text file.
	  Pseudo Code:
	  initialise word as the counter variable with initial value 1 (to avoid OBB)
	  open file fptr for reading
	  loop until End_Of_File:
	   read each character c from the file 
	   if (c is space ' ' or newline '\n' character) then increment word;
	  end loop

  fileUpdate(): This function copies the contents from original file to a temporary 	file. The execution of this function is described in steps below:
	1. Open mainFile in read mode and tempFile in write mode.
	2. Replace the "execute" string with "run" string in mainFile (using the 	   replaceAll function()) and then copy the contents into the tempFile.
	3. Close both the files.
	4. Reopen mainFile but now in write 'w' mode and tempFile in read 'r' mode.
	5. At first write the "This is updated version." into the mainFile (so that it 
	   is at the top of the file instead of being at the bottom).
	6. Then copy all the contents from the tempFile to the mainFile.
	7. Finally, close both the files.

  replaceAll(): This function takes in three arguments buffer, oldWord and newWord.
	It replaces the oldWord in a text file with the newWord. And buffer contains 	characters of length BUFFER_SIZE.
	Pseudo Code:
	loop (repeat until all occurrences are replaced):
		backup current line
		get index of current found word
		terminate str after word found index
		concatenate str with new word
		concatenate str with remaining words after oldWord found index
	loop end

 
(d) Test plan: Check for syntax errors and logical errors within each of the functions.
	I entered different marks to test if child 1 works properly as intended.
	And I inserted different strings into the afile-21.txt to check if the wc() and 	fileUpdate() functions are working properly. 
    
    Test run: 
	- Since the program complies without any errors, there are no syntax errors.

	To test for logical errors I have done the following:
	- I have entered different sets of marks to test calM() function and it returns 	  the desired output (the correct average and highest mark).
	- To check wc() function I have entered 9 words into the text file and function 	  successfully returns 9.
	- To check fileUpdate() I have entered "exercise" (similar to execute) into the    
          text file and the function does not replace "exercise", it only replaces  
          "execute", just as intended.

(e) The limitations in each of the functions are described below:
	- calM(): It only takes integer as input. Therefore, if the user enters any  
	floating point number then it will not work.
	- wc(): Because this function counts the number of words based on the number of
	space characters or newline characters, if the words in the text file is comma 
	separated or contains double space between two words, it will calculate an 
	incorrect number of words.
	- fileUpdate(): If there is any error opening any of the mainFile or tempFile
	using the fopen() function. The entire function will stop executing.   
		 
	      