#  -*- mode: python; -*-
#============================================================================
# Python configuration setup for 'xm create'.
# This script sets the parameters used when a domain is created using 'xm create'.
# You use a separate script for each domain you want to create, or
# you can set the parameters for the domain on the xm command line.
#============================================================================

#----------------------------------------------------------------------------
# Kernel image file.
kernel = "../bin/xen/latency-llamaMPI.gz"

extra = "--node 0"

# Initial memory allocation (in megabytes) for the new domain.
memory = 1024

# A name for your domain. All domains must have different names.
name = "latency-llamaMPI"

on_crash = 'destroy'

cpus="2"
