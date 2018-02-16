/* Courtesy of Richard A Burgess */

#ifndef IDE_H
#define IDE_H 1
#include "../../libraries/common.h"


/* Define of hell, wondering if this is like the 6 level of hell  */
#define ok 0
#define ErcNoMsg 20
#define ErcNotInstalled 504
#define ErcBadBlock 651
#define ErcAddrMark 652
#define ErcBadECC 653
#define ErcSectNotFound 654
#define ErcNoDrive0 655
#define ErcNotSupported 656
#define ErcBadHDC 657
#define ErcBadSeek 658
#define ErcHDCTimeOut 659
#define ErcOverRun 660
#define ErcBadLBA  661
#define ErcInvalidDrive 662
#define ErcBadOp 663
#define ErcBadRecal 664
#define ErcSendHDC 665
#define ErcNotReady 666 /* Heil satan */
#define ErcBadCmd 667
#define ErcNeedsInit 668
#define ErcTooManyBlks 669 /* The controller can only do 128 max */
#define ErcZeroBlks 670 /* 0 blocks not allowed for this cmd */
#define ErcWriteFault 672 /* Writefault bit set */

#define ErcMissHDDInt 675
#define ErcHDDMsgBogus 676
#define ErcHddIntMsg 677
#define ErcHDDAlarmMsg 678

/* Commaands that our IDE Driver accepts */
#define CmdNull 0
#define CmdRead 1
#define CmdWrite 2
#define CmdVerify 3
#define CmdFmtBlk 4
#define CmdFmtTrk 5
#define CmdSeekTrk 6
#define CmdSetMedia 7 /* Not used unless mountable */
#define CmdResetHdw 8 /* Used to reset controller hardware */

#define CmdReadSect 256 /* Only device specific call in HDD */

#define HD_PORT 0x1f0
#define HD_REG_PORT 0x3f6

#define BUSY 0x80 /* I got food in my mouth, chill! */
#define READY 0x40 /* Drive is ready for lift off */
#define WRITE_FAULT 0x20 /* Woops */
#define SEEKOK 0x10 /* Seek complete */
#define DATA_REQ 0x08 /* Sector buffer needs servicing */
#define CORRECTED 0x04 /* ECC corrected, data was read */
#define REV_INDEX 0x02 /* Set once each disk revolution?? Were you high? */
#define ERROR 0x01 /* Data address mark not found */

/* HDC Error Register Bit masks */
#define BAD_SECTOR 0x80 /* Bad Block */
#define BAD_ECC 0x40 /* Bad Data */
#define BAD_IDMARK 0x10 /* ID not found */
#define BAD_CMD 0x04 /* Aborted command */
#define BAD_SEEK 0x02 /* trk 0 not found on recalibrate, or bad seek occurred */
#define BAD_ADDRESS /* Data address mark not found */

/* HDC internal command */
#define HDC_RECALL 0x10
#define HDC_READ 0x20
#define HDC_READ_LONG 0x22
#define HDC_WRITE 0x30
#define HDC_WRITE_LONG 0x32
#define HDC_VERIFY 0x40
#define HDC_FORMAT 0x50
#define HDC_SEEK 0x70
#define HDC_DIAG 0x90
#define HDC_SET_PARAMS 0x91

#define SStatus 64

/* Variables */
static u8 HD_Cmd[8]; /* For all 8 command bytes */
static u8 FDataReq; /* Flag to indicate if FDataRequest is active or not */
static u8 StatByte; /* From HDC status register last time it was read */
static u8 HD_Control; /* Current control byte value */
static u8 HD_Command; /* Current command */
static u8 HD_Drive; /* Current physical drive, 0 or 1 */
static u8 HD_Head; /* Calculated from LBA - which head */
static u8 HD_NSectors; /* Calculated from LBA - N sectors to read/write */
static u8 HD_Sectors; /* Calculated from LBA - Starting sector */
static u8 HD0_Type;
static u8 HD0_Heads;
static u8 HD0_SecPerTrk;
static u8 HD0_Cyls;
static u8 HD1_Type;
static u8 HD1_Heads;
static u8 HD1_SecPerTrk;
static u16 HD1_Cyls;
static u32 HD_EXCH;
static u32 HD_MSG;
static u32 HD_MSG2;

static long HDDINT;

/* Struct */
static struct StatsStruct {
    u32 Erc;
    u32 Blocks_Done;
    u32 Blocks_Max;
    u8 FNewMedia;
    u8 TypeNow; /* Current FDisk_Table for drive selected */
    u8 Resvd0[2]; /* Padding for DWORD align */
    u32 NCyl; /* Total Physical cylinders */
    u32 NHead; /* Total heads on device */
    u32 NSectors; /* Sectors per track */
    u32 NBPS; /* Number of bytes per sect*/

    u32 LastRecallErc0;
    u32 LastSeekErc0;
    u8 LastStatByte0;
    u8 LastErcByte0;
    u8 FIntOnReset; /* Interrupt was received on HDC_RESET */
    u8 Filler0;

    u32 LastRecallErc1;
    u32 LastSeekErc1;
    u8 LastStatByte1;
    u8 LastErcByte1;
    u8 ResetStatByte; /* Status byte immediately after RESET */
    u8 Filler1;

    u32 Resvdl[2];
};

static struct StatsStruct HDSTATUS;
static struct StatsStruct HDSTATTMP;

static struct DCBTYPE{
    s8 Name[12];
    s8 SBName;
    s8 Type;
    s16 NBPB;
    u32 LAST_ERC;
    u32 NBlocks;
    s8 DevOp;
    s8 DevInit;
    s8 DevSt;
    u8 FDevReent;
    u8 FSingleUser;
    u16 WJob;
    u32 OS1;
    u32 OS2;
    u32 OS3;
    u32 OS4;
    u32 OS5;
    u32 OS6;
};

static struct DCBTYPE HDCB[2]; /* Two HD Device control blocks */

/* IDE functions */
u32 IDE_HDISK_SETUP(void);
static void IDE_HDISK_ISR(void);
static u32 IDE_HD_FORMAT_TRACK(u32 DLBA, u32 DnBlocks);
static void IDE_HD_RESET(void);
static u32 IDE_SEND_COMMAND(u8 Param);
static u32 IDE_HD_WAIT(void);
static u32 IDE_CHECK_BUSY(void);
static u32 IDE_HD_SEEK(u32 DLBA);
static u32 IDE_HD_RECAL(u8 Drive);
static u32 IDE_HD_WRITE(u32 DLBA, u32 DNBlocks, u8 *DataOut);
static u32 IDE_HD_READ(u32 DLBA, u32 DNBlocks, u8 *DataIn);
static u32 IDE_HD_STATUS(u8 LastCmd);
static u32 IDE_SETUP_SEEK(u32 DLBA, u32 NBlks);
static u32 IDE_READ_SECTORS(u32 Cylinder, u32 HdSect, u8 *DataRet);
static u32 IDE_HDDEV_OP(u32 DDevice, u32 DOpNum, u32 DLBA, u32 DnBLOCKS, u8 *Data);
static u32 IDE_HDDEV_STAT(u32 DDevice, s8 *StatRet, u32 DStatatusMax, u32 SDInitData);
static u32 IDE_HDDEV_INIT(u32 DDevNum, s8 *InitData, u32 SDInitData);

#endif