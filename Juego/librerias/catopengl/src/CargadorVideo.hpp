#ifndef CargadorVideo_HPP
#define CargadorVideo_HPP

#include <iostream>

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
    #include <libavformat/avformat.h>
}

class CargadorVideo
{
        public:

                CargadorVideo(const char * _rutaVideo);//carga el video y lo deja preparado para CargarFrame
                CargadorVideo();//simplemente inicializa los valores por defecto
                ~CargadorVideo();//destruye su instancia
                bool PrepararVideo(const char * _rutaVideo);//Prepara el video
                void DefinirSizeSalida(unsigned int nwidth, unsigned int nheight);//defines como quieres que te devuelva el frame de la imagen
                unsigned char * CargarFrame(unsigned int SaltoFrames = 0);//carga el frame si no se le pasa nada carga el siguiente si se le pasa salto salta tantos frames como se le indique SALIDA: != nullptr correcto, == nullptr no se ha podido cargar
                unsigned int GetFps();//obtienes a cuantos frames por segundo funciona este video SALIDA: > 0 correcto, <= 0 no se ha podido recuperar
                unsigned int GetColorComponents();//obtienes el numero de componentes que tiene este video por defecto rgb SALIDA: > 0 correcto, <= 0 no se ha podido recuperar
                bool EstaListo();/* *@return devuelve si esta preparado para reproducir o no */
        private:        
                unsigned int components,fps,height,width;
                bool AllOk;//si esta a true es que se puede leer video si no es que no se puede
                unsigned char * devolverFrame(AVFrame *);//devuelve el frame en formato para opengl
                unsigned char * procesarPaquete();//procesa el paquete de video que se ha encontrado previamente en el stream o canal 
                AVPacket * encontrarFrame();
                void flipFrame(AVFrame *);
                void unflipFrame(AVFrame *);
                bool flip;
                AVFormatContext   * pFormatCtx ;
                unsigned int      i;
                int               videoStream;
                AVCodecContext    * pCodecCtx;
                AVCodecParameters * pCodecParam ;
                AVCodec           * pCodec ;
                AVFrame           * pFrame;
                AVFrame           * pFrameRGB;
                AVPacket          packet;
                int               numBytes;
                uint8_t           * buffer;
                struct SwsContext * sws_ctx;
};

#endif