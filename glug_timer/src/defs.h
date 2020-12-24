#ifndef GLUG_DEFS_H
#define GLUG_DEFS_H

#define NSEC_PER_SEC (uint32_t)1e9

#define HIGH_MASK_U64(x) ((x) & 0xffffffff00000000)
#define LOW_MASK_U64(x)  ((x) & 0x00000000ffffffff)

#endif // GLUG_DEFS_H
