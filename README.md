# Dialogue Formatter for the ParseUltra Format

Purpose: Convert a dialogue file as much as possible to the ParseUltra dialogue format, with filler text to be replaced after.

The program has been compiled to the executable named _format_. Run the program with the command `./format [filename.txt]`. The program will create a new file named _[filename]_formatted.txt_.

Assumptions:
* The input file name is assumed to be a .txt file
* Every line in the file is assumed to either be empty, or be in the format "SPEAKER: line"
    * Lines not in the specified format will not be formatted correctly and will likely be assumed to be part of the next line's speaker name
    * These lines will need to will to be manually corrected

Info on Placeholders:
* All positions are unknown and are filled with "filler_pos" except for Midoriya's positions, which are assumed to be front left
* All expressions are unknown and are filled with "filler_exp"
* Second characters in dialogue frames are automatically added, with the speaker name "filler_char"
