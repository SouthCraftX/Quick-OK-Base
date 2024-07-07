#include "encoder.h"

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
void
__xoc_dec_quality_to_str(
    xoc_int16_t      dec ,
    xoc_cstring_t    str
){
    XOCDivisionInt32 division = XOC_DIVISION_I32(dec , 10);
    if (division.quotient)
    {
        str[0] = '0' + division.quotient;
        str[1] = '0' + division.remainder;
        str[2] = 0;
    }
    else{
        str[0] = '0' + division.remainder;
        str[1] = 0;
    }  
}

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
bool
__xoc_set_video_quality(
    XOCVideoQuality * video_quality ,
    AVCodecContext *     codec_ctx ,
    AVDictionary * *     opt
){
    char tmp_str[3];
    int ret;

    if(video_quality->preset)
    {
        if(av_dict_set(opt , "preset" , video_quality->preset , 0))
            return true;
    }

    if(video_quality->profile)
    {
        if(av_dict_set(opt , "profile" , video_quality->profile , 0))
            return true;
    }
        
    switch (video_quality->type)
    {
        case XOC_VIDEO_QUALITY_QP:
            codec_ctx->qmax = video_quality->qp.max_qp;
            codec_ctx->qmin = video_quality->qp.min_qp;
            __xoc_dec_quality_to_str(video_quality->qp.qp , tmp_str);
            ret = av_opt_set(codec_ctx->priv_data, "qp", tmp_str , 
                             AV_OPT_SEARCH_CHILDREN);
            if(ret) goto ERR_ARG;
            break;

        case XOC_VIDEO_QUALITY_BITRATE:
            codec_ctx->bit_rate = video_quality->bitrate.bitrate;
            codec_ctx->rc_max_rate = video_quality->bitrate.bitrate;
            codec_ctx->rc_min_rate = video_quality->bitrate.bitrate;
            break;

        case XOC_VIDEO_QUALITY_CRF:
            __xoc_dec_quality_to_str(video_quality->crf.crf , tmp_str);
            ret = av_opt_set(codec_ctx->priv_data, "crf", tmp_str , 
                             AV_OPT_SEARCH_CHILDREN);
            if(ret) goto ERR_ARG;
            break;

        ERR_ARG:
        default:
            return true;
    }
    return false;
}

XOC_GLOBAL_LOCAL
void
__xoc_set_video_info(
    XOCVideoInfo *   video_info ,
    AVCodecContext *    codec_ctx
){
    AVRational rad = av_d2q(1 , video_info->fps);
    codec_ctx->width  = video_info->width;
    codec_ctx->height = video_info->height;
    codec_ctx->time_base = rad;
    codec_ctx->framerate = (AVRational){ .den = rad.num , .num = 1};
    codec_ctx->pix_fmt = video_info->pix_fmt;
}

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
void
__xoc_set_av_frame(
    AVFrame *           frame ,
    XOCVideoInfo *   video_info
){
    frame->format = video_info->pix_fmt;
    frame->width  = video_info->width;
    frame->height = video_info->height;
}

XOC_GLOBAL_LOCAL
xoc_stat_t
__xoc_generic_video_encoder_init(
    XOCVideoEncoder *        encoder ,
    const enum AVCodecID        codec_id ,
    const XOCVideoInfo *     video_info ,
    const XOCVideoQuality *  video_quality ,
    xoc_ccstring_t           video_path
){
    AVCodec * codec = avcodec_find_encoder(codec_id);
    if (!codec)
        return XOC_CODEC_NOT_FOUND;
    
    AVCodecContext * codec_ctx = avcodec_alloc_context3(codec);
    if(XOC_UNLIKELY(!codec_ctx))
        return XOC_OUT_OF_MEMORY;
    
    AVDictionary * opt = NULL;

    if(__xoc_set_video_quality(codec_ctx , video_quality , opt))
    {
        avcodec_close(codec_ctx);
        return XOC_INVALID_ARG;
    }

    AVFormatContext * format_ctx;
    if(avformat_alloc_output_context2(&format_ctx , NULL , NULL , video_path) < 0)
    {
        if(opt) 
            av_dict_free(&opt);
        avcodec_close(codec_ctx);
        return XOC_INIT_VIDEO_FORMAT_FAILED;
    }

    AVStream * stream = avformat_new_stream(format_ctx , NULL);
    if(XOC_UNLIKELY(!stream))
    {
        if(opt) 
            av_dict_free(&opt);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_ADD_MEDIA_STREAM_FAILED;
    }

    if(avcodec_parameters_from_context(stream->codecpar , codec_ctx))
    {
        if(opt) 
            av_dict_free(&opt);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_UNKNOWN_ERROR;
    }
    

    AVPacket * packet = av_packet_alloc();
    if(XOC_UNLIKELY(!packet))
    {
        if(opt) 
            av_dict_free(&opt);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_OUT_OF_MEMORY;
    }

    AVFrame * frame = av_frame_alloc();
    if(XOC_UNLIKELY(!frame))
    {
        if(opt) 
            av_dict_free(&opt);
        av_packet_free(&packet);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_OUT_OF_MEMORY;
    }
    __xoc_set_av_frame(frame , video_info);

    if(avcodec_open2(codec_ctx , codec , &opt) < 0)
    {
        if(opt) 
            av_dict_free(&opt);
        av_packet_free(&packet);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_OPEN_CODEC_FAILED;
    }
    
    

    if(av_frame_get_buffer(frame , 0) < 0)
    {
        if(opt) 
            av_dict_free(&opt);
        av_packet_free(&packet);
        av_frame_free(&frame);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_OUT_OF_MEMORY;
    }

    if(avio_open(&format_ctx->pb , video_path , AVIO_FLAG_WRITE) < 0)
    {
        if(opt) 
            av_dict_free(&opt);
        av_packet_free(&packet);
        av_frame_free(&frame);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_OPEN_FILE_FAILED;
    }

    if(avformat_write_header(format_ctx , &opt) < 0)
    {
        if(opt) 
            av_dict_free(&opt);
        avio_close(format_ctx->pb);
        av_packet_free(&packet);
        av_frame_free(&frame);
        avcodec_close(codec_ctx);
        avformat_free_context(format_ctx);
        return XOC_BAD_MEDIA_HEADER;
    }

    encoder->codec      =   codec;
    encoder->codec_ctx  =   codec_ctx;
    encoder->packet     =   packet;
    encoder->frame      =   frame;
    encoder->opt        =   opt;
    encoder->format_ctx =   format_ctx;
    encoder->stream     =   stream;

    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_video_encoder_init)(
    XOCVideoEncoder *        encoder ,
    const XOCVideoInfo *     video_info ,
    const XOCVideoQuality *  video_quality ,
    enum AVCodecID              codec_id ,
    xoc_ccstring_t           video_path
){
    return __xoc_generic_video_encoder_init(
        encoder , 
        video_info , 
        video_quality , 
        codec_id , 
        video_path
    );
}

