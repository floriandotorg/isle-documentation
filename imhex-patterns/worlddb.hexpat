#pragma author xZise
#pragma description World DB file for Lego Island
#pragma endian little

import std.string;
import std.mem;
import std.io;
import std.core;
import std.sys;
import std.ptr;
import type.color;

import legoisland.common;
import legoisland.animation;
import legoisland.model;

import legoisland.textures;

fn format_named_ref(auto named_ref) {
    return std::format("{0} (Size: {1})", named_ref.name, named_ref.size);
};

struct PartROI<auto Offset, auto Lods> {
    std::string::SizedString<u32> name;
    u32 num_lods;
    u32 roi_info_offset;
    if (Lods) {
        LOD lod[num_lods];
    } else {
        u8 lod[roi_info_offset - ($ - Offset)];
    }
    std::assert(roi_info_offset + Offset == $, "ROI info offset does not match");
} [[format("format_named")]];

struct Part<auto Lods> {
    PartTextureInfo *texture_info_offset : u32 [[pointer_base("relative_to_parent")]];
    u32 num_rois;
    PartROI<addressof(this), Lods> rois[num_rois];
};

struct PartRef {
    std::string::SizedString<u32> name;
    u32 size;
    Part<false> *part : u32;
} [[format("format_named_ref")]];

struct ModelRef {
    std::string::SizedString<u32> name;
    u32 size;
    Model<false> *model : u32;
    std::string::SizedString<u32> texture_name;
    Vector3f location;
    Vector3f direction;
    Vector3f up;
    bool visible;
} [[format("format_named_ref")]];

fn format_world(auto world) {
    return std::format("{0} (Parts: {1}, Models: {2})", world.name, world.num_parts, world.num_models);
};

struct World {
    std::string::SizedString<u32> name;
    u32 num_parts;
    PartRef parts[num_parts];
    u32 num_models;
    ModelRef models[num_models];
} [[format("format_world")]];

struct WDB {
    u32 num_worlds;
    World worlds[num_worlds];
    u32 images_size;
    Textures textures;
    u32 global_part_size;
    Part<false> global_part;
};

WDB wdb @ 0;
