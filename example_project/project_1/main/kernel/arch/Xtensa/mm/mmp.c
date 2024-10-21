#include <uapi/drm.h>

unsigned long mmp(void *to, const void *from, unsigned long n)
{
    __u32 *dst = (__u32 *)to;
    __u32 *src = (__u32 *)from;
    // unsigned long times = n / 4;
    // unsigned long tres = 4 - n % 4;
    // asm volatile (
    //       " MOVI  A2 , %0 \n  "   
    //       " MOVI  A3 , %1 \n  "   
    //       " MOVI  A4 , %2 \n  "   
    //       " MOVI  A5 , 0  \n  "
    //       "_loop: \n"
    //       " L32I  A5 , 0(A3) \n "
    //       " S32I  A5 , 0(A2) \n "
    //       " ADD   A2 , 4  \n"
    //       " ADD   A3 , 4  \n"
    //       " BEQ   A4 , 0 , _end  \n"
    //       "_end:\n"
    //       " SUB   A2 , %3  \n"
    //       " SUB   A3 , %3  \n"
    //       " L32I  A5 , 0(A3) \n "
    //       " S32I  A5 , 0(A2) \n "
    //       " RET   \n"
    //       : 
    //       : "r"(dst), "r"(src), "r"(times)
    //       : "a2", "a3", "a4", "a5"
    // );
    return n;
}


