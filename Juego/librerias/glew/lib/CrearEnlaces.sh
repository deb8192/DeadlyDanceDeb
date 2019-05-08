#!/bin/bash
echo -e "\e[1m\e[93mCreando Enlaces simbolicos... \e[0m"
echo
rm libGLEW.so
ln -s libGLEW.so.2.1.0 libGLEW.so
rm libGLEW.so.2.1
ln -s libGLEW.so.2.1.0 libGLEW.so.2.1
echo
echo -e "\e[1m\e[92mEnlaces Creados \e[0m"
echo
echo -e "\e[1mSi quieres saber como crearlos visita \e[0m \e[4m\e[44m https://www.cambiatealinux.com/ln-crear-un-enlace-simbolico-al-fichero-o-directorio \e[0m"
echo
sleep 8s