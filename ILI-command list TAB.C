/**
*ILI9486L command list TAB
*Author: SVCHAO
*Created: 2015/4/22
*
*
* BCTRL:Brightness Control.  0: brightness control block OFF. 
                             1: brightness control block ON.
							 
* BL:   Backlight Control.   0: backlight control OFF.
                             1: backlight control ON. 
							 
* DD:   Display Dimming Control.  0: display dimming OFF
                                  1: display dimming ON]
								  
*CABC:  Content Adaptive Brightness Control.								  
								  
*/
#define ILI_CMD_NOP              (0x00) //NOP
#define ILI_CMD_SOFT_RES         (0x01) //soft reset
#define ILI_CMD_R_IDENT_INFO  (0X04) //read display identification information
#define ILI_CMD_R_DISP_STATUS (0x09) //Read Display Status 
#deifne ILI_CMD_R_DISP_PWRMODE  (0x0A) //Read Display Power Mode
#define ILI_CMD_R_PIXEL_FORMAT     (0x0C) //Read Pixel Format
#define ILI_CMD_R_DISP_IMG_MODE  (0x0D) //Read display image mode
#define ILI_CMD_R_DISP_SIG_MODE  (0x0E) //read display signal mode
#define ILI_CMD_R_DISP_SELF_RESULT (0x0F) //read display self-diagnostic result
#define ILI_CMD_SLEEP_IN (0x10) //sleep in
#define ILI_CMD_SLEEP_OUT (0x11) //sleep out
#deifne ILI_CMD_PARTIAL_MODE  (0x12) //partial mode ON
#define ILI_CMD_NORMAL_MODE  (0x13) //normal display mode ON
#define ILI_CMD_DISP_INV_OFF (0x20) //display inversion OFF
#define ILI_CMD_DISP_INV_ON  (0x21) //display inversion ON
#define ILI_CMD_DISP_OFF  (0x28) //display OFF
#define ILI_CMD_DISP_ON   (0x29) //display ON
#deifne ILI_CMD_SET_COL_ADDR (0x2A) //column address set 
#define ILI_CMD_SET_PAGE_ADDR (0x2B) //page address set 
#define ILI_CMD_W_TO_MEM  (0x2C) //memory write
#define ILI_CMD_W_FROM_MEM (0x2E) //memory read
#deifne ILI_CMD_PART_AREA (0x30) //partial Area
#define ILI_CMD_VSCROLL (0x33) //vertical scrolling definition ´¹Ö±¹ö¶¯
#define ILI_CMD_TEL_OFF (0x34) //tearing effect line OFF
#define ILI_CMD_TEL_ON  (0x35) //tearing effect line ON
#define ILI_CMD_MEM_ACCESS_CTRL (0x36) //memory access control
#define ILI_CMD_VSCROLL_START_ADDR (0x37) //vertical scrolling start address
#define ILI_CMD_IDLE_MODE_OFF (0x38) //idle mode OFF
#define ILI_CMD_IDLE_MODE_ON  (0x39) //idle mode ON
#define ILI_CMD_IF_PIXEL_FORMAT (0x3A) //interfac pixel format
#define ILI_CMD_MEM_WRITE_CONTINUE (0x3C) //memory  wrtie continue 
#define ILI_CMD_MEM_READ_CONTINUE  (0x3E) //memory read continue
#define ILI_CMD_WRITE_TEAR_SCAN_LINE (0x44) //write tear  scan line
#define ILI_CMD_READ_TEAR_SCAN_LINE (0x45)  //read tear scan line 
#define ILI_CMD_WRITE_BRIGHTNESS_VAL (0x51) //write display brightness value 
#define ILI_CMD_READ_BRIGHTNESS_VAL (0x52)  //read display brightness value 
#define ILI_CMD_WRITE_CTRL_VAL (0x53)  //control BCTRL,DD,BL.
#define ILI_CMD_READ_CTRL_VAL   (0x54) //read  BCTRL,DD,BL.
#define ILI_CMD_WRITE_ADAPTIVE_VAL (0x55) //write content adaptive brightness control value.
#define ILI_CMD_READ_ADAPTIVAL_VAL (0x56) //read content adaptive brightness control value.
//#define ILI_CMD_READ_ID1 (0xDA)   //read ID1
//#define ILI_CMD_READ_ID2 (0xDB)   //read ID2
//#define ILI_CMD_READ_ID3 (0xDC)   //read ID3
#define ILI_CMD_READ_ID4 (0xD3))  //read ID4
#define ILI_CMD_

#

#define ILI_CMD_SLEEP_OUT       (0x11)
#deifne ILI_CMD_

























