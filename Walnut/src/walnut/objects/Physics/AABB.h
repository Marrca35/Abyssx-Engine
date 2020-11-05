#pragma once

namespace walnut {
	class AABB {
	private:
		AABB();
		AABB(const AABB &) = delete;
		AABB(AABB &&) = delete;
	public:

		static bool InstastiateInstance();
		static bool DeleteInstance();

		static const AABB &GetInstance() { return s_currentInstance; }

	private:
		static AABB s_currentInstance;
	};
}
