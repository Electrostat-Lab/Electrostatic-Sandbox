#include <stdio.h>
#include <string.h>

/**
 * @brief Adjusts the RGBA color of a string using ASCII escape sequences.
 *
 * This function takes RGBA values and a string, and formats the string with
 * the specified color using ANSI escape sequences. The resulting formatted
 * string is stored in the provided output buffer.
 *
 * @param R The red component of the color (0-255).
 * @param G The green component of the color (0-255).
 * @param B The blue component of the color (0-255).
 * @param A The alpha component of the color (0-255). This value is currently not used in the escape sequence.
 * @param input The input string to be color adjusted.
 * @param output The output buffer where the color-adjusted string is stored. Ensure this buffer is large enough to hold the formatted string.
 */
void set_font_color(int R, int G, int B, int A, const char *input, char *output) {
    // Ensure the RGBA values are within the valid range
    if (R < 0) R = 0; if (R > 255) R = 255;
    if (G < 0) G = 0; if (G > 255) G = 255;
    if (B < 0) B = 0; if (B > 255) B = 255;
    if (A < 0) A = 0; if (A > 255) A = 255;

    // Calculate the opacity as a percentage (not used in escape sequences)
    float opacity = A / 255.0;

    // Create the color-adjusted string
    sprintf(output, "\033[38;2;%d;%d;%dm%s\033[0m", R, G, B, input);
}

int main() {
    // Example usage
    const char *text = "Hello, World!";
    int R = 255, G = 100, B = 50, A = 128; // Semi-transparent orange color
    char output[256]; // Ensure this buffer is large enough to hold the output

    set_font_color(R, G, B, A, text, output);
    printf("%s\n", output); // For demonstration purposes

    return 0;
}