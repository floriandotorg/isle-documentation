#pragma author xZise
#pragma description Animation file for Lego Island
#pragma endian little

import std.io;
import std.string;
import type.magic;

import legoisland.common;
import legoisland.animation;

struct Anim {
    type::Magic<"\x11\x00\x00\x00"> magic;
    float unknown1;
    Vector3f unknownVector;
    s32 parse_scene;
    s32 val3;
    Animation<parse_scene != 0> animation;
};

Anim a @ 0;