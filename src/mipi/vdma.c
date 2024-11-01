#include "xil_printf.h"
#include "vdma.h"
#include "display_demo.h"
#include "xparameters.h"

u32 vdma_version(XAxiVdma *Vdma) {
	return XAxiVdma_GetVersion(Vdma);
}

int vdma_read_start(XAxiVdma *Vdma) {
	int Status;

	// MM2S Startup
	Status = XAxiVdma_DmaStart(Vdma, XAXIVDMA_READ);
	if (Status != XST_SUCCESS)
	{
	   xil_printf("Start read transfer failed %d\n\r", Status);
	   return XST_FAILURE;
	}

	return XST_SUCCESS;
}


int vdma_read_stop(XAxiVdma *Vdma) {
	XAxiVdma_DmaStop(Vdma, XAXIVDMA_READ);
	return XST_SUCCESS;
}


int vdma_read_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr)
{
	XAxiVdma Vdma;
	XAxiVdma_Config *Config;
	XAxiVdma_DmaSetup ReadCfg;
	int Status;


	Config = XAxiVdma_LookupConfig(DeviceID);
	if (NULL == Config) {
		xil_printf("XAxiVdma_LookupConfig failure\r\n");
		return XST_FAILURE;
	}

	Status = XAxiVdma_CfgInitialize(&Vdma, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("XAxiVdma_CfgInitialize failure\r\n");
		return XST_FAILURE;
	}

	

	ReadCfg.EnableCircularBuf = 1;
	ReadCfg.EnableFrameCounter = 0;
	ReadCfg.FixedFrameStoreAddr = 0;

	ReadCfg.EnableSync = 1;
	ReadCfg.PointNum = 1;

	ReadCfg.FrameDelay = 0;

	ReadCfg.VertSizeInput = VertSizeInput;
	ReadCfg.HoriSizeInput = HoriSizeInput;
	ReadCfg.Stride = Stride;

	Status = XAxiVdma_DmaConfig(&Vdma, XAXIVDMA_READ, &ReadCfg);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,
				"Read channel config failed %d\r\n", Status);

			return XST_FAILURE;
	}


	ReadCfg.FrameStoreStartAddr[0] = FrameStoreStartAddr;

	Status = XAxiVdma_DmaSetBufferAddr(&Vdma, XAXIVDMA_READ, ReadCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,"Read channel set buffer address failed %d\r\n", Status);
			return XST_FAILURE;
	}



	Status = vdma_read_start(&Vdma);
	if (Status != XST_SUCCESS) {
		   xil_printf("error starting VDMA..!");
		   return Status;
	}
	return XST_SUCCESS;

}


int vdma_write_start(XAxiVdma *Vdma) {
	int Status;

	// MM2S Startup
	Status = XAxiVdma_DmaStart(Vdma, XAXIVDMA_WRITE);
	if (Status != XST_SUCCESS)
	{
	   xil_printf("Start write transfer failed %d\n\r", Status);
	   return XST_FAILURE;
	}

	return XST_SUCCESS;
}


int vdma_write_stop(XAxiVdma *Vdma) {
	XAxiVdma_DmaStop(Vdma, XAXIVDMA_WRITE);
	return XST_SUCCESS;
}

XAxiVdma Vdma;

int vdma_write_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr)
{
//	XAxiVdma Vdma;
	XAxiVdma_Config *Config;
	XAxiVdma_DmaSetup WriteCfg;
	int Status;


	Config = XAxiVdma_LookupConfig(DeviceID);
	if (NULL == Config) {
		xil_printf("XAxiVdma_LookupConfig failure\r\n");
		return XST_FAILURE;
	}

	Status = XAxiVdma_CfgInitialize(&Vdma, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("XAxiVdma_CfgInitialize failure\r\n");
		return XST_FAILURE;
	}

	

	WriteCfg.EnableCircularBuf = 0;
	WriteCfg.EnableFrameCounter = 0;
	WriteCfg.FixedFrameStoreAddr = 0;

	WriteCfg.EnableSync = 1;
	WriteCfg.PointNum = 1;

	WriteCfg.FrameDelay = 0;

	WriteCfg.VertSizeInput = VertSizeInput;
	WriteCfg.HoriSizeInput = HoriSizeInput;
	WriteCfg.Stride = Stride;

	Status = XAxiVdma_DmaConfig(&Vdma, XAXIVDMA_WRITE, &WriteCfg);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,
				"Read channel config failed %d\r\n", Status);

			return XST_FAILURE;
	}


	WriteCfg.FrameStoreStartAddr[0] = FrameStoreStartAddr;

	Status = XAxiVdma_DmaSetBufferAddr(&Vdma, XAXIVDMA_WRITE, WriteCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,"Write channel set buffer address failed %d\r\n", Status);
			return XST_FAILURE;
	}


	/*****************************VDMA Interrupt *********************************/

