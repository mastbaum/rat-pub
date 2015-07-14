/**
 * @class RAT::TriggerSum
 * @brief A waveform built from trigger pulses, to model an analog trigger
 */

#ifndef __RAT_TriggerSum___
#define __RAT_TriggerSum___

#include <vector>
#include <RAT/ListHelp.hh>
#include <RAT/TriggerPulse.hh>

namespace RAT {

class TriggerSum {
public:
  TriggerSum() {}

  virtual ~TriggerSum() {
    deepdelete_vector<TriggerPulse>(pulse);
  }

  virtual float GetHeight(int i);

  std::vector<TriggerPulse*> pulse;
};

}  // namespace RAT

#endif  // __RAT_TriggerSum__

