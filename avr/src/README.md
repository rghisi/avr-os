# Embedded OS

A OOP, toy, OS for embedded (or not) systems.

## Goals
* [ ] Multiplatform support
  * Improve build system and project structure to enable easier multiplaform
* [x] Enable context switching for multitasking
  * Currently for AVR MCUs
* [x] Periodic task scheduler
  * With milliseconds granularity
* [x] Background/Best effort task scheduler
  * Cleanup required to remove old periodic tracing
  * Move background sleep implementation out of tasks
* [x] Basic Async/Await mechanism aimed for I/O
* [ ] Console with serial hw
  * Basic blocking primitives
  * Better support needed
* [x] Custom heap memory allocator
  * A bit high on overhead
  * With free blocks merging
  * Best-fit search to reduce fragmentation
* [x] Static stack allocation for tasks
* [x] Heap stack allocation for tasks
* [x] Sample tasks for experimentation
* [ ] More?