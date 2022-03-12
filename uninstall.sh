#!/bin/bash

function do_uninstall(){
    echo "Deleting GCC directory"
    sudo rm -rf /usr/local/x86_64elfgcc
}

dialog --title "Uninstall script for AbsurdPoncho's development environment" \
--msgbox "This script will remove the cross-compiler GCC from your machine, and clear the necessary environment variables" 10 70

# Making a super fancy menu screen

dialog --title "Start uninstall procedure" --yesno "Are you sure you want to uninstall the environment?" 5 57

response=$?
case $response in
	0) do_uninstall;;
	1) clear && echo "Process aborted";;
esac
