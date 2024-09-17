#pragma once
#define __XOC_MEDIA_VIDEO_QUALITY_INDICATOR_H__

#include "base.h"
#include <avcodec.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_VideoQualityIndicator;
typedef struct _XOC_VideoQualityIndicator XOC_VideoQualityIndicator;



enum XOC_VideoQualityKeys
{
    XOC_VIDEO_PROSET,       ///< String, e.g. "veryfast"
    XOC_VIDEO_PROFILE,      ///< String, e.g. "baseline"
    XOC_VIDEO_INTRA_MODE,   ///< String, e.g. "i4x4", "i8x8", "i16x16"
    XOC_VIDEO_ME_METHOD,    ///< String, e.g. "full", "hex", "epzs"
    XOC_VIDEO_ENTROPY,      ///< String, e.g. "cavlc", "cabac"
    
    XOC_VIDEO_DEBLOCK,      ///< Boolean 
    XOC_VIDEO_NOISE_REDUCTION, ///< Boolean

    XOC_VIDEO_QP,           ///< Int32, Range: 0-51
    XOC_VIDEO_MAX_QP,       ///< Int32, Range: 0-51
    XOC_VIDEO_MIN_QP,       ///< Int32, Range: 0-51
    XOC_VIDEO_CRF,          ///< Int32 Range: 0-51
    XOC_VIDEO_GOP,          ///< Int32 Often range from 1 to hundreds
    XOC_VIDEO_B_FRAME_STRATEGY, ///< Int32 from 0 to 3. See ffmpeg documentation
    XOC_VIDEO_AQ_MODE,      ///< Int32 from 0 to 3. See ffmpeg documentation

    XOC_VIDEO_BITRATE,      ///< Size
    XOC_VIDEO_MAX_BITRATE,  ///< Size
    XOC_VIDEO_MIN_BITRATE,  ///< Size
    XOC_VIDEO_MAX_B_FRAMES, ///< Int32
    XOC_VIDEO_KEYINT_MIN,   ///< Int32
    XOC_VIDEO_PRERES,       ///< Int32 
    XOC_VIDEO_ME_RANGE,     ///< Size
    XOC_VIDEO_SCENECUT,     ///< Size 0 to disable
};

struct _VideoQualityPair
{
    enum XOC_VideoQualityKeys   key_type;
    xoc_byte_t                  value[0];
};
typedef struct _VideoQualityPair VideoQualityPair;

/// @brief  Create a new video quality indicator
/// @param  reserved_size The size of the memory reserved for the video quality 
///         indicator. 0 indicates default size.
/// @return The new video quality indicator. NULL if failed.
XOC_VideoQualityIndicator *
XOC_INTERFACE(xoc_video_quality_indicator_new)(
    xoc_size_t  reserved_size
);

/// @brief  Duplicate a video quality indicator
/// @param  old_indicator The video quality indicator to duplicate
/// @return The duplicated video quality indicator. NULL if failed.
XOC_VideoQualityIndicator *
XOC_INTERFACE(xoc_video_quality_indicator_duplicate)(
    XOC_VideoQualityIndicator * old_indicator
) XOC_NONNULL(1);

/// @brief  Delete a video quality indicator
/// @param  video_quality_indicator The video quality indicator to delete
///         NULL is allowed, in that case the function does nothing.
void
XOC_INTERFACE(xoc_video_quality_indicator_delete)(
    XOC_VideoQualityIndicator * video_quality_indicator
);

/// @brief  Set a video quality indicator key-value pair
/// @param  video_quality_indicator The video quality indicator
/// @param  key The key, see enum XOC_VIDEO_QUALITY_KEYS
/// @param  value The value. The type depends on the key. Need to be casted to 
///         xoc_intmax_t, like (xoc_intmax_t)18 , (xoc_intmax_t)"veryfast"
/// @return The status of the operation
/// @retval XOC_OK The operation is successful
/// @retval XOC_OUT_OF_MEMORY The operation failed due to out of memory
/// @retval XOC_INVALID_ARG Invalid argument passed to the function, like
///         value 100 for key XOC_VIDEO_QP
xoc_stat_t
XOC_INTERFACE(xoc_video_quality_indicator_set)(
    XOC_VideoQualityIndicator * video_quality_indicator ,
    enum XOC_VIDEO_QUALITY_KEYS key ,
    xoc_intmax_t                value
) XOC_NONNULL(1);

/// @brief  Get value of a video quality indicator key-value pair
/// @param  video_quality_indicator The video quality indicator
/// @param  key The key, see enum XOC_VIDEO_QUALITY_KEYS
/// @param  p_value A pointer to store the value. The type depends on the key.
/// @param  data_size_limit The maximum size of the data to be stored in p_value.
/// @return The status of the operation
/// @retval XOC_OK The operation is successful
/// @retval XOC_NOT_FOUND The key is not found in the video quality indicator
/// @remark Some types of value have a variable size, like string, when 
///         data_size_limit is very useful. If the object is larger than 
///         data_size_limit, the function may truncate the data.
///         If data_size_limit is 0, it indicates the buffer specified in 
///         p_value is sufficiently large to hold the data. 
xoc_stat_t
XOC_INTERFACE(xoc_video_quality_indicator_get)(
    XOC_VideoQualityIndicator * video_quality_indicator ,
    enum XOC_VIDEO_QUALITY_KEYS key ,
    xoc_pointer_t               p_value ,
    xoc_size_t                  data_size_limit
) XOC_NONNULL(1 , 3); 

/// @brief  Clear all pairs in the video quality indicator
/// @param  video_quality_indicator The video quality indicator
/// @return The number of key-value pairs in the video quality indicator cleared
xoc_size_t
XOC_INTERFACE(xoc_video_quality_indicator_clear)(
    XOC_VideoQualityIndicator * video_quality_indicator
) XOC_NONNULL(1);

/// @brief  Get the number of key-value pairs in the video quality indicator
/// @param  video_quality_indicator The video quality indicator
/// @return The number of key-value pairs in the video quality indicator. 
///         XOC_SIZE_MAX if failed. 0 if the video quality indicator is empty.
xoc_size_t
XOC_INTERFACE(xoc_video_quality_indicator_get_pair_count)(
    XOC_VideoQualityIndicator * video_quality_indicator
) XOC_NONNULL(1);

/// @brief  Get the total size of the video quality indicator
/// @param  video_quality_indicator The video quality indicator
xoc_size_t
XOC_INTERFACE(xoc_video_quality_indicator_get_total_size)(
    XOC_VideoQualityIndicator * video_quality_indicator
) XOC_NONNULL(1);

/// @brief  Reserve space for key-value pairs in the video quality indicator
/// @param  delta_size The number of key-value pairs to reserve. Negative value
///         indicates to release space sized by the absolute value. It is safe 
///         to pass delta_size even if free_size + delta_size is negative. In 
///         that case, the function will release all the unused space.
/// @return The status of the operation
/// @retval XOC_OK The operation is successful
/// @retval XOC_OUT_OF_MEMORY The memory is not enough to reserve specified space
xoc_stat_t
XOC_INTERFACE(xoc_video_quality_indicator_reserve)(
    XOC_VideoQualityIndicator * video_quality_indicator ,
    xoc_ssize_t                 delta_size
);

#if defined(__cplusplus)
}
#endif // __cplusplus