#include "port/avr/atmega328p/SerialPort0.h"
#include "system/TaskScheduler.h"
#include "comms/Serial.h"
#include "system/OS.h"
#include "system/DoublyLinkedMemoryAllocator.h"
#include "console/Shell.h"
#include "port/avr/AVRContextSwitcher.h"
#include "setup/Cpp.h"
#include "setup/C.h"
#include "port/avr/AVRCpu.h"

TaskScheduler ta = TaskScheduler();
TaskScheduler *OS::scheduler = &ta;
auto ma = DoublyLinkedMemoryAllocator<1280>();
MemoryAllocator *OS::memoryAllocator = &ma;

AVRContextSwitcher cs = AVRContextSwitcher();
ContextSwitcher *OS::contextSwitcher = &cs;

auto serialPort0 = SerialPort0();
auto serial = Serial(&serialPort0);
Serial *Serial::self = &serial;

auto avrCpu = AVRCpu();
Cpu *OS::cpu = &avrCpu;

auto initProcess = OS::createTask(Shell::run, nullptr);

int main() {
    OS::schedule(initProcess);
    OS::start();

    return 0;
}
