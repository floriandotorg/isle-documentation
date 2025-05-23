// This file was automatically generated by the actionheadergen tool.
// Please do not manually edit this file.
#ifndef ACT3_ACTIONS_H
#define ACT3_ACTIONS_H

/**
 * @file act3_actions.h
 * @brief [AI] Defines enumerated script action identifiers for Act 3 of LEGO Island scripting system. [AI]
 * @details [AI] This header file contains an auto-generated enum mapping of script action names and types used by the Act 3 segment of the LEGO Island game engine's scripting interpreter. These values are referenced by script logic and presenter code to dispatch and recognize symbolic actions and resources, such as sounds, animations, GUI elements, and actors. The numerical values match the indices or command IDs expected by the engine and associated loading or presenter classes. [AI]
 */

namespace Act3Script
{
#if __cplusplus >= 201103L
/**
 * @enum Script
 * @brief [AI] Enumerates all available script actions, events, resources, and symbolic names supported by Act 3 of the LEGO Island game engine scripting system. The enum values are used throughout the engine for identifying asset, command, or action types as referenced by scripts and actions from SI (script) files. [AI]
 *
 * @details [AI] Script actions include sound triggers, animation identifiers, GUI events, and actor or environment objects referenced in the SI scripting. Negative values typically indicate the "none" state, while positive values correspond to specific assets or engine events. These symbolic names are used to bind script logic to runtime execution, and the actual code logic switches or dispatches on these enum constants when interpreting game actions. [AI]
 */
enum Script : int {
#else
/**
 * @enum Script
 * @brief [AI] Same as above; compatibility for pre-C++11 code. [AI]
 */
enum Script {
#endif
	c_noneAct3 = -1,                            ///< [AI] No script action; used to represent an uninitialized or invalid script action. [AI]

	c__Act3 = 0,                                ///< [AI] Reserved or unnamed root action for Act 3 scripting context. [AI]

	c_shootpz_PlayWav = 8,                      ///< [AI] Triggers sound playback for pizza shooting action via .WAV resource. [AI]
	c_shootdn_PlayWav = 9,                      ///< [AI] Triggers sound playback for donut shooting action via .WAV resource. [AI]

	c_eatdn_PlayWav = 18,                       ///< [AI] Plays sound effect when eating a donut. [AI]
	c_eatpz_PlayWav = 19,                       ///< [AI] Plays sound effect when eating a pizza. [AI]
	c_pzhitdn_PlayWav = 20,                     ///< [AI] Plays sound effect when a pizza hits a donut. [AI]
	c_HelicopterDashboard = 21,                 ///< [AI] Represents the helicopter dashboard GUI interface or overlay. [AI]
	c_HelicopterDashboard_Bitmap = 22,          ///< [AI] Bitmap resource for the helicopter dashboard. [AI]

	c_Helicopter_Pizza_Ctl = 26,                ///< [AI] Script control for helicopter pizza UI or system. [AI]
	c_Helicopter_Donut_Ctl = 27,                ///< [AI] Script control for helicopter donut UI or system. [AI]
	c_Helicopter_Info_Ctl = 28,                 ///< [AI] Script control for helicopter info/help UI or system. [AI]

	c_HelicopterTakeOff_Anim = 32,              ///< [AI] Animation resource ID for helicopter takeoff sequence. [AI]
	c_HelicopterLand_Anim = 33,                 ///< [AI] Animation resource ID for helicopter landing sequence. [AI]

	c_dnhitpz_PlayWav = 45,                     ///< [AI] Sound effect: donut hits pizza. [AI]
	c_stickpz_PlayWav = 46,                     ///< [AI] Sound effect: pizza sticks to surface/target. [AI]
	c_stickdn_PlayWav = 47,                     ///< [AI] Sound effect: donut sticks to surface/target. [AI]
	c_xarrow_PlayWav = 48,                      ///< [AI] Sound effect: arrow UI or in-game indicator. [AI]
	c_thpt_PlayWav = 49,                        ///< [AI] Sound effect: possibly "thpt" (unknown actual meaning). [AI]

