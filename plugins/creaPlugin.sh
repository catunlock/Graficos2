#!/bin/bash

OLDPLUGIN=$1
NEWPLUGIN=$2

if [ "$#" -ne 2 ]; then
    echo "Usage: ./creaPlugin.sh <name_base> <name_new>"
    exit
fi

echo "SUBDIRS+=${NEWPLUGIN}" >> plugins.pro

cp -R $PWD/$OLDPLUGIN $PWD/$NEWPLUGIN

cd $PWD/$NEWPLUGIN

mv $OLDPLUGIN.cpp $NEWPLUGIN.cpp
mv $OLDPLUGIN.frag $NEWPLUGIN.frag
mv $OLDPLUGIN.h $NEWPLUGIN.h
mv $OLDPLUGIN.vert $NEWPLUGIN.vert
mv $OLDPLUGIN.pro $NEWPLUGIN.pro

rm Makefile
rm -rf build

sed -i "s/${OLDPLUGIN}/${NEWPLUGIN}/g" *


OLDPLUGIN="$(tr '[:lower:]' '[:upper:]' <<< ${OLDPLUGIN:0:1})${OLDPLUGIN:1}"

NEWPLUGIN="$(tr '[:lower:]' '[:upper:]' <<< ${NEWPLUGIN:0:1})${NEWPLUGIN:1}"

sed -i "s/${OLDPLUGIN}/${NEWPLUGIN}/g" *

