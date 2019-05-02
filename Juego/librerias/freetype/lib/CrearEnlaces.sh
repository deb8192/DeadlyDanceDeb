#!/bin/bash
echo -e "\e[1m\e[93mCreando Enlaces simbolicos... \e[0m"
echo
rm libfreetype.so
ln -s libfreetype.so.6.16.1 libfreetype.so
rm libfreetype.so.6
ln -s libfreetype.so.6.16.1 libfreetype.so.6
rm libfreetype.la
ln -s libfreetype.lai libfreetype.la
echo
echo -e "\e[1m\e[92mEnlaces Creados \e[0m"
echo
echo -e "\e[1mSi quieres saber como crearlos visita \e[0m \e[4m\e[44m https://www.cambiatealinux.com/ln-crear-un-enlace-simbolico-al-fichero-o-directorio \e[0m"
echo
sleep 8s