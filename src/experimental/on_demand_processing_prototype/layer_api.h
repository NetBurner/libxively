#ifndef __LAYER_API_H__
#define __LAYER_API_H__

#include "layer.h"

#ifdef __DEBUG
#define LAYER_LOCAL_INSTANCE( layer_name_instance, layer_interface, layer_type_id, user_data )\
    layer_t layer_name_instance                     = { layer_interface, { 0, 0, 0 }, layer_type_id, ( void* ) user_data, { 0, 0, 0, 0, 0, 0 } };\
    INIT_INSTANCE( layer_name_instance )
#define INIT_INSTANCE( instance )\
    instance.layer_connection.self                  = &instance;\
    instance.debug_info.debug_line_init             = __LINE__;\
    instance.debug_info.debug_file_init             = __FILE__;
#else
#define LAYER_LOCAL_INSTANCE( layer_name_instance, layer_interface, layer_type_id, user_data )\
    layer_t   layer_name_instance                   = { layer_interface, { 0, 0, 0 }, layer_type_id, ( void* ) user_data };\
    INIT_INSTANCE( layer_name_instance )
#define INIT_INSTANCE( instance )\
    instance.layer_connection.self                  = &instance;
#endif

#ifdef __DEBUG
#define CONNECT_LAYERS( lp_i, ln_i )\
    ln_i->layer_connection.prev  = lp_i;\
    lp_i->layer_connection.next  = ln_i;\
    lp_i->debug_info.debug_line_connect = __LINE__;\
    lp_i->debug_info.debug_file_connect = __FILE__;\
    ln_i->debug_info.debug_line_connect = __LINE__;\
    ln_i->debug_info.debug_file_connect = __FILE__;
#else
#define CONNECT_LAYERS( lp_i, ln_i )\
    ln_i->layer_connection.prev  = lp_i;\
    lp_i->layer_connection.next  = ln_i
#endif

#define LAYER_GET_CONTEXT_PTR( instance )\
    &instance->layer_connection

#ifdef __DEBUG
#define SET_DEBUG_INFO_ON( layer, context )\
    context->layer_connection.layer->debug_info.debug_line_last_call = __LINE__;\
    context->layer_connection.layer->debug_info.debug_file_last_call = __FILE__;
#endif

#ifdef __DEBUG
#define CALL_ON( layer, target, context )\
    context->layer_connection.layer->layer_functions->target( &context->layer_connection.layer->layer_connection );\
    SET_DEBUG_INFO_ON( layer, context );
#define CALL_ON2( layer, target, context, buffer, size )\
    context->layer_connection.layer->layer_functions->target( &context->layer_connection.layer->layer_connection, buffer, size );\
    SET_DEBUG_INFO_ON( layer, context )
#else
#define CALL_ON( layer, target, context )\
    context->layer_connection.layer->layer_functions->target( &context->layer_connection.layer->layer_connection );
#define CALL_ON2( layer, target, context, buffer, size )\
    context->layer_connection.layer->layer_functions->target( &context->layer_connection.layer->layer_connection, buffer, size )
#endif

// ON_DEMAND
#define CALL_ON_SELF_ON_DEMAND( context, buffer, size )\
    CALL_ON2( self, on_demand, context, buffer, size )

#define CALL_ON_NEXT_ON_DEMAND( context, buffer, size )\
    CALL_ON2( next, on_demand, context, buffer, size )

#define CALL_ON_PREV_ON_DEMAND( context, buffer, size )\
    CALL_ON2( prev, on_demand, context, buffer, size )

// ON_DATA_READY
#define CALL_ON_SELF_ON_DATA_READY( context, buffer, size )\
    CALL_ON2( self, on_data_ready, context, buffer, size )

#define CALL_ON_NEXT_ON_DATA_READY( context, buffer, size )\
    CALL_ON2( next, on_data_ready, context, buffer, size )

#define CALL_ON_PREV_ON_DATA_READY( context, buffer, size )\
    CALL_ON2( prev, on_data_ready, context, buffer, size )

// CLOSE
#define CALL_ON_SELF_CLOSE( context )\
    CALL_ON( self, close, context )

#define CALL_ON_NEXT_CLOSE( context )\
    CALL_ON( next, close, context )


#define CALL_ON_PREV_CLOSE( context )\
    CALL_ON( prev, close, context )

// ON_CLOSE
#define CALL_ON_SELF_ON_CLOSE( context )\
    CALL_ON( self, on_close, context )

#define CALL_ON_NEXT_ON_CLOSE( context )\
    CALL_ON( next, on_close, context )

#define CALL_ON_PREV_ON_CLOSE( context )\
    CALL_ON( prev, on_close, context )


#endif // __LAYER_API_H__
