#include <stdio.h>
#include <string.h>

/**
 * @brief Sets the font style of a string using ASCII escape sequences.
 *
 * This function takes a font style and a string, and formats the string with
 * the specified font style using ANSI escape sequences. The resulting formatted
 * string is stored in the provided output buffer.
 *
 * @param style The font style to be applied. Possible values:
 *              0 - Reset
 *              1 - Bold
 *              3 - Italic
 *              4 - Underline
 * @param input The input string to be styled.
 * @param output The output buffer where the styled string is stored. Ensure this buffer is large enough to hold the formatted string.
 */
void set_font_style(int style, const char *input, char *output) {
    // Validate the font style
    if (style != 0 && style != 1 && style != 3 && style != 4) {
        style = 0; // Default to reset if the style is invalid
    }

    // Create the font-styled string
    sprintf(output, "\033[%dm%s\033[0m", style, input);
}

int main() {
    // Example usage
    const char *text = "Hello, World!";
    char output[256]; // Ensure this buffer is large enough to hold the output

    // Set the text to bold
    set_font_style(1, text, output);
    printf("%s\n", output);

    // Set the text to italic
    set_font_style(3, text, output);
    printf("%s\n", output);

    // Set the text to underline
    set_font_style(4, text, output);
    printf("%s\n", output);

    // Reset the text style
    set_font_style(0, text, output);
    printf("%s\n", output);

    return 0;
}