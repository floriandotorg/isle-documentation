#ifndef LEGOOBJECTFACTORY_H
#define LEGOOBJECTFACTORY_H

#include "mxobjectfactory.h"

/**
 * @def FOR_LEGOOBJECTFACTORY_OBJECTS(X)
 * @brief [AI] Macro that lists all object types that LegoObjectFactory is capable of constructing and managing.
 * @details [AI] Used internally to generate member MxAtomId fields for each possible object type, which enables swift object lookup and construction by name.
 */
#define FOR_LEGOOBJECTFACTORY_OBJECTS(X)                                                                               \
	X(LegoEntityPresenter)                                                                                             \
	X(LegoActorPresenter)                                                                                              \
	X(LegoWorldPresenter)                                                                                              \
	X(LegoWorld)                                                                                                       \
	X(LegoModelPresenter)                                                                                              \
	X(LegoTexturePresenter)                                                                                            \
	X(LegoPhonemePresenter)                                                                                            \
	X(LegoFlcTexturePresenter)                                                                                         \
	X(LegoPalettePresenter)                                                                                            \
	X(LegoPathPresenter)                                                                                               \
	X(LegoAnimPresenter)                                                                                               \
	X(LegoLoopingAnimPresenter)                                                                                        \
	X(LegoLocomotionAnimPresenter)                                                                                     \
	X(LegoHideAnimPresenter)                                                                                           \
	X(LegoPartPresenter)                                                                                               \
	X(LegoCarBuildAnimPresenter)                                                                                       \
	X(LegoActionControlPresenter)                                                                                      \
	X(LegoMeterPresenter)                                                                                              \
	X(LegoLoadCacheSoundPresenter)                                                                                     \
	X(Lego3DWavePresenter)                                                                                             \
	X(LegoActor)                                                                                                       \
	X(LegoPathActor)                                                                                                   \
	X(LegoRaceCar)                                                                                                     \
	X(LegoJetski)                                                                                                      \
	X(JetskiRace)                                                                                                      \
	X(LegoEntity)                                                                                                      \
	X(LegoCarRaceActor)                                                                                                \
	X(LegoJetskiRaceActor)                                                                                             \
	X(LegoCarBuild)                                                                                                    \
	X(Infocenter)                                                                                                      \
	X(LegoAnimActor)                                                                                                   \
	X(MxControlPresenter)                                                                                              \
	X(RegistrationBook)                                                                                                \
	X(HistoryBook)                                                                                                     \
	X(ElevatorBottom)                                                                                                  \
	X(InfocenterDoor)                                                                                                  \
	X(Score)                                                                                                           \
	X(ScoreState)                                                                                                      \
	X(Hospital)                                                                                                        \
	X(Isle)                                                                                                            \
	X(Police)                                                                                                          \
	X(GasStation)                                                                                                      \
	X(LegoAct2)                                                                                                        \
	X(LegoAct2State)                                                                                                   \
	X(CarRace)                                                                                                         \
	X(LegoRaceCarBuildState)                                                                                           \
	X(LegoCopterBuildState)                                                                                            \
	X(LegoDuneCarBuildState)                                                                                           \
	X(LegoJetskiBuildState)                                                                                            \
	X(HospitalState)                                                                                                   \
	X(InfocenterState)                                                                                                 \
	X(PoliceState)                                                                                                     \
	X(GasStationState)                                                                                                 \
	X(SkateBoard)                                                                                                      \
	X(Helicopter)                                                                                                      \
	X(HelicopterState)                                                                                                 \
	X(DuneBuggy)                                                                                                       \
	X(Pizza)                                                                                                           \
	X(PizzaMissionState)                                                                                               \
	X(Act2Actor)                                                                                                       \
	X(Act2Brick)                                                                                                       \
	X(Act2GenActor)                                                                                                    \
	X(Act2PoliceStation)                                                                                               \
	X(Act3)                                                                                                            \
	X(Act3State)                                                                                                       \
	X(Doors)                                                                                                           \
	X(LegoAnimMMPresenter)                                                                                             \
	X(RaceCar)                                                                                                         \
	X(Jetski)                                                                                                          \
	X(Bike)                                                                                                            \
	X(Motocycle)                                                                                                       \
	X(Ambulance)                                                                                                       \
	X(AmbulanceMissionState)                                                                                           \
	X(TowTrack)                                                                                                        \
	X(TowTrackMissionState)                                                                                            \
	X(Act3Cop)                                                                                                         \
	X(Act3Brickster)                                                                                                   \
	X(Act3Shark)                                                                                                       \
	X(BumpBouy)                                                                                                        \
	X(Act3Actor)                                                                                                       \
	X(JetskiRaceState)                                                                                                 \
	X(CarRaceState)                                                                                                    \
	X(Act1State)                                                                                                       \
	X(Pizzeria)                                                                                                        \
	X(PizzeriaState)                                                                                                   \
	X(InfoCenterEntity)                                                                                                \
	X(HospitalEntity)                                                                                                  \
	X(GasStationEntity)                                                                                                \
	X(PoliceEntity)                                                                                                    \
	X(BeachHouseEntity)                                                                                                \
	X(RaceStandsEntity)                                                                                                \
	X(JukeBoxEntity)                                                                                                   \
	X(RadioState)                                                                                                      \
	X(CaveEntity)                                                                                                      \
	X(JailEntity)                                                                                                      \
	X(MxCompositeMediaPresenter)                                                                                       \
	X(JukeBox)                                                                                                         \
	X(JukeBoxState)                                                                                                    \
	X(RaceSkel)                                                                                                        \
	X(AnimState)

