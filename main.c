#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 20

void calM() {
  printf("\nChild %d here. Will calculate average and highest mark.\n", getpid());

  int input, marks[8];
  int highest = 0, total = 0;
  float avg;

  printf("Enter 8 marks: \n");

  // take user input
  for (int i = 0; i < 8; i++) {
    printf("Mark %d >>", i+1);
    scanf("%d", &input);
    marks[i] = input; //store the input value into marks array

    //check highest against input and store the highest
    if (input > highest) highest = input;

    //calculate total
    total += input;
  }
  printf("\n");

  //calculate average
  avg = (float) total / 8;

  //Show the average and highest marks
  printf("Average: %f\n", avg);
  printf("Highest: %d\n", highest);

  printf("\nChild %d done execution.\n", getpid());
  exit(10);
}

void wc(char *fileName) {
  printf("\nChild %d here. Will count words in file %s\n", getpid(), fileName);

  FILE *fptr;
  char c;
  int words = 1; //Fixing off-by-one bug due to EOF
  fptr = fopen(fileName, "r"); //open file for read only

  if (fptr == NULL) {
    perror("File reading error\n");
    exit(1);
  }

  //continue loop until end of file is reached
  while ( (c = fgetc(fptr)) != EOF ) {
    if (c == ' ' || c == '\n') { //end of each word had space or newline
      printf("."); //print a dot for each word
      words++;
    }

  }

  printf("\nTotal number of words: %d\n", words);

  fclose(fptr); //close file

  printf("\nChild %d done execution.\n", getpid());
  exit(20);
}

void replaceAll(char *str, const char *oldWord, const char *newWord) {
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    // Fix: If oldWord and newWord are same it goes to infinite loop
    if (!strcmp(oldWord, newWord)) {
        return;
    }


    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Backup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word
        strcat(str, newWord);

        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}

void fileUpdate(char *fileName) {
  printf("\nChild %d here. Will update file %s\n", getpid(), fileName);

  char oldWord[100] = "execute";
  char newWord[100] = "run";
  char buffer[BUFFER_SIZE];

  char *firstText = "This is the updated version.\n";

  FILE *mainFile = fopen(fileName, "r"); //open main file for reading only
  FILE *tempFile = fopen("temp.txt", "w"); //temporary file to store main file contents

  if (mainFile == NULL || tempFile == NULL) { //exit with error if files can not be opened
    perror("File reading error\n");
    exit(1);
  }

  while ((fgets(buffer, BUFFER_SIZE, mainFile)) != NULL)
    {
        // Replace all occurrence of word from current line of mainFile
        replaceAll(buffer, oldWord, newWord);

        // After replacing write it to tempFile.
        fputs(buffer, tempFile);
    }
  fclose(mainFile);
  fclose(tempFile);

  //reopen mainFile for writing
  mainFile = fopen(fileName, "w");
  tempFile = fopen("temp.txt", "r");
  if (mainFile == NULL || tempFile == NULL) { //exit with error if files can not be opened
    perror("File reading error\n");
    exit(1);
  }

  char c;
  fprintf(mainFile, "%s", firstText); // add the first text
  while ( (c = fgetc(tempFile)) != EOF ) { //copy contents from temporary file to main file
    fprintf(mainFile, "%c", c);
  }
  fclose(mainFile);
  fclose(tempFile);

  remove("temp.txt");
  printf("\nChild %d done execution.\n", getpid());
  exit(30);
}

int main(int argc, char *argv[]) {
  int c1, c2, c3, ppid;
  int cs1, cs2, cs3;
  int wait1, wait2, wait3;
  int statusArray[3];
  ppid = getpid();
  //calM();
  //wc(argv[1]);
  //fileUpdate("new.txt");

  if ( (c1 = fork()) == 0 ) {
    calM();
  }
  if ( (c2 = fork()) == 0 ) {
    wc(argv[1]);
  }
  if ( (c3 = fork() ) == 0 ) {
    fileUpdate(argv[2]);
  }
  if ( ppid == getpid() ) {
    wait1 = wait(&cs1);
    wait2 = wait(&cs2);
    wait3 = wait(&cs3);

    printf("\nDone: child1 %d, child2 %d, child3 %d\n", c1, c2, c3);
  }


  return 0;
}
