#include "Unknown/File_0x800bea04.h"
#include "Unknown/File_0x800bf038.h"

void setVectors(Vec v) {
    drawShadows.bounds[0][0] = drawShadows.bounds[0][0] <= v.x ? drawShadows.bounds[0][0] : v.x;
    drawShadows.bounds[0][1] = drawShadows.bounds[0][1] >= v.x ? drawShadows.bounds[0][1] : v.x;
    drawShadows.bounds[1][0] = drawShadows.bounds[1][0] <= v.y ? drawShadows.bounds[1][0] : v.y;
    drawShadows.bounds[1][1] = drawShadows.bounds[1][1] >= v.y ? drawShadows.bounds[1][1] : v.y;
    drawShadows.bounds[2][0] = drawShadows.bounds[2][0] <= v.z ? drawShadows.bounds[2][0] : v.z;
    drawShadows.bounds[2][1] = drawShadows.bounds[2][1] >= v.z ? drawShadows.bounds[2][1] : v.z;
    PSVECAdd(&drawShadows.pointSum, &v, &drawShadows.pointSum);
    drawShadows.pointCount++;
}
