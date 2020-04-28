# Outside Libraries Referenced in Wave Libaries

## FatReader.cpp & FatReader.h

• string.h

• WProgram.h

## WaveHC.cpp & WaveHC.h

• avr/interrupt.h

• mcpDac.h

• string.h

# Good Functions and Where They Are Located

## FatReader.cpp

Most all of these functions seem to pull and read the directories on the
SD card, but I don't fully understand all it's using

    dirName(...);

    printEntryName(...);    

    FatReader::ls(...);

    FatReader::open(...);

    FatReader::readDir(...);

    FatReader::rewind();

readDir(dir_t, &dir) looks like it would read the directory. This should 
then give you the short names of the files.

## FatStructs.h

Defines all the different types of directory names and FAT entries

## SdInfo.h

Defines all the different states for what to do with an SD card

## SdReader.cpp & SdReader.h

Redefines all different SD states

Funtions to read and send things to Sd card

    SdReader::init(...);

## WaveHC.cpp & Wave.HC.h

Playbuffers, pauses, plays, stops, software volume control, and
formatting

    WaveHC::play();

# Things I Didn't Understand, But Now Do

uint8\_t is the same as a byte variable type, which is the same as 
an unsigned char. It is shorthand for a type of unsigned integer 
of length 8 bits, 0 to 255.

I can't find anything about wint16\_t, but uint16\_t is the same 
thing as an unsigned short, or an unsigned integer of length 16 
bits, 0 to 65535.

I think ls() does the same thing as if you type "ls" into PowerShell 
and displays a list of all the files in that folder.

# Ideas For Program 

Make an array of (char *name) from readDir (probably) called "files"

• Find out how many files are in folder

• Set that number as size of array (subtract one because array starts at 0)

• Loop through folder again and fill array with file names. for loop - buttons example

Display files[0] on LCD, using the cursor with while loop

• If move down, increment i with i++, display files[i]...

• If move up, subtract one i--, display files[i]...

• If i == max value, i = 0

• If i < 0, i = max value - 1

• If button selected, set toPlay = files[i] 

• Leave while loop, and add delay
