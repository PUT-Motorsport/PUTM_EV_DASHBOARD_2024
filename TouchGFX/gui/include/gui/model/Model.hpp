#ifndef MODEL_HPP
#define MODEL_HPP

#include "data.h"

class ModelListener;

class Model {
  public:
    Model();

    void bind(ModelListener* listener) { modelListener = listener; }

    void tick();

  protected:
    ModelListener* modelListener;

  private:
    Data_TypeDef m_sharedData;
    Data_TypeDef m_sharedDataPrev;
    SafetyData_TypeDef m_sharedSafetyData;
    SafetyData_TypeDef m_sharedSafetyDataPrev;
    TimerData_TypeDef m_timerData;
    TimerData_TypeDef m_timerDataPrev;
};

#endif  // MODEL_HPP
