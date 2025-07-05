import type.magic;

struct Struct {
    std::string::SizedString<u8> name;
    u32 flags;
};

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

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
    
    Vec3 unknown1;
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
    Vec4 unknown2;
    Vec4 normals[num_edges];
    Vec3 unknown3;
    float unknown4;
    u8 num_triggers;
    if (num_triggers > 0) {
        BoundaryTrigger triggers[num_triggers];
        Vec3 unknown5;
    }
};

struct Start {
    u16 num_struct;
    u16 num_nodes;
    u16 num_ctrl_edges;
    u16 num_boundaries;
    Struct structs[num_struct];
    Vec3 nodes[num_nodes];
    CtrlEdge ctrl_edges[num_ctrl_edges];
    Boundary boundaries[num_boundaries];
};

Start start @ 0x00;
