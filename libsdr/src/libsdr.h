#include <volk/volk_common.h>
#include <volk/volk_complex.h>

VOLK_API inline int libsdr_version() {
    return 2;
}

#pragma region libsdr_filter_real

typedef struct {
    float* tempBufferPtr;
    float* coeffsBufferPtr;
    float* insampBufferPtr;
    float* insampBufferPtrOffset;

    int taps;
    int decimation;
    int decimationIndex;
    int offset;
} libsdr_filter_real_data;

VOLK_API libsdr_filter_real_data* libsdr_filter_real_create(int taps, int decimation);
VOLK_API int libsdr_filter_real_process(libsdr_filter_real_data* ctx, float* input, float* output, int channels, int count);
VOLK_API void libsdr_filter_real_free(libsdr_filter_real_data* ctx);

#pragma endregion libsdr_filter_real

#pragma region libsdr_filter_complex

typedef struct {
    lv_32fc_t* tempBufferPtr;
    lv_32fc_t* coeffsBufferPtr;
    lv_32fc_t* insampBufferPtr;
    lv_32fc_t* insampBufferPtrOffset;

    int taps;
    int decimation;
    int decimationIndex;
    int offset;
} libsdr_filter_complex_data;

VOLK_API libsdr_filter_complex_data* libsdr_filter_complex_create(int taps, int decimation);
VOLK_API int libsdr_filter_complex_process(libsdr_filter_complex_data* ctx, lv_32fc_t* input, lv_32fc_t* output, int channels, int count);
VOLK_API void libsdr_filter_complex_free(libsdr_filter_complex_data* ctx);

#pragma endregion libsdr_filter_complex