/**
 * Definitions for print
 */

/**
 * @name print_at
 * 
 * Prints the specified text to the given position
 * 
 * @param text
 * @param col
 * @param row
 */
void screenprint_at(char* text, int col, int row);

/**
 * @name print
 * 
 * Prints the speficied text
 * 
 * @parma print
 */
void screenprint(char* text);

void clearscreen();

void screenbackspace();