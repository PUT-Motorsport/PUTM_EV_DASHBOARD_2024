/**
 * @file communication_task.h
 * @brief Header file for the communication task.
 *
 * Declares the Communication_Task function, which handles CAN communication.
 */


#ifndef __COMMUNICATION_TASK_H__
#define __COMMUNICATION_TASK_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Communication task function.
 *
 * This function implements the CAN communication task. It continuously sends and receives
 * CAN messages, processes data, and updates shared data structures.
 *
 * @param argument Pointer to task-specific parameters (not used).
 */
void Communication_Task(void* argument);

#ifdef __cplusplus
}
#endif

#endif /* __COMMUNICATION_TASK_H__ */
