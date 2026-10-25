/*















*/
#include "musyx/musyx_priv.h"

#ifdef _DEBUG
static u32 dbgActiveVoicesMax = 0;
#endif

extern u8 salAuxFrame;
extern u8 salFrame;

DSPstudioinfo dspStudio[8];

static u32 dspARAMZeroBuffer = 0;

u16* dspCmdLastLoad = NULL;

u16* dspCmdLastBase = NULL;

u16* dspCmdList = NULL;

u16 dspCmdLastSize = 0;

u16* dspCmdCurBase = NULL;

u16* dspCmdMaxPtr = NULL;

u16* dspCmdPtr = NULL;

u16 dspCmdFirstSize = 0;

u32 dspHRTFOn = FALSE;

s16* dspHrtfHistoryBuffer = NULL;

long* dspSurround = NULL;

s16* dspITDBuffer = NULL;

DSPvoice* dspVoice = NULL;

SND_MESSAGE_CALLBACK salMessageCallback = NULL;

u32 salInitDspCtrl(u8 numVoices, u8 numStudios, u32 defaultStudioDPL2) {
  u32 i;      // r31
  u32 j;      // r27
  u32 itdPtr; // r28

  salNumVoices = numVoices;
  salMaxStudioNum = numStudios;

  MUSY_ASSERT(salMaxStudioNum <= SAL_MAX_STUDIONUM);
  dspARAMZeroBuffer = aramGetZeroBuffer();
  if ((dspCmdList = salMalloc(1024 * sizeof(u16))) != NULL) {
    MUSY_DEBUG("Allocated dspCmdList.\n\n");
    if ((dspSurround = salMalloc(160 * sizeof(long))) != NULL) {
      MUSY_DEBUG("Allocated surround buffer.\n\n");
      memset(dspSurround, 0, 160 * sizeof(long));
      DCFlushRange(dspSurround, 160 * sizeof(long));
      if ((dspVoice = salMalloc(salNumVoices * sizeof(DSPvoice))) != NULL) {
        MUSY_DEBUG("Allocated HW voice array.\n\n");
        if ((dspITDBuffer = salMalloc(salNumVoices * 64)) != NULL) {
          MUSY_DEBUG("Allocated ITD buffers for voice array.\n\n");
          DCInvalidateRange(dspITDBuffer, salNumVoices * 64);
          itdPtr = (u32)dspITDBuffer;
          for (i = 0; i < salNumVoices; ++i) {
            MUSY_DEBUG("Initializing voice %d...\n", i);
            dspVoice[i].state = 0;
            dspVoice[i].postBreak = 0;
            dspVoice[i].startupBreak = 0;
            dspVoice[i].lastUpdate.pitch = 0xff;
            dspVoice[i].lastUpdate.vol = 0xff;
            dspVoice[i].lastUpdate.volA = 0xff;
            dspVoice[i].lastUpdate.volB = 0xff;
            dspVoice[i].pb = salMalloc(sizeof(_PB));
            memset(dspVoice[i].pb, 0, sizeof(_PB));
            dspVoice[i].patchData = salMalloc(0x80);
            dspVoice[i].pb->currHi = ((u32)dspVoice[i].pb >> 16);
            dspVoice[i].pb->currLo = (u16)dspVoice[i].pb;
            dspVoice[i].pb->update.dataHi = ((u32)dspVoice[i].patchData >> 16);
            dspVoice[i].pb->update.dataLo = ((u16)dspVoice[i].patchData);
            dspVoice[i].pb->itd.bufferHi = ((u32)itdPtr >> 16);
            dspVoice[i].pb->itd.bufferLo = ((u16)itdPtr);
            dspVoice[i].itdBuffer = (void*)itdPtr;
            itdPtr += 0x40;
            dspVoice[i].virtualSampleID = 0xFFFFFFFF;
            DCStoreRangeNoSync(dspVoice[i].pb, sizeof(_PB));

            for (j = 0; j < 5; ++j) {
              dspVoice[i].changed[j] = 0;
            }
          }

          MUSY_DEBUG("All voices initialized.\n\n");

          for (i = 0; i < salMaxStudioNum; ++i) {
            MUSY_DEBUG("Initializing studio %d...\n", i);
            dspStudio[i].state = 0;
            if ((dspStudio[i].spb = (_SPB*)salMalloc(sizeof(_SPB))) == NULL) {
              return FALSE;
            }

            if ((dspStudio[i].main[0] = (void*)salMalloc(0x3c00)) == NULL) {
              return FALSE;
            }

            memset(dspStudio[i].main[0], 0, 0x3c00);
            DCFlushRangeNoSync(dspStudio[i].main[0], 0x3c00);
            dspStudio[i].main[1] = dspStudio[i].main[0] + 0x1e0;
            dspStudio[i].auxA[0] = dspStudio[i].main[1] + 0x1e0;
            dspStudio[i].auxA[1] = dspStudio[i].auxA[0] + 0x1e0;
            dspStudio[i].auxA[2] = dspStudio[i].auxA[1] + 0x1e0;
            dspStudio[i].auxB[0] = dspStudio[i].auxA[2] + 0x1e0;
            dspStudio[i].auxB[1] = dspStudio[i].auxB[0] + 0x1e0;
            dspStudio[i].auxB[2] = dspStudio[i].auxB[1] + 0x1e0;
            memset(dspStudio[i].spb, 0, sizeof(_SPB));
            dspStudio[i].hostDPopSum.l = dspStudio[i].hostDPopSum.r = dspStudio[i].hostDPopSum.s =
                0;
            dspStudio[i].hostDPopSum.lA = dspStudio[i].hostDPopSum.rA =
                dspStudio[i].hostDPopSum.sA = 0;
            dspStudio[i].hostDPopSum.lB = dspStudio[i].hostDPopSum.rB =
                dspStudio[i].hostDPopSum.sB = 0;
            DCFlushRangeNoSync(dspStudio[i].spb, sizeof(_SPB));
          }
          MUSY_DEBUG("All studios are initialized.\n\n");
          salActivateStudio(
              0, 1, defaultStudioDPL2 != FALSE ? SND_STUDIO_TYPE_RESERVED0 : SND_STUDIO_TYPE_STD);
          MUSY_DEBUG("Default studio is active.\n\n");
          if ((dspHrtfHistoryBuffer = salMalloc(0x100)) == NULL) {
            return FALSE;
          }

          salInitHRTFBuffer();
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

void salInitHRTFBuffer() {
  memset(dspHrtfHistoryBuffer, 0, 0x100);
  DCFlushRangeNoSync(dspHrtfHistoryBuffer, 0x100);
}

u32 salExitDspCtrl() {
  u8 i; // r31
  salFree(dspHrtfHistoryBuffer);

  for (i = 0; i < salNumVoices; ++i) {
    salFree(dspVoice[i].pb);
    salFree(dspVoice[i].patchData);
  }

  for (i = 0; i < salMaxStudioNum; ++i) {
    salFree(dspStudio[i].spb);
    salFree(dspStudio[i].main[0]);
  }

  salFree(dspITDBuffer);
  salFree(dspVoice);
  salFree(dspSurround);
  salFree(dspCmdList);
  return TRUE;
}

void salActivateStudio(u8 studio, u32 isMaster, SND_STUDIO_TYPE type) {
  memset(dspStudio[studio].main[0], 0, 0x3c00);
  DCFlushRangeNoSync(dspStudio[studio].main[0], 0x3c00);
  memset(dspStudio[studio].spb, 0, sizeof(_SPB));
  dspStudio[studio].hostDPopSum.l = dspStudio[studio].hostDPopSum.r =
      dspStudio[studio].hostDPopSum.s = 0;
  dspStudio[studio].hostDPopSum.lA = dspStudio[studio].hostDPopSum.rA =
      dspStudio[studio].hostDPopSum.sA = 0;
  dspStudio[studio].hostDPopSum.lB = dspStudio[studio].hostDPopSum.rB =
      dspStudio[studio].hostDPopSum.sB = 0;

  DCFlushRangeNoSync(dspStudio[studio].spb, sizeof(_SPB));
  memset(dspStudio[studio].auxA[0], 0, 0x780);
  DCFlushRangeNoSync(dspStudio[studio].auxA[0], 0x780);
  memset(dspStudio[studio].auxB[0], 0, 0x780);
  DCFlushRangeNoSync(dspStudio[studio].auxB[0], 0x780);
  dspStudio[studio].voiceRoot = NULL;
  dspStudio[studio].alienVoiceRoot = NULL;
  dspStudio[studio].state = 1;
  dspStudio[studio].isMaster = isMaster;
  dspStudio[studio].numInputs = 0;
  dspStudio[studio].type = type;
  dspStudio[studio].auxAHandler = dspStudio[studio].auxBHandler = NULL;
}

u16 dspSRCCycles[3][3] = {
    {2990, 2990, 1115},
    {3300, 3300, 1115},
    {3700, 3700, 1115},
};

static const u16 dspMixerCycles[32] = {
    1470, 2940, 2940, 4410, 2230, 4460, 4460, 6690, 2470, 4940, 4940, 7410, 3735, 7470, 7470, 11205,
    2940, 3386, 2940, 3386, 2940, 3386, 2940, 3386, 4940, 5687, 4940, 5687, 4940, 5687, 4940, 5687,
};

void salDeactivateStudio(u8 studio) { dspStudio[studio].state = 0; }

static u32 salCheckVolErrorAndResetDelta(u16* dsp_vol, u16* dsp_delta, u16* last_vol, u16 targetVol,
                                  u16* resetFlags, u16 resetMask) {
  s16 d; // r31
  s16 x; // r30

  if (targetVol != *last_vol) {
    d = (s16)targetVol - (s16)*last_vol;
    if ((s16)d >= 32 && (s16)d < 160) {
      x = (s16)d >> 5;
      if ((s16)x < 5) {
        resetFlags[x] |= resetMask;
      }

      *dsp_delta = 1;
      *last_vol += (x << 5);
      return 1;
    }

    if (-32 >= (s16)d && -160 < (s16)d) {
      x = -(s16)d >> 5;
      if (x < 5) {
        resetFlags[x] |= resetMask;
      }
      *dsp_delta = 0xFFFF;
      *last_vol -= x << 5;
      return 1;
    }

    if (targetVol == 0 && (s16)d > -32) {
      *dsp_vol = *last_vol = 0;
    }
  }

  *dsp_delta = 0;
  return 0;
}

static void sal_setup_dspvol(u16* dsp_delta, u16* last_vol, u16 vol) {
  *dsp_delta = ((s16)vol - (s16)*last_vol) / 160;
  *last_vol += (s16)*dsp_delta * 160;
}

static void sal_update_hostplayinfo(DSPvoice* dsp_vptr) {
  u32 old_lo; // r30
  u32 pitch;  // r31

  if (dsp_vptr->smp_info.loopLength != 0) {
    return;
  }
  if (dsp_vptr->pb->srcSelect != 2) {
    pitch = dsp_vptr->playInfo.pitch << 5;

  } else {
    pitch = 0x200000;
  }

  old_lo = dsp_vptr->playInfo.posLo;
  dsp_vptr->playInfo.posLo += pitch * 0x10000;

  if (old_lo > dsp_vptr->playInfo.posLo) {
    dsp_vptr->playInfo.posHi += (pitch >> 16) + 1;
  } else {
    dsp_vptr->playInfo.posHi += (pitch >> 16);
  }
}

static void AddDpop(long* sum, s16 delta) {
  *sum += (int)delta;
  *sum = (*sum > 0x7fffff) ? 0x7fffff : (*sum < -0x7fffff ? -0x7fffff : *sum);
}

static void DoDepopFade(long* dspStart, s16* dspDelta, long* hostSum) {
  if (*hostSum <= -160) {
    *dspDelta = (*hostSum <= -3200) ? 0x14 : (s16)(-*hostSum / 160);
  } else if (*hostSum >= 160) {
    *dspDelta = (*hostSum >= 3200) ? -0x14 : (s16)(-*hostSum / 160);
  } else {
    *dspDelta = 0;
  }

  *dspStart = *hostSum;
  *hostSum += *dspDelta * 160;
}

static void HandleDepopVoice(DSPstudioinfo* stp, DSPvoice* dsp_vptr) {
  _PB* pb; // r31
  dsp_vptr->postBreak = 0;
  dsp_vptr->pb->state = 0;
  pb = dsp_vptr->pb;
  if ((pb->mixerCtrl & 0x01) != 0) {
    AddDpop(&stp->hostDPopSum.l, pb->dpop.aL);
  }
  if ((pb->mixerCtrl & 0x02) != 0) {
    AddDpop(&stp->hostDPopSum.r, pb->dpop.aR);
  }
  if ((pb->mixerCtrl & 0x04) != 0) {
    AddDpop(&stp->hostDPopSum.s, pb->dpop.aS);
  }
  if ((pb->mixerCtrl & 0x10) != 0) {
    AddDpop(&stp->hostDPopSum.lA, pb->dpop.aAuxAL);
  }
  if ((pb->mixerCtrl & 0x20) != 0) {
    AddDpop(&stp->hostDPopSum.rA, pb->dpop.aAuxAR);
  }
  if ((pb->mixerCtrl & 0x80) != 0) {
    AddDpop(&stp->hostDPopSum.sA, pb->dpop.aAuxAS);
  }
  if ((pb->mixerCtrl & 0x200) != 0) {
    AddDpop(&stp->hostDPopSum.lB, pb->dpop.aAuxBL);
  }
  if ((pb->mixerCtrl & 0x400) != 0) {
    AddDpop(&stp->hostDPopSum.rB, pb->dpop.aAuxBR);
  }
  if ((pb->mixerCtrl & 0x1000) != 0) {
    AddDpop(&stp->hostDPopSum.sB, pb->dpop.aAuxBS);
  }
}

static void SortVoices(DSPvoice** voices, long l, long r) {
  long i;        // r28
  long last;     // r29
  DSPvoice* tmp; // r27

  if (l >= r) {
    return;
  }

  tmp = voices[l];
  voices[l] = voices[(l + r) / 2];
  voices[(l + r) / 2] = tmp;
  last = l;
  i = l + 1;

  for (; i <= r; ++i) {
    if (voices[i]->prio < voices[l]->prio) {
      last += 1;
      tmp = voices[last];
      voices[last] = voices[i];
      voices[i] = tmp;
    }
  }

  tmp = voices[l];
  voices[l] = voices[last];
  voices[last] = tmp;
  SortVoices(voices, l, last - 1);
  SortVoices(voices, last + 1, r);
}

u32 salSynthSendMessage(DSPvoice* dsp_vptr, u32 mesg);
u32 adsrSetup(ADSR_VARS* adsr);
u32 adsrHandle(ADSR_VARS* adsr, u16* adsr_start, u16* adsr_delta);
void adsrStartRelease(ADSR_VARS* adsr, u32 time);
extern u32 lbl_803CC35C;

#define VOICE_U8(v, off) (*(u8*)((u8*)(v) + (off)))
#define VOICE_U32(v, off) (*(u32*)((u8*)(v) + (off)))

static void sal_cmdSwitchBlock(void) {
  u32 size;

  dspCmdPtr[0] = 0x0D;
  dspCmdPtr[1] = (u16)((u32)dspCmdMaxPtr >> 16);
  dspCmdPtr[2] = (u16)(u32)dspCmdMaxPtr;
  size = (((u32)dspCmdPtr + 8) - (u32)dspCmdCurBase + 3) & 0xFFF8;
  if (dspCmdLastLoad != NULL) {
    dspCmdLastLoad[3] = size;
    DCStoreRangeNoSync(dspCmdLastBase, dspCmdLastSize);
  } else {
    dspCmdFirstSize = size;
  }

  dspCmdLastLoad = dspCmdPtr;
  dspCmdLastBase = dspCmdCurBase;
  dspCmdLastSize = size;
  dspCmdPtr = dspCmdMaxPtr;
  dspCmdCurBase = dspCmdMaxPtr;
  dspCmdMaxPtr = (u16*)((u8*)dspCmdMaxPtr + 0x180);
}

static void sal_cmdReserve(u32 bytes) {
  if ((u32)dspCmdPtr + bytes > (u32)dspCmdMaxPtr - 8) {
    sal_cmdSwitchBlock();
  }
}

static void sal_cmdPut16(u32 v) {
  *dspCmdPtr = (u16)v;
  dspCmdPtr += 1;
}

static void sal_cmdPutAddr(u32 addr) {
  sal_cmdPut16(addr >> 16);
  sal_cmdPut16(addr & 0xFFFF);
}

static void sal_cmdEndMarker(void) {
  sal_cmdReserve(2);
  sal_cmdPut16(3);
}

static void sal_cmdFinishBlock(void) {
  u32 size;

  size = ((u32)dspCmdPtr - (u32)dspCmdCurBase + 3) & 0xFFF8;
  if (dspCmdLastLoad != NULL) {
    dspCmdLastLoad[3] = size;
    DCStoreRangeNoSync(dspCmdLastBase, dspCmdLastSize);
  } else {
    dspCmdFirstSize = size;
  }
  DCStoreRangeNoSync(dspCmdCurBase, (u32)dspCmdPtr - (u32)dspCmdCurBase);
}

static void sal_cmdSetupVolume(_PB* pb, DSPvoice* dsp_vptr) {
  if (dsp_vptr->changed[0] & 0x1) {
    sal_setup_dspvol(&pb->mix.vDeltaL, &dsp_vptr->lastVolL, dsp_vptr->volL);
    sal_setup_dspvol(&pb->mix.vDeltaR, &dsp_vptr->lastVolR, dsp_vptr->volR);
    sal_setup_dspvol(&pb->mix.vDeltaS, &dsp_vptr->lastVolS, dsp_vptr->volS);
    if (pb->mix.vDeltaL != 0 || pb->mix.vDeltaR != 0) {
      pb->mixerCtrl |= 0x3;
    } else {
      pb->mixerCtrl &= ~0x3;
    }
  }
}

static void sal_cmdDepopStudio(DSPstudioinfo* sp) {
  _SPB* spb = sp->spb;

  DoDepopFade((long*)((u8*)spb + 0x00), (s16*)((u8*)spb + 0x04), &sp->hostDPopSum.l);
  DoDepopFade((long*)((u8*)spb + 0x06), (s16*)((u8*)spb + 0x0A), &sp->hostDPopSum.r);
  DoDepopFade((long*)((u8*)spb + 0x0C), (s16*)((u8*)spb + 0x10), &sp->hostDPopSum.s);
  DoDepopFade((long*)((u8*)spb + 0x12), (s16*)((u8*)spb + 0x16), &sp->hostDPopSum.lA);
  DoDepopFade((long*)((u8*)spb + 0x18), (s16*)((u8*)spb + 0x1C), &sp->hostDPopSum.rA);
  DoDepopFade((long*)((u8*)spb + 0x1E), (s16*)((u8*)spb + 0x22), &sp->hostDPopSum.sA);
  DoDepopFade((long*)((u8*)spb + 0x24), (s16*)((u8*)spb + 0x28), &sp->hostDPopSum.lB);
  DoDepopFade((long*)((u8*)spb + 0x2A), (s16*)((u8*)spb + 0x2E), &sp->hostDPopSum.rB);
  DoDepopFade((long*)((u8*)spb + 0x30), (s16*)((u8*)spb + 0x34), &sp->hostDPopSum.sB);
  DCFlushRangeNoSync(spb, 0x36);
}

static u32 sal_cmdSampleFormat(DSPvoice* voice, _PB* pb) {
  u8* si;
  u8 fmt;
  u32 len;
  u32 start;
  u32 addr;
  u32 i;

  fmt = VOICE_U8(voice, 0x90);
  si = *(u8**)((u8*)voice + 0x7C);
  len = VOICE_U32(voice, 0x78);
  start = VOICE_U32(voice, 0x80);

  if (fmt == 0 || fmt == 4 || fmt == 5) {
    addr = len * 2;
    addr += 2;
    pb->addr.format = 0;
    pb->adpcm.gain = 0;
    pb->adpcm.yn1 = 0;
    pb->adpcm.yn2 = 0;
    pb->adpcm.pred_scale = si[2];
    for (i = 0; i < 16; ++i) {
      ((s16*)pb->adpcm.a)[i] = *(s16*)(si + 8 + i * 2);
    }
    if (fmt == 4 || fmt == 5) {
      pb->loopType = 1;
    } else {
      pb->adpcmLoop.loop_yn2 = *(s16*)(si + 4);
      pb->adpcmLoop.loop_yn1 = *(s16*)(si + 6);
      pb->adpcmLoop.loop_pred_scale = si[3];
      pb->loopType = 0;
    }
    VOICE_U32(voice, 0xDC) = 0;
  } else if (fmt == 1) {
    addr = len * 2;
    addr += 2;
    pb->addr.format = 0;
    pb->adpcm.gain = 0;
    pb->adpcm.yn2 = *(s16*)(si + 0x28);
    pb->adpcm.yn1 = *(s16*)(si + 0x2A);
    pb->adpcm.pred_scale = si[0x2C];
    for (i = 0; i < 16; ++i) {
      ((s16*)pb->adpcm.a)[i] = *(s16*)(si + 8 + i * 2);
    }
    pb->adpcmLoop.loop_yn2 = *(s16*)(si + 4);
    pb->adpcmLoop.loop_yn1 = *(s16*)(si + 6);
    pb->adpcmLoop.loop_pred_scale = si[3];
    pb->loopType = 0;
    VOICE_U32(voice, 0xDC) = 0;
  } else if (fmt == 3) {
    addr = start + len;
    pb->addr.format = 0x19;
    pb->adpcm.gain = 0x100;
    for (i = 0; i < 16; ++i) {
      ((s16*)pb->adpcm.a)[i] = 0;
    }
    pb->loopType = 0;
    VOICE_U32(voice, 0xDC) = start;
  } else if (fmt == 2 || fmt == 6) {
    addr = start + (len >> 1);
    pb->addr.format = 0x0A;
    pb->adpcm.gain = 0x800;
    for (i = 0; i < 16; ++i) {
      ((s16*)pb->adpcm.a)[i] = 0;
    }
    pb->loopType = (fmt == 6) ? 1 : 0;
    VOICE_U32(voice, 0xDC) = start;
  } else {
    return 0;
  }

  VOICE_U32(voice, 0xE0) = 0;
  return addr;
}

void salBuildCommandList(signed short* dest, unsigned long nsDelay) {
  static DSPvoice * voices[64];
  u32 cycles;
  u32 busClock;
  u32 count;
  u32 k;
  u32 slot;
  u32 addr;
  u8 st;
  u8 i;
  DSPstudioinfo* sp;
  DSPstudioinfo* src;
  DSPvoice* voice;
  DSPvoice* next;
  _PB* pb;
  u16* upd;
  u32 adsrDone;

  dspCmdLastLoad = NULL;
  dspCmdPtr = dspCmdList;
  dspCmdCurBase = dspCmdList;
  dspCmdMaxPtr = (u16*)((u8*)dspCmdList + 0x180);

  busClock = *(u32*)0x800000F8;
  if (nsDelay < 200) {
    cycles = 0x28BE;
  } else {
    cycles = (nsDelay - 200) * (busClock / 400 / 5000) + 0x28BE;
  }
  if (dspHRTFOn != FALSE) {
    cycles += 0x10000 - 0x5038;
  }
  if (lbl_803CC35C != 0) {
    cycles += 0xBB8;
  }

  for (st = 0; st < salMaxStudioNum; ++st) {
    sp = &dspStudio[st];
    if (sp->state != 1) {
      continue;
    }

    voice = sp->voiceRoot;
    while (voice != NULL) {
      next = voice->next;
      if (voice->postBreak != 0 || (voice->changed[0] & 0x20) != 0) {
        HandleDepopVoice(sp, voice);
        if (voice->virtualSampleID != 0xFFFFFFFF) {
          salSynthSendMessage(voice, 3);
        }
        if (voice->state != 1 || voice->startupBreak != 0) {
          salDeactivateVoice(voice);
          voice->startupBreak = 0;
        }
      }
      voice = next;
    }

    voice = sp->alienVoiceRoot;
    while (voice != NULL) {
      HandleDepopVoice(sp, voice);
      voice = voice->nextAlien;
    }
    sp->alienVoiceRoot = NULL;

    sal_cmdReserve(6);
    sal_cmdPut16(0);
    sal_cmdPutAddr((u32)sp->spb);

    for (i = 0; i < sp->numInputs; ++i) {
      src = &dspStudio[sp->in[i].studio];
      sal_cmdReserve(12);
      sal_cmdPut16(1);
      sal_cmdPutAddr((u32)src->main[(salFrame ^ 1) & 1]);
      sal_cmdPut16(sp->in[i].vol);
      sal_cmdPut16(sp->in[i].volA);
      sal_cmdPut16(sp->in[i].volB);
    }

    count = 0;
    voice = sp->voiceRoot;
    while (voice != NULL) {
      voices[count++] = voice;
      voice = voice->next;
    }
    SortVoices(voices, 0, count - 1);

    for (k = count; k > 0; --k) {
      voice = voices[k - 1];
      if (voice->state == 0) {
        continue;
      }

      pb = voice->pb;
      if (voice->state == 1) {
        voice->virtualSampleID = 0xFFFFFFFF;
        pb->ve.currentDelta = 0x8000;
        if (adsrSetup(&voice->adsr) != 0) {
          salSynthSendMessage(voice, 0);
          salDeactivateVoice(voice);
          continue;
        }
        if (VOICE_U8(voice, 0x90) >= 5 && VOICE_U8(voice, 0x90) < 7) {
          VOICE_U32(voice, 0x98) = 0;
          voice->virtualSampleID = salSynthSendMessage(voice, 2);
          if (VOICE_U32(voice, 0x98) == 0) {
            salSynthSendMessage(voice, 1);
            salDeactivateVoice(voice);
            continue;
          }
        }
      }

      pb->src.currentAddressFrac = 0;
      pb->src.last_samples[0] = 0;
      pb->src.last_samples[1] = 0;
      pb->src.last_samples[2] = 0;
      pb->src.last_samples[3] = 0;

      if ((voice->flags & 1) != 0) {
        memset(voice->itdBuffer, 0, 0x40);
        DCFlushRange(voice->itdBuffer, 0x40);
        pb->itd.targetShiftL = voice->itdShiftL;
        pb->itd.targetShiftR = voice->itdShiftR;
        pb->itd.flag = 1;
      } else {
        pb->itd.flag = 0;
      }

      addr = sal_cmdSampleFormat(voice, pb);
      pb->addr.currentAddressHi = (u16)(addr >> 16);
      pb->addr.currentAddressLo = (u16)addr;
      voice->currentAddr = addr;

      sal_cmdSetupVolume(pb, voice);

      upd = (u16*)voice->patchData;
      adsrDone = 0;
      for (slot = 0; slot < 5; ++slot) {
        if ((voice->changed[slot] & 0x40) != 0) {
          adsrRelease(&voice->adsr);
        }
        if ((voice->changed[slot] & 0x8) != 0) {
          pb->src.ratioHi = (u16)(voice->pitch[slot] >> 16);
          pb->src.ratioLo = (u16)voice->pitch[slot];
          VOICE_U32(voice, 0xE4) = voice->pitch[slot];
        }
        adsrDone = adsrHandle(&voice->adsr, &pb->ve.currentVolume, &pb->ve.currentDelta);
        for (i = 0; i < 5; ++i) {
          pb->update.updNum[i] = 0;
        }
        if (slot != 0) {
          upd[0] = 7;
          upd[1] = 1;
          upd += 2;
          pb->update.updNum[slot] += 1;
        }
        sal_update_hostplayinfo(voice);
      }

      if (adsrDone != 0) {
        salSynthSendMessage(voice, 0);
        salDeactivateVoice(voice);
      }

      DCStoreRangeNoSync(voice->patchData, (u32)upd - (u32)voice->patchData);
    }
  }

  for (st = 0; st < salMaxStudioNum; ++st) {
    sp = &dspStudio[st];
    if (sp->state != 1) {
      continue;
    }
    if (sp->auxAHandler != NULL) {
      sal_cmdReserve(6);
      sal_cmdPut16(4);
      sal_cmdPutAddr((u32)sp->auxA[salAuxFrame % 3]);
    }
    if (sp->type == 0 && sp->auxBHandler != NULL) {
      sal_cmdReserve(6);
      sal_cmdPut16(5);
      sal_cmdPutAddr((u32)sp->auxB[salAuxFrame % 3]);
    }
    sal_cmdReserve(6);
    sal_cmdPut16(6);
    sal_cmdPutAddr((u32)sp->main[salAuxFrame & 1]);
    sal_cmdDepopStudio(sp);
  }

  sal_cmdReserve(10);
  sal_cmdPut16(0x11);
  sal_cmdPutAddr((u32)dspSurround);
  sal_cmdPut16(0);

  for (st = 0; st < salMaxStudioNum; ++st) {
    sp = &dspStudio[st];
    if (sp->state == 1 && sp->isMaster != 0) {
      sal_cmdReserve(6);
      sal_cmdPut16(9);
      sal_cmdPutAddr((u32)sp->main[salFrame & 1]);
    }
  }

  if (lbl_803CC35C != 0) {
    sal_cmdReserve(10);
    sal_cmdPut16(0x12);
    sal_cmdPut16(0x8000);
    sal_cmdPut16(0x000A);
    sal_cmdPutAddr(0x801133E0);
  }

  sal_cmdReserve(10);
  sal_cmdPut16(0x0F);
  sal_cmdPutAddr((u32)dspSurround);
  sal_cmdPutAddr((u32)dest);

  sal_cmdEndMarker();
  sal_cmdFinishBlock();
}

u32 salSynthSendMessage(DSPvoice* dsp_vptr, u32 mesg) {
  return salMessageCallback == NULL ? FALSE
                                    : salMessageCallback(mesg, dsp_vptr->mesgCallBackUserValue);
}

void salActivateVoice(DSPvoice* dsp_vptr, u8 studio) {
  if (dsp_vptr->state != 0) {
    salDeactivateVoice(dsp_vptr);
    dsp_vptr->changed[0] |= 0x20;
  }

  dsp_vptr->postBreak = 0;
  if ((dsp_vptr->next = dspStudio[studio].voiceRoot) != NULL) {
    dsp_vptr->next->prev = dsp_vptr;
  }

  dsp_vptr->prev = NULL;
  dspStudio[studio].voiceRoot = dsp_vptr;
  dsp_vptr->startupBreak = 0;
  dsp_vptr->state = 1;
  dsp_vptr->studio = studio;
}

void salDeactivateVoice(DSPvoice* dsp_vptr) {
  if (dsp_vptr->state == 0) {
    return;
  }

  if (dsp_vptr->prev != NULL) {
    dsp_vptr->prev->next = dsp_vptr->next;
  } else {
    dspStudio[dsp_vptr->studio].voiceRoot = dsp_vptr->next;
  }

  if (dsp_vptr->next != NULL) {
    dsp_vptr->next->prev = dsp_vptr->prev;
  }

  dsp_vptr->state = 0;
}

void salReconnectVoice(DSPvoice* dsp_vptr, u8 studio) {
  if (dsp_vptr->state != 0) {
    if (dsp_vptr->prev != NULL) {
      dsp_vptr->prev->next = dsp_vptr->next;
    } else {
      dspStudio[dsp_vptr->studio].voiceRoot = dsp_vptr->next;
    }

    if (dsp_vptr->next != NULL) {
      dsp_vptr->next->prev = dsp_vptr->prev;
    }

    if ((dsp_vptr->next = dspStudio[studio].voiceRoot) != NULL) {
      dsp_vptr->next->prev = dsp_vptr;
    }

    dsp_vptr->prev = NULL;
    dspStudio[studio].voiceRoot = dsp_vptr;
    if (dsp_vptr->state == 2) {
      dsp_vptr->nextAlien = dspStudio[dsp_vptr->studio].alienVoiceRoot;
      dspStudio[dsp_vptr->studio].alienVoiceRoot = dsp_vptr;
    }
  }

  dsp_vptr->studio = studio;
}

u32 salAddStudioInput(DSPstudioinfo* stp, SND_STUDIO_INPUT* desc) {
  if (stp->numInputs < 7) {
    stp->in[stp->numInputs].studio = desc->srcStudio;
    stp->in[stp->numInputs].vol = ((u16)desc->vol << 8) | ((u16)desc->vol << 1);
    stp->in[stp->numInputs].volA = ((u16)desc->volA << 8) | ((u16)desc->volA << 1);
    stp->in[stp->numInputs].volB = ((u16)desc->volB << 8) | ((u16)desc->volB << 1);
    stp->in[stp->numInputs].desc = desc;
    ++stp->numInputs;
    return 1;
  }

  return 0;
}

unsigned long salRemoveStudioInput(DSPstudioinfo* stp, SND_STUDIO_INPUT* desc) {
  long i; // r31

  for (i = 0; i < stp->numInputs; ++i) {
    if (stp->in[i].desc == desc) {
      for (; i <= stp->numInputs - 2; ++i) {
        stp->in[i] = stp->in[i + 1];
      }
      --stp->numInputs;
      return 1;
    }
  }

  return 0;
}

void salHandleAuxProcessing() {
  u8 st;             // r29
  long* work;        // r30
  DSPstudioinfo* sp; // r31
  SND_AUX_INFO info; // r1+0x8
  sp = &dspStudio[0];
  for (st = 0; st < salMaxStudioNum; ++st, ++sp) {

    if (sp->state != 1) {
      continue;
    }

    if (sp->auxAHandler != NULL) {
      work = sp->auxA[(salAuxFrame + 2) % 3];
      info.data.bufferUpdate.left = work;
      info.data.bufferUpdate.right = work + 0xa0;
      info.data.bufferUpdate.surround = work + 0x140;
      sp->auxAHandler(0, &info, sp->auxAUser);
      DCFlushRangeNoSync(work, 0x780);
    }

    if (sp->type == 0 && sp->auxBHandler != 0) {
      work = sp->auxB[(salAuxFrame + 2) % 3];
      info.data.bufferUpdate.left = work;
      info.data.bufferUpdate.right = work + 0xa0;
      info.data.bufferUpdate.surround = work + 0x140;
      sp->auxBHandler(0, &info, sp->auxBUser);
      DCFlushRangeNoSync(work, 0x780);
    }
  }
}