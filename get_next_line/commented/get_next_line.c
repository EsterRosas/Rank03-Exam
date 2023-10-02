#include "get_next_line.h"

char *get_next_line(int fd)
{
    int i = 0;                      // Initialise a variable to keep track of the current position in the buffer
    int rd = 0;                     // Initialise a variable to store the result of the read operation
    char character;                 // Declare a variable to store each character read from the file
    char *buffer = malloc(100000);  // Allocate memory for the buffer with a size of 100000 characters

    if (BUFFER_SIZE <= 0)           // Check if the buffer size is less than or equal to 0
        return (NULL);              // If so, return NULL indicating an error

    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;    // Store the current character in the buffer and increment the buffer index
        if (character == '\n')      // Check if the current character is a newline character
            break;                  // If so, exit the loop
    }

    buffer[i] = '\0';               // Add a null-terminating character at the end of the buffer to indicate the
									//end of the string

    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);  // Check for error conditions: read failure, empty buffer, or last character not
									  //present and no more characters to read. Free the buffer memory and return NULL.
    return (buffer);                // Return the buffer containing the read line
}
