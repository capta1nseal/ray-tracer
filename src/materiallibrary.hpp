#ifndef _RAYTRACERMATERIALLIBRARY_
#define _RAYTRACERMATERIALLIBRARY_

#include <memory>
#include <vector>

#include "material.hpp"

class MaterialLibrary {
public:
    MaterialLibrary();
    ~MaterialLibrary();

    const std::shared_ptr<Material> &addMaterial(Material material);

private:
    std::vector<std::shared_ptr<Material>> materialVector;
};

#endif
