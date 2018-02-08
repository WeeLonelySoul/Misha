#include "../../libraries/shell.h"
#include "../../libraries/bikka/video.h"

/*
#include "Mkernel.h"
#include "MMemory.h"
#include "MData.h"
#include "Mtimer.h"
#include "Mvid.h"
#include "MKbd.h"
#include "MJob.h"
#include "MFiles.h"
#include "Status.h" 



#define EDVID BLACK | BGWHITE
#define NORMVID WHITE | BGBLACK
#define STATVID BLACK | BGCYAN
*/

long ICol, ILine;
char AStatLine[] = "dd/mm/yy    00:00:00    Job     Path:";

char APath[70];
long CBPath;
char FUpdatePath;

char SDisk, SysPath[50]; /* Will hold the system disk and system path */
char HlpPath[60]; /* The path to our help file */
char CliPath[60]; /* The path to our cli-program file */
char CmdPath[60]; /* "Path to command file" */


char aCmd[80];
long CBCmd = 0;

unsigned char Buffer[512];
unsigned char BigBuf[4096]; /* #Madness */
char Text[70];

char ExitChar;

unsigned long GPExch;
unsigned long GPMsg[2];
unsigned long GPHndl;

unsigned long StatExch;
long StatStack[256];

long Time, Date;

long JobNum;

#define NCMDS 16

/* Supported commands */
char SupportedCommands[NCMDS+1][10] = {
    "",
    "xxxxx",  /* Only gods knows */
    "cls", /* Clear screen */
    "copy", /* Copy*/
    "mv",  /* Move */
    "rm", /* Remove <-- only works on files */
    "ls", /* List */
    "help" /* Help screen */
    "version", /* Version screen */
    "rmd", /* Remove directory */
    "cd", /* Change directory */
    "crd", /* Create directory */
    "crf", /* Create file */
    "path", /* Ehmm *insert creative comment* */
    "run" /* Used to run files */
};

/* And let us define them aka the supported commands dipshit */ 
#define EXITCMD 0
#define RESVDCMD 1
#define CLSCMD 2
#define COPYCMD 3
#define MVCMD 4
#define RMCMD 5
#define LSCMD 6
#define HELPCMD 7
#define VERSIONCMD 8
#define RMDCMD 9
#define CDCMD 10
#define CRDCMD 11
#define CRFCMD 12
#define PATHCMD 13
#define RUNCMD 14

long CmdNum = 0;

char *ApParam[13]; /* Param 0 is the cmd name */
long AcbParam[13];
#define nParamsMax 13

#define ErcBadParams 80

/* Directory Entry Records, 16 records 32 bytes each */
struct DirStruct {
    U8 Name[8];
    U8 Ext[3];
    U8 Attr;
    U8 Rsvd[10];
    U16 Time;
    U16 Date;
    U16 StartClstr;
    U32 FileSize;
} Dirent[16];


void StatTask(void){
    /* Updates the status line which has the time and path */
    for(;;){ /* Forever loop */
        if (FUpdatePath){
            if (CBPath > 30) { CBPath = 30; }
             FillData(&AStatLine[47], 30, ' ');
             CopyData(APath, &AStatLine[47], CBPath);
             FUpdatePath = 0;
        }
        GetCMOSDate(&Date);
        AStatLine[0] = '0' + ((Date >> 12) & 0x0F); /* Day */ 
        AStatLine[1] = '0' + ((Date >> 8) & 0x0F);
        AStatLine[3] = '0' + ((Date >> 20) & 0x0F); /* Month */
        AStatLine[4] = '0' + ((Date >> 16) & 0x0F);
        AStatLine[6] = '0' + ((Date >> 28) & 0x0F); /* Year */
        AStatLine[7] = '0' + ((Date >> 24) & 0x0F);

        GetCMOSTime(&Time);
        AStatLine[10] = '0' + ((Time >> 20) & 0x0F); 
        AStatLine[11] = '0' + ((Time >> 16) & 0x0F); 
        AStatLine[13] = '0' + ((Time >> 12) & 0x0F); 
        AStatLine[14] = '0' + ((Time >> 8) & 0x0F); 
        AStatLine[16] = '0' + ((Time >> 4) & 0x0F); 
        AStatLine[17] = '0' + (Time & 0x0F);

        PutVidChars(0,0, AStatLine, 80, STATVID);
    }
}

