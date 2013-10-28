
/**
 * \file 	netburner_comm.h
 * \author 	Forrest Stanley
 * \brief   Implements netburner _communication layer_ functions [see comm_layer.h and netburner_comm.c]
 */




#ifndef __NETBURNER_COMM_H__
#define __NETBURNER_COMM_H__

#include "connection.h"

#ifdef __cplusplus
extern "C" {
#endif

connection_t* netburner_open_connection( const char* address, int32_t port );
int netburner_send_data( connection_t* conn, const char* data, size_t size );
int netburner_read_data( connection_t* conn, char* buffer, size_t buffer_size );
void netburner_close_connection( connection_t* conn );

#ifdef __cplusplus
}
#endif

#endif // __NETBURNER_COMM_H__


