#include <iostream>
#include <string.h>



float bintofloat(uint32_t x) {
    float f = 0.0f;
    memcpy(&f, &x, sizeof(f) < sizeof(x) ? sizeof(f) : sizeof(x));
    return f;
}

uint32_t read_value_from_four_byte_buff(unsigned char * input)
{
    uint32_t x = 0U;
    x =  (uint32_t)(0xFF & input[0]);
    x |= (uint32_t)(0xFF & input[1]) << 8;
    x |= (uint32_t)(0xFF & input[2]) << 16;
    x |= (uint32_t)(0xFF & input[3]) << 24;
    return x;
}

static void print_bytes(const void *object, size_t size){
    #ifdef __cplusplus
    const unsigned char * const bytes = static_cast<const unsigned char *>(object);
    #else // __cplusplus
    const unsigned char * const bytes = object;
    #endif // __cplusplus

    size_t i;

    printf("[-");
    for(i = 0; i < size; i++)
    {
        //printf(bytes[i]);
        int binary[8];
        for(int n = 0; n < 8; n++){
            binary[7-n] = (bytes[size -1 - i] >> n) & 1;
        }
        /* print result */
        for(int n = 0; n < 8; n++){
            printf("%d", binary[n]);
        }
        printf("%c", '-');
    }
    printf("]\n\n");
}
