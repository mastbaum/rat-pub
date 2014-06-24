#include <vector>
#include <RAT/TriggerSum.hh>
#include <RAT/TriggerPulse.hh>

namespace RAT {

float TriggerSum::GetHeight(int i) {
  float height = 0;
  float time = pulse.at(i)->GetStartTime();
  for (int j=0; j<=i; j++){
    height += pulse.at(j)->GetHeight(time);
  }
  return height;
}

}  // namespace RAT