	c_Act3Path = 88,                            ///< [AI] Path through Act 3 scripted event flow. [AI]
	c_InfCtr = 89,                              ///< [AI] Information Center (entity or object in the scene). [AI]
	c_InfCtrModel = 90,                         ///< [AI] Model resource for Information Center. [AI]
	c_Helicopter_Actor = 91,                    ///< [AI] Logical actor/instance for Helicopter in the world. [AI]
	c_Chptr_Model = 92,                         ///< [AI] Model or mesh resource for the helicopter. [AI]
	c_Brickstr_Walk = 93,                       ///< [AI] Brickster character walk animation/event. [AI]
	c_Brickstr_Shoot = 94,                      ///< [AI] Brickster character shoot animation/event. [AI]
	c_Shark_Eat = 95,                           ///< [AI] Shark eating animation/event logic. [AI]
	c_Shark_Actor = 96,                         ///< [AI] Shark actor/instance in Act 3. [AI]
	c_Shark_Model = 97,                         ///< [AI] Model or mesh resource for the shark entity. [AI]
	c_BrickstrCar_Actor = 98,                   ///< [AI] The Brickster's car actor instance. [AI]
	c_BrickstrCar_Model = 99,                   ///< [AI] Model/mesh resource for Brickster's car. [AI]
	c_Brickstr_Actor = 100,                     ///< [AI] Brickster actor instance. [AI]
	c_Brickstr_Model = 101,                     ///< [AI] 3D model/mesh of the Brickster. [AI]
	c_Laura_Walk = 102,                         ///< [AI] Laura character walk animation. [AI]
	c_Laura_Eat = 103,                          ///< [AI] Laura character eat animation/event. [AI]
	c_LauraCar_Actor = 104,                     ///< [AI] Laura's car actor definition. [AI]
	c_LauraCar_Model = 105,                     ///< [AI] Model or mesh for Laura's car. [AI]
	c_Laura_Actor = 106,                        ///< [AI] Laura character actor object. [AI]
	c_Laura_Model = 107,                        ///< [AI] Model or mesh for Laura character. [AI]
	c_Nick_Walk = 108,                          ///< [AI] Nick character walk animation. [AI]
	c_Nick_Eat = 109,                           ///< [AI] Nick character eat animation/event. [AI]
	c_NickCar_Actor = 110,                      ///< [AI] Nick's car actor definition. [AI]
	c_NickCar_Model = 111,                      ///< [AI] Model/mesh for Nick's car. [AI]
	c_Nick_Actor = 112,                         ///< [AI] Nick character actor object. [AI]
	c_Nick_Model = 113,                         ///< [AI] Model/mesh for Nick character. [AI]
	c_Cm_Walk = 114,                            ///< [AI] "Cm" character walk animation (possibly "Cameraman"?). [AI]
	c_Cm_Actor = 115,                           ///< [AI] "Cm" actor object. [AI]
	c_Cm_Model = 116,                           ///< [AI] Model/mesh for "Cm". [AI]
	c_Bd_Walk = 117,                            ///< [AI] "Bd" character walk animation (possibly Bill Ding). [AI]
	c_Bd_Actor = 118,                           ///< [AI] "Bd" actor object. [AI]
	c_Bd_Model = 119,                           ///< [AI] Model/mesh for "Bd". [AI]
	c_Helicopter_Pizza_Up_Bitmap = 120,         ///< [AI] Bitmap resource: helicopter pizza button (up state). [AI]
	c_Helicopter_Pizza_Down_Bitmap = 121,       ///< [AI] Bitmap resource: helicopter pizza button (down state). [AI]
	c_Helicopter_Donut_Up_Bitmap = 122,         ///< [AI] Bitmap resource: helicopter donut button (up state). [AI]
	c_Helicopter_Donut_Down_Bitmap = 123,       ///< [AI] Bitmap resource: helicopter donut button (down state). [AI]
	c_Helicopter_Info_Up_Bitmap = 124,          ///< [AI] Bitmap resource: helicopter info button (up state). [AI]
	c_Helicopter_Info_Down_Bitmap = 125,        ///< [AI] Bitmap resource: helicopter info button (down state). [AI]
	c_HelicopterDotOn1_Bitmap = 126,            ///< [AI] Bitmap for helicopter dashboard indicator dot 1 (on). [AI]
	c_HelicopterDotOn2_Bitmap = 127,            ///< [AI] Bitmap for helicopter dashboard indicator dot 2 (on). [AI]
	c_HelicopterDotOn3_Bitmap = 128,            ///< [AI] Bitmap for helicopter dashboard indicator dot 3 (on). [AI]
	c_HelicopterDotOn4_Bitmap = 129,            ///< [AI] Bitmap for helicopter dashboard indicator dot 4 (on). [AI]
	c_HelicopterDotOn5_Bitmap = 130,            ///< [AI] Bitmap for helicopter dashboard indicator dot 5 (on). [AI]
	c_HelicopterDotOn6_Bitmap = 131,            ///< [AI] Bitmap for helicopter dashboard indicator dot 6 (on). [AI]
	c_HelicopterDotOn7_Bitmap = 132,            ///< [AI] Bitmap for helicopter dashboard indicator dot 7 (on). [AI]
	c_HelicopterDotOn8_Bitmap = 133,            ///< [AI] Bitmap for helicopter dashboard indicator dot 8 (on). [AI]
	c_HelicopterDotOn9_Bitmap = 134,            ///< [AI] Bitmap for helicopter dashboard indicator dot 9 (on). [AI]
	c_HelicopterDotOn10_Bitmap = 135,           ///< [AI] Bitmap for helicopter dashboard indicator dot 10 (on). [AI]
	c_HelicopterDotOn11_Bitmap = 136,           ///< [AI] Bitmap for helicopter dashboard indicator dot 11 (on). [AI]
	c_HelicopterDotOn12_Bitmap = 137,           ///< [AI] Bitmap for helicopter dashboard indicator dot 12 (on). [AI]
	c_HelicopterDotOn13_Bitmap = 138,           ///< [AI] Bitmap for helicopter dashboard indicator dot 13 (on). [AI]
	c_HelicopterDotOn14_Bitmap = 139,           ///< [AI] Bitmap for helicopter dashboard indicator dot 14 (on). [AI]
	c_HelicopterDotOn15_Bitmap = 140,           ///< [AI] Bitmap for helicopter dashboard indicator dot 15 (on). [AI]
	c_TLP067PA_Wav_500 = 141,                   ///< [AI] SFX/WAV resource with code TLP067PA, variant 500. [AI]
	c_TLP067PA_Pho_500 = 142,                   ///< [AI] Phoneme/voiceover or similar resource with code TLP067PA, variant 500. [AI]
	c_TLP066MA_Wav_500 = 143,                   ///< [AI] SFX/WAV TLP066MA, variant 500. [AI]
	c_TLP066MA_Pho_500 = 144,                   ///< [AI] PHO TLP066MA, variant 500. [AI]
	c_TLP065NI_Wav_500 = 145,                   ///< [AI] SFX/WAV TLP065NI, variant 500. [AI]
	c_TLP065NI_Pho_500 = 146,                   ///< [AI] PHO TLP065NI, variant 500. [AI]
	c_TLP053IN_Wav_500 = 147,                   ///< [AI] SFX/WAV TLP053IN, variant 500. [AI]
	c_TLP053IN_Pho_500 = 148,                   ///< [AI] PHO TLP053IN, variant 500. [AI]
	c_TLP064LA_Wav_500 = 149,                   ///< [AI] SFX/WAV TLP064LA, variant 500. [AI]
	c_TLP064LA_Pho_500 = 150,                   ///< [AI] PHO TLP064LA, variant 500. [AI]
	c_TLP063MA_Wav_500 = 151,                   ///< [AI] SFX/WAV TLP063MA, variant 500. [AI]
	c_TLP063MA_Pho_500 = 152,                   ///< [AI] PHO TLP063MA, variant 500. [AI]
	c_TLP061NI_Wav_500 = 153,                   ///< [AI] SFX/WAV TLP061NI, variant 500. [AI]
	c_TLP061NI_Pho_500 = 154,                   ///< [AI] PHO TLP061NI, variant 500. [AI]
	c_TLP060IN_Wav_500 = 155,                   ///< [AI] SFX/WAV TLP060IN, variant 500. [AI]
	c_TLP060IN_Pho_500 = 156,                   ///< [AI] PHO TLP060IN, variant 500. [AI]
	c_TLP058MA_Wav_500 = 157,                   ///< [AI] SFX/WAV TLP058MA, variant 500. [AI]
	c_TLP058MA_Pho_500 = 158,                   ///< [AI] PHO TLP058MA, variant 500. [AI]
	c_TLP057IN_Wav_500 = 159,                   ///< [AI] SFX/WAV TLP057IN, variant 500. [AI]
	c_TLP057IN_Pho_500 = 160,                   ///< [AI] PHO TLP057IN, variant 500. [AI]
	c_TLP055PA_Wav_500 = 161,                   ///< [AI] SFX/WAV TLP055PA, variant 500. [AI]
	c_TLP055PA_Pho_500 = 162,                   ///< [AI] PHO TLP055PA, variant 500. [AI]
	c_tlp053in_0_sfx = 163,                     ///< [AI] SFX for TLP053IN, subresource or variant 0. [AI]
	c_tlp053in_1_sfx = 164,                     ///< [AI] SFX for TLP053IN, variant 1. [AI]
	c_tlp053in_2_sfx = 165,                     ///< [AI] SFX for TLP053IN, variant 2. [AI]
	c_tlp053in_3_sfx = 166,                     ///< [AI] SFX for TLP053IN, variant 3. [AI]
	c_tlp053in_4_sfx = 167,                     ///< [AI] SFX for TLP053IN, variant 4. [AI]
	c_tlp053in_5_sfx = 168,                     ///< [AI] SFX for TLP053IN, variant 5. [AI]
	c_tlp053in_Anim = 169,                      ///< [AI] Animation for TLP053IN action/resource. [AI]
	c_TLP065NI_Wav_501 = 170,                   ///< [AI] SFX/WAV TLP065NI, variant 501. [AI]
	c_TLP065NI_Pho_501 = 171,                   ///< [AI] PHO TLP065NI, variant 501. [AI]
	c_TLP064LA_Wav_501 = 172,                   ///< [AI] SFX/WAV TLP064LA, variant 501. [AI]
	c_TLP064LA_Pho_501 = 173,                   ///< [AI] PHO TLP064LA, variant 501. [AI]
	c_tlp064la_0_sfx = 174,                     ///< [AI] SFX for TLP064LA, variant 0. [AI]
	c_tlp064la_Anim = 175,                      ///< [AI] Animation for TLP064LA action/resource. [AI]
	c_TLP068IN_Wav_502 = 176,                   ///< [AI] SFX/WAV TLP068IN, variant 502. [AI]
	c_TLP068IN_Pho_502 = 177,                   ///< [AI] PHO TLP068IN, variant 502. [AI]
	c_tlp068in_0_sfx = 178,                     ///< [AI] SFX for TLP068IN, variant 0. [AI]
	c_tlp068in_1_sfx = 179,                     ///< [AI] SFX for TLP068IN, variant 1. [AI]
	c_tlp068in_2_sfx = 180,                     ///< [AI] SFX for TLP068IN, variant 2. [AI]
	c_tlp068in_3_sfx = 181,                     ///< [AI] SFX for TLP068IN, variant 3. [AI]
	c_tlp068in_4_sfx = 182,                     ///< [AI] SFX for TLP068IN, variant 4. [AI]
	c_tlp068in_5_sfx = 183,                     ///< [AI] SFX for TLP068IN, variant 5. [AI]
	c_tlp068in_Anim = 184,                      ///< [AI] Animation for TLP068IN action/resource. [AI]

