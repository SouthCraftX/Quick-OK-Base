#include "media/video_quality_indicator.h"
#include "memalloc.h"

#define DEFAULT_FIRST_ALLOC_SIZE  (sizeof(NULL) * 8)



struct _XOC_VideoQualityIndicator
{
    xoc_int16_t         count; ///< Number of quality pairs
    xoc_uint32_t        free_size;
    xoc_uint32_t        total_size;

    /// @brief Pointer to the first available byte. It is after the last quality pair.
    xoc_pointer_t       available; 

    VideoQualityPair    pairs[0];
};

XOC_VideoQualityIndicator *
XOC_IMPL(xoc_video_quality_indicator_new)(
    xoc_size_t          first_alloc_size
){
    first_alloc_size = first_alloc_size ? first_alloc_size : DEFAULT_FIRST_ALLOC_SIZE;
    XOC_VideoQualityIndicator * indicator = 
        (XOC_VideoQualityIndicator *)xoc_alloc(first_alloc_size);

    if (XOC_LIKELY(indicator))
    {
        indicator->count = 0;
        indicator->free_size = first_alloc_size - sizeof(*indicator);
    }
    return indicator;
}

XOC_VideoQualityIndicator *
XOC_IMPL(xoc_video_quality_indicator_duplicate)(
    XOC_VideoQualityIndicator * old_indicator
){
    XOC_VideoQualityIndicator * new_indicator = 
        (XOC_VideoQualityIndicator *)xoc_alloc(old_indicator->total_size);

    if (XOC_LIKELY(new_indicator))
    {
        memcpy(new_indicator, old_indicator, old_indicator->total_size);
    }
    return new_indicator;
}

void
XOC_IMPL(xoc_video_quality_indicator_delete)(
    XOC_VideoQualityIndicator * indicator
){
    xoc_free(indicator);
}