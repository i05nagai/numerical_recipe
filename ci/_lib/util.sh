#!/bin/bash

#
# return:
#   * 14.04
#   * 16.06
#   * etc.
#
get_ubuntu_version()
{
  cat /etc/lsb-release | grep "DISTRIB_RELEASE" | awk -F '=' '{ print $2 }'
}

