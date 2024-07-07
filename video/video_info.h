#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include <libavformat/avformat.h>

struct _XOCVideoInfo
{
    xoc_uint16_t width;
    xoc_uint16_t height;
    xoc_uint16_t gop_size;
    AVPixelFormat   pix_fmt;
    xoc_fp64_t   fps;
    
};
typedef struct _XOCVideoInfo XOCVideoInfo;

enum _XOCVideoQualityType
{
    XOC_VIDEO_QUALITY_QP,
    XOC_VIDEO_QUALITY_BITRATE,
    XOC_VIDEO_QUALITY_CRF
};
typedef enum _XOCVideoQualityType XOCVideoQualityType;

struct _XOCVideoQuality
{
    XOCVideoQualityType  type;
    xoc_ccstring_t       preset;
    xoc_ccstring_t       profile;
    union 
    {
        struct 
        {
            xoc_int16_t  qp;
            xoc_int16_t  min_qp;
            xoc_int16_t  max_qp;
        } qp;
        struct
        {
            xoc_size_t   bitrate;
            xoc_size_t   max_bitrate;
            xoc_size_t   min_bitrate;
        } bitrate;
        struct {
            xoc_int16_t  crf;
        } crf;
    };
};
typedef struct _XOCVideoQuality XOCVideoQuality;


#if defined(__cplusplus)
}
#endif // __cplusplus
