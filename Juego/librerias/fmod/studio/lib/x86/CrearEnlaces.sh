#!/bin/bash
echo -e "\e[1m\e[93mCreando Enlaces simbolicos... \e[0m"
echo
ln -s libfmodstudio.so.10.9 libfmodstudio.so
ln -s libfmodstudio.so.10.9 libfmodstudio.so.10
ln -s libfmodstudioL.so.10.9 libfmodstudioL.so
ln -s libfmodstudioL.so.10.9 libfmodstudioL.so.10
echo
echo -e "\e[1m\e[92mEnlaces Creados \e[0m"
echo
echo -e "\e[1mSi quieres saber como crearlos visita \e[0m \e[4m\e[44m https://www.cambiatealinux.com/ln-crear-un-enlace-simbolico-al-fichero-o-directorio \e[0m"
echo
sleep 8s