#ifndef SERIAL_H_
#define SERIAL_H_

#define SERIAL_OUTPUT_BUFFER_SIZE 256
#define SERIAL_INPUT_BUFFER_SIZE  256


typedef void (*serial_rx_cbt)();

typedef struct {
    uint8_t output_buffer[SERIAL_OUTPUT_BUFFER_SIZE];
    uint8_t input_buffer[SERIAL_INPUT_BUFFER_SIZE];

    uint8_t output_buffer_len;
    uint8_t output_buffer_index;
    uint8_t input_buffer_index;

    uint8_t buf_state;
    bool    input_escaping;

    serial_rx_cbt rxCb;
} serial_vars_t;

void    serial_init();
void    serial_setCallbacks(serial_rx_cbt rxCb);
void    serial_startInput();
uint8_t serial_getInputBuffer(uint8_t* bufferToWrite, uint8_t maxNumBytes);
void    serial_send_raw(uint8_t* buffer, uint16_t length);
void    serial_send(uint8_t* buffer, uint16_t length);
void    serial_startOutput();

#endif /* SERIAL_H_ */
