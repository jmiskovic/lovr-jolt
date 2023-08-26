#include "JoltPhysicsC.h"
#include <lauxlib.h>
#include <assert.h>
#include "lua.h"

// Object layers
#define NUM_OBJ_LAYERS 2
#define OBJ_LAYER_NON_MOVING 0
#define OBJ_LAYER_MOVING 1

// Broad phase layers
#define NUM_BP_LAYERS 2
#define BP_LAYER_NON_MOVING 0
#define BP_LAYER_MOVING 1


typedef struct BPLayerInterfaceImpl
{
    const JPC_BroadPhaseLayerInterfaceVTable *vtable; // VTable has to be the first field in the struct.
    JPC_BroadPhaseLayer                       object_to_broad_phase[NUM_OBJ_LAYERS];
} BPLayerInterfaceImpl;

static uint32_t
BPLayerInterface_GetNumBroadPhaseLayers(const void *in_self)
{
    return NUM_BP_LAYERS;
}


static JPC_BroadPhaseLayer
BPLayerInterface_GetBroadPhaseLayer(const void *in_self, JPC_ObjectLayer in_layer)
{
  assert(in_layer < NUM_BP_LAYERS);
  const BPLayerInterfaceImpl *self = (BPLayerInterfaceImpl *)in_self;
  return self->object_to_broad_phase[in_layer];
}


static BPLayerInterfaceImpl
BPLayerInterface_Create(void)
{
  static const JPC_BroadPhaseLayerInterfaceVTable vtable =
  {
    .GetNumBroadPhaseLayers = BPLayerInterface_GetNumBroadPhaseLayers,
    .GetBroadPhaseLayer   = BPLayerInterface_GetBroadPhaseLayer,
  };
  BPLayerInterfaceImpl impl =
  {
    .vtable = &vtable,
  };
  impl.object_to_broad_phase[OBJ_LAYER_NON_MOVING] = BP_LAYER_NON_MOVING;
  impl.object_to_broad_phase[OBJ_LAYER_MOVING]   = BP_LAYER_MOVING;

  return impl;
}


typedef struct MyObjectFilter
{
    const JPC_ObjectLayerPairFilterVTable *vtable; // VTable has to be the first field in the struct.
} MyObjectFilter;


typedef struct MyBroadPhaseFilter
{
    const JPC_ObjectVsBroadPhaseLayerFilterVTable *vtable; // VTable has to be the first field in the struct.
} MyBroadPhaseFilter;


static bool
MyObjectFilter_ShouldCollide(const void *in_self, JPC_ObjectLayer in_object1, JPC_ObjectLayer in_object2)
{
    switch (in_object1)
    {
        case OBJ_LAYER_NON_MOVING:
            return in_object2 == OBJ_LAYER_MOVING;
        case OBJ_LAYER_MOVING:
            return true;
        default:
            assert(false);
            return false;
    }
}


static bool
MyBroadPhaseFilter_ShouldCollide(const void *in_self, JPC_ObjectLayer in_layer1, JPC_BroadPhaseLayer in_layer2)
{
    switch (in_layer1)
    {
        case OBJ_LAYER_NON_MOVING:
            return in_layer2 == BP_LAYER_MOVING;
        case OBJ_LAYER_MOVING:
            return true;
        default:
            assert(false);
            return false;
    }
}


static MyBroadPhaseFilter
MyBroadPhaseFilter_Create(void)
{
    static const JPC_ObjectVsBroadPhaseLayerFilterVTable vtable =
    {
        .ShouldCollide = MyBroadPhaseFilter_ShouldCollide,
    };
    MyBroadPhaseFilter impl =
    {
        .vtable = &vtable,
    };
    return impl;
}


static MyObjectFilter
MyObjectFilter_Create(void)
{
    static const JPC_ObjectLayerPairFilterVTable vtable =
    {
        .ShouldCollide = MyObjectFilter_ShouldCollide,
    };
    MyObjectFilter impl =
    {
        .vtable = &vtable,
    };
    return impl;
}


static int l_joltNewWorld(lua_State* L) {
  const uint32_t max_bodies = 10240;
  const uint32_t num_body_mutexes = 0; // zero is auto-detect
  const uint32_t max_body_pairs = 65536;
  const uint32_t max_contact_constraints = 20480;

  BPLayerInterfaceImpl broad_phase_layer_interface = BPLayerInterface_Create();
  MyBroadPhaseFilter broad_phase_filter = MyBroadPhaseFilter_Create();
  MyObjectFilter object_filter = MyObjectFilter_Create();

  JPC_PhysicsSystem *physics_system = JPC_PhysicsSystem_Create(
    max_bodies,
    num_body_mutexes,
    max_body_pairs,
    max_contact_constraints,
    &broad_phase_layer_interface,
    &broad_phase_filter,
    &object_filter);
  return 0;
}


static luaL_Reg jolt_api[] = {
  { "newWorld", l_joltNewWorld },
  { NULL, NULL }
};


int luaopen_jolt(lua_State *L) {
  lua_newtable(L);
  luaL_register(L, NULL, jolt_api);

  JPC_RegisterDefaultAllocator();
  JPC_CreateFactory();
  JPC_RegisterTypes();
  return 1;
}
