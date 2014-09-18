#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
#include <G4String.hh>
#include <G4ThreeVector.hh>
#include <RAT/DetectorComponent.hh>
#include <RAT/DetectorConstruction.hh>
#include <RAT/Log.hh>

namespace RAT {

DetectorComponent::DetectorComponent(G4RotationMatrix* pRot,
                                     const G4ThreeVector& tlate,
                                     G4LogicalVolume* pCurrentLogical,
                                     const G4String& pName,
                                     G4LogicalVolume* pMotherLogical,
                                     G4bool pMany,
                                     G4int pCopyNo,
                                     G4bool pSurfChk)
  : G4PVPlacement(pRot, tlate, pCurrentLogical, pName, pMotherLogical, pMany,
                  pCopyNo, pSurfChk) {
  Initialize();
}

DetectorComponent::DetectorComponent(const G4Transform3D& Transform3D,
                                     G4LogicalVolume* pCurrentLogical,
                                     const G4String& pName,
                                     G4LogicalVolume* pMotherLogical,
                                     G4bool pMany,
                                     G4int pCopyNo,
                                     G4bool pSurfChk)
  : G4PVPlacement(Transform3D, pCurrentLogical, pName, pMotherLogical, pMany,
                  pCopyNo, pSurfChk) {
  Initialize();
}

DetectorComponent::DetectorComponent(G4RotationMatrix* pRot,
                                     const G4ThreeVector& tlate,
                                     const G4String& pName,
                                     G4LogicalVolume* pLogical,
                                     G4VPhysicalVolume* pMother,
                                     G4bool pMany,
                                     G4int pCopyNo,
                                     G4bool pSurfChk)
  : G4PVPlacement(pRot, tlate, pName, pLogical, pMother, pMany, pCopyNo,
                  pSurfChk) {
  Initialize();
}
    
DetectorComponent::DetectorComponent(const G4Transform3D& Transform3D,
                                     const G4String& pName,
                                     G4LogicalVolume* pLogical,
                                     G4VPhysicalVolume* pMother,
                                     G4bool pMany,
                                     G4int pCopyNo,
                                     G4bool pSurfChk)
  : G4PVPlacement(Transform3D, pName, pLogical, pMother, pMany, pCopyNo,
                  pSurfChk) {
  Initialize();
}


DetectorComponent::~DetectorComponent() {
  debug << "DetectorComponent: Destroyed " << this->GetName() << newline;
}


void DetectorComponent::Initialize() {
  debug << "DetectorComponent: Created " << this->GetName() << newline;
  DetectorConstruction::GetDetectorConstruction()->RegisterComponent(this);
}

}  // namespace RAT

