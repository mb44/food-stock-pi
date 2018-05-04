#############################################################################
#
# Makefile for foodsupplymonitor on Linux
#
# License: GPL (General Public License)
# Author:  Morten Beuchert <214565@via.dk>
# Date:    2018/05/04 (version 1.0)
#
# Description:
# ------------
# use make all and make install to install the examples
#

ifeq ($(wildcard ../Makefile.inc), )
	$(error Configuration not found. Run ./configure first)
endif

include ../Makefile.inc

# define all programs
PROGRAMS = foodsupplymonitor

include Makefile.examples
