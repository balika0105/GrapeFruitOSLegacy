#!/bin/bash


# This script is for preparing the development environment for the OS
# It is based on AbsurdPoncho's (https://github.com/Absurdponcho) tutorial series
# This is supposed to automate the setup with dialog screens

# It only runs on Debian-based systems (tested with Ubuntu)
# Since 'dialog' package is required, it will auto-install that, among others


#Pre-defining install thing
function do_install(){
	clear
	sudo apt update && sudo apt upgrade -y
	sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo nasm -y
	export PREFIX="/usr/local/x86_64elfgcc"
	export TARGET=x86_64-elf
	export PATH="$PREFIX/bin:$PATH"
	mkdir /tmp/src
	cd /tmp/src
	curl -O https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.gz
	tar xf binutils-2.37.tar.gz
	mkdir binutils-build
	cd binutils-build
	../binutils-2.37/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
	sudo make all install 2>&1 | tee make.log
	cd /tmp/src
	curl -O https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.gz
	tar xf gcc-11.2.0.tar.gz
	mkdir gcc-build
	cd gcc-build
	../gcc-11.2.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --disable-libssp --enable-language=c++ --without-headers

	# Make gcc warning
	dialog --title "Making gcc" --msgbox "The script will now proceed to make gcc. This will take a long time. Make a coffee, or if your machine is ancient, go for a run" 7 50

	sudo make all-gcc

	# Finishing steps
	sudo make all-target-libgcc
	sudo make install-gcc
	sudo make install-target-libgcc

	# Finishing up
	clear
	dialog --title "Setup complete" --msgbox "Installation complete! You can now use the environment!" 5 59
	#echo "Script end"
	echo "Script by github.com/balika0105"

}


# This part of the script checks if 'dialog' is installed, if not, auto-install
REQUIRED_PKG="dialog curl"
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG | grep "install ok installed")
echo "Checking for $REQUIRED_PKG: $PKG_OK"
if [ "" = "$PKG_OK" ]; then
  echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
  sudo apt-get --yes install $REQUIRED_PKG
fi

dialog --title "Setup script for AbsurdPoncho's development environment" \
--msgbox "This script will install packages and set up some environment variables\nThe script installs packages with apt. If you don't have apt, please exit\nIf you want more details, please exit and open the script in an editor of choice" 10 70

# Making a super fancy menu screen

dialog --title "Start installation procedure" --yesno "Are you sure that you want to start the installation?" 5 57

response=$?
case $response in
	0) do_install;;
	1) clear && echo "Installation aborted";;
esac
