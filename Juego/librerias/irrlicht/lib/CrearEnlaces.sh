#!/bin/bash
echo -e "\e[1m\e[93mCreando Enlaces simbolicos... \e[0m"
echo
rm libIrrlicht.so.1.8
ln -s libIrrlicht.so.1.8.4 libIrrlicht.so.1.8
echo
echo -e "\e[1m\e[92mEnlaces Creados \e[0m"
echo
echo -e "\e[1mSi quieres saber como crearlos visita \e[0m \e[4m\e[44m https://www.cambiatealinux.com/ln-crear-un-enlace-simbolico-al-fichero-o-directorio \e[0m"
echo
sleep 8s