xoc_stat_t
XOC_IMPL(xoc_hardware_video_encoder_init)(
    XOCHardwareVideoEncoder *encoder ,
    const XOCVideoInfo *     video_info ,
    const XOCVideoQuality *  video_quality ,
    const enum AVHWDeviceType   hardware_type ,
    const enum AVCodecID        hardware_codec_id ,
    xoc_ccstring_t           video_path
){
    xoc_stat_t ret = __xoc_generic_video_encoder_init(
        &encoder->base ,
        hardware_codec_id ,
        video_info ,
        video_quality ,
        video_path
    );
    if(ret)
        return ret;

    AVBufferRef * hw_device_ctx;
    if(av_hwdevice_ctx_create(&hw_device_ctx , hardware_type , NULL , 
                           encoder->base.opt , 0) < 0)
        return XOC_INIT_HARDWARE_FAILED;

    AVBufferRef * hw_frames_ref = av_hwframe_ctx_alloc(hw_device_ctx);
    if(!hw_frames_ref)
    {
        return XOC_OUT_OF_MEMORY;
    }
    
    AVHWFramesContext * hw_frame_ctx = (AVHWFramesContext *)hw_frames_ref->data;
    hw_frame_ctx->width  = video_info->width;
    hw_frame_ctx->height = video_info->height;

    encoder->base.codec_ctx->hw_frames_ctx = av_buffer_ref(hw_frames_ref);

    AVFrame * hw_frame = av_frame_alloc();
    if(!hw_frame)
    {
        // todo
        return XOC_OUT_OF_MEMORY;
    }
    

    if(av_hwframe_get_buffer(encoder->base.codec_ctx->hw_frames_ctx , hw_frame , 0) < 0)
        return XOC_OUT_OF_MEMORY;

    
}

xoc_stat_t
__xoc_encode_frame(
    AVCodecContext *    codec_ctx ,
    AVFrame *           frame ,
    AVPacket *          packet ,
    AVFormatContext *   format_ctx
){
    if(avcodec_send_frame(codec_ctx , frame) < 0)
        return XOC_UNKNOWN_ERROR;
    
    int ret;
    while(ret >= 0)
    {
        ret = avcodec_receive_packet(codec_ctx , packet);
        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            break;
        else if(ret < 0)
            return XOC_UNKNOWN_ERROR;
        if(av_write_frame(format_ctx , packet) < 0)
            return XOC_UNKNOWN_ERROR;
        av_packet_unref(packet);
    }
    
    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_video_encoder_write_frame)(
    XOCVideoEncoder *    encoder ,
    xoc_pointer_t        frame
){
    if(XOC_UNLIKELY(av_frame_make_writable(encoder->frame) < 0))
        return XOC_UNKNOWN_ERROR;

    // Todo

    encoder->frame->pts = 1;
    return __xoc_encode_frame(encoder->codec_ctx , encoder->frame ,
                                 &encoder->packet , encoder->output_stream);
}

void
XOC_IMPL(xoc_video_encoder_stop)(
    XOCVideoEncoder *    encoder
){
    // Flush it
    __xoc_encode_frame(encoder->codec_ctx , NULL , encoder->packet , &
                          encoder->output_stream);
    avio_close(encoder->format_ctx->pb);    
    avformat_free_context(encoder->format_ctx);
    avcodec_free_context(&encoder->codec_ctx);
    av_frame_free(&encoder->frame);
    av_packet_free(&encoder->packet);
}   