/**
 * @class LegoObjectFactory
 * @brief [AI] Object factory for the LEGO Island game, responsible for instantiating all game-specific entities and presenters via name-based lookup.
 * @details [AI] LegoObjectFactory maintains a table of MxAtomId objects which provide a fast mapping from class name strings to object type. The Create function uses these mappings to return a new instance of the relevant class or delegates to its base class for unsupported types. All memory management of constructed objects is centralized; deleting via Destroy ensures proper deallocation.
 *
 * This class centralizes the construction of almost all runtime game objects and presenters (including entities, race actors, presenters for media, and game-state classes). It is used heavily when objects are loaded dynamically from scripts or streamed data.
 *
 * The object factory is key for extensibility and supporting both new and legacy entity types in a safe manner.
 */
class LegoObjectFactory : public MxObjectFactory {
public:
	/**
	 * @brief [AI] Constructs a new LegoObjectFactory; initializes all known type names as MxAtomId for rapid lookup.
	 * @details [AI] All type name identifiers are constructed with case-exact matching to support correct mapping from incoming script or system requests.
	 */
	LegoObjectFactory();

	/**
	 * @brief [AI] Creates an object by name.
	 * @param p_name Name of the class/type to instantiate. [AI]
	 * @details [AI] Looks up the class name in its member MxAtomId table. If a match is found, instantiates the appropriate concrete object and returns a pointer to its base type (MxCore).
	 * If not recognized, delegates to the base MxObjectFactory implementation.
	 * The return is always non-null; an assertion is triggered otherwise.
	 */
	MxCore* Create(const char* p_name) override; // vtable+0x14

	/**
	 * @brief [AI] Destroys an object that was previously created by this factory.
	 * @param p_object Pointer to the object to delete. [AI]
	 * @details [AI] Centralized destruction allows maintenance of custom deletion logic, though currently this directly deletes the pointer.
	 */
	void Destroy(MxCore* p_object) override;     // vtable+0x18

	// SYNTHETIC: LEGO1 0x10009000
	// LegoObjectFactory::`scalar deleting destructor'
	// @brief [AI] Standard compiler-generated scalar deleting destructor. Handles deletion of an array or single object via operator delete.

	// SYNTHETIC: LEGO1 0x10009170
	// LegoObjectFactory::~LegoObjectFactory
	// @brief [AI] Default virtual destructor for LegoObjectFactory. Ensures that all derived destructors are called in correct order.

private:
	/**
	 * @var m_idV
	 * @brief [AI] Stores a MxAtomId corresponding to the string class/type name V for factory object identification.
	 * @details [AI] For every supported object type, an m_idV member is created by macro expansion of FOR_LEGOOBJECTFACTORY_OBJECTS(X). Used for rapid class name to type conversion.
	 */
#define X(V) MxAtomId m_id##V;
	FOR_LEGOOBJECTFACTORY_OBJECTS(X)
#undef X
};

#endif // LEGOOBJECTFACTORY_H