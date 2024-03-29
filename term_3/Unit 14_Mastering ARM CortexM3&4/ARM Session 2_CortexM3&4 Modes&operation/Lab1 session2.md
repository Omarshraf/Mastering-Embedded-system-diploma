# Handler mode Vs Thread mode

## Thread mode
### Default Operation:
The MCU typically starts in Thread mode, which is also called unprivileged mode. In this mode, the processor operates in an unprivileged state, meaning it has restricted access to certain resources and instructions.

### Privileged Access:
However, Thread mode can be switched to privileged mode, giving the processor access to all system resources and instructions. This is typically done for tasks requiring higher privileges, such as handling system-level operations.

### Privilege Level Change: 
Once the MCU is in non-privileged (unprivileged) mode, it cannot directly switch back to privileged mode. This restriction helps maintain system security and prevents unauthorized access to critical resources.

## Handler mode
### Interrupt Handling:
When an interrupt occurs, the processor switches from Thread mode to Handler mode to handle the interrupt service routine (ISR). Interrupts could be triggered by external events (like peripheral events) or internal events (like software triggers).

### Privileged Operation:
In Handler mode, the processor operates in a privileged state, which provides unrestricted access to system resources and instructions. This unrestricted access is necessary for handling interrupts efficiently and performing critical system tasks.

### Non-Changeable Privilege:
Unlike Thread mode, the privilege level in Handler mode cannot be changed. This is because maintaining privileged access is crucial for handling interrupts effectively and ensuring system stability and security during interrupt servicing.