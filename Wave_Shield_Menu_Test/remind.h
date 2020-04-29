/*
 * *******************************************
 * 
 *  Remind Library for Wave Shield Functions
 * 
 * *******************************************
 */


// This is the format needed for the header file
#ifndef REMIND_H

#define REMIND_H

// Declare functions that will be defined in the .cpp file

FatReader waveSetup(void);

// Plays a full file from beginning to end with no pause.
void playcomplete(char *name);

void playfile(char *name);

uint32_t getFiles(FatReader &dir);



#endif /* REMIND_H */
