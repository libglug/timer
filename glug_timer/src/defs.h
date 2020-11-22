#ifndef GLUG_DEFS_H
#define GLUG_DEFS_H

#define NSEC_PER_SEC (uint32_t)1e9

#define HIGH_U64(x) ((x) >> 32 & 0xffffffff)
#define LOW_U64(x)  ((x) & 0xffffffff)

#endif // GLUG_DEFS_H
