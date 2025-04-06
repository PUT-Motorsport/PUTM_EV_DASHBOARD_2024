/**
 * @file led_test_task.h
 * @brief Header file for the LED test task.
 *
 * Declares the Led_Test_Task function, which tests the LED functionality.
 */
#ifndef __LED_TEST_TASK_H__
#define __LED_TEST_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LED test task function.
 *
 * This function implements the LED test task. It waits for a set time,
 * then resets the LED test flag and terminates the task.
 *
 * @param argument Pointer to task-specific parameters (not used).
 */
void Led_Test_Task(void* argument);

#ifdef __cplusplus
}
#endif

#endif /* __LED_TEST_TASK_H__ */
