#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include <libavformat/avformat.h>

struct _XOceanVideoInfo
{
    xocean_uint16_t width;
    xocean_uint16_t height;
    xocean_uint16_t gop_size;
    AVPixelFormat   pix_fmt;
    xocean_fp64_t   fps;
    
};
typedef struct _XOceanVideoInfo XOceanVideoInfo;

enum _XOceanVideoQualityType
{
    XOCEAN_VIDEO_QUALITY_QP,
    XOCEAN_VIDEO_QUALITY_BITRATE,
    XOCEAN_VIDEO_QUALITY_CRF
};
typedef enum _XOceanVideoQualityType XOceanVideoQualityType;

struct _XOceanVideoQuality
{
    XOceanVideoQualityType  type;
    xocean_ccstring_t       preset;
    xocean_ccstring_t       profile;
    union 
    {
        struct 
        {
            xocean_int16_t  qp;
            xocean_int16_t  min_qp;
            xocean_int16_t  max_qp;
        } qp;
        struct
        {
            xocean_size_t   bitrate;
            xocean_size_t   max_bitrate;
            xocean_size_t   min_bitrate;
        } bitrate;
        struct {
            xocean_int16_t  crf;
        } crf;
    };
};
typedef struct _XOceanVideoQuality XOceanVideoQuality;


#if defined(__cplusplus)
}
#endif // __cplusplus
