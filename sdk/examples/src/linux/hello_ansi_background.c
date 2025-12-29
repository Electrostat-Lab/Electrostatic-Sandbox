#include <stdio.h>
#include <string.h>

/**
 * @brief Sets the background color of a string using ASCII escape sequences.
 *
 * This function takes RGB values and a string, and formats the string with
 * the specified background color using ANSI escape sequences. The resulting
 * formatted string is stored in the provided output buffer.
 *
 * @param R The red component of the background color (0-255).
 * @param G The green component of the background color (0-255).
 * @param B The blue component of the background color (0-255).
 * @param input The input string to be color-adjusted.
 * @param output The output buffer where the color-adjusted string is stored. Ensure this buffer is large enough to hold the formatted string.
 */
void set_background_color(int R, int G, int B, const char *input, char *output) {
    // Ensure the RGB values are within the valid range
    if (R < 0) R = 0; if (R > 255) R = 255;
    if (G < 0) G = 0; if (G > 255) G = 255;
    if (B < 0) B = 0; if (B > 255) B = 255;

    // Create the background color-adjusted string
    sprintf(output, "\033[48;2;%d;%d;%dm%s\033[0m", R, G, B, input);
}

int main() {
    // Example usage
    const char *text = "Hello, World!";
    char output[256]; // Ensure this buffer is large enough to hold the output

    // Set the background to a shade of blue
    set_background_color(0, 0, 255, text, output);
    printf("%s\n", output);

    // Set the background to a shade of green
    set_background_color(0, 255, 0, text, output);
    printf("%s\n", output);

    // Set the background to a shade of red
    set_background_color(255, 0, 0, text, output);
    printf("%s\n", output);

    return 0;
}