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

using Color = type::RGB8 [[hex::inline_visualize("color", r, g, b, 0xff)]];

struct Gif {
    u32 width;
    u32 height;
    u32 num_colors;
    Color colors[num_colors];
    u8 image[width * height];
};

struct NamedGif {
    std::string::SizedString<u32> name;
    Gif gif [[inline]];
};

struct TextureInfoEntry {
    std::string::SizedString<u32> name;
    Gif image1;
    if (std::string::at(name, 0) == '^') {
        Gif image2;
    }
} [[format("format_named")]];

struct ModelTextureInfo {
    u32 num_textures;
    u32 skip_textures;
    TextureInfoEntry textures[num_textures];
};

struct PartTextureInfo {
    u32 num_textures;
    TextureInfoEntry textures[num_textures];
};

bitfield PackedVertexIndex {
    new_vertex: 1;
    if (new_vertex == 0) {
        padding: 15;
    } else {
        normal_index: 15;
    }
    padding: 1;
    vertex_index: 15;
} [[bitfield_order(std::core::BitfieldOrder::MostToLeastSignificant, 32)]];

enum Shading: u8 {
    Flat = 0,
    Gouraud = 1,
    WireFrame = 2,
};

struct Mesh {
    u16 num_polys;
    u16 num_mesh_verts;
    PackedVertexIndex vertex_indices_packed[num_polys * 3];
    u32 num_texture_indices;
    if (num_texture_indices > 0) {
        u32 texture_indices[num_polys * 3];
    }
    Color color;
    float transparency;
    Shading shading;
    padding[2];
    bool use_color_alias;
    std::string::SizedString<u32> texture_name;
    std::string::SizedString<u32> material_name;
};

struct LOD {
    u32 unknown;
    u32 num_meshes;
    if (num_meshes > 0) {
        u16 num_verts;
        u16 double_num_normals;
        u32 num_text_verts;
        Vector3f vertices[num_verts];
        Vector3f normals[double_num_normals >> 1];
        Vector2f uvs[num_text_verts];
        Mesh meshes[num_meshes];
    }
};

fn format_roi(auto roi) {
    return std::format("{0} (Children: {1})", roi.name, roi.num_children);
};

struct ModelROI<auto Offset, auto Lods> {
    std::string::SizedString<u32> name;
    Vector3f boundingSpherePosition;
    float boundingSphereRadius;
    Vector3f boundingBoxMin;
    Vector3f boundingBoxMax;
    std::string::SizedString<u32> texture_name;
    bool defined_elsewhere;
    if (!defined_elsewhere) {
        u32 num_lods;
        if (num_lods > 0) {
            u32 end_component_offset;
            if (Lods) {
                LOD lod[num_lods];
            } else {
                u8 lod[end_component_offset - ($ - Offset)];
            }
            std::assert(end_component_offset + Offset == $, "End component offset does not match");
        }
    }
    u32 num_children;
    ModelROI<Offset, Lods> children[num_children];
} [[format("format_roi")]];

// workaround as long as std::ptr::relative_to_parent does not return the actual parent but the same value.
fn relative_to_parent(u32 offset) {
    return addressof(parent.parent);
};

fn format_model(auto model) {
    return std::format("{0}", model.roi.name);
};

struct Model<auto Lods> {
    u32 version;
    ModelTextureInfo *texture_info_offset : u32 [[pointer_base("relative_to_parent")]];
    u32 num_rois;
    Animation<false> animation;
    ModelROI<addressof(this), Lods> roi;
} [[format("format_model")]];

fn format_named(auto named) {
    return named.name;
};

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
    u32 num_images;
    NamedGif images[num_images];
    u32 global_part_size;
    Part<false> global_part;
};

WDB wdb @ 0;
