#include "UUID.h"

#include <random>

namespace Shroom {

    namespace {
        std::random_device RandomDevice;
        std::mt19937_64 Engine(RandomDevice());
        std::uniform_int_distribution<uint64> UniformDistribution;
    }

    UUID::UUID() : _ID(UniformDistribution(Engine)) {}

    UUID::UUID(uint64 uuid) : _ID(uuid) {}

} // namespace Shroom
