/* Erik Nielsen - POC on ESP32 with Nextion 3.5 Basic Display
*	Developed on Generic ESP32-WROOM-DevkitC using the esp-edf v3.1Dev branch from GitHub 
*
*	esp32-nextion.h
*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE":
* <duderu> hanging at gmail- wrote this file.  As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return. duderu
* ----------------------------------------------------------------------------
  This software is FREE and thus distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
*/
//
//
//
//
/* -----------Stuff to think about or just Do
*static const char* nxEND = "ÿÿÿ"; //termination characters for Nextion commands-- (Oxff,0xff,0xff) in Hex
*
*
*/
static const int RX_BUF_SIZE = 1024;
static const char *TX_TASK_TAG = "TX_TASK";
static const char *RX_TASK_TAG = "RX_TASK";
static const char *ESP_SOFT_RESET = "espreset";


//This defines the UART(0,1,2) and the TX/RX pins on the ESP32
//Default showing is for UART2 Pins 16,17 for the ESP32-WROOM-DevKitC breakout board.
//
//This should really go into the menuconfig for esp-idf
#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)
#define nUART	(UART_NUM_2)
