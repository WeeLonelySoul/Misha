#include "../../libraries/bikka/ide.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/common.h"


/* Courtesy of Richard A Burgess */

u32 IDE_HDISK_SETUP(void){

    /* Setup */
    u32 Erc;
    HDCB[0].Name[0] = 'H';
    HDCB[0].Name[1] = 'D';
    HDCB[0].Name[2] = 'O';
    HDCB[0].SBName = 3;
    HDCB[0].Type = 1;
    HDCB[0].NBPB = 512;
    HDCB[0].NBlocks = 524288; /* ~2GB */
    HDCB[0].DevOp = &IDE_HDDEV_OP;
    HDCB[0].DevInit = &IDE_HDDEV_INIT;
    HDCB[0].DevSt = &IDE_HDDEV_STAT;

    HDCB[1].Name[0] = 'H';
    HDCB[1].Name[1] = 'D';
    HDCB[1].Name[2] = 'O';
    HDCB[1].SBName = 3;
    HDCB[1].Type = 1;
    HDCB[1].NBPB = 512;
    HDCB[1].NBlocks = 524288; /* ~2GB */
    HDCB[1].DevOp = &IDE_HDDEV_OP;
    HDCB[1].DevInit = &IDE_HDDEV_INIT;
    HDCB[1].DevSt = &IDE_HDDEV_STAT;

    /* These are defaulted to none zero values to ensure that we don't get a 
        'divide by zero' */
    HD0_Type = READ_CMOS(0x19);
    HD0_Heads = 16; /* Max amount of hydra heads */
    HD0_SecPerTrk = 17; /* Most common */
    HD0_Cyls = 1024;

    HD1_Type = READ_CMOS(0x1A);
    HD1_Heads = 16; /* Max amount of hydra heads */
    HD1_SecPerTrk = 17; /* Most common */
    HD1_Cyls = 1024;

    Erc = AllocExch(&HD_EXCH);
    IRQ_SET_VECTOR(14, &IDE_HDISK_ISR);
    IRQ_UNMASK(14);

    IDE_HD_RESET(); /* Reset the harddrive */

    Erc = IDE_HD_RECAL(0); /* Trying to Recal */
    if (Erc){
        IDE_HD_RESET(); /* Let's try it again */
        Erc = IDE_HD_RECAL(0);
        if (Erc){
            HDCB[0].LAST_ERC = Erc;
            HD0_Type = 0;
            return(ErcNoDrive0);
        }
    }

    /*
    If we get to this point, then drive 0 is looking OK and the controller is 
    functioning, now let's try the same but with drive 1
    */

    if (HD1_Type){
        Erc = IDE_HD_RECAL(1);
        HD1_Type = 0;
        if (!Erc){
            IDE_HD_RESET();
            Erc = IDE_HD_RECAL(0);
        }
        HDCB[0].LAST_ERC = Erc;
    }
    return(Erc = InitDevDr(12, &HDCB, 2, 1));
}

