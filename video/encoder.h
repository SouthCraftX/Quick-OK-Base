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

#define QO_VIDEO_PROFILE_BASELINE   "baseline"
#define QO_VIDEO_PROFILE_MAIN       "main"
#define QO_VIDEO_PROFILE_HIGH       "high"
#define QO_VIDEO_PROFILE_EXTENDED   "extended"

#define QO_VIDEO_PRESET_PLACEBO     "placebo"
#define QO_VIDEO_PRESET_VERYSLOW    "veryslow"
#define QO_VIDEO_PRESET_SLOW        "slow"
#define QO_VIDEO_PRESET_MEDIUM      "medium"
#define QO_VIDEO_PROSET_FAST        "fast"
#define QO_VIDEO_PRESET_VERYFAST    "veryfast"
#define QO_VIDEO_PRESET_ULTRAFAST   "ultrafast"



struct _QOVideoEncoder
{
    QOVideoInfo     video_info;
    AVCodecContext *    codec_ctx;
    AVFormatContext *   format_ctx;
    AVCodec *           codec;
    AVFrame *           frame;
    AVPacket *          packet;
    AVDictionary *      opt;
    AVStream *          stream;
};
typedef struct _QOVideoEncoder QOVideoEncoder;


struct _QOHardwareVideoEncoder
{
    QOVideoEncoder  base;
    AVFrame *           hw_frame;
    AVBufferRef *       hw_device_ctx;
    AVBufferRef *       hw_frames_ref;
    AVHWFramesContext * hw_frames_ctx;
};
typedef struct _QOHardwareVideoEncoder QOHardwareVideoEncoder;
int a =sizeof(QOHardwareVideoEncoder);

qo_stat_t
QO_INTERFACE(qo_video_encoder_init)(
    QOVideoEncoder *        encoder ,
    const QOVideoInfo *     video_info ,
    const QOVideoQuality *  video_quality ,
    enum AVCodecID              codec_id ,
    qo_ccstring_t           video_path
);


qo_stat_t
QO_INTERFACE(qo_hardware_video_encoder_init)(
    QOVideoEncoder *        encoder ,
    const QOVideoInfo *     video_info ,
    const QOVideoQuality *  video_quality ,
    const enum AVHWDeviceType   hardware_type ,
    qo_ccstring_t           video_path
);

qo_stat_t
QO_INTERFACE(qo_video_encoder_write_frame)(
    QOVideoEncoder *    encoder ,
    qo_pointer_t        frame
);

void
QO_INTERFACE(qo_video_encoder_stop)(
    QOVideoEncoder *    encoder
);


#if defined(__cplusplus)
}
#endif // __cplusplus   