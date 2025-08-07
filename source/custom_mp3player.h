#ifndef __MP3PLAYER_H__
#define __MP3PLAYER_H__

#include <mad.h>
#include <gctypes.h>

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

void MP3Player_Init(void);
void MP3Player_Stop(void);
void MP3Player_Reset(void);
bool MP3Player_IsPlaying(void);
void MP3Player_Volume(u32 volume);
s32 MP3Player_PlayBuffer(const void *buffer,s32 len,bool (*filterfunc)(struct mad_stream *,struct mad_frame *));
s32 MP3Player_PlayFile(void *cb_data,s32 (*reader)(void *,void *,s32),bool (*filterfunc)(struct mad_stream *,struct mad_frame *));
float MP3Player_GetAmplitude(void);
void MP3Player_SetSeconds(float seconds);
bool seek_filter(struct mad_stream *stream, struct mad_frame *frame);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif
