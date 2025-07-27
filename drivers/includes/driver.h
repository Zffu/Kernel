/**
 * Driver Definitions
 */

#pragma once

typedef unsigned char byte_t;
typedef unsigned short word_t;

typedef unsigned short port;

byte_t port_get_byte(port port);
void port_put_byte(port port, byte_t data);

word_t port_get_word(port port);
void port_put_word(port port, word_t data);