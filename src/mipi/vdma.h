
#ifndef VDMA_H_
#define VDMA_H_

#include "xaxivdma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xil_printf.h"
#ifdef XPAR_INTC_0_DEVICE_ID
#include "xintc.h"
#else
#include "xscugic.h"
#endif

#ifndef __MICROBLAZE__
#include "xpseudo_asm_gcc.h"
#endif

#if defined(XPAR_UARTNS550_0_BASEADDR)
#include "xuartns550_l.h"       /* to use uartns550 */
#endif

/*
 * Device related constants. These need to defined as per the HW system.
 */
#define DMA_DEVICE_ID		XPAR_AXIVDMA_0_DEVICE_ID

#ifdef XPAR_INTC_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#define WRITE_INTR_ID		XPAR_FABRIC_AXI_VDMA_0_S2MM_INTROUT_INTR
//#define READ_INTR_ID		XPAR_INTC_0_AXIVDMA_0_MM2S_INTROUT_VEC_ID
#else
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define WRITE_INTR_ID		XPAR_FABRIC_AXI_VDMA_0_S2MM_INTROUT_INTR
//#define READ_INTR_ID		XPAR_FABRIC_AXIVDMA_0_MM2S_INTROUT_VEC_ID
#endif

#ifdef XPAR_INTC_0_DEVICE_ID
static XIntc Intc;	/* Instance of the Interrupt Controller */
#else
static XScuGic Intc;	/* Instance of the Interrupt Controller */
#endif

extern XAxiVdma Vdma;

int vdma_read_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
int vdma_write_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
u32 vdma_version();
static int SetupIntrSystem(XAxiVdma *AxiVdmaPtr/*, u16 ReadIntrId*/,
				u16 WriteIntrId);
static void WriteCallBack(void *CallbackRef, u32 Mask);
static void WriteErrorCallBack(void *CallbackRef, u32 Mask);

#endif /* VDMA_H_ */
