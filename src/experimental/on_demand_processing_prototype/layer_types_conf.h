#ifndef __LAYER_TYPES_CONF_H__
#define __LAYER_TYPES_CONF_H__

/**
 *\file     layer_types_conf.h
 *\author   Olgierd Humenczuk
 *\brief    containes set of macros required to create the layers types configuration
 */

#include "layer_type.h"

#define BEGIN_LAYER_TYPES_CONF() \
    const layer_type_t LAYER_TYPES[] = {

#define LAYER_TYPE_BEGIN( type_id ) \
    { type_id, ( layer_interface_t[] ) {

#define LAYER_VARIANT( on_demand, on_data_ready, close, on_close ) \
    { on_demand, on_data_ready, close, on_close }

#define LAYER_TYPE_END() \
    } }

#define END_LAYER_TYPES_CONF() \
    };

#endif // __LAYER_TYPES_CONF_H__
