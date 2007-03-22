

int atomic_increment(unsigned long *p)
{
    int retval;
    __asm
    {
        mov             eax, p
        lock inc        [eax]
        mov             eax, 0
        setnz           al

        mov             retval, eax
    }
    return retval;
}

int atomic_decrement(unsigned long *p)
{
    int retval;
    
    __asm
    {
        mov             eax, p
        lock dec        [eax]
        mov             eax, 0
        setnz           al

        mov             retval, eax
    }

    return retval;
}