void CheckErc(unsigned long ERC){
    /* Displays error text connected to the value of 'ERC' */
    char *PST;
    char ST[40];

    FillData(ST, 40, 0);
    switch(ERC){
        case 0: return;
        case 1: PST = "End of file"; break;
        case 4: PST = "User cancelled"; break;
        case 80: PST = "Invalid parameters"; break;
        case 101: PST = "Out of Memory and I need more for this operation"; break;
        case 200: PST = "Invalid Filename!"; break;
        case 201: PST = "No such drive"; break;
        case 202: PST = "That's a directory.. not a file.. dumbo"; break;
        case 203: PST = "File does not exist!"; break;
        case 204: PST = "Directory does not exist!"; break;
        case 205: PST = "File is ReadOnly!"; break;
        case 208: PST = "File is already in use"; break;
        case 222: PST = "Can not rename across drives!"; break;
        case 223: PST = "Can not rename across directories"; break;
        case 226: PST = "A file with that name already exists!"; break;
        case 228: PST = "Root directory is full!"; break;
        case 230: PST = "Disk is full!"; break;
        case 231: PST = "Directory is fulll!"; break;
        default:
            sprintf(ST, "Error %05d on last command!", ERC);
            PST = ST;
            break;
    }
        printf("Error: %s\r\n", PST);
}

/*void GoDebug(void){
;
#asm
    INT 03
#endasm
}*/

void InitScreen(int FNew){
    /* Initializes the screen on call, supposed to be used i.e. when a program exits */
    SetNormVid(NORMVID);
    GETXY(&ICol, &ILine);
    if (FNew){
        /* Let's start fresh */
        ICol = 0;
        ILine = 0;
        ClrScr();
    }
    SetXY(ICol, ILine);
    PutVidChars(0, 0, AStatLine, 80, STATVID);
    return;
}

/* Skipping the dump functions for now */

long DoType(char *PName, long CBName){
    /**/
    long i, j, LFA, ERC = 0, DRet, FH, KeyCode;

    if ((PName) && (CBName)){
        if (ILine >= 23){
            ScrollVid(0, 1, 80, 23, 1);
            SetXY(0, 23);
        }
        ERC = OpenFile(PName, CBName, 0, 1, &FH);
        if (!ERC){
            FillData(Buffer, 512, 0);
            DRet = 1;
            while ((ERC < 2) && (DRet)){
                GetFileLFA(FH, &LFA);
                ERC = ReadBytes(FH, Buffer, 78, &DRet);
                i = 1;
                while ((Buffer[i -1 ] != 0x0A) && (i < DRet)) { i++; } /* Sideways while loooop, edgy!! */

                for (j = 0; j <= i; j++){
                    if ((Buffer[j]) == 0x09 || (Buffer[j]) == 0x0d || (Buffer[j]) == 0x0a) { Buffer[j] == 0x20; }
                }
                if (DRet){
                    PutVidChars(0, ILine, Buffer, i, NORMVID);
                    ILine++;
                }
                SetXY(0, ILine);
                SetFileLFA(FH, LFA+i);

                if (ILine >= 22){
                    SetXY(0, 23);
                    printf("Press ESC to cancel, press any other key to continue...");
                    ReadKbd(&KeyCode, 1) /* Read for any entry */
                    if ((Keycode & 0xff) == 0x1b) { return(4); }
                    InitScreen(TRUE);
                    SetXY(0, 1);
                    ILine = 1;
                }
            }
            printf("\r\nError: %d\r\n", ERC);
            CloseFile(FH);
        }
    }else{
        printf("Filename not give\r\n");
    }
    return ERC;
}

void ConvertFATTime(U16 Time, U16 Date, char *TimeRet, char *DateRet){
    /* Converts FAT date and time to strings in the format of HH/MM/SS */
    U32 YR, MO, DA, HR, MI, SE;
    char ST[15];

    YR = ((Date & 0xFE00) >> 9) + 1980 - 1900;
    if (YR > 99) { YR -= 100; }

    MO = (Date & 0x01E0) >> 5;
    DA = Date & 0x001F;
    HR = (Time & 0xF800) >> 11;
    MI = (Time & 0x07E0) >> 5;
    SE = (Time & 0x001F) * 2;

    sprintf(ST, "%02d:%02d:%02d", HR, MI, SE);
    CopyData(ST, TimeRet, 8);
    sprintf(ST, "%02d-%02d-%02d", MO, DA, YR);
    CopyData(ST, DateRet, 8);

}

