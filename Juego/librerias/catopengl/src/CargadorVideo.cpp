#include "CargadorVideo.hpp"

CargadorVideo::CargadorVideo()
{
        // Inicializamos a nulo para prevenir segmentation faults.
        pFormatCtx = NULL;
        pCodecCtx = NULL;
        pCodecParam = NULL;
        pCodec = NULL;
        pFrame = NULL;
        pFrameRGB = NULL;
        buffer = NULL;
        sws_ctx = NULL;
        width = 800;//por defecto
        height = 600;//por defecto
        videoStream = -1;
        AllOk = false;
        flip = false;
}

CargadorVideo::CargadorVideo(const char * _rutaVideo)
{
        // Inicializamos a nulo para prevenir segmentation faults.
        pFormatCtx = NULL;
        pCodecCtx = NULL;
        pCodecParam = NULL;
        pCodec = NULL;
        pFrame = NULL;
        pFrameRGB = NULL;
        buffer = NULL;
        sws_ctx = NULL;
        flip = false;
        width = 800;//por defecto
        height = 600;//por defecto
        videoStream = -1;

        AllOk = PrepararVideo(_rutaVideo);
}

CargadorVideo::~CargadorVideo()
{
        if(sws_ctx)
        {
                sws_freeContext(sws_ctx);
        }
        if(buffer)
        {
                av_free(buffer);
        }
        if(pCodecCtx)
        {
                avcodec_close(pCodecCtx);
        }
        if(pFormatCtx)
        {
                avformat_close_input(&pFormatCtx);
        }
}

bool CargadorVideo::PrepararVideo(const char * _rutaVideo)
{
        if(!_rutaVideo)
        {
                fprintf(stderr, "Valor de la ruta no encontrado. !\n");
                return false;
        }

        // instanciamos el video
        if(avformat_open_input(&pFormatCtx, _rutaVideo, NULL, NULL)!=0)
        {
                fprintf(stderr, "No se encontro el archivo. !\n");
                return false; // No se puede abrir el video
        }

        //Miramos si el video tiene informacion sobre su codec,fps,duracion,pistas o streams, etc...
        if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        {
                fprintf(stderr, "No se encontro informacion del video. !\n");
                return false; //No encontro informacion del video salimos del programa, porque no se puede trabajar sin saber la informacion
        }
        
        //buscamos pista o stream de video dentro del archivo
        for(i=0; i<pFormatCtx->nb_streams; i++)
        {
                if(pFormatCtx->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO)  //si el tipo es de video, el codec es correcto pasamos a guardanos la pista para buscar el codec 
                {
                        videoStream=i;//guardamos la pista o stream
                        break;//salimos del for
                }
        }

        if(videoStream == -1)
        {
                fprintf(stderr, "No se encontro pista o stream de video. !\n");
                return false; //no se encontro pista o stream de video
        }

        // Obtiene un puntero del codec del video
        pCodecParam=pFormatCtx->streams[videoStream]->codecpar;

        // Encuentra el decoder para desencriptar el video
        pCodec=avcodec_find_decoder(pCodecParam->codec_id);
        
        //si no es nulo es que ha encontrado el decoder
        if(pCodec==NULL) 
        {
                fprintf(stderr, "Codec no soportado!\n");
                return false; // No se encontro codec
        }

        // Copiamos el contexto (instancia)
        pCodecCtx = avcodec_alloc_context3(pCodec);
        avcodec_parameters_to_context(pCodecCtx, pCodecParam);

        // Instanciamos el codec para trabajar con el y decodear el video
        if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
        {
                fprintf(stderr, "No se puede instanciar el codec. (seguramente no existe en la libreria) !\n");
                return false; // No se puede abrir el video o no se encuentra el codec en la libreria libavcodec
        }

        // Rerserva memoria para un frame
        pFrame=av_frame_alloc();

        // Reserva memoria para un frame que luego se convertira en espacio de color rgb
        pFrameRGB=av_frame_alloc();

        if(pFrame == NULL || pFrameRGB==NULL) //comprobamos que haya realizado la reserva de la estructura, si no es asi salimos del programa
        {
                fprintf(stderr, "No se puede reservar memoria para frame o marco \n");
                return false;
        }

        // Determina la longitud del buffer y cuantos bytes tendra
        numBytes=av_image_get_buffer_size(AV_PIX_FMT_RGB24,width,height,1);
        //std::cout << "Tamayo en bytes " << numBytes << " w " << width << " h " << height << "\n";
        //reservamos memoria para el buffer del frame
        buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t)); 

        //determina como sera la imagen o frame o marco
        av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize,buffer,AV_PIX_FMT_RGB24,width,height,1);

        // esto escala la imagen por software (por hardware cada ordenador puede tener unas formas asi que mejor por software)
        sws_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,width,height,AV_PIX_FMT_RGB24,SWS_BILINEAR,NULL,NULL,NULL);

        AllOk = true;
        return true;
}

