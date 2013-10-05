#include <stdio.h>

#include "xi_consts.h"
#include "xively.h"

#include "common.h"
#include "layer_api.h"
#include "layer_interface.h"
#include "layer_connection.h"
#include "layer_types_conf.h"
#include "layer_factory.h"
#include "layer_factory_conf.h"
#include "layer_default_allocators.h"

#include "posix_io_layer.h"
#include "http_layer.h"

enum LAYERS_ID
{
      IO_LAYER = 0
    , HTTP_LAYER
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CONNECTION_SCHEME_1_DATA IO_LAYER, HTTP_LAYER
DEFINE_CONNECTION_SCHEME( CONNECTION_SCHEME_1, CONNECTION_SCHEME_1_DATA );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_LAYER_TYPES_CONF()
      LAYER_TYPE( IO_LAYER, &posix_io_layer_data_ready, &posix_io_layer_on_data_ready
                          , &posix_io_layer_close, &posix_io_layer_on_close )
    , LAYER_TYPE( HTTP_LAYER, &http_layer_data_ready, &http_layer_on_data_ready
                                    , &http_layer_close, &http_layer_on_close )
END_LAYER_TYPES_CONF()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_FACTORY_CONF()
      FACTORY_ENTRY( IO_LAYER, &placement_layer_pass_create, &placement_layer_pass_delete
                             , &default_layer_heap_alloc, &default_layer_heap_free )
    , FACTORY_ENTRY( HTTP_LAYER, &placement_layer_pass_create, &placement_layer_pass_delete
                                       , &default_layer_heap_alloc, &default_layer_heap_free )
END_FACTORY_CONF()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, const char* argv[] )
{
    ( void ) argc;
    ( void ) argv;

    void* user_datas[] = { 0, 0 };

    layer_chain_t layer_chain = create_and_connect_layers( CONNECTION_SCHEME_1, user_datas, CONNECTION_SCHEME_LENGTH( CONNECTION_SCHEME_1 ) );

    layer_t* io_layer = connect_to_endpoint( layer_chain.bottom, XI_HOST, XI_PORT );
    layer_t* http_layer = layer_chain.top;

    printf( "%d\n", http_layer->layer_type_id );

    xi_context_t* context = xi_create_context( XI_HTTP, "1", 2 );
    http_layer_data_t http_layer_data = { HTTP_LAYER_DATA_DATASTREAM_GET, context, { { "3" } } };

    if( io_layer == 0 )
    {
        printf( "Could not connect to the endpoint\n" ); exit( 1 );
    }

    // prepare the xi data
    CALL_ON_SELF_DATA_READY( http_layer, ( void *) &http_layer_data, LAYER_HINT_NONE );

	return 0;
}
