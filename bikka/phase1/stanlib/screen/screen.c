#include "screen.h"
#include "../common/common.h"

void SayChar(char CharacterToPrint, int Col, int Row, char AttributeByte){
    unsigned char *VidMem = (unsigned char *) VIDEO_ADDRESS;

    if (!AttributeByte){
        // Failsafe if SayChar was not called with an attributebyte
        AttributeByte = WHITE_ON_BLACK;
    }

    int offset;

    if (Col >= 0 && Row >= 0){
        offset = GetScreenOffset(Col,Row);
    }else{
        offset = GetCursor();
    }
    if (CharacterToPrint == '\n'){
        int Rows = offset / (2 * MAX_COLS);
        offset = GetScreenOffset(79, Rows);
    } else {
        VidMem[offset] = CharacterToPrint;
        VidMem[offset+1] = AttributeByte;
    }
    /* Update the offset to the next character cell
       Which is two bytes ahead of the current cell */
    offset += 2;
    offset = HandleScrolling(offset);
    /* Make scrolling adjustement for when we reach
        the bottom of the screen */
    SetCursor(offset);
}

int GetScreenOffset(int Col, int Row){
    return ((Row * MAX_COLS) + Col) * 2;
}

int GetCursor(){
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset*2;
}

int SetCursor(int offset){
    offset /= 2;
    
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, offset);
}

void SayAt(char* MessageToSay, int Col, int Row){
    if (Col >= 0 && Row >= 0){
        SetCursor(GetScreenOffset(Col, Row));
    }
    int i = 0;
    while(MessageToSay[i] != '\0'){
        SayChar(MessageToSay[i++], Col, Row, WHITE_ON_BLACK);
    }
}

void Say(const char *MessageToSay){
    SayAt(MessageToSay, -1, -1);
}

void ClearScreen(){
    int Row = 0;
    int Col = 0;
    for (Row = 0; Row < MAX_ROWS; Row++){
        for (Col = 0; Col < MAX_COLS; Col++){
            SayChar(' ', Col, Row, WHITE_ON_BLACK);
        }
    }
    SetCursor(GetScreenOffset(0, 0));
}

int HandleScrolling(int offset){
    int CursorOffset = offset;
    int i;
    if (CursorOffset < (MAX_ROWS*MAX_COLS*2)){
        return CursorOffset;
    }

    for (i=1; i < MAX_ROWS; i++){
        MemoryCopy(GetScreenOffset(0,i) + VIDEO_ADDRESS, 
        GetScreenOffset(0,i-1) + VIDEO_ADDRESS, MAX_COLS*2);
    }
    char* LastLine = GetScreenOffset(0,MAX_ROWS-1) + VIDEO_ADDRESS;
    for(i=0; i < MAX_COLS*2; i++){
        LastLine[i] = 0;
    }
    CursorOffset -= 2*MAX_COLS;
    return CursorOffset;
}

int GetOffset(int Col, int Row){
    return 2 * (Row * MAX_COLS);
}

int GetOffsetRow(int offset){
    return offset / (2*MAX_COLS);
}
int GetOffsetCol(int offset){
    return (offset - (GetOffsetRow(offset)*2*MAX_COLS))/2;
}

void Backspace(){
    /* Removes two 'spaces' from vidmem, 1 'space' is the attribute and the 2 'space is the character itself*/
    int offset = GetCursor()-2; /* If you set -2 to -3 it works, but it doesn't delete the FIRST character the cursor is on, but if you put it to -2 it doesn't work. What the hell..*/
    int row = GetOffsetRow(offset);
    int col = GetOffsetCol(offset);
    SayChar(' ', col, row, WHITE_ON_BLACK);
    
}