#include "serial.h"

serial_vars_t serial_vars;

enum
{
    HDLC_FLAG   = 0x7e,
    HDLC_ESCAPE = 0X7d,
    HDLC_MASK   = 0x20
};

enum {WAIT_START, WAIT_END};

void serial_processByte(uint8_t c)
{
    // reset if input buffer overflow
    if (serial_vars.input_buffer_index == SERIAL_INPUT_BUFFER_SIZE)
    {
        serial_vars.input_buffer_index = 0;
        serial_vars.input_escaping = false;
        serial_vars.buf_state = WAIT_START;
        return;
    }

    switch (serial_vars.buf_state)
    {
    case WAIT_START:
        if (c == HDLC_FLAG)
        {
            serial_vars.buf_state = WAIT_END;
        }
        return;
    case WAIT_END:
        if (serial_vars.input_escaping == true)
        {
            serial_vars.input_buffer[serial_vars.input_buffer_index++] = c^HDLC_MASK;
            serial_vars.input_escaping = false;
        }
        else if (c == HDLC_ESCAPE)
        {
            serial_vars.input_escaping = true;
        }
        else if (c == HDLC_FLAG)
        {
            serial_vars.buf_state = WAIT_START;
            if (serial_vars.input_buffer_index > 0 &&
                serial_vars.rxCb != NULL)
            {
                // receive done and invoke callback function
                // uart_disableInterrupts();
                serial_vars.rxCb();
            }
        }
        else
        {
            serial_vars.input_buffer[serial_vars.input_buffer_index++] = c;
        }
        return;
    }
}

void isr_serial_tx()
{
    if (serial_vars.output_buffer_index < serial_vars.output_buffer_len) {
        uart_writeByte(serial_vars.output_buffer[serial_vars.output_buffer_index++]);
    }
    else
    {
        serial_vars.output_buffer_index = 0;
        serial_vars.output_buffer_len = 0;
    }
}

void isr_serial_rx()
{
    serial_processByte(uart_readByte());
}

void serial_init()
{
    serial_vars.output_buffer_index = 0;
    serial_vars.output_buffer_len = 0;

    uart_setCallbacks(isr_serial_tx, isr_serial_rx);
}

void serial_setCallbacks(serial_rx_cbt rxCb)
{
    serial_vars.rxCb = rxCb;
}


uint8_t serial_getInputBuffer(uint8_t* bufferToWrite, uint8_t maxNumBytes)
{
    uint16_t input_len = serial_vars.input_buffer_index;
    serial_vars.input_buffer_index = 0;
    if (maxNumBytes < input_len)
        return 0;
    memcpy(bufferToWrite, &(serial_vars.input_buffer[0]), input_len);
    return input_len;
}

void serial_startInput()
{
    serial_vars.input_buffer_index = 0;
    serial_vars.input_escaping = false;
    serial_vars.buf_state = WAIT_START;

    uart_clearTxInterrupts();
    uart_clearRxInterrupts();          // clear possible pending interrupts
    uart_enableInterrupts();           // Enable USCI_A1 TX & RX interrupt
    ENABLE_INTERRUPTS();
}

void serial_startOutput()
{
    uart_clearTxInterrupts();
    uart_clearRxInterrupts();          // clear possible pending interrupts
    uart_enableInterrupts();           // Enable USCI_A1 TX & RX interrupt
    ENABLE_INTERRUPTS();

    if (serial_vars.output_buffer_len > 0)
    {
        serial_vars.output_buffer_index = 0;
        uart_writeByte(serial_vars.output_buffer[serial_vars.output_buffer_index++]);
    }
}

void serial_send_raw(uint8_t* buffer, uint16_t length)
{
    uint8_t counter;

    DISABLE_INTERRUPTS();

    serial_vars.output_buffer_index = 0;
    for (counter = 0; counter < length; counter++)
    {
        serial_vars.output_buffer[serial_vars.output_buffer_index++] = (uint8_t)buffer[counter];
    }
    serial_vars.output_buffer_len = serial_vars.output_buffer_index;
    ENABLE_INTERRUPTS();
}


// serial send by HDLC
void serial_send(uint8_t* buffer, uint16_t length)
{
    uint8_t counter;
    
    if (length > SERIAL_OUTPUT_BUFFER_SIZE - 20)
        return;

    DISABLE_INTERRUPTS();

    serial_vars.output_buffer_index = 0;
    serial_vars.output_buffer[serial_vars.output_buffer_index++] = HDLC_FLAG;

    for (counter = 0; counter < length; counter++)
    {
        if (buffer[counter] == HDLC_FLAG || buffer[counter] == HDLC_ESCAPE) {
            serial_vars.output_buffer[serial_vars.output_buffer_index++] = HDLC_ESCAPE;
            serial_vars.output_buffer[serial_vars.output_buffer_index++] = (buffer[counter])^HDLC_MASK;
        }
        else
        {
            serial_vars.output_buffer[serial_vars.output_buffer_index++] = (uint8_t)buffer[counter];
        }
    }
    serial_vars.output_buffer[serial_vars.output_buffer_index++] = HDLC_FLAG;
    serial_vars.output_buffer_len = serial_vars.output_buffer_index;
    ENABLE_INTERRUPTS();
}



