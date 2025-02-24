#include "fun.h"

BoundingBox GetBoundingBox(Model model, Vector3 pos) {
    BoundingBox boundingBox = GetMeshBoundingBox(model.meshes[0]);
    Vector3 minBoundary = Vector3Add(pos, boundingBox.min);
    Vector3 maxBoundary = Vector3Add(pos, boundingBox.max);
    return (BoundingBox){minBoundary, maxBoundary};
}