U32 CopyFile(char *FromPath, U32 CBFrom, char *ToPath, U32 CBTo){
    U32 FHTo, FHFrom, BytesWant, BytesGot, BytesLeft, ERC, BytesOut, Size, DLFA, KeyCode;

    ERC = OpenFile(FromPath, CBFrom, ModeRead, 0, &FHFrom);
    if (!ERC){
        /* Check to see if the file already exists */
        ERC = CreateFile(ToPath, CBTo, 0);
        if ((!ERC) || (ERC == ErcDupName)){
            if (ERC == ErcDupName){
                printf("File already exists!! Overwrite? [y/n]\r\n");
                ReadKbd(&KeyCode, 1);
                if (((KeyCode & 0xff) == 'Y') || ((KeyCode & 0xff) == 'y')){
                    ERC = 0;
                }
            }
            if (!ERC){
                ERC = OpenFile(ToPath, CBTo, ModeModify, 0, &FHTo);
                if (!ERC){
                    ERC = GetFileSize(FHFrom, &Size);
                    if (!ERC) { ERC = SetFileSize(FHTo, Size); }

                    DLFA = 0;
                    BytesLeft = Size;
                    while ((!ERC) && (BytesLeft)){
                        if (BytesLeft >= 4096){ BytesWant = 4096; }
                        else{ BytesWant = BytesLeft; }
                        if (BytesWant & 511){ BytesWant += 512; }
                        BytesWant = (BytesWant / 512) * 512;
                        ERC = ReadBlock(FHFrom, BigBuf, BytesGot, DLFA, &BytesOut);
                        if (BytesGot){
                            ERC = WriteBlock(FHTo, BigBuf, BytesGot, DLFA, &BytesOut);
                            if (BytesLeft < BytesOut) { BytesLeft = 0; }
                            else { BytesLeft -= BytesOut; }
                        }
                        DLFA += BytesGot;
                    }
                    CloseFile(FHTo);
                }
            }
        }
        CloseFile(FHFrom);
    }
    return(ERC);
}

U32 ListCommand(void){
    U8 FDone;
    U32 SectNum, ERC, KeyCode, i;
    char ST[78];

    if (ILine >= 23){
        ScrollVid(0, 1, 80, 23, 1);
        SetXY(0, 23);
    }
    FDone = 0;
    SectNum = 0;
    while (!FDone){
        ERC = GetDirSector(ApParam[1], AcbParam[1], &Dirent[0], 512, SectNum);
        if (!ERC){
            for (i = 0; i < 16; i++){
                if (!DirEnt[i].Name[0]){ ERC = 1; FDone = 1; }
                if ((DirEnt[i].Name[0]) && (DirEnt[i].Name[0] != 0xE5)){
                    sprintf(ST, "%8s %3s %8d XX/XX/XX XX/XX/XX %2x  %04x\r\n",
                    DirEnt[i].Name,
                    DirEnt[i].Ext,
                    DirEnt[i].FileSize,
                    DirEnt[i].Attr,
                    DirEnt[i].StartClstr);
                    ConvertFATTime(Dirent[i].Time, Dirent[i].Date, &ST[33], &ST[24]);
                    printf("%s", ST);
                    ILine++;
                    if (ILine >= 22){
                        SetXY(0, 23);
                        printf("Press ESC to cancel, press any other key to continue...");
                        ReadKbd(&KeyCode, 1);
                        if ((KeyCode & 0xff) == 0x1b){
                            ERC = 4;
                            FDone = TRUE;
                        }
                        InitScreen(TRUE);
                        SetXY(0, 1);
                        ILine = 1;
                    }else{ FDone = TRUE; SectNum++; }
                }
            }
        }
    }
    return (ERC);
}


void ParseCommandLine(void){
    /* Parses the user input  */
    long ICmd = 0, IPrm, i; /* ICmd is index to ACmd */
    for (IPrm = 0; IPrm < nParamsMax; IPrm++ ){
        AcbParam[IPrm] = 0; /* Default the param to empty */
        ApParam[IPrm] = 0; /* Null the pointer */
        if (ICmd < CBCmd){
            if (!isspace(aCmd[ICmd])){
                ApParam[IPrm] = &aCmd[ICmd++];
                i = 1;
                while ((ICmd < cbCmd) && (!isspace(aCmd[ICmd]))){ i++; ICmd++; }
                AcbParam[IPrm] = i; /* Size of param */
            }
            while ((ICmd < cbCmd) && (isspace(aCmd[ICmd]))){ ICmd++; }
        }
    }
}

