cmake_minimum_required(VERSION 3.14)

project(lovr-jolt)

option(USE_DOUBLE_PRECISION "Use double precision" OFF)
option(ENABLE_ASSERTS "Enable asserts" ON)

set(LUA_LIBRARY ${LOVR_LUA})

set(JOLTC_SOURCES
    JoltC/JoltPhysicsC.cpp
    JoltC/JoltPhysicsC_Extensions.cpp
)

if(LOVR)
    list(APPEND JOLTC_SOURCES l_jolt.c)
endif()

# The JoltPhysicsC_Extensions includes Jolt headers which include then sstream. That file also makes
# the `#define public public` hack and so the sstream is redeclared with different access.
# The sstream has header guard, so it can only be included once. So `-include` makes sure it is
# included at the top before the hack is applied. It's a hacky workaround for a hacky workaround.
set_source_files_properties(JoltC/JoltPhysicsC_Extensions.cpp PROPERTIES COMPILE_FLAGS "-include sstream")

set(JOLT_SOURCES
    Jolt/AABBTree/AABBTreeBuilder.cpp
    Jolt/Core/Color.cpp
    Jolt/Core/Factory.cpp
    Jolt/Core/IssueReporting.cpp
    Jolt/Core/JobSystemThreadPool.cpp
    Jolt/Core/JobSystemWithBarrier.cpp
    Jolt/Core/LinearCurve.cpp
    Jolt/Core/Memory.cpp
    Jolt/Core/Profiler.cpp
    Jolt/Core/RTTI.cpp
    Jolt/Core/Semaphore.cpp
    Jolt/Core/StringTools.cpp
    Jolt/Core/TickCounter.cpp
    Jolt/Geometry/ConvexHullBuilder.cpp
    Jolt/Geometry/ConvexHullBuilder2D.cpp
    Jolt/Geometry/Indexify.cpp
    Jolt/Geometry/OrientedBox.cpp
    Jolt/Math/UVec4.cpp
    Jolt/Math/Vec3.cpp
    Jolt/ObjectStream/ObjectStream.cpp
    Jolt/ObjectStream/ObjectStreamBinaryIn.cpp
    Jolt/ObjectStream/ObjectStreamBinaryOut.cpp
    Jolt/ObjectStream/ObjectStreamIn.cpp
    Jolt/ObjectStream/ObjectStreamOut.cpp
    Jolt/ObjectStream/ObjectStreamTextIn.cpp
    Jolt/ObjectStream/ObjectStreamTextOut.cpp
    Jolt/ObjectStream/SerializableObject.cpp
    Jolt/ObjectStream/TypeDeclarations.cpp
    Jolt/Physics/Body/Body.cpp
    Jolt/Physics/Body/BodyAccess.cpp
    Jolt/Physics/Body/BodyCreationSettings.cpp
    Jolt/Physics/Body/BodyInterface.cpp
    Jolt/Physics/Body/BodyManager.cpp
    Jolt/Physics/Body/MassProperties.cpp
    Jolt/Physics/Body/MotionProperties.cpp
    Jolt/Physics/Character/Character.cpp
    Jolt/Physics/Character/CharacterBase.cpp
    Jolt/Physics/Character/CharacterVirtual.cpp
    Jolt/Physics/Collision/BroadPhase/BroadPhase.cpp
    Jolt/Physics/Collision/BroadPhase/BroadPhaseBruteForce.cpp
    Jolt/Physics/Collision/BroadPhase/BroadPhaseQuadTree.cpp
    Jolt/Physics/Collision/BroadPhase/QuadTree.cpp
    Jolt/Physics/Collision/CastConvexVsTriangles.cpp
    Jolt/Physics/Collision/CastSphereVsTriangles.cpp
    Jolt/Physics/Collision/CollideConvexVsTriangles.cpp
    Jolt/Physics/Collision/CollideSphereVsTriangles.cpp
    Jolt/Physics/Collision/CollisionDispatch.cpp
    Jolt/Physics/Collision/CollisionGroup.cpp
    Jolt/Physics/Collision/EstimateCollisionResponse.cpp
    Jolt/Physics/Collision/GroupFilter.cpp
    Jolt/Physics/Collision/GroupFilterTable.cpp
    Jolt/Physics/Collision/ManifoldBetweenTwoFaces.cpp
    Jolt/Physics/Collision/NarrowPhaseQuery.cpp
    Jolt/Physics/Collision/NarrowPhaseStats.cpp
    Jolt/Physics/Collision/PhysicsMaterial.cpp
    Jolt/Physics/Collision/PhysicsMaterialSimple.cpp
    Jolt/Physics/Collision/Shape/BoxShape.cpp
    Jolt/Physics/Collision/Shape/CapsuleShape.cpp
    Jolt/Physics/Collision/Shape/CompoundShape.cpp
    Jolt/Physics/Collision/Shape/ConvexHullShape.cpp
    Jolt/Physics/Collision/Shape/ConvexShape.cpp
    Jolt/Physics/Collision/Shape/CylinderShape.cpp
    Jolt/Physics/Collision/Shape/DecoratedShape.cpp
    Jolt/Physics/Collision/Shape/HeightFieldShape.cpp
    Jolt/Physics/Collision/Shape/MeshShape.cpp
    Jolt/Physics/Collision/Shape/MutableCompoundShape.cpp
    Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.cpp
    Jolt/Physics/Collision/Shape/RotatedTranslatedShape.cpp
    Jolt/Physics/Collision/Shape/ScaledShape.cpp
    Jolt/Physics/Collision/Shape/Shape.cpp
    Jolt/Physics/Collision/Shape/SphereShape.cpp
    Jolt/Physics/Collision/Shape/StaticCompoundShape.cpp
    Jolt/Physics/Collision/Shape/TaperedCapsuleShape.cpp
    Jolt/Physics/Collision/Shape/TriangleShape.cpp
    Jolt/Physics/Collision/TransformedShape.cpp
    Jolt/Physics/Constraints/ConeConstraint.cpp
    Jolt/Physics/Constraints/Constraint.cpp
    Jolt/Physics/Constraints/ConstraintManager.cpp
    Jolt/Physics/Constraints/ContactConstraintManager.cpp
    Jolt/Physics/Constraints/DistanceConstraint.cpp
    Jolt/Physics/Constraints/FixedConstraint.cpp
    Jolt/Physics/Constraints/GearConstraint.cpp
    Jolt/Physics/Constraints/HingeConstraint.cpp
    Jolt/Physics/Constraints/MotorSettings.cpp
    Jolt/Physics/Constraints/PathConstraint.cpp
    Jolt/Physics/Constraints/PathConstraintPath.cpp
    Jolt/Physics/Constraints/PathConstraintPathHermite.cpp
    Jolt/Physics/Constraints/PointConstraint.cpp
    Jolt/Physics/Constraints/PulleyConstraint.cpp
    Jolt/Physics/Constraints/RackAndPinionConstraint.cpp
    Jolt/Physics/Constraints/SixDOFConstraint.cpp
    Jolt/Physics/Constraints/SliderConstraint.cpp
    Jolt/Physics/Constraints/SwingTwistConstraint.cpp
    Jolt/Physics/Constraints/TwoBodyConstraint.cpp
    Jolt/Physics/DeterminismLog.cpp
    Jolt/Physics/IslandBuilder.cpp
    Jolt/Physics/LargeIslandSplitter.cpp
    Jolt/Physics/PhysicsLock.cpp
    Jolt/Physics/PhysicsScene.cpp
    Jolt/Physics/PhysicsSystem.cpp
    Jolt/Physics/PhysicsUpdateContext.cpp
    Jolt/Physics/Ragdoll/Ragdoll.cpp
    Jolt/Physics/StateRecorderImpl.cpp
    Jolt/Physics/Vehicle/MotorcycleController.cpp
    Jolt/Physics/Vehicle/TrackedVehicleController.cpp
    Jolt/Physics/Vehicle/VehicleAntiRollBar.cpp
    Jolt/Physics/Vehicle/VehicleCollisionTester.cpp
    Jolt/Physics/Vehicle/VehicleConstraint.cpp
    Jolt/Physics/Vehicle/VehicleController.cpp
    Jolt/Physics/Vehicle/VehicleDifferential.cpp
    Jolt/Physics/Vehicle/VehicleEngine.cpp
    Jolt/Physics/Vehicle/VehicleTrack.cpp
    Jolt/Physics/Vehicle/VehicleTransmission.cpp
    Jolt/Physics/Vehicle/Wheel.cpp
    Jolt/Physics/Vehicle/WheeledVehicleController.cpp
    Jolt/RegisterTypes.cpp
    Jolt/Renderer/DebugRenderer.cpp
    Jolt/Renderer/DebugRendererPlayback.cpp
    Jolt/Renderer/DebugRendererRecorder.cpp
    Jolt/Skeleton/SkeletalAnimation.cpp
    Jolt/Skeleton/Skeleton.cpp
    Jolt/Skeleton/SkeletonMapper.cpp
    Jolt/Skeleton/SkeletonPose.cpp
    Jolt/TriangleGrouper/TriangleGrouperClosestCentroid.cpp
    Jolt/TriangleGrouper/TriangleGrouperMorton.cpp
    Jolt/TriangleSplitter/TriangleSplitter.cpp
    Jolt/TriangleSplitter/TriangleSplitterBinning.cpp
    Jolt/TriangleSplitter/TriangleSplitterFixedLeafSize.cpp
    Jolt/TriangleSplitter/TriangleSplitterLongestAxis.cpp
    Jolt/TriangleSplitter/TriangleSplitterMean.cpp
    Jolt/TriangleSplitter/TriangleSplitterMorton.cpp
)

