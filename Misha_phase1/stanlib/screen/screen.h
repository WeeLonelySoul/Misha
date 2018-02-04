#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Color scheme
#define WHITE_ON_BLACK 0x0f 

// Screen device for I/O
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5


// Global Video Functions
void SayChar(char CharacterToPrint, int Col, int Row, char AttributeByte);
int GetScreenOffset(int Col, int Row);
int GetCursor();
int SetCursor(int offset);
void SayAt(char* MessageToSay, int Col, int Row);
void Say(const char* MessageToSay);
void ClearScreen();
int HandleScrolling(int offset);
int GetOffset(int Col, int Row);
int GetOffsetRow(int offset);
int GetOffsetCol(int offset);
void Backspace();
#endif