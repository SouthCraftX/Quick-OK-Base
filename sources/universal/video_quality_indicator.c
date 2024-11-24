#include "media/video_quality_indicator.h"
#include "memalloc.h"

#define DEFAULT_FIRST_ALLOC_SIZE  (sizeof(NULL) * 8)



struct _QO_VideoQualityIndicator
{
    qo_int16_t         count; ///< Number of quality pairs
    qo_uint32_t        free_size;
    qo_uint32_t        total_size;

    /// @brief Pointer to the first available byte. It is after the last quality pair.
    qo_pointer_t       available; 

    VideoQualityPair    pairs[0];
};

QO_VideoQualityIndicator *
QO_IMPL(qo_video_quality_indicator_new)(
    qo_size_t          first_alloc_size
){
    first_alloc_size = first_alloc_size ? first_alloc_size : DEFAULT_FIRST_ALLOC_SIZE;
    QO_VideoQualityIndicator * indicator = 
        (QO_VideoQualityIndicator *)qo_alloc(first_alloc_size);

    if (QO_LIKELY(indicator))
    {
        indicator->count = 0;
        indicator->free_size = first_alloc_size - sizeof(*indicator);
    }
    return indicator;
}

QO_VideoQualityIndicator *
QO_IMPL(qo_video_quality_indicator_duplicate)(
    QO_VideoQualityIndicator * old_indicator
){
    QO_VideoQualityIndicator * new_indicator = 
        (QO_VideoQualityIndicator *)qo_alloc(old_indicator->total_size);

    if (QO_LIKELY(new_indicator))
    {
        memcpy(new_indicator, old_indicator, old_indicator->total_size);
    }
    return new_indicator;
}

void
QO_IMPL(qo_video_quality_indicator_delete)(
    QO_VideoQualityIndicator * indicator
){
    qo_free(indicator);
}