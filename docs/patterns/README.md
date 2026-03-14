# ImHex patterns

ImHex is a hex editor which also supports custom made patterns to more easily decode and inspect binary files. There some custom made binary formats within Lego Island and the files in this repository aim to support at least some of them.

## Usage

As some patterns import other patterns in this directory it is advised to add this directory to ImHex. To do that open the [settings](https://docs.werwolv.net/imhex/misc/settings#categories) and simply add this directory. To work correctly this directory needs the subdirectory `patterns` with the subdirectory `legoisland`.

The patterns aren't automatically detected and need to manually imported.

## Supported files

| Name | Path | Description |
|------|------|-------------|
| ani files | [`patterns/legoisland/ani.hexpat`](ani.hexpat) | Animation file for Lego Island |
| dta files | [`patterns/legoisland/dta.hexpat`](dta.hexpat) | DTA file for Lego Island |
| gph files | [`patterns/legoisland/path.hexpat`](path.hexpat) | GPH file/Path definition for Lego Island |
| mod files | [`patterns/legoisland/mod.hexpat`](mod.hexpat) | Model file for Lego Island |
| tex files | [`patterns/legoisland/tex.hexpat`](tex.hexpat) | TEX files (textures) for Lego Island |
| WORLD.WDB | [`patterns/legoisland/worlddb.hexpat`](worlddb.hexpat) | World DB file for Lego Island |

Other file types (WAVE, FLIC and Smacker) are supported by ImHex itself and don't need this directory.

## Special handling for WORLD.WDB

The pattern for WORLD.WDB files can decode it into very high detail. Doing this unfortunately takes a lot of time and so parts of the pattern can be switched between high and low detail. By default it uses low detail when decoding the complete file just using a byte array for the data. When more detail is wanted the `Model<>`, `ModelROI<>`, `Part<>` and `PartROI<>` structs can be manually placed with the high detail enabled.

To do that determine the address where the relevant type is placed and set the `Lods` template constant to `true`. The `ModelROI<>` and `PartROI<>` structs also needs the offset to the `Model`'s or `Part`'s address. A few examples could look like this:

```rust
// The `pizpie` model in `ACT1` world
Model<true> pizpie @ 0x73FF1E;
// The same ROI information for the model
ModelROI<0x73FF1E, true> pizpie_roi @ 0x73FF48;
// The `capdb` part in `ACT1` world
Part<true> capdb @ 0x122626;
// Only the global `HEAD` part
PartROI<0x6778A, true> head @ 0x6BF3E;
```

It is also possible to change the `Model<false>` and `Part<false>` fields in `ModelRef` and `PartRef` but doing that would also require to increase the pattern limit.