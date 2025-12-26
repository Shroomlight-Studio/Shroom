#pragma once

#include "Shroom/Core/Types.h"

namespace Shroom {

    class UUID {
    public:
        UUID();
        UUID(uint64 uuid);
        UUID(UUID&) = default;

        bool operator==(const UUID& o) const { return _ID == o._ID; }
        bool operator!=(const UUID& o) const { return _ID != o._ID; }

        operator uint64() const { return _ID; }

    private:
        uint64 _ID;
    };

} // namespace Shroom

namespace std {

    template<>
    struct hash<Shroom::UUID> {
        std::size_t operator()(const Shroom::UUID& uuid) const {
            return (uint64)uuid;
        }
    };

} // namespace std
