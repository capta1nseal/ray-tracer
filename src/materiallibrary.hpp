#ifndef _RAYTRACERMATERIALLIBRARY_
#define _RAYTRACERMATERIALLIBRARY_


#include <vector>
#include <memory>

#include "material.hpp"


class MaterialLibrary{
public:
    MaterialLibrary();
    ~MaterialLibrary();

    const std::shared_ptr<Material>& addMaterial(Material material);

private:
    std::vector<std::shared_ptr<Material>> materialVector;

};


#endif
