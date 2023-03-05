#include "../h/printing.hpp"
#include "../h/riscv.hpp"
#include "../h/UserMain.hpp"
#include "../h/MemoryAllocator.hpp"


int main() {

    MemoryAllocator::mem_init();

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

    _thread::running = _thread::createThread(nullptr);

    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    __asm__ volatile ("mv a0, %0" : : "r" (45));
    __asm__ volatile ("ecall");

    userMain();

    printString("Finished\n");
    return 0;
}