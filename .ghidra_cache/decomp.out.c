=== FUN_80658650 @ 0x80658650 size=436 ===

/* WARNING: Variable defined which should be unmapped: local_20 */
/* WARNING: Unable to use type for symbol unkStrPtr */

void FUN_80658650(void)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int ballStruct;
  int iVar4;
  int ball;
  int unVec;
  int iVar5;
  int local_20;
  Vec3f unkVec;
  cameraStruct *unkStrPtr;
  
  unkStrPtr = camera;
  fVar2 = c_0_85;
  ball = (int)&inMemBall;
  unkVec.Z = const_0_0;
  unVec = (int)&unkVec;
  iVar4 = 0;
  unkVec.Y = const_0_0;
  unkVec.X = const_0_0;
  do {
    iVar5 = 5;
    ballStruct = ball;
    do {
      if ((iVar4 != 1) || (c_1_0 <= *(float *)(ballStruct + 0x3c))) {
        *(float *)unVec = *(float *)unVec + *(float *)(ballStruct + 0x3c);
      }
      else {
        *(float *)unVec = *(float *)unVec + c_1_0;
      }
      if ((iVar4 != 1) || (c_1_0 <= *(float *)(ballStruct + 0x48))) {
        *(float *)unVec = *(float *)unVec + *(float *)(ballStruct + 0x48);
      }
      else {
        *(float *)unVec = *(float *)unVec + c_1_0;
      }
      ballStruct = ballStruct + 0x18;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar4 = iVar4 + 1;
    ball = ball + 4;
    *(float *)unVec = *(float *)unVec * const_0_1;
    unVec = unVec + 4;
  } while (iVar4 < 3);
  camera->field70_0xfc = unkVec.X;
  unkStrPtr->field71_0x100 = fVar2 * unkVec.Y;
  unkStrPtr->field72_0x104 = unkVec.Z;
  sVar1._0_1_ = camera->field91_0x11a;
  sVar1._1_1_ = camera->field92_0x11b;
  if (sVar1 == 1) {
    unkStrPtr->field67_0xf0 = unkStrPtr->field70_0xfc;
    unkStrPtr->field68_0xf4 = unkStrPtr->field71_0x100;
    unkStrPtr->field69_0xf8 = unkStrPtr->field72_0x104;
  }
  else {
    fVar2 = const_0_2 * (unkStrPtr->field71_0x100 - unkStrPtr->field68_0xf4);
    fVar3 = const_0_2 * (unkStrPtr->field72_0x104 - unkStrPtr->field69_0xf8);
    unkStrPtr->field67_0xf0 =
         unkStrPtr->field67_0xf0 + const_0_2 * (unkStrPtr->field70_0xfc - unkStrPtr->field67_0xf0);
    unkStrPtr->field68_0xf4 = unkStrPtr->field68_0xf4 + fVar2;
    unkStrPtr->field69_0xf8 = unkStrPtr->field69_0xf8 + fVar3;
  }
  return;
}


