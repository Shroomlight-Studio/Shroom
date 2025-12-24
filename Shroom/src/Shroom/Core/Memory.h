#pragma once

// TODO: make our own memory system
#include <memory>

namespace Shroom {

	template<typename T>
	using Owned = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr Owned<T> Own(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Shared<T> Share(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

} // namespace Shroom
