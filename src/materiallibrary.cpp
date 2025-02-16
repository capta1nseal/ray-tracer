#include "materiallibrary.hpp"


#include <vector>

#include "material.hpp"


MaterialLibrary::MaterialLibrary() {
}
MaterialLibrary::~MaterialLibrary() {
}

// Add a material to the library and return a reference to it.
// Don't lose your references!
const std::shared_ptr<Material>& MaterialLibrary::addMaterial(Material material) {
    materialVector.push_back(std::make_shared<Material>(material));
    return *(materialVector.rbegin());
}
