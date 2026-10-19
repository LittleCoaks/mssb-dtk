
#include "musyx/musyx_priv.h"

void vsInit() {
  u32 i;
  vs.numBuffers = 0;
  for (i = 0; i < 64; i++) {
    vs.voices[i] = 0xFF;
  }

  vs.nextInstID = 0;
  vs.callback = NULL;
}

static inline void vsFreeBuffer(u8 bufferIndex) {
  vs.streamBuffer[bufferIndex].state = 0;
  vs.voices[vs.streamBuffer[bufferIndex].voice] = 0xFF;
}

u32 vsSampleStartNotify(u32 voice) {
  u8 i;
  u8 sb;
  u16 instID;
  u32 addr;

  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state != 0 && vs.streamBuffer[i].voice == (u8)voice) {
      vsFreeBuffer(i);
    }
  }

  sb = 0xFF;
  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state == 0) {
      vs.streamBuffer[i].state = 1;
      vs.streamBuffer[i].last = 0;
      sb = i;
      break;
    }
  }

  vs.voices[(u8)voice] = sb;
  if (sb != 0xFF) {
    addr = aramGetStreamBufferAddress(vs.voices[(u8)voice], 0);
    hwSetVirtualSampleLoopBuffer(voice, (void*)addr, vs.bufferLength);
    vs.streamBuffer[sb].info.smpID = hwGetSampleID(voice);
    do {
      instID = vs.nextInstID++;
      for (i = 0; i < vs.numBuffers; ++i) {
        if (vs.streamBuffer[i].state != 0 && vs.streamBuffer[i].info.instID == instID) {
          break;
        }
      }
    } while (i != vs.numBuffers);
    vs.streamBuffer[sb].info.instID = instID;
    vs.streamBuffer[sb].info.data.start.publicID = vidGetPublicId(voice);
    if (vs.streamBuffer[sb].info.data.start.publicID != 0xFFFFFFFF) {
      vs.streamBuffer[sb].info.data.start.seqInstances =
          seqGetInstancesForVoice(vs.streamBuffer[sb].info.data.start.publicID);
    } else {
      vs.streamBuffer[sb].info.data.start.seqInstances = -1;
    }
    vs.streamBuffer[sb].info.data.start.extraData = hwGetSampleExtraData(voice);
    vs.streamBuffer[sb].smpType = hwGetSampleType(voice);
    vs.streamBuffer[sb].voice = (u8)voice;
    if (vs.callback != NULL && vs.callback(0, &vs.streamBuffer[sb].info) == 0) {
      return (vs.streamBuffer[sb].info.instID << 8) | (u8)voice;
    }
    hwSetVirtualSampleLoopBuffer(voice, 0, 0);
    vsFreeBuffer(sb);
  } else {
    hwSetVirtualSampleLoopBuffer(voice, 0, 0);
  }

  return 0xFFFFFFFF;
}

void vsSampleEndNotify(unsigned long pubID) {
  u8 sb;
  u8 voice;

  if (pubID != 0xFFFFFFFF) {
    u8 id = (u8)pubID;
    sb = vs.voices[id];
    if (sb != 0xFF) {
      if (vs.streamBuffer[sb].info.instID == ((pubID >> 8) & 0xFFFF)) {
        if (vs.callback != NULL) {
          vs.callback(2, &vs.streamBuffer[sb].info);
        }
        vsFreeBuffer(sb);
      }
    }
  }
}

void vsUpdateBuffer(struct VS_BUFFER* sb, unsigned long cpos) {
  u32 len;
  u32 off;

  if (sb->last == cpos) {
    return;
  }
  if ((s32)sb->last < cpos) {
    switch (sb->smpType) {
    case 5:
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = cpos - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    case 6:
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = cpos - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    default:
      break;
    }
  } else if (cpos == 0) {
    switch (sb->smpType) {
    case 5:
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    case 6:
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    default:
      break;
    }
  } else {
    switch (sb->smpType) {
    case 5:
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = cpos;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    case 6:
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = cpos;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        off = sb->last + len;
        sb->last = off % vs.bufferLength;
      }
      break;
    default:
      break;
    }
  }
}