long GetCommandLineCommand(char *RunFile){
    /* 
    Opens and parses Commands.CLI in the system dir and looks for the 
    command name in ApParam[0]. If it find it, it places the full filespec for the run file in
    "RunFile" for the caller, then it fixes up the aCmd command line just as if it had come from
    the user
    */

    long i, j, k;
    FILE *F;
    char RawLine[90]; /* Used to build a pseudo command line */
    char CmdLine[90]; /* Used to build a pseudo command line */
    char FDone;
    CmdLine[0] = 0;

    F = fopen(CmdPath, "r");
    if (F){
        FDone = 0;
        while (!FDone){
            if (fgets(RawLine, 89, F)){
                if (RawLine[0] == ';') { continue; }/* We found a comment, so let's ignore it */
                j = CompareNCS[ApParam[0], RawLine, AcbParam[0]];
                if (j == -1){
                    /* We found our command! */
                    i = 0; /* Index into RawLine */
                    j = 0; /* Index into CmdLine */
                    k = 0;

                    while (!(isspace(RawLine[i]))){ CmdLine[j++] = RawLine[i++]; }
                    CmdLine[j++] = ' ';

                    while (!(isspace(RawLine[i]))) { i++; }
                    while (!(isspace(RawLine[i]))) { RunFile[k++] = RawLine[i++]}
                    RunFile[k] = 0; /* Null terminator */

                    while (isspace(RawLine[i])) { i++; }

                    while (RawLine[i]) { CmdLine[j++] = RawLine[i++]; }
                    CmdLine[j] = 0;

                    strcpy(aCmd, Cmdline);
                    CBCmd = strlen(aCmd);
                    return (1);
                }
            }else{ FDone = 1; }
        }
    }else{ printf("Commands.CLI not found.\r\n"); }
    return (0);
}

void FindRunFile(void){
    /* 
    When a command is specified to the CLI and it's not an internal command
    We'll look for a .RUN file in the current path. If we don't find it
    we'll look into the system directory AAAND if it's not there, we'll then
    go to COMMAND.CLI  and search it line by line to see if the run file is
    specified there. If so, we set the command line with everything after the runfile and
    specified and at last try to execute it
    */
    char RunFile[80];
    long i, ERC, FH;

    /* Let's check the current path */
    CopyData(ApParam[0], RunFile, AcbParam[0]);
    RunFile[AcbParam[0]] = 0;
    strcat(RunFile, ".RUN");

    ERC = OpenFile(RunFile, strlen(RunFile), ModeRead, 1, &FH);
    if (!ERC) {
        /* We found the .RUN file */
        CloseFile(FH);
        SetCommandLine(aCmd, CBCmd);
        SetExitJob(CliPath, strlen(CliPath));
        ERC = Chain(RunFile, strlen(RunFile), 0);
    }else{
        /* Let's check the system directory */
        strcpy(RunFile, SysPath);
        i = strlen(RunFile);
        CopyData(ApParam[0], &RunFile[i], AcbParam[0]);
        RunFile[AcbParam[0] + i] = 0; /* Null terminator */
        strcat(RunFile, ".RUN");
        ERC = OpenFile(RunFile, strlen(RunFile), ModeRead, 1, &FH);
        if (!ERC){
            /* We found the .RUN file */
            CloseFile(FH);
            SetCommandLine(aCmd, CBCmd);
            SetExitJob(CliPath, strlen(CliPath));
            ERC = Chain(RunFile, strlen(RunFile), 0);
        }else if (GetCommandLineCommand(RunFile)){
            /* Last Resort */
            ERC = OpenFile(RunFile, strlen(RunFile), ModeRead, 1, &FH);

            if (!ERC){
                /* We found the .RUN file */
                CloseFile(FH);
                SetCommandLine(aCmd, CBCmd);
                SetExitJob(CliPath, strlen(CliPath));
                ERC = Chain(RunFile, strlen(RunFile), 0);
            }
        }
    }
    printf("Command not found\r\n"); /* Hello darkness my old friend */
}

