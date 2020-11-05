#pragma once

namespace walnut {
	class Application {
	public:
		virtual ~Application() { }


	private:
		Application() = delete;
		Application(const Application &) = delete;
		Application(Application &&) = delete;
	};
}


