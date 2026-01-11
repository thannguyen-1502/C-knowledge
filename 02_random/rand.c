#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>

typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;

typedef struct 
{
    u64 state;
    u64 inc;
} prng_state;

void prng_seed_r(prng_state *rng, u64 initState, u64 initSeq);
void prng_seed(u64 initState, u64 initSeq);

u32 prng_rand_r(prng_state *rng);
u32 prng_rand(void);

f32 prng_randf_r(prng_state* rng);
f32 prng_randf(void);

int main(void)
{
    for (size_t i = 0; i < 10; i++)
    {
        printf("%u\n", prng_rand());
    }
    
    return 0;
}

static prng_state s_prng_state = {0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL,};

void prng_seed_r(prng_state *rng, u64 initState, u64 initSeq)
{
    rng->state = 0U;
    rng->inc = (initSeq << 1u) | 1u;
    prng_rand_r(rng);
    rng->state += initState;
    prng_rand_r(rng);
}

void prng_seed(u64 initState, u64 initSeq)
{
    prng_seed_r(&s_prng_state, initState, initSeq);
}

u32 prng_rand_r(prng_state *rng)
{
    u64 oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    u32 xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    u32 rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}
u32 prng_rand(void)
{
    return prng_rand_r(&s_prng_state);
}

f32 prng_randf_r(prng_state* rng) {
    return (f32)prng_rand_r(rng) / (f32)UINT32_MAX;
}

f32 prng_randf(void) {
    return prng_randf_r(&s_prng_state);
}