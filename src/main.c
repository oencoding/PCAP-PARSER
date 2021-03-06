#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("No filename specified\n");
        return 1;
    }

    char* filename = argv[1];   //just to make it more readable
    parser_t parser;
    initParser(&parser);

    if(parse(&parser, filename) == NOK){
        printf("\n\nPARSING FAILED\n\n");
        exit(1);
    }

    processFrames(parser.frame_list, &parser.packet_list);
    processPackets(parser.packet_list, &parser.datagram_list);

    clearFrames(&parser.frame_list);

    printf("Total number of datagrams: ");
    printLongLong(numDatagrams(&parser));
    printf("\n\n");
    printUDPStats();
    print4thLayer(&parser);

    clearPackets(&parser.packet_list);
    clearDatagrams(&parser.datagram_list);

    return 0;
}