void main(void){
    /* Main function */
    unsigned long ERC, i, j, FH;
    ERC = AllochExch(&StatExch);
    ERC = AllochExch(&GPExch);

    SpawnTask(&StatTask, 24, 0, &StatTask[255], 0);
    GetJobNum(&JobNum);
    sprintf(&AStatLine[37], "%02d", JobNum);
    SetJobName("CLI v1.0", 8);

    /* Get system disk and set up path names for cli, command file and help file */

    GetSystemDisk(&SDisk);
    SDisk &= 0x7F;
    SDisk +=  0x41;
    SysPath[0] = SDisk;
    SysPath[1] = ':';
    SysPath[2] = 0;
    strcat(SysPath, "\\MMSYS\\"); /* Change? */

    strcpy(CliPath, SysPath);
    strcat(CliPath, "CLI.RUN");

    strcpy(CliPath, SysPath);
    strcat(CliPath, "CLI.RUN");

    strcpy(CmdPath, SysPath);
    strcat(CmdPath, "COMMANDS.CLI");

    strcopy(HlpPath, SysPath);
    strcat(HlpPath, "HELP.CLI");

    /*
    If a path was already set we assume that we are re-loading
    after an external command has been run. We do not want to
    reset the screen completly so the user can see anything
    the external command left on the screen
    */

    CBPath = 0;
    GetPath(JobNum, APath, &CBPath);
    if (CBPath){
        GetXY(&ICol, &ILine);
        if (ILine == 0){ ILine = 1; }
        InitScreen(FALSE);
        SetXY(0, ILine);
    }else{
        strcpy(APath, SysPath);
        CBPath = strlen(SysPath);
        SetPath(SysPath, strlen(SysPath));
        InitScreen(TRUE);
    }
    FUpdatePath = 1;
    SetExitJob(CliPath, strlen(CliPath));
    while (1){
        FillData(aCmd, 79, ' ');
        aCmd[79] = 0;
        CBCmd  =0;
        SetXY(0, ILine);
        TTYOUT("-:- ", 1, NORMVID);
        EditLine(aCmd, CBCmd, 79, &CBCmd, &ExitChar, EDVID);
        TTYOUT("\r\n", 2, NORMVID);
        GETXY(&Icol, ILine);

        AcbParam[0] = 0;
        ApParam[0] = 0;
        CmdNum = 0;

        if (ExitChar == 0x0d){ ParseCommandLine(); } /*  Setup the params */

        if ((AcbParam[0]) && (ApParam[0])){
            i = 1;
            while (i <= NCMDS){
                j = strlen(PACmds[i]);
                if ((AcbParam[0 == j] && (CompareNCS[ApParam[0], PACmds[i], j] == -1)){ CmdNum = i; break; }
                i++;
            }
            ERC = 0;
            switch(CmdNum){
                case EXTCMD: FindRunFile(); break; /* Run the .RUN file */
                case CLSCMD: InitScreen(TRUE); break; /* Clear the screen */
                case COPYCMD: /* Copy command */
                    if ((AcbParam[1]) && (AcbParam[2])){ ERC = CopyFile(ApParam[1], AcbParam[1], ApParam[2], AcbParam[2]); }
                    else{ ERC = ErcBadParams; }
                    break;
                case RMCMD: /* Remove file */
                    ERC = OpenFile(ApParam[1], AcbParam[1], 1, 0, &FH);
                    if (!ERC){
                        ERC = DeleteFile(FH);
                        if (ERC){ printf("Error while deleting file! %d", ERC);}

                    }
                    break;
                case LSCMD: ERC = ListCommand(); break; /* List command */

                case EXITCMD: SetExitJob("", 0); ExitJob(0); break; break; /* Exit */
                case HELPCMD: ERC = DoType(HlpPath, strlen(HlpPath)); break; /* Help  */
                case CRDCMD: ERC = CreateDir(ApParam[1], AcbParam[1]); break; /* Create directory */
                case PATHCMD: 
                    ERC = SetPath(ApParam[1], AcbParam[1]);
                    if (!ERC){ ERC = GetPath(JobNum, APath, &CBPath); }
                    FUpdatePath = 1;
                    break;
                case RMDCMD: ERC = DeleteDir(ApParam[1], AcbParam[1]); break;
                case RUNCMD:
                    if (AcbParam[1]){
                        i = 2;
                        while (aCmd[i] != ' '){ i++; }
                        SetCommandLine(&aCmd[i], CBCmd-i);
                        SetExitJob(CliPath, strnlen(CliPath));
                        ERC = Chain(ApParam[1], AcbParam[1], 0);
                    }
                    break;
                
                default:
                    break;
            }
            CheckErc(ERC);
        }
        GetXY(&ICol, ILine);
        if (ILine >= 23){ ScrollVid(0,1,80,23,1); SetXY(0,23); }
    }
}