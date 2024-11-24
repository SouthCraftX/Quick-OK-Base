#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include <libavformat/avformat.h>

struct _QOVideoInfo
{
    qo_uint16_t width;
    qo_uint16_t height;
    qo_uint16_t gop_size;
    AVPixelFormat   pix_fmt;
    qo_fp64_t   fps;
    
};
typedef struct _QOVideoInfo QOVideoInfo;

enum _QOVideoQualityType
{
    QO_VIDEO_QUALITY_QP,
    QO_VIDEO_QUALITY_BITRATE,
    QO_VIDEO_QUALITY_CRF
};
typedef enum _QOVideoQualityType QOVideoQualityType;

struct _QOVideoQuality
{
    QOVideoQualityType  type;
    qo_ccstring_t       preset;
    qo_ccstring_t       profile;
    union 
    {
        struct 
        {
            qo_int16_t  qp;
            qo_int16_t  min_qp;
            qo_int16_t  max_qp;
        } qp;
        struct
        {
            qo_size_t   bitrate;
            qo_size_t   max_bitrate;
            qo_size_t   min_bitrate;
        } bitrate;
        struct {
            qo_int16_t  crf;
        } crf;
    };
};
typedef struct _QOVideoQuality QOVideoQuality;


#if defined(__cplusplus)
}
#endif // __cplusplus
