/**
 * @file interface_task.h
 * @brief Header file for the interface task.
 *
 * Declares the Interface_Task function, which handles button inputs and LED updates.
 */

#ifndef __INTERFACE_TASK_H__
#define __INTERFACE_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Interface task function.
 *
 * This function implements the user interface task that processes button inputs and controls LEDs.
 *
 * @param argument Pointer to task-specific parameters (not used).
 */
void Interface_Task(void* argument);

#ifdef __cplusplus
}
#endif

#endif /* __INTERFACE_TASK_H__ */
