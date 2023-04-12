#pragma once
#include<vector>
#include<functional>
class Input
{
public:
	inline void RegisterKeyPressed(std::function<void(unsigned char)> keyPressedFunc) { keyPressedFunctions.push_back(keyPressedFunc); }
	inline void RegisterKeyReleased(std::function<void(unsigned char)> keyReleasedFunc) { keyReleasedFunctions.push_back(keyReleasedFunc); }
	inline void RegisterMouseMove(std::function<void(int x, int y)> mouseMoveFunc) { mouseMoveFunctions.push_back(mouseMoveFunc); }
	inline void RegisterMouseEnter(std::function<void()> mouseEnterFunc) { mouseEnterFunctions.push_back(mouseEnterFunc); }
	inline void RegisterMouseLeave(std::function<void()> mouseLeaveFunc) { mouseLeaveFunctions.push_back(mouseLeaveFunc); }
	inline void RegisterLeftPressed(std::function<void(int x, int y)> leftPressedFunc) { leftPressedFunctions.push_back(leftPressedFunc); }
	inline void RegisterRightPressed(std::function<void(int x, int y)> rightPressedFunc) { rightPressedFunctions.push_back(rightPressedFunc); }
	inline void RegisterLeftReleased(std::function<void(int x, int y)> leftReleasedFunc) { leftReleasedFunctions.push_back(leftReleasedFunc); }
	inline void RegisterRightReleased(std::function<void(int x, int y)> rightReleasedFunc) { rightReleasedFunctions.push_back(rightReleasedFunc); }
	inline void RegisterWheelDelta(std::function<void(int x, int y, int delta)> wheelDeltaFunc) { wheelDeltaFunctions.push_back(wheelDeltaFunc); }
	inline void RegisterKillFocus(std::function<void()> killFocusFunc) { killFocusFunctions.push_back(killFocusFunc); }
	
	inline void OnKeyPressed(unsigned char key) { for (const auto& func : keyPressedFunctions)func(key); }
	inline void OnKeyReleased(unsigned char key) { for (const auto& func : keyReleasedFunctions)func(key); }
	inline void OnMouseMove(int x, int y) { for (const auto& func : mouseMoveFunctions)func(x, y); }
	inline void OnMouseEnter() { for (const auto& func : mouseEnterFunctions)func(); }
	inline void OnMouseLeave() { for (const auto& func : mouseLeaveFunctions)func(); }
	inline void OnLeftPressed(int x, int y) { for (const auto& func : leftPressedFunctions)func(x, y); }
	inline void OnRightPressed(int x, int y) { for (const auto& func : rightPressedFunctions)func(x, y); }
	inline void OnLeftReleased(int x, int y) { for (const auto& func : leftReleasedFunctions)func(x, y); }
	inline void OnRightReleased(int x, int y) { for (const auto& func : rightReleasedFunctions)func(x, y); }
	inline void OnWheelDelta(int x, int y, int delta) { for (const auto& func : wheelDeltaFunctions)func(x, y, delta); }
	inline void OnKillFocus() { for (const auto& func : killFocusFunctions)func(); }
private:
	std::vector<std::function<void(unsigned char)>> keyPressedFunctions;
	std::vector<std::function<void(unsigned char)>> keyReleasedFunctions;
	std::vector<std::function<void(int x, int y)>> mouseMoveFunctions;
	std::vector<std::function<void()>> mouseEnterFunctions;
	std::vector<std::function<void()>> mouseLeaveFunctions;
	std::vector<std::function<void(int x, int y)>> leftPressedFunctions;
	std::vector<std::function<void(int x, int y)>> rightPressedFunctions;
	std::vector<std::function<void(int x, int y)>> leftReleasedFunctions;
	std::vector<std::function<void(int x, int y)>> rightReleasedFunctions;
	std::vector<std::function<void(int x, int y, int delta)>> wheelDeltaFunctions;
	std::vector<std::function<void()>> killFocusFunctions;
};

