/**
 * @class RAT::DetectorComponent
 * @author A. Mastbaum <mastbaum@hep.upenn.edu>
 *
 * @brief An augmented G4PVPlacement with additional information
 *
 * WARNING: PORT IS A WORK IN PROGRESS!
 *
 * Detector components inherit from G4VPhysicalVolumes, but they contain
 * additional information and methods related to event generation and
 * output recording.
 *
 * This class and functionality are ported from the Baccarat package, and
 * are originally authored by V. Gehman and K. Kazkaz. All bugs are RAT's!
 */

#ifndef __RAT_DetectorComponent__
#define __RAT_DetectorComponent__

#include <vector>
#include <G4PVPlacement.hh>

namespace RAT {

class DetectorComponent : public G4PVPlacement {
public:
  DetectorComponent(G4RotationMatrix* pRot,
                    const G4ThreeVector& tlate,
                    G4LogicalVolume* pCurrentLogical,
                    const G4String& pName,
                    G4LogicalVolume* pMotherLogical,
                    G4bool pMany,
                    G4int pCopyNo,
                    G4bool pSurfChk=false);
  
  DetectorComponent(const G4Transform3D& Transform3D,
                    G4LogicalVolume* pCurrentLogical,
                    const G4String& pName,
                    G4LogicalVolume* pMotherLogical,
                    G4bool pMany,
                    G4int pCopyNo,
                    G4bool pSurfChk=false);

  DetectorComponent(G4RotationMatrix* pRot,
                    const G4ThreeVector& tlate,
                    const G4String& pName,
                    G4LogicalVolume* pLogical,
                    G4VPhysicalVolume* pMother,
                    G4bool pMany,
                    G4int pCopyNo,
                    G4bool pSurfChk=false);
  
  DetectorComponent(const G4Transform3D& Transform3D,
                    const G4String& pName,
                    G4LogicalVolume* pLogical,
                    G4VPhysicalVolume* pMother,
                    G4bool pMany,
                    G4int pCopyNo,
                    G4bool pSurfChk=false);
               
  virtual ~DetectorComponent();
  
  void Initialize();

  double GetVolume();  ///< Calculate the volume (G4 does a poor job)

private:
  /**
   * This method records the displacement and orientation of this sub-volume
   * with respect to the physical volume that is passed to it. If you pass
   * this method the world volume, it will record this object's global
   * coordinates.
   */
  void DetermineCenterAndExtent(G4PVPlacement*);

private:
  double maxX;
  double minX;
  double maxY;
  double minY;
  double maxZ;
  double minZ;
  double xPos;
  double yPos;
  double zPos;

  G4ThreeVector globalCenter;
  G4RotationMatrix globalOrientation;
};

}  // namespace RAT

#endif  // __RAT_DetectorComponent__

