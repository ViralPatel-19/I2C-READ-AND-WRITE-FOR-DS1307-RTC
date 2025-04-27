#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#define I2C_SLAVE_ADDR  (0x68U)    // DS1307 I2C address
#define I2C_TIMEOUT     (100U)     // Timeout for I2C operations in ms

cy_stc_scb_i2c_context_t i2cContext;

void I2C_Isr(void)
{
    Cy_SCB_I2C_Interrupt(SCB3, &i2cContext);
}

uint8_t bcdToDec(uint8_t val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

int main(void)
{
    cy_rslt_t result;
    cy_stc_scb_i2c_master_xfer_config_t xferConfig;

    uint8_t timeReadBuffer[7];  // Buffer to hold the time data read from the DS1307
    uint8_t timeAddress = 0x00; // Starting address for reading time

    result = cybsp_init();
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    result = cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX,
                                    CYBSP_DEBUG_UART_RX,
                                    CYBSP_DEBUG_UART_CTS,
                                    CYBSP_DEBUG_UART_RTS,
                                    CY_RETARGET_IO_BAUDRATE);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    // Initialize the I2C block (SCB3 is used as an example)
    Cy_SCB_I2C_Init(SCB3, &scb_3_config, &i2cContext);

    const cy_stc_sysint_t i2cIntrConfig =
    {
        .intrSrc      = scb_3_interrupt_IRQn,
        .intrPriority = 7,
    };

    (void) Cy_SysInt_Init(&i2cIntrConfig, &I2C_Isr);
    NVIC_EnableIRQ(scb_3_interrupt_IRQn);

    Cy_SCB_I2C_Enable(SCB3);
    __enable_irq();

    printf("I2C Master: Reading time data from DS1307...\r\n");

    // Step 1: Set up to write the register address to DS1307
    xferConfig.slaveAddress = I2C_SLAVE_ADDR;
    xferConfig.buffer       = &timeAddress;
    xferConfig.bufferSize   = sizeof(timeAddress);
    xferConfig.xferPending  = true; // Do not generate STOP condition after the write

    result = Cy_SCB_I2C_MasterWrite(SCB3, &xferConfig, &i2cContext);

    if (result == CY_SCB_I2C_SUCCESS)
    {
        while (0UL != (CY_SCB_I2C_MASTER_BUSY & Cy_SCB_I2C_MasterGetStatus(SCB3, &i2cContext)))
        {
        }

        // Step 2: Read 7 bytes of time data from the DS1307
        xferConfig.slaveAddress = I2C_SLAVE_ADDR;
        xferConfig.buffer       = timeReadBuffer;
        xferConfig.bufferSize   = sizeof(timeReadBuffer);
        xferConfig.xferPending  = false; // Generate STOP condition after reading

        result = Cy_SCB_I2C_MasterRead(SCB3, &xferConfig, &i2cContext);

        if (result == CY_SCB_I2C_SUCCESS)
        {
            while (0UL != (CY_SCB_I2C_MASTER_BUSY & Cy_SCB_I2C_MasterGetStatus(SCB3, &i2cContext)))
            {
            }

            // Convert BCD to Decimal and print the time
            uint8_t seconds = bcdToDec(timeReadBuffer[0] & 0x7F); // Mask to ignore CH bit
            uint8_t minutes = bcdToDec(timeReadBuffer[1]);
            uint8_t hours   = bcdToDec(timeReadBuffer[2] & 0x3F); // Mask to ignore 12/24 hour mode bit
            uint8_t day     = bcdToDec(timeReadBuffer[3]);
            uint8_t date    = bcdToDec(timeReadBuffer[4]);
            uint8_t month   = bcdToDec(timeReadBuffer[5]);
            uint8_t year    = bcdToDec(timeReadBuffer[6]);

            printf("Time: %02u:%02u:%02u, Date: %02u-%02u-20%02u, Day : %02u \r\n", hours, minutes, seconds, date, month, year, day);
        }
        else
        {
            printf("Failed to read time data.\r\n");
        }
    }
    else
    {
        printf("Failed to set DS1307 register pointer.\r\n");
    }

    for (;;)
    {
        // Main loop does nothing; the program is done after sending the data
    }
}