//		Status = SetupIntrSystem(&Vdma,/* READ_INTR_ID,*/ WRITE_INTR_ID);
//		if (Status != XST_SUCCESS) {
//
//			xil_printf(
//			    "Setup interrupt system failed %d\r\n", Status);
//
//			return XST_FAILURE;
//		}
//		else
//		{
//			xil_printf(
//			    "Setup interrupt system succeeded");
//		}

		/* Register callback functions*/
		XAxiVdma_SetCallBack(&Vdma, XAXIVDMA_HANDLER_GENERAL,
		    WriteCallBack, (void *)&Vdma, XAXIVDMA_WRITE);

		XAxiVdma_SetCallBack(&Vdma, XAXIVDMA_HANDLER_ERROR,
		    WriteErrorCallBack, (void *)&Vdma, XAXIVDMA_WRITE);

		xil_printf(
		    "call back set up succeeded");
		/* If interrupts overwhelms the system, please do not enable interrupt*/
		XAxiVdma_IntrEnable(&Vdma, XAXIVDMA_IXR_ALL_MASK, XAXIVDMA_WRITE);
		xil_printf(
		    "intr enabled ");
	/*****************************************************************************/

	Status = vdma_write_start(&Vdma);
	if (Status != XST_SUCCESS) {
		   xil_printf("error starting VDMA..!");
		   return Status;
	}
	return XST_SUCCESS;

}


//
//static int SetupIntrSystem(XAxiVdma *AxiVdmaPtr/*, u16 ReadIntrId*/,
//				u16 WriteIntrId)
//{
//	int Status;
//
//#ifdef XPAR_INTC_0_DEVICE_ID
//	XIntc *IntcInstancePtr =&Intc;
//
//
//	/* Initialize the interrupt controller and connect the ISRs */
//	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
//	if (Status != XST_SUCCESS) {
//
//		xil_printf( "Failed init intc\r\n");
//		return XST_FAILURE;
//	}
//
//
//
//	Status = XIntc_Connect(IntcInstancePtr, WriteIntrId,
//	         (XInterruptHandler)XAxiVdma_WriteIntrHandler, AxiVdmaPtr);
//	if (Status != XST_SUCCESS) {
//
//		xil_printf(
//		    "Failed write channel connect intc %d\r\n", Status);
//		return XST_FAILURE;
//	}
//
//	/* Start the interrupt controller */
//	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
//	if (Status != XST_SUCCESS) {
//
//		xil_printf( "Failed to start intc\r\n");
//		return XST_FAILURE;
//	}
//
//	/* Enable interrupts from the hardware */
//	//XIntc_Enable(IntcInstancePtr, ReadIntrId);
//	XIntc_Enable(IntcInstancePtr, WriteIntrId);
//
//	Xil_ExceptionInit();
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
//			(Xil_ExceptionHandler)XIntc_InterruptHandler,
//			(void *)IntcInstancePtr);
//
//	Xil_ExceptionEnable();
//
//#else
//
//	XScuGic *IntcInstancePtr = &Intc;	/* Instance of the Interrupt Controller */
//	XScuGic_Config *IntcConfig;
//
//
//	/*
//	 * Initialize the interrupt controller driver so that it is ready to
//	 * use.
//	 */
//	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
//	if (NULL == IntcConfig) {
//		return XST_FAILURE;
//	}
//
//	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
//					IntcConfig->CpuBaseAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}
//
//	//XScuGic_SetPriorityTriggerType(IntcInstancePtr, ReadIntrId, 0xA0, 0x3);
//	//XScuGic_SetPriorityTriggerType(IntcInstancePtr, WriteIntrId, 0xA0, 0x3);
//
//	/*
//	 * Connect the device driver handler that will be called when an
//	 * interrupt for the device occurs, the handler defined above performs
//	 * the specific interrupt processing for the device.
//	 */
////	Status = XScuGic_Connect(IntcInstancePtr, ReadIntrId,
////				(Xil_InterruptHandler)XAxiVdma_ReadIntrHandler,
////				AxiVdmaPtr);
////	if (Status != XST_SUCCESS) {
////		return Status;
////	}
//
//	Status = XScuGic_Connect(IntcInstancePtr, WriteIntrId,
//				(Xil_InterruptHandler)XAxiVdma_WriteIntrHandler,
//				AxiVdmaPtr);
//	if (Status != XST_SUCCESS) {
//		return Status;
//	}
//
//	/*
//	 * Enable the interrupt for the DMA device.
//	 */
////	XScuGic_Enable(IntcInstancePtr, ReadIntrId);
//	XScuGic_Enable(IntcInstancePtr, WriteIntrId);
//
//	Xil_ExceptionInit();
//
//	/*
//	 * Connect the interrupt controller interrupt handler to the hardware
//	 * interrupt handling logic in the processor.
//	 */
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
//				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
//				IntcInstancePtr);
//
//
//	/*
//	 * Enable interrupts in the Processor.
//	 */
//	Xil_ExceptionEnable();
//
//
//#endif
//
//	return XST_SUCCESS;
//}



/*****************************************************************************/
/*
 * Call back function for write channel
 *
 * This callback only clears the interrupts and updates the transfer status.
 *
 * @param	CallbackRef is the call back reference pointer
 * @param	Mask is the interrupt mask passed in from the driver
 *
 * @return	None
*
******************************************************************************/
static void WriteCallBack(void *CallbackRef, u32 Mask)
{

	if (Mask & XAXIVDMA_IXR_FRMCNT_MASK) {
		xil_printf("\r\n frame transmit done \r\n");
        XAxiCdma_SimplePollExample(XPAR_AXICDMA_0_DEVICE_ID,frameBuf);
	}
}


/*****************************************************************************/
/*
* Call back function for write channel error interrupt
*
* @param	CallbackRef is the call back reference pointer
* @param	Mask is the interrupt mask passed in from the driver
*
* @return	None
*
******************************************************************************/
static void WriteErrorCallBack(void *CallbackRef, u32 Mask)
{

	if (Mask & XAXIVDMA_IXR_ERROR_MASK) {
		xil_printf("\r\n frame transmit error \r\n");
	}
}





