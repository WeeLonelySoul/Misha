#include "../../libraries/common.h"


size_t STR_LEN(const char *String){
    /*
        Returns the size of String
        We init a size_t called LengthOfString, which will hold our length in the form of a int
        While there is still a character that isn't EOF or '\0', we'll add a 1 to LengthOfString
        And when it's done, we return it
    */
    size_t LengthOfString;
    for (LengthOfString = 0; String[LengthOfString]; LengthOfString++){}
    return LengthOfString;
}