unsigned char * CargadorVideo::CargarFrame(unsigned int SaltoFrames)
{
        if(AllOk)
        {
                if(SaltoFrames == 0)
                {
                        //cargamos el siguiente 

                        if(encontrarFrame() != nullptr)
                        {
                                //se trabaja con el frame
                                int used;
                                // Decode video frame
                                used = avcodec_send_packet(pCodecCtx, &packet);
                                // Did we get a video frame?
                                if(used >= 0) 
                                {
                                        packet.size = 0;
                                        used = avcodec_receive_frame(pCodecCtx, pFrame);
                                        if(used >= 0)
                                        {
                                                //flipFrame(pFrame);
                                                sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data,pFrame->linesize,0, pCodecCtx->height,pFrameRGB->data,pFrameRGB->linesize);

                                                //Procesamos el frame
                                                av_packet_unref(&packet);
                                                return devolverFrame(pFrameRGB);
                                        }
                                }
                                
                                //se libera el espacio del paquete
                                av_packet_unref(&packet);
                        }
                        else
                        {
                                //cogemos el frame anterior 
                                return devolverFrame(pFrameRGB); 
                        } 
                }
                else
                {
                        //saltamos los frames
                        unsigned int framesSaltados = 0;

                        while(SaltoFrames != framesSaltados) 
                        {
                                encontrarFrame();
                                framesSaltados++;       
                        }
                        //falta procesarlo
                }
        }
        
        return nullptr;
}

unsigned int CargadorVideo::GetFps()
{
        return fps;
}

unsigned int CargadorVideo::GetColorComponents()
{
        return components;
}

unsigned char * CargadorVideo::devolverFrame(AVFrame * frame)
{
        if(frame)
        {
                return (unsigned char *)frame->data[0];
        }

        return nullptr;
}

AVPacket * CargadorVideo::encontrarFrame()
{
        while(av_read_frame(pFormatCtx, &packet) >=0) 
        {
                //hay frame
                if(packet.stream_index == videoStream) //esto se utiliza para saber si estamos en un paquete del canal o stream correcto
                {    
                        return &packet;
                }
        }

        return nullptr; //no se encontro paquete
}

bool CargadorVideo::EstaListo()
{
        return AllOk;
}

void CargadorVideo::DefinirSizeSalida(unsigned int nwidth, unsigned int nheight)
{
        width = nwidth;
        height = nheight;
}

void CargadorVideo::flipFrame(AVFrame* pFrame) 
{
        //(sizeof pFrame->data / sizeof * pFrame->data)
        std::cout << "Entra \n ";
        for (int i = 0; i < 3; i++) 
        {
                std::cout << "Paso " << i << " " << pFrame->linesize[i] * (pFrame->height-1) << " " <<  pFrame->linesize[i] << "\n";
                pFrame->data[i] += pFrame->linesize[i] * (pFrame->height);
                pFrame->linesize[i] = -pFrame->linesize[i];            
        }
        std::cout << "Sale \n ";
}

void CargadorVideo::unflipFrame(AVFrame* pFrame) 
{
        for (int i = 0; i < 4; i++) 
        {
                if(flip)
                {
                        flip = false;
                        pFrame->linesize[i] = -pFrame->linesize[i];
                        pFrame->data[i] -= pFrame->linesize[i] * (pFrame->height-1);
                }
        }
}

