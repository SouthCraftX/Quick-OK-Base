#pragma once

#include "video_info.h"
#include "../fstream/fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/hwcontext.h>
#include <libavutil/imgutils.h>

#define XOC_VIDEO_PROFILE_BASELINE   "baseline"
#define XOC_VIDEO_PROFILE_MAIN       "main"
#define XOC_VIDEO_PROFILE_HIGH       "high"
#define XOC_VIDEO_PROFILE_EXTENDED   "extended"

#define XOC_VIDEO_PRESET_PLACEBO     "placebo"
#define XOC_VIDEO_PRESET_VERYSLOW    "veryslow"
#define XOC_VIDEO_PRESET_SLOW        "slow"
#define XOC_VIDEO_PRESET_MEDIUM      "medium"
#define XOC_VIDEO_PROSET_FAST        "fast"
#define XOC_VIDEO_PRESET_VERYFAST    "veryfast"
#define XOC_VIDEO_PRESET_ULTRAFAST   "ultrafast"



struct _XOCVideoEncoder
{
    XOCVideoInfo     video_info;
    AVCodecContext *    codec_ctx;
    AVFormatContext *   format_ctx;
    AVCodec *           codec;
    AVFrame *           frame;
    AVPacket *          packet;
    AVDictionary *      opt;
    AVStream *          stream;
};
typedef struct _XOCVideoEncoder XOCVideoEncoder;


struct _XOCHardwareVideoEncoder
{
    XOCVideoEncoder  base;
    AVFrame *           hw_frame;
    AVBufferRef *       hw_device_ctx;
    AVBufferRef *       hw_frames_ref;
    AVHWFramesContext * hw_frames_ctx;
};
typedef struct _XOCHardwareVideoEncoder XOCHardwareVideoEncoder;
int a =sizeof(XOCHardwareVideoEncoder);

xoc_stat_t
XOC_INTERFACE(xoc_video_encoder_init)(
    XOCVideoEncoder *        encoder ,
    const XOCVideoInfo *     video_info ,
    const XOCVideoQuality *  video_quality ,
    enum AVCodecID              codec_id ,
    xoc_ccstring_t           video_path
);


xoc_stat_t
XOC_INTERFACE(xoc_hardware_video_encoder_init)(
    XOCVideoEncoder *        encoder ,
    const XOCVideoInfo *     video_info ,
    const XOCVideoQuality *  video_quality ,
    const enum AVHWDeviceType   hardware_type ,
    xoc_ccstring_t           video_path
);

xoc_stat_t
XOC_INTERFACE(xoc_video_encoder_write_frame)(
    XOCVideoEncoder *    encoder ,
    xoc_pointer_t        frame
);

void
XOC_INTERFACE(xoc_video_encoder_stop)(
    XOCVideoEncoder *    encoder
);


#if defined(__cplusplus)
}
#endif // __cplusplus   