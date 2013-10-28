
#include "comm_layer.h"
#include "netburner_comm.h"

/**
 * \file 	netburner_comm_layer.c
 * \author 	Forrest Stanley
 * \brief   Implements netburner _communication layer_ functions [see comm_layer.h]
 */

 /**
  * \brief   Initialise NetBurner implementation of the _communication layer_
  */
const comm_layer_t* get_comm_layer()
{
    static comm_layer_t __netburner_comm_layer =
    {
          &netburner_open_connection
        , &netburner_send_data
        , &netburner_read_data
        , &netburner_close_connection
    };

    return &__netburner_comm_layer;
}
