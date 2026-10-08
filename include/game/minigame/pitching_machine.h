#ifndef __GAME_MINIGAME_PITCHING_MACHINE_H_
#define __GAME_MINIGAME_PITCHING_MACHINE_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

/* One entry of the model table at hugeAnimStruct+0x2D94 (the other files call
 * it BallModel/bombModels); update is the per-frame callback and is passed the
 * entry's index. */
typedef struct {
    /*0x00*/ void (*update)(int);
    /*0x04*/ VecXYZ pos;
    /*0x10*/ VecXYZ rot;
    /*0x1C*/ u8 _1C[0x26 - 0x1C];
    /*0x26*/ E(u8, BOOL) visible;
    /*0x27*/ u8 _27;
} PMEffect; // size: 0x28

void mm_HidePlayerMarkers(void);
void mm_ClearFirst40Effects(void);
void mm_PlaceExtraPipes(void);
void mm_ResetPiranhas(void);
void mm_HideWallBallEffects(void);
void mm_ResetPitchingMachine(void);
void mm_ResetModels(void);
void mm_SetPowerupFrame(int idx);
void mm_UpdateStarDashPowerup(void);
void mm_DrawThwompShadow(int idx);
void mm_UpdateThwomps(void);
void mm_UpdateFireBarHub(void);
void mm_DrawStarGlow(int idx);
void mm_UpdateStar(void);
void mm_UpdateCoinBag(void);
void mm_UpdateStarDashCoins(void);
void mm_GetPiranhaSpitPos(int slot, VecXYZ* out);
void mm_PlacePlayerMarkers(void);
void mm_RemoveFlameSprites(void);
void mm_AddFlameSprites(void);
void mm_UpdateObjectShadows(void);
void mm_SetPipeFrame(int idx);
void mm_PlacePiranhaPipes(void);
void mm_SetPiranhaColour(int idx);
void mm_SetPiranhaAnim(int slot, int kind, int frame, int divisor, u8 flag);
void mm_UpdatePiranhaAnim(int slot);
void mm_UpdatePiranhas(void);
void mm_AttachPulseTexture(int idx);
void mm_SetPiranhaBallColour(int idx);
void mm_UpdatePiranhaBalls(void);
f32 mm_GetItemScale(u8 kind);
void mm_UpdateChainChompPowerup(void);
void mm_UpdateChainChompItems(void);
void mm_StartBarrelMachineAnim(void);
void mm_StartBarrelAnim(int idx);
f32 mm_GetPitchingMachineScale(void);
void mm_UpdateBarrelBatterMachine(void);
void mm_FlashBombBarrel(int idx);
void mm_SetBarrelColour(int idx);
void mm_UpdateBarrels(void);
void mm_EmptyHook(void);
void mm_UpdateWallBallCoins(void);
u32 mm_ScanModelBones(int idx);
void mm_StartWallAnim(int idx, int kind);
void mm_UpdateWallBallBlocks(void);
void mm_PlacePitchingMachine(PMEffect* fx, int idx);
void mm_UpdatePitchingMachine(void);
void mm_UpdateModels(void);
void mm_LoadPiranhaPanicModels(void);
void mm_LoadStarDashModels(void);
void mm_LoadChainChompModels(void);
void mm_LoadBarrelBatterModels(void);
void mm_LoadWallBallModels(void);
void mm_LoadBobombDerbyModels(void);
void mm_CleanupResources(void);
void mm_UnloadModels(void);
void mm_LoadModels(void);
void mm_LoadModelAsset(int asset, int start, int count, int a, int b);
void mm_ParseCommonArchive(void);
int mm_LoadCommonArchiveStep(void);
void mm_DrawResultCode(void);
void mm_EncodeResultCode(u8* out, u8* raw, u8 a, u8 b);
u16 mm_Crc16(u8* data, u32 len);
void fn_3_11DE80(void);
void fn_3_11DECC(void);
void fn_3_11E308(void);
void fn_3_11E364(void);
void fn_3_11E7C4(void);

#endif // !__GAME_MINIGAME_PITCHING_MACHINE_H_
