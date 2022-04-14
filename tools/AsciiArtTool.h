//
// Created by eyal on 11/04/2022.
//

#ifndef MTM_EX1_ASCIIARTTOOL_H
#define MTM_EX1_ASCIIARTTOOL_H
#include "../RLEList.h"





/**
*   asciiArtRead: Reads the given file and returns its content encoded as a RLE list.
*
* @param in_stream - The file.
* @return
* 	RLEList that contains the content of the file.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
*   asciiArtPrint: parse the image that is writen in a RLEList form
*   and prints the result.
* @param list - The List containing the image.
* @param out_stream
* @return
* 	RLEList that contains the content of the file.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 *   asciiArtPrintEncoded: prints the image encoded into the file and prints the result
 * @param list - The List containing the image.
 *  @param out_stream -
 *  @return RLEList that contains the content of the file.
 *
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //MTM_EX1_ASCIIARTTOOL_H
