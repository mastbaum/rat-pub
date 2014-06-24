/**
 * @class RAT::DS::Sample
 * @brief A digitized charge and time sample
 */

#ifndef __RAT_DS_Sample__
#define __RAT_DS_Sample__

#include <TObject.h>

namespace RAT {
  namespace DS {

class Sample : public TObject {
public:
  Sample() {}
  virtual ~Sample() {}

  virtual Double_t GetTime() const { return time; }
  virtual void SetTime (Double_t _time) { time = _time; }

  virtual Float_t GetCharge() const { return charge; }
  virtual void SetCharge(Float_t _charge) { charge = _charge; }

  ClassDef(Sample, 1)

protected:
  double time;
  float charge;
};

  }  // namespace DS
}  // namespace RAT

#endif  // __RAT_DS_Sample__

