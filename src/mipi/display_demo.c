
/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "display_demo.h"
#include <stdio.h>
#include "math.h"
#include <ctype.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xiicps.h"
#include "vdma.h"
#include "i2c/PS_i2c.h"
#include "xgpiops.h"
#include "sleep.h"
#include "dp/dp.h"
#include "ov5640.h"
#include "config.h"
#include "demosaic.h"
#include "gamma_lut.h"
#include "cdma/xaxicdma_simple_poll_header.h"

#if P1080 == 1
#define HORSIZE 1920*4
#define VERSIZE 1080
#else
#define HORSIZE 1280*4
#define VERSIZE 720
#endif

#define CAM_EMIO	78
/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

/*
 * Display Driver structs
 */

XIicPs ps_i2c0;
XGpioPs Gpio;

/*
 * Framebuffers for video data
 */
u8 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME] __attribute__ ((aligned(256)));
u8 *pFrames[DISPLAY_NUM_FRAMES]; //array of pointers to the frame buffers

int PsGpioSetup() ;

int main(void)
{

	int Status;
	int i ;

	Xil_DCacheDisable();
	Xil_ICacheDisable();


	/*
	 * Initialize an array of pointers to the 3 frame buffers
	 */
	for (i = 0; i < DISPLAY_NUM_FRAMES; i++)
	{
		pFrames[i] = frameBuf[i];
		memset(pFrames[i], 0, DEMO_MAX_FRAME);
	}

	PsGpioSetup() ;
	/*
	 * Reset sensor
	 */
	XGpioPs_WritePin(&Gpio, CAM_EMIO, 0) ;
	usleep(1000000);
	XGpioPs_WritePin(&Gpio, CAM_EMIO, 1) ;
	usleep(1000000);

	i2c_init(&ps_i2c0, XPAR_XIICPS_0_DEVICE_ID,100000);

	
	/*
	 * DP dma demo
	 */
	xil_printf("DPDMA Generic Video Example Test \r\n");
	Status = DpdmaVideoExample(&RunCfg, pFrames[0]);
	if (Status != XST_SUCCESS) {
		xil_printf("DPDMA Video Example Test Failed\r\n");
		return XST_FAILURE;
	}

	gamma_lut_init();
	demosaic_init();

	/* Start Sensor Vdma */
	//vdma_write_init(XPAR_AXIVDMA_0_DEVICE_ID,HORSIZE,VERSIZE,DEMO_STRIDE,(unsigned int)pFrames[0]);
	vdma_write_init(XPAR_AXIVDMA_0_DEVICE_ID,HORSIZE,VERSIZE,DEMO_STRIDE,(unsigned int)0x0000000080000000);


	/*
	 * Initialize Sensor
	 */
	sensor_init(&ps_i2c0);

//	   {
//	      int status;
//
//	      print("\r\n Running XAxiCdma_SimplePollExample() for axi_cdma_0...\r\n");
//
//	      status = XAxiCdma_SimplePollExample(XPAR_AXI_CDMA_0_DEVICE_ID);
//
//	      if (status == 0) {
//	         print("XAxiCdma_SimplePollExample Test PASSED\r\n");
//	      }
//	      else {
//	         print("XAxiCdma_SimplePollExample Test FAILED\r\n");
//	      }
//	   }
	return 0;
}


int PsGpioSetup()
{
	XGpioPs_Config *GPIO_CONFIG ;
	int Status ;

	GPIO_CONFIG = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID) ;

	Status = XGpioPs_CfgInitialize(&Gpio, GPIO_CONFIG, GPIO_CONFIG->BaseAddr) ;
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE ;
	}
	/* set MIO 54 as output */
	XGpioPs_SetDirectionPin(&Gpio, CAM_EMIO, 1) ;

	XGpioPs_SetOutputEnablePin(&Gpio, CAM_EMIO, 1);


	return XST_SUCCESS ;
}
