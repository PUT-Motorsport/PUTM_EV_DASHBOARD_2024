/**
 * @file Model.hpp
 * @brief Declaration of the Model class.
 *
 * The Model class collects system data and updates its internal state.
 * It notifies the associated ModelListener about data changes.
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include "data.h"

class ModelListener;


/**
 * @brief The Model class.
 */
class Model {
  public:

    /**
     * @brief Constructor.
     */
    Model();

    /**
     * @brief Binds a ModelListener to this model.
     * @param listener Pointer to an object implementing the ModelListener interface.
     */
    void bind(ModelListener* listener) { modelListener = listener; }


    /**
     * @brief Performs a tick update, refreshing internal data and notifying the listener.
     */
    void tick();

  protected:
    ModelListener* modelListener; ///< Pointer to the listener.

  private:
    Data_TypeDef m_sharedData; ///< Shared data.
    Data_TypeDef m_sharedDataPrev;  ///< Previous shared data.
    SafetyData_TypeDef m_sharedSafetyData; ///< SDC "Safety" data
    SafetyData_TypeDef m_sharedSafetyDataPrev; ///< Previous safety data.
    TimerData_TypeDef m_timerData; ///< Timer data.
    TimerData_TypeDef m_timerDataPrev; ///< Previous timer data.
};

#endif  // MODEL_HPP
