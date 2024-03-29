#include "load_frame.hpp"
#include <iostream>
using namespace std;
static const char* av_make_error(int errnum) {
    static char str[AV_ERROR_MAX_STRING_SIZE];
    memset(str, 0, sizeof(str));
    return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
}
bool load_frame(const char *filename){
    
    
    AVFormatContext* av_format_ctx = avformat_alloc_context();
    
    if(!av_format_ctx){
        printf("error in allocating avformat context ");
        return false;
    }
    int result_of_opening = avformat_open_input(&av_format_ctx,filename, NULL, NULL);
    if(result_of_opening < 0){
        printf("error in opening file\n");
        return false;
    }

    /**
     * here we are going to find video stream index
    */

    int video_stream_index = -1;
    AVCodecParameters * av_code_parameters;
    AVCodec* av_codec;


    for (size_t i = 0; i < av_format_ctx->nb_streams; i++)
    {
        auto stream = av_format_ctx->streams[i];
        av_code_parameters = stream->codecpar;
        av_codec = const_cast<AVCodec *> (avcodec_find_decoder(av_code_parameters->codec_id));
        if (av_codec ->type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream_index = i;
            break;
        }
        
    }
    if (video_stream_index ==-1){
        cout<<"unable to find video stream index\n";
        return false;
    }
    cout<< "video stream channel is "<<video_stream_index<<endl;
    AVCodecContext *av_codec_context = avcodec_alloc_context3(av_codec);
    if(!av_codec_context){
        cout<<"unable to allocate context\n";
        return false;
    }
    if(avcodec_parameters_to_context(av_codec_context,av_code_parameters)<0){
        cout<<"unable to transform paramters to context\n";
        return false;  
    }
    if(avcodec_open2(av_codec_context,av_codec,NULL)<0){
        cout<< "unable to open avcodec"<<endl;
        return false;
    }

    AVPacket * av_packet = av_packet_alloc();    
    AVFrame * av_frame = av_frame_alloc();

    int response;
    while(av_read_frame(av_format_ctx,av_packet)>=0){
        if (av_packet->stream_index != video_stream_index)
        {
            av_packet_unref(av_packet);
            continue;
        }
        response = avcodec_send_packet(av_codec_context,av_packet);
        if(response != 0){
            printf("error happened in sending packet %s",av_make_error(response));
            return false;
        }
        response = avcodec_receive_frame(av_codec_context,av_frame);
        if(response == AVERROR(EAGAIN) || response == AVERROR(EOF)){
            continue;
        }
        else if(response < 0){
            printf("error happened in receiving frame %s",av_make_error(response));
        }
        int i = 0;
    }


    avformat_close_input(&av_format_ctx);
    avformat_free_context(av_format_ctx);
    avcodec_free_context(&av_codec_context);

    return true;
}