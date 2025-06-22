#pragma author xZise
#pragma description DTA file for Lego Island
#pragma endian little

import std.io;
import std.string;

import legoisland.common;

fn format_name(auto block) {
    return std::format("{}", block.name);
};

struct ModelInfo {
    std::string::SizedString<u8> name;
    u8 unknown1;
    Vector3f location;
    Vector3f direction;
    Vector3f up;
    u8 unknown2;
} [[format("format_name")]];

bitfield ActorMask {
    Pepper: 1;
    Mama: 1;
    Papa: 1;
    Nick: 1;
    Laura: 1;
    padding: 3;
};

struct Animation {
    std::string::SizedString<u8> name;
    u32 object_id;
    s16 location;
    u8 unknown1;
    u8 unknown2;
    ActorMask actor_mask;
    u8 unknown4;
    Vector3f unknown_position;
    float unknown_radius;
    u8 model_count;
    ModelInfo model_info[model_count];
} [[format("format_name")]];

u32 version @ 0x00;
u16 num_animations @ $;
Animation animation[num_animations] @ $;