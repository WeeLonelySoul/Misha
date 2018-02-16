#include "../../libraries/common.h"



void APPEND(char String1[], char CharacterToAdd){
    /* Adds CharacterToAdd to the end of String1 */
    int STRING_LENGTH = STR_LEN(String1);
    String1[STRING_LENGTH] = CharacterToAdd; /* Every strings ends in '\0' indicating that it's finished, so that's why replace it here */
    String1[STRING_LENGTH+1] = '\0'; /* And then we re-add it here to indicate the new stop */
}