﻿#pragma once
#include <Siv3D.hpp>
#include "Wiimote.hpp"
#include <chrono>

enum class Threshould : int
{
	Weak = 220,
	Normal = 400,
	Strong = 700
};

namespace wm4s3d
{
	class Button
	{
	public:
		Button();
		bool pressed;
		bool clicked;
		bool released;
		int32 pressedDuration;
		std::chrono::time_point<std::chrono::system_clock> pressedStart;
	};
}

class Wii
{
private:
	enum class ButtonType
	{
		A, B, One, Two, Plus, Minus, Home, Up, Down, Left, Right, C, Z
	};

	std::unordered_map<ButtonType, bool> m_pressed;
	std::unordered_map<ButtonType, wm4s3d::Button*> m_buttons;

	bool m_connected;

	Optional<Vec3> m_prevAcc;
	Stopwatch m_shakeWait;
	bool m_isShaked;
	int m_shakeThreshould;

public:
	Wiimote controller;

	Wii();
	~Wii();

	/// <summary>
	/// Wiiリモコンのボタン情報などを更新します (ループ毎に呼び出す)
	/// </summary>
	void update();

	/// <summary>
	/// Wiiリモコンが接続されているかどうか
	/// </summary>
	bool isConnected()
	{
		return controller.isConnected();
	}

	/// <summary>
	/// Wiiリモコンが接続された時はtrue、それ以外はfalseを返します。
	/// </summary>
	bool hasConnected()
	{
		if (!m_connected && isConnected())
		{
			m_connected = true;
			return true;
		}

		return false;
	}

	/// <summary>
	/// Wiiリモコンを振動させます
	/// </summary>
	/// <param name="ms">振動させる時間 (ミリ秒)</param>
	void rumble(int ms)
	{
		controller.rumbleForMiliseconds(ms);
	}

	/// <summary>
	/// Wiiリモコンを振動させます
	/// </summary>
	/// <param name="on">振動</param>
	void rumble(bool on)
	{
		controller.setRumble(on);
	}

	/// <summary>
	/// WiiリモコンのLEDを点灯/消灯させます
	/// </summary>
	/// <param name="one">左から1番目のLED</param>
	/// <param name="two">左から2番目のLED</param>
	/// <param name="three">左から3番目のLED</param>
	/// <param name="four">左から4番目のLED</param>
	void setLED(bool one, bool two, bool three, bool four)
	{
		controller.setLED(one, two, three, four);
	}

	/// <summary>
	/// WiiリモコンのLEDを点灯/消灯させます
	/// </summary>
	/// <param name="led">4桁でLEDの状態 (消灯:0, 点灯:1)</param>
	void setLED(const char* _led)
	{
		const String led = WidenAscii(_led);
		if (led.length > 4 || led.length == 0) return;

		controller.setLED(
			led[0] != '0',
			led[1] != '0',
			led[2] != '0',
			led[3] != '0'
		);
	}

	/// <summary>
	/// WiiリモコンのLEDを点灯/消灯させます
	/// </summary>
	/// <param name="num">LED番号 (0-3)</param>
	/// <param name="on">LEDのON/OFF</param>
	void setLED(int num, bool on)
	{
		bool one	= num == 0 ? on : getLED(0),
			 two	= num == 1 ? on : getLED(1),
			 three	= num == 2 ? on : getLED(2),
			 four	= num == 3 ? on : getLED(3);

		controller.setLED(one, two, three, four);
	}

	/// <summary>
	/// WiiリモコンのLEDの状態を返します
	/// </summary>
	/// <param name="num">LED番号 (0-3)</param>
	bool getLED(int num)
	{
		switch (num)
		{
		case 0: return controller.LEDs.LED1;
		case 1: return controller.LEDs.LED2;
		case 2: return controller.LEDs.LED3;
		case 3: return controller.LEDs.LED4;
		default: return false;
		}
	}

	/// <summary>
	/// Wiiリモコンの加速度を取得します
	/// </summary>
	Vec3 acc()
	{
		return Vec3(controller.acc.x, controller.acc.y, controller.acc.z);
	}

	/// <summary>
	/// 振られたことを検知する際のしきい値を設定します
	/// </summary>
	void setShakeThreshould(int thd)
	{
		m_shakeThreshould = thd;
	}

	/// <summary>
	/// 振られたことを検知する際のしきい値を設定します
	/// </summary>
	void setShakeThreshould(Threshould thd)
	{
		setShakeThreshould((int)thd);
	}

	/// <summary>
	/// Wiiリモコンが振られたかどうか
	/// </summary>
	bool isShaked()
	{
		return m_isShaked;
	}

	/// <summary>
	/// ヌンチャクが使えるかどうか
	/// </summary>
	bool isNunchukConnected()
	{
		return controller.extensionType == Wiimote::ExtensionType::Nunchuk;
	}

	/// <summary>
	/// ウィンドウ上でのポインターの位置を計算して返します
	/// </summary>
	Point getPointerInWindow();

	/// <summary>
	/// ウィンドウ上でのポインターの位置を計算して返します
	/// </summary>
	/// <param name="shift">trueなら座標を2倍してWindow::Size()の半分並行移動させた座標を返します</param>
	Point getPointerInWindow(bool shift);

	/// <summary>
	/// ウィンドウ上でのジョイスティックの位置を計算して返します
	/// </summary>
	Point getJoystickInWindow();

	/// <summary>
	/// いずれかのボタンが押されたかどうか
	/// </summary>
	bool AnyKeyClicked();

	/// <summary>
	/// ボタン
	/// </summary>
	wm4s3d::Button buttonA;
	wm4s3d::Button buttonB;
	wm4s3d::Button buttonOne;
	wm4s3d::Button buttonTwo;
	wm4s3d::Button buttonPlus;
	wm4s3d::Button buttonMinus;
	wm4s3d::Button buttonHome;
	wm4s3d::Button buttonUp;
	wm4s3d::Button buttonDown;
	wm4s3d::Button buttonLeft;
	wm4s3d::Button buttonRight;
	wm4s3d::Button nunchukC;
	wm4s3d::Button nunchukZ;

	/// <summary>
	/// ポインターの位置 (要センサーバー)
	/// </summary>
	Vec2 pointer;

	/// <summary>
	///ヌンチャクのジョイスティック (要ヌンチャク)
	/// </summary>
	Vec2 joystick;

};