if(USE_DOUBLE_PRECISION)
    add_compile_definitions(JPH_DOUBLE_PRECISION)
endif()

if(ENABLE_ASSERTS)
    add_compile_definitions(JPH_ENABLE_ASSERTS)
endif()

add_library(lovr-jolt SHARED ${JOLTC_SOURCES} ${JOLT_SOURCES})
set_target_properties(lovr-jolt PROPERTIES PREFIX "") # skip the 'lib' prefix

target_include_directories(lovr-jolt
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/JoltC
    ${CMAKE_CURRENT_SOURCE_DIR}/Jolt
)

set_target_properties(lovr-jolt PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    POSITION_INDEPENDENT_CODE TRUE
)

target_compile_options(lovr-jolt PRIVATE
  -fno-sanitize=undefined
)

# standalone joltC test (no Lua bindings)
if(NOT DEFINED LOVR)
    add_executable(lovrjolt_tests joltc_test_runner.c JoltC/JoltPhysicsC_Tests.c)
    set_source_files_properties(JoltC/JoltPhysicsC_Tests.c PROPERTIES COMPILE_FLAGS "-DPRINT_OUTPUT")
    target_link_libraries(lovrjolt_tests lovr-jolt)

    target_include_directories(lovrjolt_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/JoltC
        ${CMAKE_CURRENT_SOURCE_DIR}/Jolt
    )
endif()
