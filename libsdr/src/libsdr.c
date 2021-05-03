#include "libsdr.h"
#include <volk/volk_common.h>
#include <volk/volk_malloc.h>
#include <volk/volk.h>

int libsdr_version() {
    return 2;
}

#pragma region libsdr_filter_real

libsdr_filter_real_data* libsdr_filter_real_create(int taps, int decimation)
{
	//Allocate context
    libsdr_filter_real_data* ctx = malloc(sizeof(libsdr_filter_real_data));
    
    //Allocate arrays
    size_t alignment = volk_get_alignment();
    ctx->tempBufferPtr = volk_malloc(sizeof(float) * 1, alignment);
    ctx->coeffsBufferPtr = volk_malloc(sizeof(float) * taps, alignment);
    ctx->insampBufferPtr = volk_malloc(sizeof(float) * taps * 2, alignment);
    ctx->insampBufferPtrOffset = &ctx->insampBufferPtr[taps];

    //Apply settings
    ctx->taps = taps;
    ctx->decimation = decimation;
    ctx->decimationIndex = 0;
    ctx->offset = 0;

    return ctx;
}

int libsdr_filter_real_process(libsdr_filter_real_data* ctx, float* input, float* output, int channels, int count)
{
    int read = 0;
    for (int i = 0; i < count; i++) {
        // Write to both the real position as well as an offset value
        ctx->insampBufferPtr[ctx->offset] = *input;
        ctx->insampBufferPtrOffset[ctx->offset++] = *input;
        input += channels;
        ctx->offset %= ctx->taps;

        // Process (if needed)
        if (ctx->decimationIndex++ == 0) {
            volk_32f_x2_dot_prod_32f_u(ctx->tempBufferPtr,
                                            &ctx->insampBufferPtr[ctx->offset],
                                            ctx->coeffsBufferPtr,
                                            ctx->taps);
            output[read++ * channels] = ctx->tempBufferPtr[0];
        }
        ctx->decimationIndex %= ctx->decimation;
    }
    return read;
}

void libsdr_filter_real_free(libsdr_filter_real_data* ctx)
{
    volk_free(ctx->tempBufferPtr);
    volk_free(ctx->coeffsBufferPtr);
    volk_free(ctx->insampBufferPtr);
}

#pragma endregion libsdr_filter_real

#pragma region libsdr_filter_complex

libsdr_filter_complex_data* libsdr_filter_complex_create(int taps, int decimation)
{
	//Allocate context
    libsdr_filter_complex_data* ctx = malloc(sizeof(libsdr_filter_complex_data));
    
    //Allocate arrays
    size_t alignment = volk_get_alignment();
    ctx->tempBufferPtr = volk_malloc(sizeof(lv_32fc_t) * 1, alignment);
    ctx->coeffsBufferPtr = volk_malloc(sizeof(lv_32fc_t) * taps, alignment);
    ctx->insampBufferPtr = volk_malloc(sizeof(lv_32fc_t) * taps * 2, alignment);
    ctx->insampBufferPtrOffset = &ctx->insampBufferPtr[taps];

    //Apply settings
    ctx->taps = taps;
    ctx->decimation = decimation;
    ctx->decimationIndex = 0;
    ctx->offset = 0;

    return ctx;
}

int libsdr_filter_complex_process(libsdr_filter_complex_data* ctx, lv_32fc_t* input, lv_32fc_t* output, int channels, int count)
{
    int read = 0;
    for (int i = 0; i < count; i++) {
        // Write to both the real position as well as an offset value
        ctx->insampBufferPtr[ctx->offset] = *input;
        ctx->insampBufferPtrOffset[ctx->offset++] = *input;
        input += channels;
        ctx->offset %= ctx->taps;

        // Process (if needed)
        if (ctx->decimationIndex++ == 0) {
            volk_32fc_x2_dot_prod_32fc_u(ctx->tempBufferPtr,
                                            &ctx->insampBufferPtr[ctx->offset],
                                            ctx->coeffsBufferPtr,
                                            ctx->taps);
            output[read++ * channels] = ctx->tempBufferPtr[0];
        }
        ctx->decimationIndex %= ctx->decimation;
    }
    return read;
}

void libsdr_filter_complex_free(libsdr_filter_complex_data* ctx)
{
    volk_free(ctx->tempBufferPtr);
    volk_free(ctx->coeffsBufferPtr);
    volk_free(ctx->insampBufferPtr);
}

#pragma endregion libsdr_filter_complex