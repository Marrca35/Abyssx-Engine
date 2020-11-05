#pragma once

namespace walnut {
	struct KeyEvent {
		int key;
		int scancode;
		int mods;
	};

	class KeyEventListener {
	public:
		virtual ~KeyEventListener() { }

		virtual void OnKeyPressed(KeyEvent e) = 0;
		virtual void OnKeyReleased(KeyEvent e) = 0;
	private:
		KeyEventListener() = delete;
		KeyEventListener(const KeyEventListener &) = delete;
		KeyEventListener(KeyEventListener &&) = delete;
		void operator=(KeyEventListener const &) = delete;
	};
}