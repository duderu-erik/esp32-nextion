/* Erik Nielsen - POC on ESP32 with Nextion 3.5 Basic Display
*	Developed on Generic ESP32-WROOM32-DevkitC using the esp-edf v3.1Dev branch from GitHub 
*
*	esp32-nextion.c
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


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "string.h"
#include "esp32-nextion.h"

void initNextion() {
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(nUART, &uart_config);
    uart_set_pin(nUART, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    // We won't use a buffer for sending data.
    uart_driver_install(nUART, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

int sendData(const char* logName, const char* data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(nUART, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

static void tx_task()
{
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1) {
		// OK so here is where you can play around and change values or add text and/or numeric fields to the Nextion and update them
		sendData(TX_TASK_TAG, "page0.tempout.txt=\"69\"ÿÿÿ");		//example text value - Outside temp
		sendData(TX_TASK_TAG, "page0.temppool.txt=\"70\"ÿÿÿ");		//example text value - Pool temp
		sendData(TX_TASK_TAG, "page0.tempspa.txt=\"71\"ÿÿÿ");		//exapmle text value - SPA temp
		sendData(TX_TASK_TAG, "page0.n0.val=69ÿÿÿ");            	//demonstrates a numeric value -- note how the ÿÿÿ is not escaped. 
		sendData(TX_TASK_TAG, "page4.tdebug.txt=page4.tdebug.txt+\"Hello from ESP32\\r\"ÿÿÿ");	//text value that carriage returns. 254 char max in Nextion text boxes.
        vTaskDelay(10000 / portTICK_PERIOD_MS); //Transmit every 10 seconds
    }
}

static void rx_task()
{
	esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);
    char *dstream = malloc(RX_BUF_SIZE+1);
	while (1) {
        const int rxBytes = uart_read_bytes(nUART, data, RX_BUF_SIZE, 1000 / portTICK_RATE_MS);
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
			//
			// if it sees the incoming 'espreset' text then reboot the ESP32.
			snprintf(dstream, RX_BUF_SIZE+1, "%s", data);
			char *ismatch = strstr(dstream, ESP_SOFT_RESET);
			if (ismatch) {
				//esp_restart() is an esp-idf function---check for deprecation
				esp_restart();
			}
        }
    }
    free(data);
	free(dstream);
}

void app_main()
{
    initNextion();
	//Send one time boot up values
	sendData(TX_TASK_TAG, "page0.tinfo.txt=\"ESP32 to Nextion example - tinfo\"ÿÿÿ");
	sendData(TX_TASK_TAG, "page0.gblinfo.txt=\"ESP32 to Nextion example - gblinfo\"ÿÿÿ");
	sendData(TX_TASK_TAG, "page3.tabout.txt=\"ESP32 to Nextion example- tabout\"ÿÿÿ");
	
	//create the asynchronous send and receive tasks 
    xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);
}
