

int atomic_increment(unsigned long *p)
{
    __asm
    {
        mov             eax, [ebp+8] 
        lock inc        [eax]
        mov             eax, 0
        setnz           al

        leave
        ret
    }
}

int atomic_decrement(unsigned long *p)
{
    __asm
    {
        mov             eax, [ebp+8] 
        lock dec        [eax]
        mov             eax, 0
        setnz           al

        leave
        ret
    }
}

