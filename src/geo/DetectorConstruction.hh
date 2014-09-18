/**
 * @class RAT::DetectorConstruction
 * @brief Load detector geometry and construct the volumes.
 */

#ifndef __RAT_DetectorConstruction__
#define __RAT_DetectorConstruction__

#include <vector>
#include <G4VUserDetectorConstruction.hh>

class G4VPhysicalVolume;

namespace RAT {

class DetectorComponent;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction() {}
  virtual ~DetectorConstruction() {}

  // Make volumes, return pointer to world
  virtual G4VPhysicalVolume* Construct();

  // Called by Construct, provided for convenience
  void ConstructMaterials();

  // Get a pointer to the world volume
  G4VPhysicalVolume* GetWorld() const { return fWorldPhys; }

  // Register a detector component
  void RegisterComponent(DetectorComponent* comp) {
    fComponents.push_back(comp);
  }

  // Get the list of all registered detector components
  std::vector<DetectorComponent*> GetComponents() const { return fComponents; }

  static DetectorConstruction* GetDetectorConstruction();

protected:
  static DetectorConstruction* sDetectorConstruction;
  G4VPhysicalVolume* fWorldPhys;

  /** A registry of the DetectorComponents */
  std::vector<DetectorComponent*> fComponents;
};

}  // namespace RAT

#endif  // __RAT_DetectorConstruction__

