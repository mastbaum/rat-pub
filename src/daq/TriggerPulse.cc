#include <RAT/TriggerPulse.hh>

namespace RAT {

float SquareTriggerPulse::GetHeight(double time) {
  if (time - fStartTime < fPulseWidth) {
    return fPulseHeight;
  }

  return 0;
}

}  // namespace RAT

