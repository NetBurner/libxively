/**
 * \file    netburner_comm.c
 * \author  Forrest Stanley
 * \brief   Implements netburner _communication layer_ abstraction interface [see comm_layer.h]
 */


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "netburner_comm.h"
#include "comm_layer.h"
#include "xi_helpers.h"
#include "xi_allocator.h"
#include "netburner_comm_layer_data_specific.h"
#include "xi_debug.h"
#include "xi_err.h"
#include "xi_macros.h"
#include "xi_globals.h"

#include <tcp.h>
#include <utils.h>
#include <iosys.h>
#include <dns.h>


connection_t* netburner_open_connection( const char* address, int32_t port )
{
	netburner_comm_layer_data_specific_t* netburner_comm_data = 0;
	connection_t* conn = 0;
	netburner_comm_data = ( netburner_comm_layer_data_specific_t* ) xi_alloc(
			sizeof(netburner_comm_layer_data_specific_t));

	conn = (connection_t*) xi_alloc(sizeof(connection_t));
	conn->address = xi_str_dup( address );
	conn->port = port;

	IPADDR host;
	GetHostByName( address, &host,0,0 );

	netburner_comm_data->socket_fd = connect(host,0,port,0);

	// save netburner layer specific connection details
    conn->layer_specific = (void*) netburner_comm_data;
    if( netburner_comm_data->socket_fd < 0 )
    {
        xi_set_err( XI_SOCKET_CONNECTION_ERROR );
        if( netburner_comm_data ) { XI_SAFE_FREE( netburner_comm_data ); }
        if( conn ) { XI_SAFE_FREE( conn->address ) }
        XI_SAFE_FREE(conn);
        return 0;
    }
    return conn;

}



int netburner_send_data( connection_t* conn, const char* data, size_t size )
{
	netburner_comm_layer_data_specific_t* netburner_comm_data =
			( netburner_comm_layer_data_specific_t* ) conn->layer_specific;

	int bytes_written = write(netburner_comm_data->socket_fd,data,size);

	if ( bytes_written == -1 ) {
		xi_set_err( XI_SOCKET_WRITE_ERROR );
	}

	conn->bytes_sent += bytes_written;

	return bytes_written;
}

int netburner_read_data( connection_t* conn, char* buffer, size_t buffer_size )
{
	netburner_comm_layer_data_specific_t* netburner_comm_data =
			( netburner_comm_layer_data_specific_t* ) conn->layer_specific;

    memset( buffer, 0, buffer_size );

	int bytes_read = ReadWithTimeout( netburner_comm_data->socket_fd, buffer, buffer_size,10 * TICKS_PER_SECOND);

	if( bytes_read < 0 ) {
		xi_set_err( XI_SOCKET_READ_ERROR );
	}

	conn->bytes_received += bytes_read;

	return bytes_read;
}

void netburner_close_connection( connection_t* conn )
{
	netburner_comm_layer_data_specific_t* netburner_comm_data =
			( netburner_comm_layer_data_specific_t* ) conn->layer_specific;

    if( close( netburner_comm_data->socket_fd ) != 0 )
    {
        xi_set_err( XI_SOCKET_CLOSE_ERROR );
        if( conn ) { XI_SAFE_FREE( conn->layer_specific ); }
        if( conn ) { XI_SAFE_FREE( conn->address ); }
        XI_SAFE_FREE( conn );
    }

	return;
}
