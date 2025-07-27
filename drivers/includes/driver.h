/**
 * Driver Definitions
 */

#pragma once

#include <types.h>

/**
 * @name port_get_byte
 * 
 * Get a byte from the specified port
 * 
 * @param port the port
 * @return the byte
 */
byte_t port_get_byte(port port);

/**
 * @name port_put_byte
 * 
 * Puts a byte on the specified port
 * 
 * @param port the port
 * @param data the byte to put
 */
void port_put_byte(port port, byte_t data);

/**
 * @name port_get_word
 * 
 * Gets a word from the specified port
 * 
 * @param port the port
 * @return the word
 */
word_t port_get_word(port port);

/**
 * @name port_put_put
 * 
 * Puts a word on the specified port
 * 
 * @param port the port
 * @param data the word to put
 */
void port_put_word(port port, word_t data);