#ifndef COLORS_H
#define COLORS_H

#include <string>

/* Bad workaround making it static bc each file
 * that includes this gets it's own copy of the
 * array. But I just want to declare it once.
 * It's just a lookup table anyway for printing.
 */
static std::string COLORS[32] = {
    "", /* No color */
    "Red",
    "Green",
    "Blue",
    "Yellow",
    "Orange",
    "Purple",
    "Pink",
    "Brown",
    "Gray",
    "Black",
    "White",
    "Cyan",
    "Magenta",
    "Lime",
    "Teal",
    "Olive",
    "Navy",
    "Maroon",
    "Aqua",
    "Fuchsia",
    "Silver",
    "Gray",
    "Lavender",
    "Coral",
    "Turquoise",
    "Indigo",
    "Violet",
    "Gold",
    "Silver",
    "Beige",
    "Khaki"
};

#endif
