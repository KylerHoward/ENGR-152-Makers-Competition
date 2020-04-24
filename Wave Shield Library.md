# Outside Libraries Referenced in Wave Libaries

alt 7 = • alt 9 = ○

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

# Still do not understand

What does uint8\_t or wint16\_t mean? 

What is ls()
