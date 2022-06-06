#pragma once
/*
#include "Battery/Core/Exception.h"
//#include "Battery/Core/ApplicationEvents.h"
#include "Battery/Renderer/Bitmap.h"
#include "clip.h"

// Forward declarations for the Windows handle
struct HWND__;
typedef HWND__* HWND;

namespace Battery {

	class Event;

	typedef clip::format ClipboardFormatID;

	enum class ClipboardFormat {
		NONE  = 0,
		TEXT  = 1,
		IMAGE = 2
	};

	class Window {
	public:
		Window(int w, int h);
		~Window();

		void Create(int windowFlags = 0);
		void Destroy();
		void SetEventCallback(std::function<void(Battery::Event* event)> eventCallback);
		void HandleEvents();
		void HandleEvent(Battery::Event* event);

		glm::ivec2 GetScreenPosition();
		void SetScreenPosition(const glm::ivec2& position);
		bool SetWindowSizeConstraints(const glm::ivec2& minimum, const glm::ivec2& maximum);
		void CenterOnPrimaryMonitor();
		int GetWidth();
		int GetHeight();
		glm::ivec2 GetSize();
		void SetSize(const glm::ivec2 size);
		void SetTitle(const std::string title);		// TODO: Get window title
		void Maximize();
		void Minimize();
		void Restore();
		HWND GetSystemHandle();
		bool IsFocused();
		void Focus();
		void Hide();
		void Show();
		void HideFromTaskbar();
		void ShowInTaskbar();
		void SetFrameless(bool frameless);
		void FlipDisplay();

		ClipboardFormatID RegisterClipboardFormat(const std::string& format);
		bool HasClipboardText();
		bool HasClipboardImage();
		bool HasClipboardFormat(ClipboardFormatID format);
		std::pair<std::string, bool> GetClipboardText();
		//std::optional<Battery::Bitmap> GetClipboardImage();
		std::optional<std::vector<uint8_t>> GetClipboardCustomFormat(ClipboardFormatID customFormat);
		std::optional<std::string> GetClipboardCustomFormatString(ClipboardFormatID customFormat);
		bool SetClipboardText(const std::string& text);
		//bool SetClipboardImage(const Battery::Bitmap& image);
		bool SetClipboardCustomFormat(ClipboardFormatID customFormat, void* data, size_t size);
		bool SetClipboardCustomFormatString(ClipboardFormatID customFormat, const std::string& string);

		/// <summary>
		/// This function sets the cursor icon. It must be called for every mouse event.
		/// Parameter is the ALLEGRO_SYSTEM_MOUSE_CURSOR enum
		/// </summary>
		bool SetMouseCursor(int cursorID);

		/// <summary>
		/// Parameter is the ID of an icon, which is embedded in the executable using a .rc resource file.
		/// </summary>
		/// <param name="iconID">- the id of the embedded icon in the executable.</param>
		/// <returns>bool - if loading the icon was successful</returns>
#ifdef _WIN32
		bool SetWindowExecutableIcon(int iconID);
#endif

	private:

		sf::RenderWindow window;

		// These are only for remembering the size until the window is created
		uint32_t width = 0;
		uint32_t height = 0;

		//ParentEventContainer eventContainer;
		std::function<void(Battery::Event* event)> eventCallback = nullptr;
	};

}*/