	c_tlp053in_RunAnim = 500,                   ///< [AI] Run animation for TLP053IN action/resource. [AI]
	c_tlp064la_RunAnim = 501,                   ///< [AI] Run animation for TLP064LA action/resource. [AI]
	c_tlp068in_RunAnim = 502,                   ///< [AI] Run animation for TLP068IN action/resource. [AI]
	c_sns76xra_PlayWav = 503,                   ///< [AI] Play sound for SNS76XRA action. [AI]
	c_sns77xra_PlayWav = 504,                   ///< [AI] Play sound for SNS77XRA action. [AI]
	c_sns02xni_PlayWav = 505,                   ///< [AI] Play sound for SNS02XNI action. [AI]
	c_sns03xni_PlayWav = 506,                   ///< [AI] Play sound for SNS03XNI action. [AI]
	c_sns04xni_PlayWav = 507,                   ///< [AI] Play sound for SNS04XNI action. [AI]
	c_sns05xni_PlayWav = 508,                   ///< [AI] Play sound for SNS05XNI action. [AI]
	c_sns06xni_PlayWav = 509,                   ///< [AI] Play sound for SNS06XNI action. [AI]
	c_sns07xni_PlayWav = 510,                   ///< [AI] Play sound for SNS07XNI action. [AI]
	c_sns08xni_PlayWav = 511,                   ///< [AI] Play sound for SNS08XNI action. [AI]
	c_sns09xni_PlayWav = 512,                   ///< [AI] Play sound for SNS09XNI action. [AI]
	c_sns10xni_PlayWav = 513,                   ///< [AI] Play sound for SNS10XNI action. [AI]
	c_sns11xni_PlayWav = 514,                   ///< [AI] Play sound for SNS11XNI action. [AI]
	c_sns12xla_PlayWav = 515,                   ///< [AI] Play sound for SNS12XLA action. [AI]
	c_sns13xla_PlayWav = 516,                   ///< [AI] Play sound for SNS13XLA action. [AI]
	c_sns14xla_PlayWav = 517,                   ///< [AI] Play sound for SNS14XLA action. [AI]
	c_sns15xla_PlayWav = 518,                   ///< [AI] Play sound for SNS15XLA action. [AI]
	c_sns16xla_PlayWav = 519,                   ///< [AI] Play sound for SNS16XLA action. [AI]
	c_sns17xla_PlayWav = 520,                   ///< [AI] Play sound for SNS17XLA action. [AI]
	c_sns18xni_PlayWav = 521,                   ///< [AI] Play sound for SNS18XNI action. [AI]
	c_sns19xni_PlayWav = 522,                   ///< [AI] Play sound for SNS19XNI action. [AI]
	c_sns20xni_PlayWav = 523,                   ///< [AI] Play sound for SNS20XNI action. [AI]
	c_sns21xni_PlayWav = 524,                   ///< [AI] Play sound for SNS21XNI action. [AI]
	c_sns22xni_PlayWav = 525,                   ///< [AI] Play sound for SNS22XNI action. [AI]
	c_sns23xni_PlayWav = 526,                   ///< [AI] Play sound for SNS23XNI action. [AI]
	c_sns24xni_PlayWav = 527,                   ///< [AI] Play sound for SNS24XNI action. [AI]
	c_sns25xni_PlayWav = 528,                   ///< [AI] Play sound for SNS25XNI action. [AI]
	c_sns26xni_PlayWav = 529,                   ///< [AI] Play sound for SNS26XNI action. [AI]
	c_sns27xni_PlayWav = 530,                   ///< [AI] Play sound for SNS27XNI action. [AI]
	c_sns28xni_PlayWav = 531,                   ///< [AI] Play sound for SNS28XNI action. [AI]
	c_sns29xni_PlayWav = 532,                   ///< [AI] Play sound for SNS29XNI action. [AI]
	c_sns30xni_PlayWav = 533,                   ///< [AI] Play sound for SNS30XNI action. [AI]
	c_sns31xni_PlayWav = 534,                   ///< [AI] Play sound for SNS31XNI action. [AI]
	c_sns32xni_PlayWav = 535,                   ///< [AI] Play sound for SNS32XNI action. [AI]
	c_sns33xni_PlayWav = 536,                   ///< [AI] Play sound for SNS33XNI action. [AI]
	c_sns34xla_PlayWav = 537,                   ///< [AI] Play sound for SNS34XLA action. [AI]
	c_sns35xla_PlayWav = 538,                   ///< [AI] Play sound for SNS35XLA action. [AI]
	c_sns36xla_PlayWav = 539,                   ///< [AI] Play sound for SNS36XLA action. [AI]
	c_sns37xla_PlayWav = 540,                   ///< [AI] Play sound for SNS37XLA action. [AI]
	c_sns38xla_PlayWav = 541,                   ///< [AI] Play sound for SNS38XLA action. [AI]
	c_sns39xla_PlayWav = 542,                   ///< [AI] Play sound for SNS39XLA action. [AI]
	c_sns40xla_PlayWav = 543,                   ///< [AI] Play sound for SNS40XLA action. [AI]
	c_sns41xla_PlayWav = 544,                   ///< [AI] Play sound for SNS41XLA action. [AI]
	c_sns42xla_PlayWav = 545,                   ///< [AI] Play sound for SNS42XLA action. [AI]
	c_sns43xma_PlayWav = 546,                   ///< [AI] Play sound for SNS43XMA action. [AI]
	c_sns44xma_PlayWav = 547,                   ///< [AI] Play sound for SNS44XMA action. [AI]
	c_sns45xma_PlayWav = 548,                   ///< [AI] Play sound for SNS45XMA action. [AI]
	c_sns46xin_PlayWav = 549,                   ///< [AI] Play sound for SNS46XIN action. [AI]
	c_sns47xin_PlayWav = 550,                   ///< [AI] Play sound for SNS47XIN action. [AI]
	c_sns48xin_PlayWav = 551,                   ///< [AI] Play sound for SNS48XIN action. [AI]
	c_sns49xin_PlayWav = 552,                   ///< [AI] Play sound for SNS49XIN action. [AI]
	c_sns50xin_PlayWav = 553,                   ///< [AI] Play sound for SNS50XIN action. [AI]
	c_sns51xin_PlayWav = 554,                   ///< [AI] Play sound for SNS51XIN action. [AI]
	c_sns52xro_PlayWav = 555,                   ///< [AI] Play sound for SNS52XRO action. [AI]
	c_sns53xro_PlayWav = 556,                   ///< [AI] Play sound for SNS53XRO action. [AI]
	c_sns54xro_PlayWav = 557,                   ///< [AI] Play sound for SNS54XRO action. [AI]
	c_sns55xnu_PlayWav = 558,                   ///< [AI] Play sound for SNS55XNU action. [AI]
	c_sns56xnu_PlayWav = 559,                   ///< [AI] Play sound for SNS56XNU action. [AI]
	c_sns57xnu_PlayWav = 560,                   ///< [AI] Play sound for SNS57XNU action. [AI]
	c_sns58xna_PlayWav = 561,                   ///< [AI] Play sound for SNS58XNA action. [AI]
	c_sns59xna_PlayWav = 562,                   ///< [AI] Play sound for SNS59XNA action. [AI]
	c_sns60xna_PlayWav = 563,                   ///< [AI] Play sound for SNS60XNA action. [AI]
	c_sns61xva_PlayWav = 564,                   ///< [AI] Play sound for SNS61XVA action. [AI]
	c_sns62xmg_PlayWav = 565,                   ///< [AI] Play sound for SNS62XMG action. [AI]
	c_sns63xcl_PlayWav = 566,                   ///< [AI] Play sound for SNS63XCL action. [AI]
	c_sns64xen_PlayWav = 567,                   ///< [AI] Play sound for SNS64XEN action. [AI]
	c_sns65xre_PlayWav = 568,                   ///< [AI] Play sound for SNS65XRE action. [AI]
	c_sns66xsl_PlayWav = 569,                   ///< [AI] Play sound for SNS66XSL action. [AI]
	c_sns67xml_PlayWav = 570,                   ///< [AI] Play sound for SNS67XML action. [AI]
	c_sns68xbu_PlayWav = 571,                   ///< [AI] Play sound for SNS68XBU action. [AI]
	c_sns69xsn_PlayWav = 572,                   ///< [AI] Play sound for SNS69XSN action. [AI]
	c_sns70xni_PlayWav = 573,                   ///< [AI] Play sound for SNS70XNI action. [AI]
	c_sns71xni_PlayWav = 574,                   ///< [AI] Play sound for SNS71XNI action. [AI]
	c_sns72xni_PlayWav = 575,                   ///< [AI] Play sound for SNS72XNI action. [AI]
	c_sns73xla_PlayWav = 576,                   ///< [AI] Play sound for SNS73XLA action. [AI]
	c_sns74xla_PlayWav = 577,                   ///< [AI] Play sound for SNS74XLA action. [AI]
	c_sns75xla_PlayWav = 578,                   ///< [AI] Play sound for SNS75XLA action. [AI]
	c_sns76xja_PlayWav = 579,                   ///< [AI] Play sound for SNS76XJA action. [AI]
	c_sns76xjs_PlayWav = 580,                   ///< [AI] Play sound for SNS76XJS action. [AI]
	c_sns77xja_PlayWav = 581,                   ///< [AI] Play sound for SNS77XJA action. [AI]
	c_sns77xjs_PlayWav = 582,                   ///< [AI] Play sound for SNS77XJS action. [AI]
	c_tns069ni_PlayWav = 583,                   ///< [AI] Play sound for TNS069NI event/action. [AI]
	c_tns070br_PlayWav = 584,                   ///< [AI] Play sound for TNS070BR event/action. [AI]
	c_tns071ni_PlayWav = 585,                   ///< [AI] Play sound for TNS071NI event/action. [AI]
	c_tns072br_PlayWav = 586,                   ///< [AI] Play sound for TNS072BR event/action. [AI]
	c_tns073ni_PlayWav = 587,                   ///< [AI] Play sound for TNS073NI event/action. [AI]
	c_tns074ni_PlayWav = 588,                   ///< [AI] Play sound for TNS074NI event/action. [AI]
	c_tns075br_PlayWav = 589,                   ///< [AI] Play sound for TNS075BR event/action. [AI]
	c_tns076la_PlayWav = 590,                   ///< [AI] Play sound for TNS076LA event/action. [AI]
	c_tns077br_PlayWav = 591,                   ///< [AI] Play sound for TNS077BR event/action. [AI]

	c_tns079la_PlayWav = 593,                   ///< [AI] Play sound for TNS079LA event/action. [AI]
	c_tns081ni_PlayWav = 594,                   ///< [AI] Play sound for TNS081NI event/action. [AI]
	c_tns082br_PlayWav = 595,                   ///< [AI] Play sound for TNS082BR event/action. [AI]
	c_tns080br_PlayWav = 596,                   ///< [AI] Play sound for TNS080BR event/action. [AI]
	c_tnsx07br_PlayWav = 597,                   ///< [AI] Play sound for TNSX07BR or related event. [AI]
	c_tnsx02br_PlayWav = 598,                   ///< [AI] Play sound for TNSX02BR or related event. [AI]
	c_snsxx2br_PlayWav = 599,                   ///< [AI] Play sound for SNSXX2BR or related event. [AI]
	c_snsy23br_PlayWav = 600                    ///< [AI] Play sound for SNSY23BR or related event. [AI]
};
} // namespace Act3Script

#endif // ACT3_ACTIONS_H