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

#define XOCEAN_VIDEO_PROFILE_BASELINE   "baseline"
#define XOCEAN_VIDEO_PROFILE_MAIN       "main"
#define XOCEAN_VIDEO_PROFILE_HIGH       "high"
#define XOCEAN_VIDEO_PROFILE_EXTENDED   "extended"

#define XOCEAN_VIDEO_PRESET_PLACEBO     "placebo"
#define XOCEAN_VIDEO_PRESET_VERYSLOW    "veryslow"
#define XOCEAN_VIDEO_PRESET_SLOW        "slow"
#define XOCEAN_VIDEO_PRESET_MEDIUM      "medium"
#define XOCEAN_VIDEO_PROSET_FAST        "fast"
#define XOCEAN_VIDEO_PRESET_VERYFAST    "veryfast"
#define XOCEAN_VIDEO_PRESET_ULTRAFAST   "ultrafast"



struct _XOceanVideoEncoder
{
    XOceanVideoInfo     video_info;
    AVCodecContext *    codec_ctx;
    AVFormatContext *   format_ctx;
    AVCodec *           codec;
    AVFrame *           frame;
    AVPacket *          packet;
    AVDictionary *      opt;
    AVStream *          stream;
};
typedef struct _XOceanVideoEncoder XOceanVideoEncoder;


struct _XOceanHardwareVideoEncoder
{
    XOceanVideoEncoder  base;
    AVFrame *           hw_frame;
    AVBufferRef *       hw_device_ctx;
    AVBufferRef *       hw_frames_ref;
    AVHWFramesContext * hw_frames_ctx;
};
typedef struct _XOceanHardwareVideoEncoder XOceanHardwareVideoEncoder;
int a =sizeof(XOceanHardwareVideoEncoder);

xocean_stat_t
XOCEAN_INTERFACE(xocean_video_encoder_init)(
    XOceanVideoEncoder *        encoder ,
    const XOceanVideoInfo *     video_info ,
    const XOceanVideoQuality *  video_quality ,
    enum AVCodecID              codec_id ,
    xocean_ccstring_t           video_path
);


xocean_stat_t
XOCEAN_INTERFACE(xocean_hardware_video_encoder_init)(
    XOceanVideoEncoder *        encoder ,
    const XOceanVideoInfo *     video_info ,
    const XOceanVideoQuality *  video_quality ,
    const enum AVHWDeviceType   hardware_type ,
    xocean_ccstring_t           video_path
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_video_encoder_write_frame)(
    XOceanVideoEncoder *    encoder ,
    xocean_pointer_t        frame
);

void
XOCEAN_INTERFACE(xocean_video_encoder_stop)(
    XOceanVideoEncoder *    encoder
);


#if defined(__cplusplus)
}
#endif // __cplusplus   