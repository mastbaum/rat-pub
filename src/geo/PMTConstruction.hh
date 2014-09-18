#ifndef __RAT_PMTConstruction__
#define __RAT_PMTConstruction__

#include <string>
#include <vector>
#include <RAT/GLG4TorusStack.hh>
#include <G4Material.hh>
#include <G4OpticalSurface.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4LogicalVolume.hh>
#include <RAT/DetectorComponent.hh>

namespace RAT {

struct PMTConstructionParams {
  PMTConstructionParams () { 
    efficiencyCorrection = 1.0; 
    prepulseProb = 0.0;
  };
  
  // Envelope control
  bool useEnvelope;
  double faceGap;
  double minEnvelopeRadius;
  
  // Body
  std::vector<double> zEdge; // n+1
  std::vector<double> rhoEdge; // n+1
  std::vector<double> zOrigin; // n
  double wallThickness; // mm

  double dynodeRadius; // mm
  double dynodeTop; // mm

  G4Material *exterior;
  G4Material *glass;
  G4Material *vacuum;
  G4Material *dynode;
  
  G4OpticalSurface *photocathode;
  G4OpticalSurface *mirror;
  G4OpticalSurface *dynode_surface;

  G4VSensitiveDetector *detector;
  
  double efficiencyCorrection; // default to 1.0 for no correction
  double prepulseProb;
};

class PMTConstruction {
public:
  
  PMTConstruction (const PMTConstructionParams &params);
  G4LogicalVolume *NewPMT(const std::string &prefix, bool simpleVis=false);
  GLG4TorusStack *NewBodySolid(const std::string &name);
  void SetPMTOpticalSurfaces(DetectorComponent *body_phys, const std::string &name_prefix);
protected:
  G4VSolid *NewEnvelopeSolid(const std::string &name);
  
  void CalcInnerParams(GLG4TorusStack *body,
                       std::vector<double> &innerZEdge, std::vector<double> &innerRhoEdge,
                       int &equatorIndex, double &zLowestDynode);  
  // phyiscal volumes 
  DetectorComponent* body_phys;
  DetectorComponent* inner1_phys;
  DetectorComponent* inner2_phys;
  DetectorComponent* central_gap_phys;
  DetectorComponent* dynode_phys;
  
  PMTConstructionParams fParams;
};

} // namespace RAT

#endif

