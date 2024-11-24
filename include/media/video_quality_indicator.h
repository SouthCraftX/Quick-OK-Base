#pragma once
#define __QO_MEDIA_VIDEO_QUALITY_INDICATOR_H__

#include "base.h"
#include <avcodec.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_VideoQualityIndicator;
typedef struct _QO_VideoQualityIndicator QO_VideoQualityIndicator;



enum QO_VideoQualityKeys
{
    QO_VIDEO_PROSET,       ///< String, e.g. "veryfast"
    QO_VIDEO_PROFILE,      ///< String, e.g. "baseline"
    QO_VIDEO_INTRA_MODE,   ///< String, e.g. "i4x4", "i8x8", "i16x16"
    QO_VIDEO_ME_METHOD,    ///< String, e.g. "full", "hex", "epzs"
    QO_VIDEO_ENTROPY,      ///< String, e.g. "cavlc", "cabac"
    
    QO_VIDEO_DEBLOCK,      ///< Boolean 
    QO_VIDEO_NOISE_REDUCTION, ///< Boolean

    QO_VIDEO_QP,           ///< Int32, Range: 0-51
    QO_VIDEO_MAX_QP,       ///< Int32, Range: 0-51
    QO_VIDEO_MIN_QP,       ///< Int32, Range: 0-51
    QO_VIDEO_CRF,          ///< Int32 Range: 0-51
    QO_VIDEO_GOP,          ///< Int32 Often range from 1 to hundreds
    QO_VIDEO_B_FRAME_STRATEGY, ///< Int32 from 0 to 3. See ffmpeg documentation
    QO_VIDEO_AQ_MODE,      ///< Int32 from 0 to 3. See ffmpeg documentation

    QO_VIDEO_BITRATE,      ///< Size
    QO_VIDEO_MAX_BITRATE,  ///< Size
    QO_VIDEO_MIN_BITRATE,  ///< Size
    QO_VIDEO_MAX_B_FRAMES, ///< Int32
    QO_VIDEO_KEYINT_MIN,   ///< Int32
    QO_VIDEO_PRERES,       ///< Int32 
    QO_VIDEO_ME_RANGE,     ///< Size
    QO_VIDEO_SCENECUT,     ///< Size 0 to disable
};

struct _VideoQualityPair
{
    enum QO_VideoQualityKeys   key_type;
    qo_byte_t                  value[0];
};
typedef struct _VideoQualityPair VideoQualityPair;

/// @brief  Create a new video quality indicator
/// @param  reserved_size The size of the memory reserved for the video quality 
///         indicator. 0 indicates default size.
/// @return The new video quality indicator. NULL if failed.
QO_VideoQualityIndicator *
QO_INTERFACE(qo_video_quality_indicator_new)(
    qo_size_t  reserved_size
);

/// @brief  Duplicate a video quality indicator
/// @param  old_indicator The video quality indicator to duplicate
/// @return The duplicated video quality indicator. NULL if failed.
QO_VideoQualityIndicator *
QO_INTERFACE(qo_video_quality_indicator_duplicate)(
    QO_VideoQualityIndicator * old_indicator
) QO_NONNULL(1);

/// @brief  Delete a video quality indicator
/// @param  video_quality_indicator The video quality indicator to delete
///         NULL is allowed, in that case the function does nothing.
void
QO_INTERFACE(qo_video_quality_indicator_delete)(
    QO_VideoQualityIndicator * video_quality_indicator
);

/// @brief  Set a video quality indicator key-value pair
/// @param  video_quality_indicator The video quality indicator
/// @param  key The key, see enum QO_VIDEO_QUALITY_KEYS
/// @param  value The value. The type depends on the key. Need to be casted to 
///         qo_intmax_t, like (qo_intmax_t)18 , (qo_intmax_t)"veryfast"
/// @return The status of the operation
/// @retval QO_OK The operation is successful
/// @retval QO_OUT_OF_MEMORY The operation failed due to out of memory
/// @retval QO_INVALID_ARG Invalid argument passed to the function, like
///         value 100 for key QO_VIDEO_QP
qo_stat_t
QO_INTERFACE(qo_video_quality_indicator_set)(
    QO_VideoQualityIndicator * video_quality_indicator ,
    enum QO_VIDEO_QUALITY_KEYS key ,
    qo_intmax_t                value
) QO_NONNULL(1);

/// @brief  Get value of a video quality indicator key-value pair
/// @param  video_quality_indicator The video quality indicator
/// @param  key The key, see enum QO_VIDEO_QUALITY_KEYS
/// @param  p_value A pointer to store the value. The type depends on the key.
/// @param  data_size_limit The maximum size of the data to be stored in p_value.
/// @return The status of the operation
/// @retval QO_OK The operation is successful
/// @retval QO_NOT_FOUND The key is not found in the video quality indicator
/// @remark Some types of value have a variable size, like string, when 
///         data_size_limit is very useful. If the object is larger than 
///         data_size_limit, the function may truncate the data.
///         If data_size_limit is 0, it indicates the buffer specified in 
///         p_value is sufficiently large to hold the data. 
qo_stat_t
QO_INTERFACE(qo_video_quality_indicator_get)(
    QO_VideoQualityIndicator * video_quality_indicator ,
    enum QO_VIDEO_QUALITY_KEYS key ,
    qo_pointer_t               p_value ,
    qo_size_t                  data_size_limit
) QO_NONNULL(1 , 3); 

/// @brief  Clear all pairs in the video quality indicator
/// @param  video_quality_indicator The video quality indicator
/// @return The number of key-value pairs in the video quality indicator cleared
qo_size_t
QO_INTERFACE(qo_video_quality_indicator_clear)(
    QO_VideoQualityIndicator * video_quality_indicator
) QO_NONNULL(1);

/// @brief  Get the number of key-value pairs in the video quality indicator
/// @param  video_quality_indicator The video quality indicator
/// @return The number of key-value pairs in the video quality indicator. 
///         QO_SIZE_MAX if failed. 0 if the video quality indicator is empty.
qo_size_t
QO_INTERFACE(qo_video_quality_indicator_get_pair_count)(
    QO_VideoQualityIndicator * video_quality_indicator
) QO_NONNULL(1);

/// @brief  Get the total size of the video quality indicator
/// @param  video_quality_indicator The video quality indicator
qo_size_t
QO_INTERFACE(qo_video_quality_indicator_get_total_size)(
    QO_VideoQualityIndicator * video_quality_indicator
) QO_NONNULL(1);

/// @brief  Reserve space for key-value pairs in the video quality indicator
/// @param  delta_size The number of key-value pairs to reserve. Negative value
///         indicates to release space sized by the absolute value. It is safe 
///         to pass delta_size even if free_size + delta_size is negative. In 
///         that case, the function will release all the unused space.
/// @return The status of the operation
/// @retval QO_OK The operation is successful
/// @retval QO_OUT_OF_MEMORY The memory is not enough to reserve specified space
qo_stat_t
QO_INTERFACE(qo_video_quality_indicator_reserve)(
    QO_VideoQualityIndicator * video_quality_indicator ,
    qo_ssize_t                 delta_size
);

#if defined(__cplusplus)
}
#endif // __cplusplus