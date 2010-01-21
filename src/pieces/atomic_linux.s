.text
.global atomic_increment
atomic_increment:
        lock
        incl    (%rdi)
        movl    $0,%eax
        setnz   %al
        ret

.global atomic_decrement
atomic_decrement:
        lock
        decl    (%rdi)
        movl    $0,%eax
        setnz   %al
        ret