void vsSampleUpdates() {
  u32 i;
  u32 cpos;
  u32 realCPos;
  VS_BUFFER* sb;
  u32 nextSamples;

  if (vs.callback == NULL) {
    return;
  }

  for (i = 0; i < 64; ++i) {
    if (vs.voices[i] != 0xFF && hwGetVirtualSampleState(i) != 0) {
      sb = &vs.streamBuffer[vs.voices[i]];
      realCPos = hwGetPos(i);
      cpos = sb->smpType == 5 ? (realCPos / 14) * 14 : realCPos;

      switch (sb->state) {
      case 1:
        vsUpdateBuffer(sb, cpos);
        break;
      case 2:
      case 3:
        if (((sb->info.instID << 8) | sb->voice) == hwGetVirtualSampleID(sb->voice)) {
          vsUpdateBuffer(sb, cpos);

          if (realCPos >= sb->finalLast) {
            sb->finalGoodSamples -= (realCPos - sb->finalLast);
          } else {
            sb->finalGoodSamples -= (vs.bufferLength - (sb->finalLast - realCPos));
          }

          sb->finalLast = realCPos;
          nextSamples = (synthVoice[sb->voice].curPitch * 160 + 0xFFF) / 4096;
          if ((s32)nextSamples > (s32)sb->finalGoodSamples) {
            if (!hwVoiceInStartup(sb->voice)) {
#if MUSY_VERSION >= MUSY_VERSION_CHECK(1, 5, 4)
              if (sb->state == 2) {
                hwBreak(sb->voice);
                macSampleEndNotify(&synthVoice[sb->voice]);
              } else {
                voiceKill(sb->voice);
              }
#else
              hwBreak(sb->voice);
#endif
            }

            sb->state = 0;
            vs.voices[sb->voice] = 0xff;
          }
        } else {
          sb->state = 0;
          vs.voices[sb->voice] = 0xff;
        }
        break;
      }
    }
  }
}

unsigned long sndVirtualSampleAllocateBuffers(unsigned char numInstances,
                                              unsigned long numSamples) {
  long i;
  unsigned long len;

  hwDisableIrq();
  vs.numBuffers = numInstances;
  len = sndStreamAllocLength(numSamples, 1);
  vs.bufferLength = (len / 8) * 14;

  for (i = 0; i < vs.numBuffers; ++i) {
    if ((vs.streamBuffer[i].hwId = aramAllocateStreamBuffer(len)) == 0xFF) {
      break;
    }
    vs.streamBuffer[i].state = 0;
    vs.voices[vs.streamBuffer[i].voice] = 0xFF;
  }

  if (i >= vs.numBuffers) {
    hwEnableIrq();
    return 1;
  }

  while ((i - 1) > 0) {
    aramFreeStreamBuffer(vs.streamBuffer[i - 1].hwId);
    --i;
  }

  hwEnableIrq();
  return 0;
}

s32 sndVirtualSampleFreeBuffers() {
  u8 i;

  for (i = 0; i < vs.numBuffers; ++i) {
    aramFreeStreamBuffer(vs.streamBuffer[i].hwId);
  }

  vs.numBuffers = 0;
}

void sndVirtualSampleSetCallback(unsigned long (*callback)(unsigned char,
                                                           struct SND_VIRTUALSAMPLE_INFO *))
{
  vs.callback = callback;
}

void vsARAMDMACallback(unsigned long user) {
  if (vs.callback == NULL) {
    return;
  }

  vs.callback(3, &((VS_BUFFER*)user)->info);
}

void sndVirtualSampleARAMUpdate(unsigned short instID, void* base, unsigned long off1,
                                unsigned long len1, unsigned long off2, unsigned long len2) {
  u8 i;

  hwDisableIrq();

  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state == 0 || vs.streamBuffer[i].info.instID != instID) {
      continue;
    }
    if ((s32)vs.streamBuffer[i].smpType != 5) {
      i = i;
    } else {
      off1 = (off1 / 14) * 8;
      len1 = ((len1 + 13) / 14) * 8;
      off2 = (off2 / 14) * 8;
      len2 = ((len2 + 13) / 14) * 8;
    }

    if (len1 != 0) {
      hwFlushStream(base, off1, len1, vs.streamBuffer[i].hwId, vsARAMDMACallback,
                    (u32)&vs.streamBuffer[i]);
    }
    if (len2 != 0) {
      hwFlushStream(base, off2, len2, vs.streamBuffer[i].hwId, vsARAMDMACallback,
                    (u32)&vs.streamBuffer[i]);
    }

    if (vs.streamBuffer[i].smpType == 5) {
      hwSetStreamLoopPS(vs.streamBuffer[i].voice, *(u32*)(OSCachedToUncached(base)) >> 24);
    }
    break;
  }

  hwEnableIrq();
}

void sndVirtualSampleEndPlayback(unsigned short instID) {
  u8 i;
  VS_BUFFER* stream;
  u32 cpos;

  hwDisableIrq();

  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state == 0 || vs.streamBuffer[i].info.instID != instID) {
      continue;
    }

    stream = &vs.streamBuffer[i];
    cpos = hwGetPos(i);

    if (stream->last < cpos) {
      stream->finalGoodSamples = vs.bufferLength - (cpos - stream->last);
    } else {
      stream->finalGoodSamples = stream->last - cpos;
    }

    stream->finalLast = cpos;
    stream->state = 2;
    break;
  }
  hwEnableIrq();
}