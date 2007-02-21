.text
.global atomic_increment
atomic_increment:
        movl    4(%esp), %eax
        lock
        incl    (%eax)
        movl    $0,%eax
        setnz   %al
        ret

.global atomic_decrement
atomic_decrement:
        movl    4(%esp), %eax
        lock
        decl    (%eax)
        movl    $0,%eax
        setnz   %al
        ret
