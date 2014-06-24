#ifndef __RAT_TriggerPulse__
#define __RAT_TriggerPulse__

namespace RAT {

/**
 * @class RAT::TriggerPulse
 * @brief A trigger signal due to a hit channel, to model an analog trigger
 */
class TriggerPulse {
public:
  TriggerPulse() {}
  virtual ~TriggerPulse() {}

  virtual void SetStartTime(double time){ fStartTime = time; }
  virtual double GetStartTime() const { return fStartTime; }

  virtual void SetWidth(float width){ fPulseWidth = width; }
  virtual float GetWidth() { return fPulseWidth; }

  virtual void SetHeight(float height) = 0;
  virtual float GetHeight(double time) = 0;

protected:
  double fStartTime;
  float fPulseWidth;
};


/**
 * @class RAT::SquareTriggerPulse
 * @brief A trigger pulse with a perfectly square shape
 */
class SquareTriggerPulse : public TriggerPulse {
public:
  SquareTriggerPulse() {}
  virtual ~SquareTriggerPulse() {}

  virtual void SetHeight(float height) { fPulseHeight = height; }
  virtual float GetHeight(double time);

private:
  float fPulseHeight;
};

}  // namespace RAT

#endif  // __RAT_TriggerPulse__

