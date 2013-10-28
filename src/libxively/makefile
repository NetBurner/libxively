#    Copyright 1998-2013 NetBurner, Inc.  ALL RIGHTS RESERVED
#    Permission is hereby granted to purchasers of NetBurner Hardware
#    to use or modify this computer program for any use as long as the
#    resultant program is only executed on NetBurner provided hardware.
#
#    No other rights to use this program or it's derivitives in part or
#    in whole are granted.
#
#    It may be possible to license this or other NetBurner software for
#    use on non NetBurner Hardware. Please contact Licensing@Netburner.com
#    for more information.
#
#    NetBurner makes no representation or warranties with respect to the
#    performance of this computer program, and specifically disclaims any
#    responsibility for any damages, special or consequential, connected
#    with the use of this program.
#
#    NetBurner, Inc
#    http://www.netburner.com

NAME = nb-libxively

CXXSRCS = \
	netburner_comm.cpp \

CSRCS = \
	csv_data.c \
	csv_data_layer.c \
	http_layer_parser.c \
	http_layer_queries.c \
	http_transport.c \
	http_transport_layer.c \
	netburner_comm_layer.c \
	xively.c \
	xi_err.c \
	xi_globals.c \
	xi_helpers.c \
	xi_time.c \

EXTRACXXFLAGS += \
	-DXI_DEBUG_OUTPUT=0 \
	-DXI_USER_AGENT='"nb-libxively"' \
	-DXI_DEBUG_ASSERT=0 \
	-I.
EXTRACFLAGS += $(EXTRACXXFLAGS) -std=c99

include $(NBROOT)/make/libmain.mak




