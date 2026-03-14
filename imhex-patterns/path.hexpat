import type.magic;

import legoisland.common;

struct Struct {
    std::string::SizedString<u8> name;
    u32 flags;
} [[format("format_named")]];

struct CtrlEdge {
    u16 flags;
    
    u16 point_a_idx;
    u16 point_b_idx;
    
    if (flags & 0x04) {
        u16 face_a_idx;
        u16 ccw_a_idx;
        u16 cw_a_idx;
    }
    
    if (flags & 0x08) {
        u16 face_b_idx;
        u16 ccw_b_idx;
        u16 cw_b_idx;
    }
    
    Vector3f unknown1;
    float unknown2;
};

struct BoundaryTrigger {
    u16 path_idx;
    u32 data;
    float unknown;
};

struct Boundary {
    u8 num_edges;
    u16 edges_idx[num_edges];
    u8 flags;
    u8 unknown1;
    std::string::SizedString<u8> name;
    Vector4f unknown2;
    Vector4f normals[num_edges];
    Vector3f unknown3;
    float unknown4;
    u8 num_triggers;
    if (num_triggers > 0) {
        BoundaryTrigger triggers[num_triggers];
        Vector3f unknown5;
    }
} [[format("format_named")]];

struct Start {
    u16 num_struct;
    u16 num_nodes;
    u16 num_ctrl_edges;
    u16 num_boundaries;
    Struct structs[num_struct];
    Vector3f nodes[num_nodes];
    CtrlEdge ctrl_edges[num_ctrl_edges];
    Boundary boundaries[num_boundaries];
};

Start start @ 0x00;
