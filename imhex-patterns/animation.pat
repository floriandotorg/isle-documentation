#pragma author xZise
#pragma description Animation types used in ani and wdb files
#pragma endian little

import std.string;

import legoisland.common;

bitfield TimeAndFlags {
    time: 24;
    skip_interpolation: 1;
    negate_rotation: 1;
    active: 1;
    padding: 5;
};

struct VertexKey {
    TimeAndFlags timeAndFlags;
    Vector3f vertex;
};

struct RotationKey {
    TimeAndFlags timeAndFlags;
    float w;
    float x;
    float y;
    float z;
};

struct RotationZKey {
    TimeAndFlags timeAndFlags;
    float z;
};

struct MorphKey {
    TimeAndFlags timeAndFlags;
    bool visible;
};

struct AnimationNode {
    std::string::SizedString<u32> name;
    u16 num_translations;
    VertexKey translations[num_translations];
    u16 num_rotations;
    RotationKey rotations[num_rotations];
    u16 num_scales;
    VertexKey scales[num_scales];
    u16 num_morphs;
    MorphKey morphs[num_morphs];
    u32 num_children;
    AnimationNode children[num_children];
};

struct Actor {
    std::string::SizedString<u32> name;
    if (name.size > 0) {
        u32 actor_type;
    }
};

struct Scene {
    u16 num_translations1;
    VertexKey translations1[num_translations1];
    u16 num_translations2;
    VertexKey translations2[num_translations2];
    u16 num_rotations;
    RotationZKey rotations[num_rotations];
};

struct Animation<auto ParseScene> {
    u32 num_actors;
    Actor actors[num_actors];
    s32 duration;

    if (ParseScene) {
        Scene scene;
    }

    AnimationNode animation;
};