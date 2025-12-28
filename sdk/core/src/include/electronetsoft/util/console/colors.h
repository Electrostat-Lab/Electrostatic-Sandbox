#ifndef _CONSOLE_COLORS_H_
#define _CONSOLE_COLORS_H_

#define RESET   "\x1b[0m"
#define RGB(a, r, g, b) "\x1b[38;" #a ";" #r ";" #g ";" #b "m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"

#endif